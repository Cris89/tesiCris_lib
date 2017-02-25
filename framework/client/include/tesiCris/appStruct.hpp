#ifndef TESICRIS_APPSTRUCT_HPP
#define TESICRIS_APPSTRUCT_HPP

#include <vector>
#include <deque>

#include <string>

class AppStruct
{
public:
	enum appStatus{ defaultStatus, dse, autotuning };

	AppStruct();
	AppStruct( std::string name, std::vector< std::string > i, std::vector<float> defaultConf );

	std::string getAppName();

	std::string getHostpidStr();
	char *getHostpid();
	
	char *getAppName_hostpid();
	
	appStatus getStatus();
	
	std::vector< std::vector<float> > getConfigurationsList();

	std::vector< std::vector<float> > getUsedConfigurations();
	void addUsedConfiguration( std::vector<float> conf );
	
	std::vector< std::string > getInfo();

	std::vector< std::vector<float> > getModel();

	void setStatus( appStatus s );
	void setConfigurationsList( std::vector< std::vector<float> > confsList );
	void addOp( std::vector<float> op );

	virtual ~AppStruct();

private:
	appStatus status;
	
	std::string appName;

	// hostname_pid
	// es.: "crisXPS15_1897"
	char *hostpid;

	// application name + hostpid
	// es.: "swaptions crisXPS15_1897"
	char *appName_hostpid;

	// double-ended queue che contiene le configurazioni con cui l'app deve essere eseguita
	std::vector< std::vector<float> > configurationsList;

	// double-ended queue che contiene le configurazioni con cui l'app è stata già eseguita
	std::vector< std::vector<float> > usedConfigurations;

	// double-ended queue che contiene il modello
	std::vector< std::vector<float> > model;

	std::vector< std::string > info;
};

#endif