#include "matrix.h"


matrix *create_matrix(){
    matrix *m = (matrix *)malloc(sizeof(matrix));
    init_matrix(m, 0, 0);
    while(m->num_rows == 0){
        printf("Enter number of rows: ");
        m->num_rows = input_int();
    }
    while(m->num_cols == 0){
        printf("Enter number of columns: ");
        m->num_cols = input_int();
    }
    if(!allocate_matrix(m)){
        free_matrix(m);
        return NULL;
    }
    printf("Enter elements one by one:\n");
    for(int i = 0; i < m->num_rows; ++i){
        for(int j = 0; j < m->num_cols; ++j){
            m->matrix[i][j] = input_int();
        }
    }
    return m;
}

bool allocate_matrix(matrix *matr){
    matr->matrix = (int **)malloc(matr->num_rows * sizeof(int *));
    if(matr->matrix == NULL){
        printf("Cannot allocate memory\n");
        return false;
    }
    for(int i = 0; i < matr->num_rows; ++i){
        matr->matrix[i] = (int *)malloc(matr->num_cols * sizeof(int));
        if(matr->matrix[i] == NULL){
            printf("Cannot allocate memory\n");
            for(int k = 0; k < i; ++k){
                free(matr->matrix[k]);
            }
            free(matr->matrix);
            return false;
        }
    }
    return true;

}
bool init_matrix(matrix *matr, size_t num_rows, size_t num_cols){
    matr->matrix = NULL;
    matr->num_rows = num_rows;
    matr->num_cols = num_cols;
}
void free_matrix(matrix *matr){
    if(matr == NULL){
        return;
    }
    if(matr->matrix != NULL) {
        for (int i = 0; i < matr->num_rows; ++i) {
            free(matr->matrix[i]);
        }
        free(matr->matrix);
    }
    free(matr);
}

void print_matrix(matrix *matr){
    if(matr == NULL || matr->matrix == NULL){
        return;
    }
    for(int i = 0; i < matr->num_rows; ++i){
        for(int j = 0; j < matr->num_cols; ++j) {
            printf("%d ", matr->matrix[i][j]);
        }
        printf("\n");
    }
}