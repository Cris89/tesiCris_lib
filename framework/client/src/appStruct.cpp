#include "tesiCris/appStruct.hpp"

#include <unistd.h>
#include <iostream>
#include <cstring>

AppStruct::AppStruct()
{

}

AppStruct::AppStruct( std::string name, int numP, int numM, std::vector< std::string > i, std::vector<float> defaultConf )
{
	appName = name;
	info = i;

	numParams = numP;
	numMetrics = numM;

	argoOPs = new ArgoOPs();
	argoManager = new ArgoManager();

	defaultConfiguration = defaultConf;

	configurationsList.push_back( defaultConfiguration );

	AppStruct::updateOPs();

	argoOPs->makeOPs( configurationsList, numParams, newOPs );





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
		argoOPs->makeOPs( configurationsList, numParams, newOPs);
		argoOPs->makeOPs( currentConfigurations, numParams, notNewOPs);
		argoOPs->makeCommonOPs();
		
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

ArgoOPs *AppStruct::getArgoOPs()
{
	return argoOPs;
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