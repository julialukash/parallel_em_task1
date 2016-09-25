#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/normal_distribution.hpp>

#include "em_algo.h"

typedef boost::numeric::ublas::matrix<double> matrix;
typedef boost::numeric::ublas::vector<int> vector;

void read_from_file(char* filename, matrix& features, vector& labels)
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
    labels = vector(n_points);

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

void write_to_file(char* filename, matrix& features, vector& labels)
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
    vector labels;
    read_from_file(input_filename, features, labels);
    for (auto i = 0; i < features.size1(); ++i)
    {
        for (auto j = 0 ; j < features.size2(); ++j)
            std::cout << features(i, j) << " ";
        std::cout << std::endl;
    }
    auto em_algorithm = em_algo(number_of_clusters);
    write_to_file(output_filename, features, labels);
    return 0;
}

