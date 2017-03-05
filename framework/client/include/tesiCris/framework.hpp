#ifndef TESICRIS_FRAMEWORK_HPP
#define TESICRIS_FRAMEWORK_HPP

#include "tesiCris/appStruct.hpp"
#include "tesiCris/mqtt.hpp"
#include "tesiCris/topics.hpp"

#include <vector>

class Framework
{
public:
	Framework( std::string name, int numParams, int numMetrics, std::vector<float> defaultConf, std::vector< std::string > info );

	void init();

	bool changeOPs;

	AppStruct *getAppStruct();

	void checkOPs();

	void sendResult( std::string op );

	void manageUsedConf( std::vector<float> conf );

	void updateOPs();

private:
	AppStruct *appStruct;

	Topics *topics;

	MQTT *mqtt;
};

#endif
