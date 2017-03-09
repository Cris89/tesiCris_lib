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

	configurationsList.push_back(defaultConf);

	AppStruct::updateOPs();

	argoOPs->makeOPs(configurationsList, numParams, newOPs);





	char hostname[128];
	gethostname(hostname, 128);

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





	setStatus(defaultStatus);
}

void AppStruct::addOp( std::vector<float> op )
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	model.push_back(op);
}

std::vector< std::vector<float> > AppStruct::getModel()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);
	
	return model;
}

bool AppStruct::checkOPs()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

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
	//std::lock_guard<std::mutex> lock(appStruct_mutex);
	
	model.clear();
}

std::string AppStruct::getAppName()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return appName;
}

char *AppStruct::getAppName_hostpid()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return appName_hostpid;
}

ArgoOPs *AppStruct::getArgoOPs()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return argoOPs;
}

char *AppStruct::getHostpid()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return hostpid;
}

std::string AppStruct::getHostpidStr()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	std::string hostpidStr = hostpid;
	return hostpidStr;
}

std::vector< std::string > AppStruct::getInfo()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return info;
}

AppStruct::appStatus AppStruct::getStatus()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	return status;
}

void AppStruct::setConfigurationsList( std::vector< std::vector<float> > confsList )
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	configurationsList = confsList;
}

void AppStruct::setStatus( appStatus s)
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);

	status = s;
}

void AppStruct::updateOPs()
{
	//std::lock_guard<std::mutex> lock(appStruct_mutex);
	
	currentConfigurations = configurationsList;
}

AppStruct::~AppStruct()
{

}