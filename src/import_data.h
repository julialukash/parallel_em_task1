#ifndef IMPORT_DATA_H
#define IMPORT_DATA_H

#include "interface.h"

namespace import
{
void read(char* filename, double_matrix& features, int_vector& labels);

void write(char* filename, double_matrix& features, int_vector& labels);
}

#endif // IMPORT_DATA_H
