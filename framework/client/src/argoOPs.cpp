#include "tesiCris/argoOPs.hpp"

#include <algorithm>

ArgoOPs::ArgoOPs()
{

}

operating_points_t ArgoOPs::getCommonOPs()
{
	return commonOPs;
}

operating_points_t ArgoOPs::getCurrentOPs()
{
	return currentOPs;
}

operating_points_t ArgoOPs::getNewOPs()
{
	return newOPs;
}

void ArgoOPs::makeCommonOPs()
{
	commonOPs.clear();

	for( auto currentOP : currentOPs )
	{
		for( auto newOP : newOPs )
		{
			if( newOP == currentOP )
			{
				commonOPs.push_back(newOP);
				newOPs.erase( std::remove( newOPs.begin(), newOPs.end(), newOP ), newOPs.end() );

				break;
			}
		}
	}
}

void ArgoOPs::makeOPs( std::vector< std::vector<float> > ops, int numParams, bool areNew)
{
	if( areNew == true)
	{
		newOPs.clear();
	}
	else
	{
		currentOPs.clear();
	}

	if( ops.empty() == false )
	{
		if( ops[0].size() == numParams )
		{
			// I have to create Operating Points from configurations --> with fake metrics values
			int fakeMetricsValues = 6;

			for( auto op : ops )
			{
				configuration_t params;
				performance_t metrics;

				for( auto value : op )
				{
					params.push_back( value );
					metrics.push_back( fakeMetricsValues );
				}

				operating_point_t oper;

				oper.first = params;
				oper.second = metrics;

				if( areNew == true )
				{
					newOPs.push_back(oper);
				}
				else
				{
					currentOPs.push_back(oper);
				}
			}
		}
		else
		{
			// I have both params and metrics values
			for( auto op : ops )
			{
				configuration_t params;
				for( int i = 0; i < numParams; i++ )
				{
					params.push_back( op[i] );
				}

				performance_t metrics;
				for( int i = numParams; i < op.size(); i++ )
				{
					metrics.push_back( op[i] );
				}

				operating_point_t oper;

				oper.first = params;
				oper.second = metrics;

				if( areNew == true )
				{
					newOPs.push_back(oper);
				}
				else
				{
					currentOPs.push_back(oper);
				}
			}
		}
	}
}

ArgoOPs::~ArgoOPs()
{

}