#ifndef IZ_1_NON_ZERO_MATRIX_H
#define IZ_1_NON_ZERO_MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct non_zero_matrix{
    int **matrix;
    size_t num_vectors;
} non_zero_matrix;

non_zero_matrix *init_non_zero_matrix(size_t num_vectors);
bool change_size_non_zero_matrix(non_zero_matrix *non_zero_m, size_t new_size);
void free_non_zero_matrix(non_zero_matrix *non_zero_m);
void print_non_zero_matrix(non_zero_matrix *non_zero_m);
non_zero_matrix *delete_zeros(int **input_matrix, size_t num_rows, size_t num_cols);

#endif //IZ_1_NON_ZERO_MATRIX_H
