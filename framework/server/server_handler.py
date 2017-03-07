import os
import csv

import threading

import paho.mqtt.client as paho

from appStruct import appStruct

from doe import doe
from rsm import rsm


####################################################################################################
# doeThread
####################################################################################################

class doeThread( threading.Thread ):
    def __init__( self, threadID, name, cond, struct ):
        threading.Thread.__init__( self )
        
        self.threadID = threadID
        self.name = name
        
        self.appStruct = struct
        
        self.cond = cond   
        
        self.doe = doe( struct )
        
    def run( self ):
        print( "\nstarting " + self.name + " thread" )
        
        with self.cond:
            self.cond.wait()
            
            configurations = self.doe.buildDoe()
            
            self.appStruct.setDoeConfs( configurations )
            self.appStruct.setDoeConfsNumber( len( self.appStruct.getDoeConfs() ) )
                    
            self.appStruct.setStatus( "dse" )
        
        self.appStruct.showStruct()
        
        print( "\nexiting " + self.name + " thread" )


####################################################################################################
# rsmThread
####################################################################################################
    
class rsmThread( threading.Thread ):
    def __init__( self, threadID, name, cond, struct ):
        threading.Thread.__init__( self )
        
        self.threadID = threadID
        self.name = name
        
        self.cond = cond
        
        self.appStruct = struct
        
        self.rsm = rsm( struct )
        
    def run( self ):
        print( "\nstarting " + self.name + " thread" )
        
        with self.cond:
            self.cond.wait()
            
            self.appStruct.setStatus( "buildingTheModel" )
            
            model = self.rsm.buildRsm()
            self.appStruct.setModel( model )
            
            self.appStruct.setStatus( "autotuning" )
            
            self.appStruct.showStruct()
        
        print( "\nexiting " + self.name + " thread" )


####################################################################################################
# server_handler
####################################################################################################

