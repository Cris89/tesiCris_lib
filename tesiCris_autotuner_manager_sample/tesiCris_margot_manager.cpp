#include "tesiCris_margot_manager.hpp"

tesiCris_Margot_Manager::tesiCris_Margot_Manager()
{
	
}

void tesiCris_Margot_Manager::init()
{
	std::string appName = "sleepApp2params1feature";

	int numParams = 2;
	int numFeatures = 1;
	int numMetrics = 2;



	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////// good_func
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<float> defaultConfiguration = { 150, 360, 100 };

	std::vector< std::string > info = { "metric avg_error",
										"metric avg_throughput",

										"param param1 enum 1 50 150 300 450 700 800",
										"param param2 range 10 850 70",

										"numFeats 1",
										"minNumObsFeatValues 9",

										"doe fcccd",
										"lhdSamples 10",
										"numOPs 5",

										"rsm sparkGenLinRegr2nd" };

	// milliseconds
	int threadMQTTReqSleepTime = 3000;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////// good_func
	////////////////////////////////////////////////////////////////////////////////////////////////////



	/*////////////////////////////////////////////////////////////////////////////////////////////////////
	////////// strange_func
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<float> defaultConfiguration = {15, 10, 10};

	std::vector< std::string > info = { "metric avg_error",
										"metric avg_throughput",

										"param param1 enum 1 10 15 25 40 65 80",
										"param param2 enum 1 5 10 20",
										"param param3 range 10 46 3",

										"doe fcccd",
										
										"lhdSamples 10",

										"numOPs 1",

										"rsm sparkGenLinRegr2nd" };

	// milliseconds
	int threadMQTTReqSleepTime = 3000;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////// strange_func
	////////////////////////////////////////////////////////////////////////////////////////////////////*/



	tesiCris_framework = new Framework( appName,
											
										numParams,
										numFeatures,
										numMetrics,

										defaultConfiguration,
										
										info,
											
										threadMQTTReqSleepTime );

	tesiCris_framework->init();





	operating_points_t defaultOP = tesiCris_framework->getAppStruct()->getOperatingPoints()->getNewOPs();

	margot::sleeping::manager.add_operating_points( defaultOP );

	margot::init();
}

void tesiCris_Margot_Manager::updateOPs()
{
	tesiCris_framework->checkOPs();

	if(tesiCris_framework->changeOPs == true)
	{
		operating_points_t newOPs = tesiCris_framework->getAppStruct()->getOperatingPoints()->getNewOPs();
		operating_points_t currentOPs = tesiCris_framework->getAppStruct()->getOperatingPoints()->getCurrentOPs();
		operating_points_t commonOPs = tesiCris_framework->getAppStruct()->getOperatingPoints()->getCommonOPs();

		/*printf("\t+-------newOPs---------+\n");
		for( auto newOP : newOPs)
		{
			for ( const auto c : newOP.first )
			{
				printf("\t|% 22.2f|\n", c);
			}

			for ( const auto c : newOP.second )
			{
				printf("\t|% 22.2f|\n", c);
			}

			printf("\t+----------------------+\n");
		}

		printf("\n\t+-----currentOPs-------+\n");
		for( auto currentOP : currentOPs)
		{
			for ( const auto c : currentOP.first )
			{
				printf("\t|% 22.2f|\n", c);
			}

			for ( const auto c : currentOP.second )
			{
				printf("\t|% 22.2f|\n", c);
			}

			printf("\t+----------------------+\n");
		}

		printf("\n\t+-----commonOPs--------+\n");
		for( auto commonOP : commonOPs)
		{
			for ( const auto c : commonOP.first )
			{
				printf("\t|% 22.2f|\n", c);
			}

			for ( const auto c : commonOP.second )
			{
				printf("\t|% 22.2f|\n", c);
			}

			printf("\t+----------------------+\n");
		}*/

		margot::sleeping::manager.add_operating_points(newOPs);
		margot::sleeping::manager.remove_operating_points(currentOPs);
		margot::sleeping::manager.add_operating_points(commonOPs);

		margot::sleeping::manager.dump();

		tesiCris_framework->updateOPs();
	}
}

void tesiCris_Margot_Manager::sendResult( std::vector<float> params, std::vector<float> metrics )
{
	std::string operatingPoint;

	for( int i = 0; i < params.size(); i++ )
	{
		operatingPoint += std::to_string( params[i] ) + " ";
	}

	operatingPoint = operatingPoint.substr( 0, operatingPoint.size() - 1 );
	operatingPoint += ":";

	for( int i = 0; i < metrics.size(); i++ )
	{
		operatingPoint += std::to_string( metrics[i] ) + " ";
	}

	operatingPoint = operatingPoint.substr( 0, operatingPoint.size() - 1 );

	tesiCris_framework->sendResult( operatingPoint );
}

void tesiCris_Margot_Manager::sendResult( std::vector<float> params, std::vector<float> features, std::vector<float> metrics )
{
	std::string operatingPoint;

	for( int i = 0; i < params.size(); i++ )
	{
		operatingPoint += std::to_string( params[i] ) + " ";
	}

	operatingPoint = operatingPoint.substr( 0, operatingPoint.size() - 1 );
	operatingPoint += ":";

	for( int i = 0; i < features.size(); i++ )
	{
		operatingPoint += std::to_string( features[i] ) + " ";
	}

	operatingPoint = operatingPoint.substr( 0, operatingPoint.size() - 1 );
	operatingPoint += ":";

	for( int i = 0; i < metrics.size(); i++ )
	{
		operatingPoint += std::to_string( metrics[i] ) + " ";
	}

	operatingPoint = operatingPoint.substr( 0, operatingPoint.size() - 1 );

	tesiCris_framework->sendResult( operatingPoint );
}

void tesiCris_Margot_Manager::storeFeatures( std::vector<float> features )
{
	tesiCris_framework->storeFeatures( features );
}

tesiCris_Margot_Manager::~tesiCris_Margot_Manager()
{

}
