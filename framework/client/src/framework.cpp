#include "tesiCris/framework.hpp"

#include <string>
#include <cstring>
#include <vector>

Framework::Framework( std::string name, std::vector<float> defaultConf, std::vector< std::string > info )
{
	appStruct = new AppStruct( name, info, defaultConf );

	topics = new Topics( appStruct->getAppName(), appStruct->getHostpidStr() );

	mqtt = new MQTT( *appStruct, *topics );
}

void Framework::init()
{
	mqtt->connect();

	// topic on which the app will eventually receive the request about app info
	// es.: "tesiCris/swaptions"
	mqtt->subscribe( topics->getCommunicationTopic() );

	// topic on which the app will receive the configurations
	// es.: "tesiCris/swaptions/crisXPS15_1897/conf"
	mqtt->subscribe( topics->getConfTopic() );
	
	// topic on which the app will receive the model
	// es.: "tesiCris/swaptions/crisXPS15_1897/model"
	mqtt->subscribe( topics->getModelTopic() );

	// topic es.: "tesiCris/apps"
	// payload es.: "swaptions crisXPS15_1897"
	mqtt->publish( appStruct->getAppName_hostpid(), topics->getAppsTopic() );
}

std::vector<float> Framework::update()
{
	int randomConf = rand() % ( appStruct->getConfigurationsList().size() );

	std::vector<float> configuration = appStruct->getConfigurationsList()[randomConf];

	appStruct->setConfigurationsList( appStruct->getUsedConfigurations() );

	return configuration;
}

void Framework::sendResult( std::string op )
{
	char* operatingPointP = new char[op.length() + 1];
	std::strcpy(operatingPointP, op.c_str());

	mqtt->publish( operatingPointP, topics->getOPsTopic() );
}

void Framework::manageUsedConf( std::vector<float> conf )
{
	bool alreadyPresent = false;

	for( int i = 0; i < appStruct->getUsedConfigurations().size(); i++ )
	{
		if( conf == appStruct->getUsedConfigurations()[i] )
		{
			alreadyPresent = true;
			break;
		}
	}

	if( alreadyPresent == false )
	{
		appStruct->addUsedConfiguration( conf );
	}
}
