#include "tesiCris/appStruct.hpp"

#include <unistd.h>

#include <cstring>

AppStruct::AppStruct()
{

}

AppStruct::AppStruct( std::string name, std::vector< std::string > i, std::vector<float> defaultConf )
{
	appName = name;
	info = i;

	configurationsList.push_back(defaultConf);
	usedConfigurations.push_back(defaultConf);





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

std::string AppStruct::getAppName()
{
	return appName;
}

std::string AppStruct::getHostpidStr()
{
	std::string hostpidStr = hostpid;
	return hostpidStr;
}

char *AppStruct::getHostpid()
{
	return hostpid;
}

char *AppStruct::getAppName_hostpid()
{
	return appName_hostpid;
}

AppStruct::appStatus AppStruct::getStatus()
{
	return status;
}

void AppStruct::setStatus( appStatus s)
{
	status = s;
}

std::vector< std::string > AppStruct::getInfo()
{
	return info;
}

std::vector< std::vector<float> > AppStruct::getUsedConfigurations()
{
	return usedConfigurations;
}

void AppStruct::addUsedConfiguration( std::vector<float> conf )
{
	usedConfigurations.push_back( conf );
}

std::vector< std::vector<float> > AppStruct::getConfigurationsList()
{
	return configurationsList;
}

void AppStruct::setConfigurationsList( std::vector< std::vector<float> > confsList )
{
	configurationsList = confsList;
}

void AppStruct::addOp( std::vector<float> op )
{
	model.push_back(op);
}

std::vector< std::vector<float> > AppStruct::getModel()
{
	return model;
}

AppStruct::~AppStruct()
{

}
