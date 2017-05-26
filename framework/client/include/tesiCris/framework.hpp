#ifndef TESICRIS_FRAMEWORK_HPP
#define TESICRIS_FRAMEWORK_HPP

#include "tesiCris/appStruct.hpp"
#include "tesiCris/mqtt.hpp"
#include "tesiCris/topics.hpp"

#include <vector>
#include <string>

class Framework
{
public:
	Framework( std::string name, 
				int numParams,
				int numFeatures,
				int numMetrics, 
				std::vector<float> defaultConf, 
				std::vector< std::string > info,
				int threadSleepTime );

	bool changeOPs;

	void checkOPs();
	
	AppStruct *getAppStruct();
	
	void init();
	
	void sendResult( std::string op );

	void storeFeatures( std::vector<float> features );
	
	void updateOPs();

private:
	std::string IPaddress = "127.0.0.1";
	std::string brokerPort = "8883";

	AppStruct *appStruct;
	
	MQTT *mqtt;
	
	Topics *topics;
};

#endif
