#ifndef TESICRIS_MQTT_HPP
#define TESICRIS_MQTT_HPP

#include "tesiCris/appStruct.hpp"
#include "tesiCris/topics.hpp"

#include <MQTTClient.h>

#include <mutex>

#include <pthread.h>

class MQTT 
{
public:
	MQTT( AppStruct &app, Topics &t );

	void connect();

	static void publish( char *payload, const char *topicName );

	void subscribe( const char *topic );
	
	virtual ~MQTT();

private:
	static AppStruct *appStruct;

	static MQTTClient client;

	// clientID
	// es.: "swaptions_crisXPS15_1897"
	static char *clientID;

	static MQTTClient_messageArrived messageArrived;

	static std::mutex mtx;

	static int rc;

	pthread_t reqThread;
	
	static void *reqThreadFunc( void * );

	static Topics *topics;
};

#endif