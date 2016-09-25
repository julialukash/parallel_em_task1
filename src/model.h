#ifndef MODEL_H
#define MODEL_H

#include "interface.h"

class model
{
public:
    matrix means;
    double_vector weights;

    model();

    friend std::ostream& operator<<(std::ostream& os, const model& model);
};

#endif // MODEL_H
