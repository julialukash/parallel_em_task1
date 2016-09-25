#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "interface.h"
#include "em_algo.h"


void read_from_file(char* filename, matrix& features, int_vector& labels)
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

    features = matrix(n_points, n_features);
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

void write_to_file(char* filename, matrix& features, int_vector& labels)
{
    std::ofstream output_file(filename);
    if (!output_file.is_open())
    {
        std::cerr << "Incorrect output file " << filename;
        exit(1);
    }

    for (auto i = 0; i < features.size1(); ++i)
    {
        output_file << labels(i) << " ";
        for (auto j = 0 ; j < features.size2(); ++j)
            output_file << features(i, j) << " ";
        output_file << std::endl;
    }
    output_file.close();
}


int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Not enough input arguments";
        exit(1);
    }
    auto input_filename = argv[1];
    auto number_of_clusters = std::stoi(argv[2]);
    auto output_filename = argv[3];

    matrix features;
    int_vector labels;

    read_from_file(input_filename, features, labels);

    auto algorithm = em_algo(number_of_clusters);
    algorithm.init(features);
    //write_to_file(output_filename, features, labels);
    return 0;
}

