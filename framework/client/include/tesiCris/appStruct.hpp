#ifndef TESICRIS_APPSTRUCT_HPP
#define TESICRIS_APPSTRUCT_HPP

#include "tesiCris/OPs.hpp"

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
	AppStruct( std::string name,

				int numParams,
				int numFeatures,
				int numMetrics,

				std::vector< std::string > i,

				std::vector<float> defaultConf,
				std::vector<int> params_idx,
				std::vector<int> feats_idx );
	
	void addOp( std::vector<float> op );
	
	bool checkOPs();

	void clearModel();
	
	std::string getAppName();
	
	char *getAppName_hostpid();

	std::vector<float> getFeatures();
	
	OPs *getOperatingPoints();

	std::vector<float> getDefaultConfiguration();
	
	char *getHostpid();
	
	std::string getHostpidStr();
	
	std::vector< std::string > getInfo();
	
	std::vector< std::vector<float> > getModel();

	std::vector<int> getParametersIndexes();
	std::vector<int> getFeaturesIndexes();
	
	appStatus getStatus();

	std::vector<float> orderValues( std::vector<float> values );
	
	void setConfigurationsList( std::vector< std::vector<float> > confsList );

	void setFeatures( std::vector<float> feats );
	
	void setStatus( appStatus s );
	
	void updateOPs();

	virtual ~AppStruct();

private:
	std::string appName;

	bool areNewOPs;
	
	OPs *operatingPoints;
	
	// application name + hostpid
	// es.: "swaptions crisXPS15_1897"
	char *appName_hostpid;
	
	// double-ended queue che contiene le configurazioni con cui l'app deve essere eseguita
	std::vector< std::vector<float> > configurationsList;
	
	// double-ended queue che contiene le configurazioni con cui l'app deve essere eseguita
	std::vector< std::vector<float> > currentConfigurations;

	// default configuration
	std::vector<float> defaultConfiguration;

	// vector in which possible features values are stored
	std::vector<float> features;

	char *hostpid;
	
	// double-ended queue che contiene il modello
	std::vector< std::string > info;
	
	std::vector< std::vector<float> > model;

	int numMetrics;

	int numFeatures;

	int numParams;

	// vectors that contain parameters and features indexes in order to build correctly
	// the OPs for mARGOt autotuner
	std::vector<int> parameters_indexes;
	std::vector<int> features_indexes;

	appStatus status;

	// double-ended queue che contiene le configurazioni con cui l'app è stata già eseguita
	std::vector< std::vector<float> > usedConfigurations;
};

#endif