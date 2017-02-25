import threading
import paho.mqtt.client as paho
from server_handler import server_handler

address = "127.0.0.1"
clientID = "server_listener"
client = paho.Client(client_id = clientID)
qos = 0

root = "tesiCris/"
appsTopic = root + "apps"

apps = []

threadID = 0

lock = threading.Lock()


####################################################################################################
# listener thread
####################################################################################################

class listenerThread (threading.Thread):
    def __init__(self, threadID, appName, hostpid):
        threading.Thread.__init__(self)
        
        self.threadID = threadID
        self.appName = appName
        self.hostpid = hostpid
        
    def run(self):
        print( "\nstarting thread" + str(self.threadID) + " for application " + self.appName )
        
        if self.appName in apps:
            print( "\nserver_handler for application " + self.appName + " already created" )
            print( "sending hostpid to the server_handler" )
            
            publish( root + self.appName + "/newHostpid", self.hostpid )
        
        else:
            apps.append(self.appName)
            
            print( "\ncreating server_handler for application " + self.appName )
            
            handler = server_handler()
            handler.start(self.appName, self.hostpid)
        
        print( "\nexiting thread" + str(self.threadID) + " for application " + self.appName )
        

####################################################################################################
# MQTT
####################################################################################################

def on_connect(host):
    print("\nclient ID: " + client._client_id + " connected at " + host + ":8883")

def on_subscribe(topic):
        print ("\nsubscription")
        print ("topic: " + topic)
 
def on_message(client, userdata, msg):
    print ("\nreceived message")
    print ("topic: " + msg.topic)
    print ("payload: " + msg.payload)
     
    if(msg.topic == appsTopic):
        lock.acquire()
        
        global threadID
        
        # splitted[0]: appName (es.: "swaptions")
        # spitted[1]: hostpid (es.: "crisXPS15_1897")
        splitted = msg.payload.split(" ")
        
        thread = listenerThread( threadID, splitted[0], splitted[1] )
        thread.start()
        
        threadID += 1
        
        lock.release()

def connect(host):
    client.connect(host, port = 8883)
    client.on_connect = on_connect(host)
    
def subscribe(topic):
    global qos
    
    client.subscribe(topic, qos = qos)
    client.on_subscribe = on_subscribe(topic)
    client.on_message = on_message

def on_publish(topic, message):
        print ("\npublication")
        print ("topic: " + topic)
        print ("message: " + message)
        
def publish(topic, message):
    client.on_publish = on_publish(topic, message)
    client.publish(topic, message, qos = qos)
           

####################################################################################################
# main
####################################################################################################

if __name__ == '__main__':
    connect(address)
    subscribe(appsTopic)
     
    client.loop_forever()