#include "model.h"

std::ostream& operator<<(std::ostream& os, const model& model)
{
    os << "means: \n" << model.means << std::endl;
    os << "sigma: \n" << model.sigma << std::endl;
    os << "weights: \n" << model.weights  << std::endl;
    return os;
}
