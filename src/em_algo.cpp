#include "em_algo.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>

typedef boost::minstd_rand base_generator_type;

em_algo::em_algo(int number_of_clusters)
{
    n_clusters = number_of_clusters;
}

void em_algo::init(matrix& features)
{
    base_generator_type generator(42);
    long n_objects = features.size1();
    long n_features = features.size2();

    parameters = model();

    // init means
    parameters.means = matrix(n_features, n_clusters);
    parameters.sigma = matrix(n_features, n_features, n_clusters);

    for (auto i = 0; i < n_features; ++i)
    {
        // take min, max value and create random from [min, max]
        boost::numeric::ublas::matrix_column<matrix > column(features, i);
        auto min_max_values = boost::minmax_element(column.begin(), column.end());

        boost::uniform_real<> uni_dist(*min_max_values.first, *min_max_values.second);
        boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);
        for(auto j = 0; j < n_clusters; j++)
            parameters.means(i, j) = uni();

    }
    // init weights
    parameters.weights = double_vector(n_clusters, 1.0 / n_clusters);
    std::cout << parameters << std::endl;
}

void em_algo::expectation_step()
{

}

void em_algo::maximization_step()
{

}

void em_algo::process()
{

}
