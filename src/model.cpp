#include "model.h"

model::model()
{
}

std::ostream& operator<<(std::ostream& os, const model& model)
{
    os << "means: \n" << model.means << std::endl;
    os << "weights: \n" << model.weights  << std::endl;
    return os;
}
