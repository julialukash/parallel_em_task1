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
        double_matrix_column column(features, i);
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
        parameters.sigmas.push_back(double_matrix(parameters.n_features, parameters.n_features));

    boost::uniform_real<> uni_01_dist(0, 1);
    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni_01(generator, uni_01_dist);

    for (auto k = 0; k < n_clusters; ++k)
        for (auto i = 0; i < parameters.n_features; ++i)
            for (auto j = 0; j < parameters.n_features; ++j)
                if (i != j)
                    parameters.sigmas[k](i, j) = 0;
                else
                    parameters.sigmas[k](i, j) = uni_01();

    std::cout << parameters << std::endl;
}

void em_algo::expectation_step(double_matrix& features)
{
    long n_objects = features.size1();
    int n_clusters = parameters.sigmas.size();

    double pi = boost::math::constants::pi<double>();
    // precalculate inverse matrices and dets
    std::vector<double_matrix> sigmas_inverted(n_clusters);
    std::vector<double> norm_distribution_denominator(n_clusters);
    for (size_t i = 0; i < n_clusters; ++i)
    {        
        double_matrix sigma_inverted(parameters.sigmas[i].size1(), parameters.sigmas[i].size2());
        double det = InvertMatrix(parameters.sigmas[i], sigma_inverted);
        if (det == 0)
        {
            std::cerr << "Matrix can not be inverted\n";
            exit(1);
        }
        norm_distribution_denominator[i] = sqrt(pow(2 * pi, n_objects) * det);
        std::cout << parameters.sigmas[i] << std::endl;
        std::cout << sigma_inverted << std::endl;
        sigmas_inverted[i] = sigma_inverted;
    }

    hidden_vars = double_matrix(n_objects, n_clusters);
    for (auto i = 0; i < n_objects; ++i)
    {
        double_matrix_row x(features, i);
        for (auto j = 0; j < n_clusters; ++j)
        {
            double_matrix_column current_means(parameters.means, j);

            std::cout << x << std::endl;
            std::cout << current_means << std::endl;

            double_vector x_centered = x - current_means;

            std::cout << x_centered << std::endl;

            double_vector prod1 = prod(x_centered, sigmas_inverted[i]);

            std::cout << prod1 << std::endl;

            double exp_power = inner_prod(prod1, x_centered);

            std::cout << exp_power << std::endl;
            exp_power = -0.5 * exp_power;
            hidden_vars(i, j) = parameters.weights(j) * norm_distribution_denominator[j] * exp(exp_power);
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
