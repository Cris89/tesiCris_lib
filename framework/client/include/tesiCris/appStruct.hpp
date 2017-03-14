#ifndef TESICRIS_APPSTRUCT_HPP
#define TESICRIS_APPSTRUCT_HPP

#include "tesiCris/argoOPs.hpp"
#include "tesiCris/argoManager.hpp"

#include <vector>
#include <deque>
#include <string>

class AppStruct
{
public:
	enum appStatus{ defaultStatus, dse, doeModel, autotuning };

	enum OPsType : bool {
    newOPs = true,
    notNewOPs = false,
	};

	AppStruct();
	AppStruct( std::string name, int numParams, int numMetrics, std::vector< std::string > i, std::vector<float> defaultConf );
	
	void addOp( std::vector<float> op );
	
	bool checkOPs();

	void clearModel();
	
	std::string getAppName();
	
	char *getAppName_hostpid();
	
	ArgoOPs *getArgoOPs();

	std::vector<float> getDefaultConfiguration();
	
	char *getHostpid();
	
	std::string getHostpidStr();
	
	std::vector< std::string > getInfo();
	
	std::vector< std::vector<float> > getModel();
	
	appStatus getStatus();
	
	void setConfigurationsList( std::vector< std::vector<float> > confsList );
	
	void setStatus( appStatus s );
	
	void updateOPs();

	virtual ~AppStruct();

private:
	std::string appName;

	bool areNewOPs;
	
	ArgoOPs *argoOPs;
	ArgoManager *argoManager;
	
	// application name + hostpid
	// es.: "swaptions crisXPS15_1897"
	char *appName_hostpid;
	
	// hostname_pid
	// es.: "crisXPS15_1897"
	// double-ended queue che contiene le configurazioni con cui l'app deve essere eseguita
	std::vector< std::vector<float> > configurationsList;
	
	// double-ended queue che contiene le configurazioni con cui l'app deve essere eseguita
	std::vector< std::vector<float> > currentConfigurations;

	// default configuration
	std::vector<float> defaultConfiguration;

	char *hostpid;
	
	// double-ended queue che contiene il modello
	std::vector< std::string > info;
	
	std::vector< std::vector<float> > model;

	int numMetrics;

	int numParams;

	appStatus status;

	// double-ended queue che contiene le configurazioni con cui l'app è stata già eseguita
	std::vector< std::vector<float> > usedConfigurations;
};

#endif