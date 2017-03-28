#include "tesiCris_margot_manager.hpp"

tesiCris_Margot_Manager::tesiCris_Margot_Manager()
{
	
}

void tesiCris_Margot_Manager::init()
{
	std::string appName = "tutorial";

	int numParams = 1;
	int numMetrics = 2;

	std::vector<float> defaultConfiguration = {10};

	std::vector< std::string > info = { "metric avg_error",
										"metric avg_computation_time",

										"param num_trials range 10 1000 10",
								
										"numOPs 5",

										"doe lhd",
										"lhdSamples 5" };

	// milliseconds
	int threadMQTTReqSleepTime = 1000;

	tesiCris_framework = new Framework( appName,
											
										numParams,
										numMetrics,

										defaultConfiguration,
										
										info,
											
										threadMQTTReqSleepTime );

	tesiCris_framework->init();





	operating_points_t defaultOP = tesiCris_framework->getAppStruct()->getOperatingPoints()->getNewOPs();

	margot::foo::manager.add_operating_points( defaultOP );

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

		margot::foo::manager.add_operating_points(newOPs);
		margot::foo::manager.remove_operating_points(currentOPs);
		margot::foo::manager.add_operating_points(commonOPs);

		/*margot::foo::manager.dump();*/

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

tesiCris_Margot_Manager::~tesiCris_Margot_Manager()
{

}
