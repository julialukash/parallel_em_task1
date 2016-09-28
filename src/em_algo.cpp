#include "em_algo.h"

#include <boost/algorithm/minmax_element.hpp>
#include <boost/array.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "cholesky.hpp"
#include "inverse.h"

typedef boost::minstd_rand base_generator_type;

em_algo::em_algo(int number_of_clusters)
{
    n_clusters = number_of_clusters;
}

void em_algo::init(double_matrix& features)
{
    base_generator_type generator(42);

    parameters = model();
    parameters.n_features = features.size2();

    // init weights
    parameters.weights = double_vector(n_clusters, 1.0 / n_clusters);

    // init means
    parameters.means = double_matrix(parameters.n_features, n_clusters);
    for (int i = 0; i < parameters.n_features; ++i)
    {
        // take min, max value and create random from [min, max]
        ublas::matrix_column<double_matrix > column(features, i);
        auto min_max_values = boost::minmax_element(column.begin(), column.end());

        boost::uniform_real<> uni_dist(*min_max_values.first, *min_max_values.second);
        boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);
        for (auto j = 0; j < n_clusters; j++)
        {
            parameters.means(i, j) = uni();
        }
    }

    std::cout << "create sigma\n";
    for (auto i = 0; i < n_clusters; ++i)
        parameters.sigma.push_back(double_matrix(parameters.n_features, parameters.n_features));

    boost::uniform_real<> uni_01_dist(0, 1);
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni_01(generator, uni_01_dist);

    for (auto k = 0; k < n_clusters; ++k)
        for (auto i = 0; i < parameters.n_features; ++i)
            for (auto j = 0; j < parameters.n_features; ++j)
                if (i != j)
                    parameters.sigma[k](i, j) = 0;
                else
                    parameters.sigma[k](i, j) = uni_01();

    std::cout << parameters << std::endl;
}

double_vector em_algo::calculate_log_likelihood(double_matrix& features, double_matrix& sigma, ublas::matrix_column<double_matrix > & means)
{
    long n_objects = features.size1();

    double_matrix lower_triangular_sigma(parameters.n_features, parameters.n_features);
    // todo: compare to matlab
    size_t res = cholesky_decompose(sigma, lower_triangular_sigma);
    std::cout << res << std::endl;
    std::cout << lower_triangular_sigma << std::endl;

    // computing error to zero
    for (size_t i = 0; i < lower_triangular_sigma.size1(); ++i)
        for (size_t j = 0; j < lower_triangular_sigma.size2(); ++j)
            if (lower_triangular_sigma(i, j) < tol)
                lower_triangular_sigma(i, j) = 0;

    // center features
    for (int i = 0; i < n_objects; ++i)
        // todo: maybe there is a better way + make features not change
        for (int j = 0; j < parameters.n_features; ++j)
            features(i, j) = features(i, j) - means(j);

    // todo:check inverse
    double_matrix inverse_lower_triangular_sigma(lower_triangular_sigma.size1(), lower_triangular_sigma.size2());
    bool is_inverted = InvertMatrix(lower_triangular_sigma, inverse_lower_triangular_sigma);
    if (!is_inverted)
    {
        std::cerr << "Matrix can not be inverted\n";
        exit(1);
    }
    // todo : check noalias http://www.boost.org/doc/libs/1_58_0/libs/numeric/ublas/doc/operations_overview.html
    auto features_lower_sigma = ublas::prod(features, inverse_lower_triangular_sigma);
    //std::cout <<  features_lower_sigma.size1() << " " << features_lower_sigma.size2() << std::endl;
    auto features_lower_sigma_square = element_prod(features_lower_sigma, features_lower_sigma);

    // ld
    double ld = 0;
    for (size_t i = 0; i < lower_triangular_sigma.size1(); ++i)
    {
        ld += log(lower_triangular_sigma(i, i));
    }
    double pi = boost::math::constants::pi<double>();
    double likelihood_const = -0.5 * (n_objects * log(2 * pi) + 2 * ld);
    double_vector log_likelihood = double_vector(n_objects, likelihood_const);
    for (size_t i = 0; i < log_likelihood.size(); ++i)
        log_likelihood(i) += features_lower_sigma_square(i, 0) + features_lower_sigma_square(i, 1);
    return log_likelihood;
}

void em_algo::expectation_step(double_matrix& features)
{
    long n_objects = features.size1();

    hidden_vars = double_matrix(n_objects, n_clusters);
    for (auto j = 0; j < n_clusters; ++j)
    {
        ublas::matrix_column<double_matrix > current_means(parameters.means, j);
        auto log_likelihood = calculate_log_likelihood(features, parameters.sigma[j], current_means);

        for (size_t i = 0; i < log_likelihood.size(); ++i)
        {
//            std::cout << "ll = " << log_likelihood(i) << " exp = " << exp(log_likelihood(i)) << " , w = " << parameters.weights(j) << std::endl;
            hidden_vars(i, j) = parameters.weights(j) * exp(log_likelihood(i));
//            std::cout << "hv = " << hidden_vars(i, j) << std::endl;
        }
    }
//    std::cout << hidden_vars << std::endl;
}

void em_algo::maximization_step(double_matrix& features)
{
    for (int j = 0; j < n_clusters; ++j) {

    }
}

model em_algo::process(double_matrix& features, int max_iterations)
{
    int iteration = 0;
    while (iteration++ < max_iterations)
    {
        expectation_step(features);
        maximization_step(features);
    }
    return parameters;
}
