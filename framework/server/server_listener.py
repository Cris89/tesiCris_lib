import paho.mqtt.client as paho
from server_handler import server_handler
import threading

clientID = "server_listener"
client = paho.Client(client_id = clientID)

IPaddress = "127.0.0.1"
brokerPort = "8883"

qos = 0

root = "tesiCris/"
appsTopic = root + "apps"

apps = []

threadID = 0


####################################################################################################
# listener thread
####################################################################################################

class listenerThread( threading.Thread ):
    def __init__( self, threadID, appName, hostpid ):
        threading.Thread.__init__(self)

        self.threadID = threadID
        self.appName = appName
        self.hostpid = hostpid
        
    def run( self ):
        global apps

        print( "\nstarting thread" + str(self.threadID) + " for application " + self.appName )
        
        if self.appName in apps:
            print( "\nserver_handler for application " + self.appName + " already created" )
            print( "sending hostpid to the server_handler" )
            
            publish( root + self.appName + "/newHostpid", self.hostpid )
        
        else:
            apps.append( self.appName )
            
            print( "\ncreating server_handler for application " + self.appName )
            
            handler = server_handler()
            handler.start( self.appName, self.hostpid )
        
        print( "\nexiting thread" + str(self.threadID) + " for application " + self.appName )
        

####################################################################################################
# MQTT
####################################################################################################

def on_connect( IPaddress, brokerPort ):
    print( "\nclient ID: " + client._client_id + " connected at " + IPaddress + ":" + brokerPort )

def on_subscribe( topic ):
        print( "\nsubscription" )
        print( "topic: " + topic )
 
def on_message( client, userdata, msg ):
    print( "\nreceived message" )
    print( "topic: " + msg.topic )
    print( "payload: " + msg.payload )
     
    if( msg.topic == appsTopic ):        
        global threadID
        
        splitted = msg.payload.split(" ")
        # splitted[0]: appName (es.: "swaptions")
        # spitted[1]: hostpid (es.: "crisXPS15_1897")

        thread = listenerThread( threadID, splitted[0], splitted[1] )
        thread.start()
        
        threadID += 1

def connect( IPaddress, brokerPort ):
    client.connect( IPaddress, port = brokerPort )
    client.on_connect = on_connect( IPaddress, brokerPort )
    
def subscribe( topic ):
    client.subscribe( topic, qos = qos )
    client.on_subscribe = on_subscribe( topic )
    client.on_message = on_message

def on_publish( topic, message ):
        print( "\npublication" )
        print( "topic: " + topic )
        print( "message: " + message )
        
def publish( topic, message ):
    client.on_publish = on_publish( topic, message )
    client.publish( topic, message, qos = qos )
           

####################################################################################################
# main
####################################################################################################

if __name__ == '__main__':
    connect( IPaddress, brokerPort )
    subscribe( appsTopic )
     
    client.loop_start()

    while (True):
        pass

    client.loop_stop()