#ifndef IZ_1_MATRIX_H
#define IZ_1_MATRIX_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "input.h"

typedef struct matrix{
    int **matrix;
    size_t num_rows;
    size_t num_cols;
} matrix;

matrix *create_matrix();
bool allocate_matrix(matrix *matr);
bool init_matrix(matrix *mat, size_t num_rows, size_t num_cols);
void free_matrix(matrix *matr);
void print_matrix(matrix *matr);
#endif //IZ_1_MATRIX_H
