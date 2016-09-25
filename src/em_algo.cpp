#include "em_algo.h"

#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/math/constants/constants.hpp>


#include "cholesky.hpp"
#include "inverse.h"


typedef boost::minstd_rand base_generator_type;

em_algo::em_algo(int number_of_clusters)
{
    n_clusters = number_of_clusters;
}

void em_algo::init(double_matrix& features)
{
    long n_objects = features.size1();
    long n_features = features.size2();

    base_generator_type generator(42);

    parameters = model();

    // init means
    parameters.means = double_matrix(n_features, n_clusters);
    parameters.sigma = double_matrix(n_features, n_features);
    parameters.sigma(0, 0) = 1;
    parameters.sigma(0, 1) = 0;
    parameters.sigma(1, 0) = 0;
    parameters.sigma(1, 1) = 2;


    for (auto i = 0; i < n_features; ++i)
    {
        // take min, max value and create random from [min, max]
        ublas::matrix_column<double_matrix > column(features, i);
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

double_vector em_algo::calculate_log_likelihood(double_matrix& features, double_matrix& sigma, ublas::matrix_column<double_matrix > & means)
{
    long n_objects = features.size1();
    long n_features = features.size2();
    double_matrix lower_triangular_sigma(n_features, n_features);
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

    // todo:check inverse
    double_matrix inverse_lower_triangular_sigma(lower_triangular_sigma.size1(), lower_triangular_sigma.size2());
    bool is_inverted = InvertMatrix(lower_triangular_sigma, inverse_lower_triangular_sigma);
    if (!is_inverted)
    {
        // todo: throw exception
    }
    // todo : check noalias http://www.boost.org/doc/libs/1_58_0/libs/numeric/ublas/doc/operations_overview.html
    auto features_lower_sigma = ublas::prod(features, inverse_lower_triangular_sigma);
    std::cout <<  features_lower_sigma.size1() << " " << features_lower_sigma.size2() << std::endl;
    auto features_lower_sigma_square = element_prod(features_lower_sigma, features_lower_sigma);

    // ld
    double ld = 0;
    for (auto i = 0; i < lower_triangular_sigma.size1(); ++i)
    {
        ld += log(lower_triangular_sigma(i, i));
    }
    double pi = boost::math::constants::pi<double>();
    double likelihood_const = -0.5 * (n_objects * log(2 * pi) + 2 * ld);
    double_vector likelihood = double_vector(n_clusters, 1.0 / n_clusters);
    for (auto i = 0; i < likelihood.size(); ++i)
        likelihood(i) += features_lower_sigma_square(i, 0) + features_lower_sigma_square(i, 1);
    return likelihood;
}

void em_algo::expectation_step(double_matrix& features)
{
    long n_objects = features.size1();
    long n_features = features.size2();

    double_matrix hidden_vars(n_objects, n_clusters);
    for (auto j = 0; j < n_clusters; ++j)
    {
        ublas::matrix_column<double_matrix > current_means(parameters.means, j);
        auto likelihood = calculate_log_likelihood(features, parameters.sigma, current_means);
        // g(:, j) = w_j * N(X(:, means(j), sigmas(j)
    }
}

void em_algo::maximization_step(double_matrix& features)
{

}

model em_algo::process(double_matrix& features)
{
    int iteration = 0;
    while (iteration++ < max_iterations)
    {
        expectation_step(features);
        maximization_step(features);
    }
    return parameters;
}
