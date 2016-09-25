#pragma once
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

typedef boost::numeric::ublas::matrix<double> matrix;
typedef boost::numeric::ublas::vector<int> vector;

void read_from_file(char* filename, matrix& input_matrix, vector& labels)
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

    input_matrix = matrix(n_points, n_features);
    labels = vector(n_points);

    std::getline(input_file, value);

    long i = 0;
    while (std::getline(input_file, value))
    {
        std::istringstream iss(value);
        iss >> labels(i);
        for (auto j = 0; j < n_features; ++j)
            iss >> input_matrix(i, j);
        ++i;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Not enough input arguments";
        exit(1);
    }
    auto filename = argv[1];
    matrix features;
    vector labels;
    read_from_file(filename, features, labels);
    for (auto i = 0; i < features.size1(); ++i)
    {
        for (auto j = 0 ; j < features.size2(); ++j)
            std::cout << features(i, j) << " ";
        std::cout << std::endl;
    }

    return 0;
}

