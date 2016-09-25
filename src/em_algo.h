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

    void calculate_log_likelihood(matrix& features, matrix& sigma, ublas::matrix_column<matrix > & means);

    void expectation_step(matrix &features);
    void maximization_step(matrix& features);
public:
    em_algo(int number_of_clusters = 100);
    void init(matrix& features);
    model process(matrix& features);
};

#endif // EM_ALGO_H
