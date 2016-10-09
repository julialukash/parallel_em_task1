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

    int retval;
    PAPI_dmem_info_t dmem;
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
        exit(1);
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT)
        exit(1);
    PAPI_get_dmem_info(&dmem);

    printf("Mem Size:\t\t%lld\n",dmem.size);
    printf("Mem Resident:\t\t%lld\n",dmem.resident);
    printf("Mem High Water Mark:\t%lld\n",dmem.high_water_mark);
    printf("Mem Shared:\t\t%lld\n",dmem.shared);
    printf("Mem Text:\t\t%lld\n",dmem.text);
    printf("Mem Library:\t\t%lld\n",dmem.library);
    printf("Mem Heap:\t\t%lld\n",dmem.heap);
    printf("Mem Locked:\t\t%lld\n",dmem.locked);
    printf("Mem Stack:\t\t%lld\n",dmem.stack);
    printf("Mem Pagesize:\t\t%lld\n",dmem.pagesize);

    auto begin = omp_get_wtime();

    model optimal_model = algorithm.process(features, 50);
    std::cout << "Elapsed time is " << (omp_get_wtime() - begin) << " sec" << std::endl;

    PAPI_get_dmem_info(&dmem);
    printf("Mem Size:\t\t%lld\n",dmem.size);
    printf("Mem Resident:\t\t%lld\n",dmem.resident);
    printf("Mem High Water Mark:\t%lld\n",dmem.high_water_mark);
    printf("Mem Shared:\t\t%lld\n",dmem.shared);
    printf("Mem Text:\t\t%lld\n",dmem.text);
    printf("Mem Library:\t\t%lld\n",dmem.library);
    printf("Mem Heap:\t\t%lld\n",dmem.heap);
    printf("Mem Locked:\t\t%lld\n",dmem.locked);
    printf("Mem Stack:\t\t%lld\n",dmem.stack);
    printf("Mem Pagesize:\t\t%lld\n",dmem.pagesize);

    //std::cout << "optimal model\n" << optimal_model << std::endl;
    import::write(output_filename, optimal_model);
    return 0;
}
