#include "em_algo.h"

em_algo::em_algo(int number_of_clusters)
{
    _number_of_clusters = number_of_clusters;
}

void em_algo::init_start_parameters()
{
    double_vector weights(_number_of_clusters, 1.0 / _number_of_clusters);
    std::cout << "printing weights, size = " << weights.size() << std::endl;
    std::cout << weights << std::endl;
}

void em_algo::expectation_step()
{

}

void em_algo::maximization_step()
{

}
