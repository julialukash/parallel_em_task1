#include "em_algo.h"

#include <boost/algorithm/minmax_element.hpp>
#include <boost/array.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include "inverse.h"

#define PARALLEL 1

typedef boost::minstd_rand base_generator_type;

em_algo::em_algo(int number_of_clusters)
{
    n_clusters = number_of_clusters;
}

void em_algo::init(double_matrix& features)
{
    base_generator_type generator(198);

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

    // init sigmas
    for (int k = 0; k < n_clusters; ++k)
    {
        parameters.sigmas.push_back(double_matrix(parameters.n_features, parameters.n_features, 0.0));
        for (int i = 0; i < parameters.n_features; ++i)
            parameters.sigmas[k](i, i) = 1;
    }
}

double_vector em_algo::expectation_step(double_matrix& features)
{
    long n_objects = features.size1();
    int n_clusters = parameters.sigmas.size();
    double pi = boost::math::constants::pi<double>();

    // precalculate inverse matrices and dets
    std::vector<double_matrix> sigmas_inverted(n_clusters);
    std::vector<double> norm_distribution_denominator(n_clusters);

    for (int i = 0; i < n_clusters; ++i)
    {
        double_matrix sigma_inverted(parameters.sigmas[i].size1(), parameters.sigmas[i].size2());
        double det = InvertMatrix(parameters.sigmas[i], sigma_inverted);
        if (det == 0)
        {
            std::cerr << "Matrix can not be inverted\n";
            exit(1);
        }
        norm_distribution_denominator[i] = sqrt(pow(2 * pi, parameters.n_features) * det);
        sigmas_inverted[i] = sigma_inverted;
    }

    hidden_vars = double_matrix(n_objects, n_clusters);
    double_vector log_likelihood(n_objects, 0);

    auto means = parameters.means;
    auto w = parameters.weights;
#ifdef PARALLEL
    #pragma omp parallel for //firstprivate(sigmas_inverted, means, w, norm_distribution_denominator)
#endif
    for (auto i = 0; i < n_objects; ++i)
    {
        double_matrix_row x(features, i);
        double norm_value = 0;
        for (auto j = 0; j < n_clusters; ++j)
        {
            double_matrix_column current_means(means, j);
            double_vector x_centered = x - current_means;

            double exp_power = -0.5 * inner_prod(prod(x_centered, sigmas_inverted[j]), x_centered);
            hidden_vars(i, j) = w(j) * exp(exp_power) / norm_distribution_denominator[j];

            norm_value += hidden_vars(i, j);
        }
        double_matrix_row hidden_vars_row(hidden_vars, i);
        if (norm_value != 0)
        {
            hidden_vars_row = hidden_vars_row / norm_value;
            log_likelihood(i) = log(inner_prod(hidden_vars_row, parameters.weights));
        }
    }
    return log_likelihood;
}

void em_algo::maximization_step(double_matrix& features)
{
    int n_objects = features.size1();

    double_vector w = double_vector(n_clusters, 0.0);
    double_matrix means = double_matrix(parameters.n_features, n_clusters, 0.0);
    std::vector<double_matrix> sigmas;
    for (int j = 0; j < n_clusters; ++j)
        sigmas.push_back(double_matrix(parameters.n_features, parameters.n_features, 0.0));

#ifdef PARALLEL
    #pragma omp parallel for
#endif
    for (int i = 0; i < n_objects; ++i)
    {
        double_matrix_row x_i = row(features, i);

        for (int j = 0; j < n_clusters; ++j)
        {
            double g = hidden_vars(i, j);
            w(j) += g;

            double_matrix_column single_mean = column(means, j);

            single_mean += g * x_i;

            double_vector x_centered = x_i - column(parameters.means, j);
            for (int k = 0; k < parameters.n_features; ++k)
                for (int l = 0; l < parameters.n_features; ++l)
                    sigmas[j](k, l) = sigmas[j](k, l) + g * x_centered(k) * x_centered(l);
        }
    }
    // update weights
    parameters.weights = w / n_objects;

    for (int j = 0; j < n_clusters; ++j) {
        double weight = w(j);
        // update means
        double_matrix_column means_old = column(parameters.means, j);
        double_matrix_column means_new = column(means, j);
        means_old = means_new / weight;

        // update sigmas
        parameters.sigmas[j] = sigmas[j] / weight;
        for (int k = 0; k < parameters.n_features; ++k)
            parameters.sigmas[j](k, k) = parameters.sigmas[j](k, k) + tol;
    }
}

bool em_algo::is_likelihood_stabilized(double_vector likelihood, double_vector previous_likelihood)
{
    double likelihood_diff = sum(likelihood) - sum(previous_likelihood);
    return fabs(likelihood_diff) < tol;
}

model em_algo::process(double_matrix& features, int max_iterations)
{
#ifdef PARALLEL
    omp_set_num_threads(2);
#endif
    int iteration = 0;
    double_vector likelihood, previous_likelihood;
    while (iteration++ < max_iterations && (iteration <= 2 || !is_likelihood_stabilized(likelihood, previous_likelihood)))
    {
//        std::cout << "iteration = " << iteration << ", likelihood sum = " << sum(likelihood) << std::endl;
        previous_likelihood = likelihood;
        likelihood = expectation_step(features);
        maximization_step(features);
    }
    return parameters;
}
