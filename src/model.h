#ifndef MODEL_H
#define MODEL_H

#include "interface.h"
#include <vector>

struct model
{
    double_matrix means;
    std::vector<double_matrix> sigmas;
    double_vector weights;

    model() {};

    friend std::ostream& operator<<(std::ostream& os, const model& model);
};

#endif // MODEL_H
