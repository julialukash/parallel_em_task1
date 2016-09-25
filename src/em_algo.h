#ifndef EM_ALGO_H
#define EM_ALGO_H

#include "interface.h"
#include "model.h"

class em_algo
{
private:
    const int max_iterations = 50;
    const double tol = 1e-4;
    int n_clusters;
public:
    em_algo(int number_of_clusters);
    model init(matrix& features);
    void expectation_step();
    void maximization_step();
};

#endif // EM_ALGO_H
