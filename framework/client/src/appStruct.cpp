#include "tesiCris/appStruct.hpp"

#include <unistd.h>
#include <iostream>
#include <cstring>

AppStruct::AppStruct()
{

}

AppStruct::AppStruct( std::string name, int numP, int numF, int numM, std::vector< std::string > i, std::vector<float> defaultConf )
{
	appName = name;
	info = i;

	numParams = numP;
	numFeatures = numF;
	numMetrics = numM;

	operatingPoints = new OPs();

	defaultConfiguration = defaultConf;

	configurationsList.push_back( defaultConfiguration );

	AppStruct::updateOPs();

	operatingPoints->makeOPs( configurationsList, numParams + numFeatures, numMetrics, newOPs );





	char hostname[128];
	gethostname( hostname, 128 );

	int pid = getpid();





	// hostpid
	// es.: crisXPS15_1897
	std::string hostpidStr = hostname;
	hostpidStr += "_" + std::to_string(pid);

	hostpid = new char[hostpidStr.length() + 1];
	std::strcpy( hostpid, hostpidStr.c_str() );





	// name of the application + hostname_pid for MQTT pubblication on topic /apps
	std::string appName_hostpidStr = appName + " " + hostpid;

	appName_hostpid = new char[appName_hostpidStr.length() + 1];
	std::strcpy( appName_hostpid, appName_hostpidStr.c_str() );





	setStatus( defaultStatus );
}

void AppStruct::addOp( std::vector<float> op )
{
	model.push_back(op);
}

bool AppStruct::checkOPs()
{
	if( configurationsList != currentConfigurations )
	{
		operatingPoints->makeOPs( configurationsList, numParams + numFeatures, numMetrics, newOPs);
		operatingPoints->makeOPs( currentConfigurations, numParams + numFeatures, numMetrics, notNewOPs);
		operatingPoints->makeCommonOPs();
		
		return true;
	}
	else
	{
		return false;
	}
}

void AppStruct::clearModel()
{	
	model.clear();
}

std::string AppStruct::getAppName()
{
	return appName;
}

char *AppStruct::getAppName_hostpid()
{
	return appName_hostpid;
}

std::vector<float> AppStruct::getFeatures()
{
	return features;
}

OPs *AppStruct::getOperatingPoints()
{
	return operatingPoints;
}

std::vector<float> AppStruct::getDefaultConfiguration()
{
	return defaultConfiguration;
}

char *AppStruct::getHostpid()
{
	return hostpid;
}

std::string AppStruct::getHostpidStr()
{
	std::string hostpidStr = hostpid;
	return hostpidStr;
}

std::vector< std::string > AppStruct::getInfo()
{
	return info;
}

std::vector< std::vector<float> > AppStruct::getModel()
{
	return model;
}

AppStruct::appStatus AppStruct::getStatus()
{
	return status;
}

void AppStruct::setConfigurationsList( std::vector< std::vector<float> > confsList )
{
	configurationsList = confsList;
}

void AppStruct::setFeatures( std::vector<float> feats )
{
	features = feats;

	if( status == AppStruct::defaultStatus )
	{
		// update defaultConfiguration with new feature values
		std::vector<float> newDefaultConf;

		// add params values
		for( int i = 0; i < numParams; i++ )
		{
			newDefaultConf.push_back( defaultConfiguration[i] );
		}

		// add features values
		for( int i = 0; i < features.size(); i++ )
		{
			newDefaultConf.push_back( features[i] );
		}

		AppStruct::setConfigurationsList( { newDefaultConf } );
	}
}

void AppStruct::setStatus( appStatus s)
{
	status = s;
}

void AppStruct::updateOPs()
{	
	currentConfigurations = configurationsList;
}

AppStruct::~AppStruct()
{

}