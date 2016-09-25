#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/random/normal_distribution.hpp>

#include <omp.h>

typedef boost::numeric::ublas::matrix<double> matrix;
typedef boost::numeric::ublas::vector<int> int_vector;
typedef boost::numeric::ublas::vector<double> double_vector;

#endif // INTERFACE_H