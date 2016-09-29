#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

using namespace std;

const double tol = 1e-6;

template<class T>
double InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
    if (input.size1() != 2 || input.size2() != 2)
	{
        std::cerr << "Matrix's size is incorrect\n";
        	exit(1);
	}

    double det = input(0, 0) * input(1, 1) - input(0, 1) * input(1, 0);
    if (det != 0)
    {
        inverse = matrix<T>(input.size1(), input.size2());
        inverse(0, 0) = input(1, 1);
        inverse(1, 1) = input(0, 0);
        inverse(0, 1) = -input(0, 1);
        inverse(1, 0) = -input(1, 0);
    }
    inverse = inverse / det;
    for (size_t i = 0; i < inverse.size1(); ++i)
        for (size_t j = 0; j < inverse.size2(); ++j)
            if (inverse(i, j) < tol)
                inverse(i, j) = 0;
	return det;
}
