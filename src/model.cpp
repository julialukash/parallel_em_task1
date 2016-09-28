#include "model.h"

std::ostream& operator<<(std::ostream& os, const model& model)
{
    os << "weights: \n" << model.weights  << std::endl;
    os << "means: \n" << model.means << std::endl;
    os << "sigma: \n";
    for (auto k = 0; k < model.sigmas.size(); ++k) {
        for (auto i = 0; i < model.sigmas[0].size1(); ++i) {
            for (auto j = 0; j < model.sigmas[0].size2(); ++j)
                os << model.sigmas[k](i, j) << " ";
            os << "\n";
        }
        os << "\n";
    }
    return os;
}
