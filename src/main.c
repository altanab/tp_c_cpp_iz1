#include <stdio.h>
#include "non_zero_matrix.h"
#include "matrix.h"


int main() {
    matrix *matr = create_matrix();
    printf("Input matrix:\n");
    print_matrix(matr);
    non_zero_matrix *m = delete_zeros(matr->matrix, matr->num_rows, matr->num_cols);
    if(m == NULL){
        printf("Error");
        free_matrix(matr);
        return 1;
    }
    print_non_zero_matrix(m);
    free_non_zero_matrix(m);
    free_matrix(matr);
    return 0;
}
