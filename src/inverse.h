#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

using namespace std;

template<class T>
int InvertMatrix(const matrix<T>& input, matrix<T>& inverse)
{
    if (input.size1() != 2 || input.size2() != 2)
	{
        std::cerr << "Matrix's size is incorrect\n";
        	exit(1);
	}

    auto det = input(0, 0) * input(1, 1) - input(0, 1) * input(1, 0);
    if (det != 0)
    {
        inverse = matrix<T>(input.size1(), input.size2());
        inverse(0, 0) = input(1, 1);
        inverse(1, 1) = input(0, 0);
        inverse(0, 1) = -input(0, 1);
        inverse(1, 0) = -input(1, 0);
    }

	return det;
}
