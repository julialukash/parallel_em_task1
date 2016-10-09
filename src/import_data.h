#ifndef IMPORT_DATA_H
#define IMPORT_DATA_H

#include "interface.h"
#include "model.h"

namespace import
{
long read(char* filename, double_matrix& features, int_vector& labels);

void write(char* filename, model optimal_model);
}

#endif // IMPORT_DATA_H
