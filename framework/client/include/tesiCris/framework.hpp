#ifndef TESICRIS_FRAMEWORK_HPP
#define TESICRIS_FRAMEWORK_HPP

#include "tesiCris/appStruct.hpp"
#include "tesiCris/mqtt.hpp"
#include "tesiCris/topics.hpp"

#include <vector>

class Framework
{
public:
	Framework( std::string name, 
				int numParams, 
				int numMetrics, 
				std::vector<float> defaultConf, 
				std::vector< std::string > info );

	bool changeOPs;

	void checkOPs();
	
	AppStruct *getAppStruct();
	
	void init();
	
	void sendResult( std::string op );
	
	void updateOPs();

private:
	AppStruct *appStruct;
	
	MQTT *mqtt;
	
	Topics *topics;
};

#endif
