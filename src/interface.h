#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

typedef ublas::matrix<double> double_matrix;
typedef ublas::vector<double> double_vector;
typedef ublas::vector<int> int_vector;

typedef ublas::matrix_row<double_matrix > double_matrix_row;
typedef ublas::matrix_column<double_matrix > double_matrix_column;

//#include <omp.h>

#endif // INTERFACE_H
