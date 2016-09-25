#include <iostream>
#include <fstream>
//#include <memory>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "import_data.h"

void import::read(char* filename, double_matrix& features, int_vector& labels)
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
}

void import::write(char* filename, double_matrix& features, int_vector& labels)
{
    std::ofstream output_file(filename);
    if (!output_file.is_open())
    {
        std::cerr << "Incorrect output file " << filename;
        exit(1);
    }

    for (size_t i = 0; i < features.size1(); ++i)
    {
        output_file << labels(i) << " ";
        for (size_t j = 0 ; j < features.size2(); ++j)
            output_file << features(i, j) << " ";
        output_file << std::endl;
    }
    output_file.close();
}
