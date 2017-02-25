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
	void subscribe( const char *topic );
	static void publish( char *payload, const char *topicName );

	static AppStruct *getAppStruct();
	static Topics *getTopics();

	virtual ~MQTT();

private:
	static MQTTClient client;
	static int rc;

	// clientID
	// es.: "swaptions_crisXPS15_1897"
	static char *clientID;

	static AppStruct *appStruct;
	static Topics *topics;

	static std::mutex mtx;

	static MQTTClient_messageArrived messageArrived;

	pthread_t reqThread;

    static void *reqThreadFunc( void * );
};

#endif
