#ifndef EM_ALGO_H
#define EM_ALGO_H

#include "interface.h"
#include "model.h"

class em_algo
{
private:
    model parameters;

    const int max_iterations = 50;
    const double tol = 1e-4;
    int n_clusters;

    void calculate_log_likelihood(double_matrix& features, double_matrix& sigma, ublas::matrix_column<double_matrix > & means);

    void expectation_step(double_matrix &features);
    void maximization_step(double_matrix& features);
public:
    em_algo(int number_of_clusters = 100);
    void init(double_matrix& features);
    model process(double_matrix& features);
};

#endif // EM_ALGO_H
