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

//initialize struct
non_zero_matrix *init_non_zero_matrix(size_t num_vectors);
//changes size of inner matrix to new_size
//assign num_vectors to new_size
bool change_size_non_zero_matrix(non_zero_matrix *non_zero_m, size_t new_size);
void free_non_zero_matrix(non_zero_matrix *non_zero_m);
void print_non_zero_matrix(non_zero_matrix *non_zero_m);
//creates new structure from input matrix without zero elements
//returns created structure
non_zero_matrix *delete_zeros(int **input_matrix, size_t num_rows, size_t num_cols);
//checks if structs are equal
bool is_equal(non_zero_matrix *non_zero_m_1, non_zero_matrix *non_zero_m_2);
#endif //IZ_1_NON_ZERO_MATRIX_H
