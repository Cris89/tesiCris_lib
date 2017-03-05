#ifndef TESICRIS_TOPICS_HPP
#define TESICRIS_TOPICS_HPP

#include <string>

class Topics
{
public:
	Topics();
	Topics( std::string appName, std::string hostpid );
	
	const char *getAppsTopic();
	
	const char *getCommunicationTopic();
	
	const char *getConfTopic();
	
	const char *getLastWillTopic();
	
	const char *getModelTopic();
	
	const char *getOPsTopic();
	
	const char *getReqTopic();
	
	const char *getSendInfoTopic();
	
	virtual ~Topics();

private:
	// topic on which the app will notify its existence
	// es.: "tesiCris/apps"
	const char *appsTopic;

	// topic on which the app will eventually receive the request about app info
	// es.: "tesiCris/swaptions"
	const char *communicationTopic;

	// topic on which the app will receive the configurations
	// es.: "tesiCris/swaptions/crisXPS15_1897/conf"
	const char *confTopic;

	// last will and testament topic
	// es.: "tesiCris/swaptions/disconnection"
	const char *lastWillTopic;

	// topic on which the app will publish the operating points during the dse
	// es.: "tesiCris/swaptions/OPs"
	const char *OPsTopic;

	// topic on which the app will receive the model
	// es.: "tesiCris/swaptions/crisXPS15_1897/model"
	const char *modelTopic;

	// topic on which the app will do a request
	// es.: "tesiCris/swaptions/req"
	const char *reqTopic;

	// topic on which the app will eventually publish app info
	// es.: "tesiCris/swaptions/info"
	const char *sendInfoTopic;
};

#endif