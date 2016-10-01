#include <time.h>

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/algorithm/minmax_element.hpp>
#include <boost/array.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <omp.h>

namespace ublas = boost::numeric::ublas;

typedef boost::minstd_rand base_generator_type;

typedef ublas::matrix<double> double_matrix;
typedef std::vector<double> double_vector;
typedef ublas::vector<int> int_vector;

typedef ublas::matrix_row<double_matrix > double_matrix_row;
typedef ublas::matrix_column<double_matrix > double_matrix_column;

#include <stdio.h>
//int main() {
////    #pragma omp parallel
////    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
////    long n = 100000000;
////    double_vector src(n, 0.0);
////    double_vector dst(n, 0.0);

////    base_generator_type generator(198);
////    boost::uniform_real<> uni_dist(1, 1000000);
////    boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(generator, uni_dist);
////    for (int i = 0; i < n; ++i)
////        src[i] = uni();


////    double value, sum = 0;
//    long number = 100000;
////    omp_set_num_threads(4);
//    clock_t begin = clock();
//    double fac = 1;
//    #pragma omp parallel for reduction(*:fac)
//    for(int n=2; n<=number; ++n)
//       fac *= n;
//    std::cout << "Elapsed time is " << (clock() - begin)  << " sec" << std::endl;
//}

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{

    omp_set_num_threads(8);

    //Below code will be run once for each processor (there are two)
    #pragma omp parallel
    {
        cout << omp_get_thread_num() << endl; //this should output 1 and 0, in random order
    }


    long k = 100000;
    long n_iterations = 10000;

    //The parallel example:
    vector <double> a(k,0);

    clock_t start = omp_get_wtime();
#pragma omp parallel for  shared(a)
    for (int i=0; i < k; i++)
    {
        double StartVal=i;

        for (int j=0; j<n_iterations; ++j)
            a[i]=(StartVal + log(exp(exp((double) i))));
    }

    cout<< "Time: " << ( (double) ( omp_get_wtime() - start )) <<endl;

    //The serial example:
    start = omp_get_wtime();

    for (int i=0; i < k; i++)
    {
        double StartVal=i;

        for (int j=0; j<n_iterations; ++j)
            a[i]=(StartVal + log(exp(exp((double) i))));
    }

    cout<< "Time: " << ( (double) ( omp_get_wtime() - start )) <<endl;

    return 0;
}
