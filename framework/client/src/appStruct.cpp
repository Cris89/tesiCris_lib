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
	model.push_back(op);
}

std::vector< std::vector<float> > AppStruct::getModel()
{
	return model;
}

bool AppStruct::checkOPs()
{
	if( configurationsList != currentConfigurations )
	{
		argoOPs->makeOPs( configurationsList, numParams, true);
		argoOPs->makeOPs( currentConfigurations, numParams, false);
		return true;
	}
	else
	{
		return false;
	}
}

std::string AppStruct::getAppName()
{
	return appName;
}

ArgoOPs *AppStruct::getArgoOPs()
{
	return argoOPs;
}

char *AppStruct::getAppName_hostpid()
{
	return appName_hostpid;
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

AppStruct::appStatus AppStruct::getStatus()
{
	return status;
}

void AppStruct::manageCurrentConfs()
{
	bool alreadyPresent = false;

	for( auto currentConf : currentConfigurations )
	{
		for( auto usedConf : usedConfigurations )
		{
			if( usedConf == currentConf )
			{
				alreadyPresent = true;
				break;
			}
		}

		if( alreadyPresent == false )
		{
			usedConfigurations.push_back(currentConf);
		}

		else
		{
			alreadyPresent = false;
		}
	}
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
	AppStruct::manageCurrentConfs();
	
	currentConfigurations = configurationsList;
}

AppStruct::~AppStruct()
{

}