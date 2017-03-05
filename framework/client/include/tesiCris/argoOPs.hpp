#ifndef TESICRIS_ARGOOPS_HPP
#define TESICRIS_ARGOOPS_HPP

#include <vector>
#include <deque>
#include <utility>

/**
 * @brief Define the type used internally by the monitor module
 */
typedef float statistical_properties_t;

/**
 * @brief Define the type used internally by the AS-RTM module
 */
typedef statistical_properties_t argo_value_t;

/**
 * @brief The type of a parameter of the configuration
 */
typedef argo_value_t parameter_t;

/**
 * @brief The type of a metric of the performance
 */
typedef argo_value_t metric_t;

/**
 * @brief The list of parameters
 */
typedef std::vector< parameter_t > configuration_t;

/**
 * @brief The list of metrics
 */
typedef std::vector< metric_t > performance_t;

/**
 * @brief The definition of an Operating Point
 */
typedef std::pair< configuration_t, performance_t > operating_point_t;

/**
 * @brief The list of Operating Points
 *
 * @details
 * It is meant to store a defined set of Operating Point. Iteration and random
 * deletes are efficient operations.
 */
typedef std::deque< operating_point_t > operating_points_t;

class ArgoOPs
{
public:
	ArgoOPs();

	operating_points_t getCurrentOPs();

	operating_points_t getNewOPs();

	void makeOPs( std::vector< std::vector<float> > ops, int numParams, bool areNew);

	virtual ~ArgoOPs();

private:
	operating_points_t currentOPs;

	operating_points_t newOPs;
};

#endif