#include "em_algo.h"

#include <boost/algorithm/minmax_element.hpp>
#include <boost/array.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "cholesky.hpp"


typedef boost::minstd_rand base_generator_type;

em_algo::em_algo(int number_of_clusters)
{
    n_clusters = number_of_clusters;
}

void em_algo::init(matrix& features)
{
    long n_objects = features.size1();
    long n_features = features.size2();

    base_generator_type generator(42);

    parameters = model();

    // init weights
    parameters.weights = double_vector(n_clusters, 1.0 / n_clusters);

    // init means
    parameters.means = matrix(n_features, n_clusters);
    for (auto i = 0; i < n_features; ++i)
    {
        // take min, max value and create random from [min, max]
        ublas::matrix_column<matrix > column(features, i);
        auto min_max_values = boost::minmax_element(column.begin(), column.end());

        boost::uniform_real<> uni_dist(*min_max_values.first, *min_max_values.second);
        boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);
        for(auto j = 0; j < n_clusters; j++)
        {
            parameters.means(i, j) = uni();
        }
    }

    for (auto i = 0; i < n_clusters; ++i)
        parameters.sigma.push_back(matrix(n_features, n_features));

    boost::uniform_real<> uni_01_dist(0, 1);
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni_01(generator, uni_01_dist);

    for (auto k = 0; k < n_clusters; ++k)
        for (auto i = 0; i < n_features; ++i)
            for (auto j = 0; j < n_features; ++j)
                if (i != j)
                    parameters.sigma[k](i, j) = 0;
                else
                    parameters.sigma[k](i, j) = uni_01();

    std::cout << parameters << std::endl;
}

void em_algo::calculate_log_likelihood(matrix& features, matrix& sigma, ublas::matrix_column<matrix > & means)
{
    long n_objects = features.size1();
    long n_features = features.size2();
    matrix lower_triangular_sigma(n_features, n_features);
    // todo: compare to matlab
    std::cout << sigma << std::endl;
    size_t res = cholesky_decompose(sigma, lower_triangular_sigma);
    std::cout << res << std::endl;
    std::cout << lower_triangular_sigma << std::endl;
    // todo: set to zero elements < eps

    // center features
    for (int i = 0; i < n_objects; ++i)
        // todo: maybe there is a better way + make features not change
        for (int j = 0; j < n_features; ++j)
            features(i, j) = features(i, j) - means(j);

//    auto features_lower_sigma = features / lower_triangular_sigma;
//    std::cout <<  features_lower_sigma  << std::endl;
    //    ld = sum(log(diag(R)));
//    l = -0.5*( d*log(2*pi) + ld*2 + sum(xR.^2, 2) );
}

void em_algo::expectation_step(matrix& features)
{
    long n_objects = features.size1();
    long n_features = features.size2();

    matrix hidden_vars(n_objects, n_clusters);
    for (auto j = 0; j < n_clusters; ++j)
    {
        ublas::matrix_column<matrix > current_means(parameters.means, j);
        calculate_log_likelihood(features, parameters.sigma, current_means);
        // g(:, j) = w_j * N(X(:, means(j), sigmas(j)
    }
}

void em_algo::maximization_step(matrix& features)
{

}

model em_algo::process(matrix& features)
{
    int iteration = 0;
    while (iteration++ < max_iterations)
    {
        expectation_step(features);
        maximization_step(features);
    }
    return parameters;
}
