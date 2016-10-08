#include <time.h>

#include "em_algo.h"
#include "import_data.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Not enough input arguments";
        exit(1);
    }
    auto input_filename = argv[1];
    int number_of_clusters = std::stoi(argv[2]);
    auto output_filename = argv[3];

    double_matrix features;
    int_vector labels;

    import::read(input_filename, features, labels);

    em_algo algorithm = em_algo(number_of_clusters);
    algorithm.init(features);

    clock_t begin = clock();
    model optimal_model = algorithm.process(features, 50);
    std::cout << "Elapsed time is " << (clock() - begin) / CLOCKS_PER_SEC << " sec" << std::endl;

    std::cout << "optimal model\n" << optimal_model << std::endl;
    import::write(output_filename, optimal_model);
    return 0;
}
