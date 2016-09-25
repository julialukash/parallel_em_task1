#ifndef MODEL_H
#define MODEL_H

#include "interface.h"

struct model
{
    double_matrix means;
    double_matrix sigma;
    double_vector weights;

    model() {};

    friend std::ostream& operator<<(std::ostream& os, const model& model);
};

#endif // MODEL_H