class server_handler():

    def __init__(self):
        '''
        constructor
        '''
        self.address = "127.0.0.1"
        self.clientID = "server_handler"
        self.qos = 0
        
        self.root = "/home/cris/Documents/"
        self.tesiCris = "tesiCris/"
        
        self.newHostpidTopic = None
        self.clientsReqTopic = None
        self.communicationTopic = None
        self.receiveInfoTopic = None
        self.OPsTopic = None
        self.doneConfTopic = None
        self.disconnectionTopic = None
        
        self.struct = None
        self.doe = None
        
        self.client = None
        
        self.thread_doe = None
        self.thread_rsm = None
        
        self.lock = threading.Lock()
        
        self.doeCond = None
        self.rsmCond = None
    
    
    ####################################################################################################
    # MQTT
    ####################################################################################################
    
    def on_connect(self, host):
        print("\nclient ID: " + self.client._client_id + " connected at " + host + ":8883")
    
    def on_subscribe(self, topic):
            print ("\nsubscription")
            print ("topic: " + topic)
     
    def on_message(self, client, userdata, msg):
        print ("\nreceived message")
        print ("topic: " + msg.topic)
        print ("payload: " + msg.payload)
        
        if( msg.topic == self.newHostpidTopic ):
            # new client (hostpid) arrived
            #self.lock.acquire()
            
            self.manageNewHostpid(msg.payload)
            
            #self.lock.release()
        
        elif( msg.topic == self.clientsReqTopic ):
            # a client (hostpid) made a request
            #self.lock.acquire()         
            
            if( self.struct.getStatus() == "dse" ):
                # se ci sono configurazioni da eseguire    
                self.sendConfiguration(msg.payload)

            if( self.struct.getStatus() == "buildingTheModel" ):
                # se il modello non e' ancora pronto    
                self.sendDoEsModel(msg.payload)
            
            elif( self.struct.getStatus() == "autotuning" ):
                # esiste il modello completo
                self.sendModel(msg.payload)
            
            #self.lock.release()

        elif( msg.topic == self.receiveInfoTopic ):
            # received app info
            #self.lock.acquire()
            
            if( self.struct.getStatus() != "receivingInfo" ):
                self.struct.setStatus("receivingInfo")  
            
            with self.doeCond:
                splitted = msg.payload.split(" ")
                
                if( splitted[0] == "metric" ):
                    self.struct.addMetric( splitted[1] )
                    
                elif( splitted[0] == "param" ):
                    self.struct.addParam( splitted[1] )
                    
                    values = []
                    
                    if( splitted[2] == "range" ):
                        value = float( splitted[3] )
                        MAXvalue = float( splitted[4] )
                        step = float( splitted[5] )
                     
                        while(value <= MAXvalue):
                            values.append(value)
                            value += step
                        
                        self.struct.addParamValues(values)
                    
                    elif( splitted[2] == "enum" ):
                        for i in range(3, len(splitted) ):
                            values.append( float(splitted[i]) )
                        
                        self.struct.addParamValues(values)
                         
                elif( splitted[0] == "doe" ):
                    self.struct.setDoeKind( splitted[1] )
                
                elif( splitted[0] == "numOPs" ):
                    self.struct.setNumOPs( int( splitted[1] ) )
                    
                elif( splitted[0] == "rsm" ):
                    self.struct.setRsmKind( splitted[1] )
                
                elif( splitted[0] == "sparkGenLinearRegrTransforms" ):
                    self.struct.addMetricToSparkGenLinearRegrTransforms( splitted[1] )
                    
                    self.struct.addMetricInfoToSparkGenLinearRegrTransforms( splitted[1], splitted[2] )
                    self.struct.addMetricInfoToSparkGenLinearRegrTransforms( splitted[1], splitted[3] )
                    self.struct.addMetricInfoToSparkGenLinearRegrTransforms( splitted[1], splitted[4] )
                    self.struct.addMetricInfoToSparkGenLinearRegrTransforms( splitted[1], splitted[5] )
                
                elif( splitted[0] == "done" ):
                    self.struct.setStatus("buildingDoe")
                    
                    # notify the thread that computes the doeThread configurations
                    self.doeCond.notifyAll()
            
            #self.lock.release()
        
        elif( msg.topic == self.OPsTopic ):
            # msg.payload es.: "1 100000:5.3454867 0.2343545"
            
            #self.lock.acquire()
            
            splitted = msg.payload.split(":")
            # splitted[0]: configuration
            # splitted[1]: metrics
            
            configuration = []
            
            splittedConf = splitted[0].split(" ")
            for value in splittedConf:
                configuration.append( float(value) )
            
            newOP = False
            
            for conf in self.struct.getDoeConfs():
                if( conf.getConf() == configuration ):
                    # if the configuration is not one of the done configurations
                    newOP = True
                    
                    self.struct.addOP(msg.payload)
                    
                    conf.decrementNumOPs()
                    
                    if( conf.getNumOPs() == 0 ):
                        # if I have the right number of ops for this configuration
                        self.struct.addConfToDoneConfs(conf)
                                                
                        self.struct.removeConfToDoeConfs( conf )
                        
                        self.struct.showStruct()
                        
                        self.checkStartRsm()
            
            if( newOP == False ):
                self.struct.addOtherOP(msg.payload)
            
            #self.lock.release()
        
        elif( msg.topic == self.disconnectionTopic ):
            # a client (hostpid) has disconnected
            #self.lock.acquire()
            
            self.struct.removeHostpid(msg.payload)
            
            #self.lock.release()
                
    def connect(self, host):
        self.client.connect(host, port = 8883)
        self.client.on_connect = self.on_connect(host)
        
    def subscribe(self, topic):
        self.client.subscribe(topic, qos = self.qos)
        self.client.on_subscribe = self.on_subscribe(topic)
        self.client.on_message = self.on_message
    
    def on_publish(self, topic, message):
        print ("\npublication")
        print ("topic: " + topic)
        print ("message: " + message)
        
    def publish(self, topic, message):
        self.client.on_publish = self.on_publish(topic, message)
        self.client.publish(topic, message, qos = self.qos)
    
    ####################################################################################################
    ####################################################################################################
    
        
    def start(self, appName, hostpid):
        self.struct = appStruct(appName)
        
        self.manageNewHostpid(hostpid)
        
        self.client = paho.Client(client_id = self.clientID + "_" + self.struct.getName())
        self.connect(self.address)
        
        self.firstSubscriptions()
        
        if( os.path.exists(self.root + self.tesiCris + self.struct.getName() + "/model.txt") == True ):
            self.loadModel()
            
            self.struct.setStatus("autotuning")
        
        else:
            self.secondSubscriptions()
            
            self.threadsCreation()
            
            self.requestAppInfo()
        
        self.client.loop_forever()
    
    def manageNewHostpid(self, hostpid):
        self.struct.addHostpid(hostpid)
        
        if( self.struct.getStatus() == "dse"):
            self.sendConfiguration(hostpid)
    
    def firstSubscriptions(self):
        self.newHostpidTopic = self.tesiCris + self.struct.getName() + "/newHostpid"
        self.subscribe(self.newHostpidTopic)
        
        self.clientsReqTopic = self.tesiCris + self.struct.getName() + "/req"
        self.subscribe(self.clientsReqTopic)
        
        self.disconnectionTopic = self.tesiCris + self.struct.getName() + "/disconnection"
        self.subscribe(self.disconnectionTopic)
        
    def secondSubscriptions(self):
        self.receiveInfoTopic = self.tesiCris + self.struct.getName() + "/info"
        self.subscribe(self.receiveInfoTopic)
        
        self.OPsTopic = self.tesiCris + self.struct.getName() + "/OPs"
        self.subscribe(self.OPsTopic)
        
        self.doneConfTopic = self.tesiCris + self.struct.getName() + "/doneConf"
        self.subscribe(self.doneConfTopic)
        
    def threadsCreation(self):
        self.doeCond = threading.Condition()
        self.rsmCond = threading.Condition()
         
        self.thread_doe = doeThread(1, self.struct.getName() + "_doe", self.doeCond, self.struct)
        self.thread_rsm = rsmThread(2, self.struct.getName() + "_rsm", self.rsmCond, self.struct)
         
        # Start new Threads
        self.thread_doe.start()
        self.thread_rsm.start()
        
    def requestAppInfo(self):
        if( self.communicationTopic == None ):
            self.communicationTopic = self.tesiCris + self.struct.getName()
        self.publish(self.communicationTopic, "info")
    
    def sendConfiguration(self, hostpid):
        if len( self.struct.getDoeConfs() ) > 0:
            #self.struct.restoreConfs(hostpid, False)
            
            configuration = self.struct.getDoeConfs().pop(0)
            self.struct.addDoeConf(configuration)
            
            confStr = ""
            for value in configuration.getConf():
                confStr += str(value) + " "
         
            # elimino ultimo carattere (spazio vuoto)
            confStr = confStr[:-1]
            # configurationStr finale es.: "4.0 500000.0"

            # invio la configurazione
            # topic es.: tesiCris/swaptions/crisXPS15_1897/configuration
            # payload es.: "1 400000"
            self.publish( self.tesiCris + self.struct.getName() + "/" + hostpid + "/conf", confStr )
        
    def checkStartRsm(self):
        with self.rsmCond:
            if( len(self.struct.getDoneConfs()) == self.struct.getDoeConfsNumber() ):
                # partial model with only DoEs configurations
                self.buildDoEsModel()

                # notify the thread that computes the model through Spark
                self.rsmCond.notifyAll()
    
    def sendModel(self, hostpid):
        for op in self.struct.getModel():
            op = op.replace(":", " ")
            
            self.publish( self.tesiCris + self.struct.getName() + "/" + hostpid + "/model", op )
        
        self.publish( self.tesiCris + self.struct.getName() + "/" + hostpid + "/model", "modelDone")
    
    def loadModel(self):
        model = []
        
        with open(self.root + self.tesiCris + self.struct.getName() + "/model.txt", 'r') as csvfile:
            tracereader = csv.reader(csvfile)
            for row in tracereader:
                for op in row:
                    model.append( str(op) )
        
        self.struct.setModel(model)

    def buildDoEsModel( self ):
        pass
        #dall'Oplist genero un modelo parziale con le configurazioni del DoEs e la media delle metriche
        #e lo invio ai client che fanno req

    def sendDoEsModel( self, hostpid ):
        pass
        #invio il modello parziale generato da buildDoEsModel()