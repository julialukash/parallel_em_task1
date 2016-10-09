#include <iostream>
#include <fstream>
//#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "import_data.h"

long import::read(char* filename, double_matrix& features, int_vector& labels)
{
    std::ifstream input_file(filename);
    std::string value;
    long n_points, n_features;
    if (!input_file.is_open())
    {
        std::cerr << "Incorrect input file " << filename;
        exit(1);
    }

    input_file >> value;
    n_points = std::stol(value);

    input_file >> value;
    n_features = std::stol(value);

    features = double_matrix(n_points, n_features);
    labels = int_vector(n_points);

    std::getline(input_file, value);

    long i = 0;
    while (std::getline(input_file, value))
    {
        std::istringstream iss(value);
        iss >> labels(i);
        for (auto j = 0; j < n_features; ++j)
            iss >> features(i, j);
        ++i;
    }
    return n_points;
}

void import::write(char* filename, model optimal_model)
{
    std::ofstream output_file(filename);
    if (!output_file.is_open())
    {
        std::cerr << "Incorrect output file " << filename;
        exit(1);
    }

    int n_clusters = optimal_model.means.size2();

    for (int i = 0; i < n_clusters; ++i)
        output_file << optimal_model.means(0, i) << " " << optimal_model.means(1, i) << "\n";

    for (int i = 0; i < n_clusters; ++i)
        output_file << optimal_model.sigmas[i](0, 0) << " "
                    << optimal_model.sigmas[i](0, 1) << "\n"
                    << optimal_model.sigmas[i](1, 0) << " "
                    << optimal_model.sigmas[i](1, 1) << "\n";

    output_file.close();
}

void import::write_performance(char* filename, int n_threads, long n_objects, double time)
{
    std::ofstream output_file(filename, std::ofstream::out | std::ofstream::app);
    if (!output_file.is_open())
    {
        std::cerr << "Incorrect output file " << filename;
        exit(1);
    }

    output_file << n_threads << " " << n_objects << " " << time << "\n";
    output_file.close();
}
