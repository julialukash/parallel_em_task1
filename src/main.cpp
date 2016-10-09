#include <time.h>

#include "em_algo.h"
#include "import_data.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cerr << "Not enough input arguments";
        exit(1);
    }
    auto input_filename = argv[1];
    auto number_of_clusters = std::stoi(argv[2]);
    auto output_filename = argv[3];
    auto number_of_threads = std::stoi(argv[4]);

    double_matrix features;
    int_vector labels;

    auto number_of_points = import::read(input_filename, features, labels);

    em_algo algorithm = em_algo(number_of_clusters);
    algorithm.init(features);

    auto begin = omp_get_wtime();

    model optimal_model = algorithm.process(features, number_of_threads, 50);
    auto time_elapsed = omp_get_wtime() - begin;
    std::cout << "n_threads =  " << number_of_threads << std::endl;
    std::cout << "Elapsed time is " << time_elapsed << " sec" << std::endl;
    std::cout << number_of_threads << " " << number_of_points << " " << time_elapsed << std::endl;

<<<<<<< HEAD
    std::cout << "optimal model\n" << optimal_model << std::endl;
=======
>>>>>>> origin/master
    import::write(output_filename, optimal_model);
    return 0;
}
