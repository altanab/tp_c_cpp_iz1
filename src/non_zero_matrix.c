#include "non_zero_matrix.h"

non_zero_matrix *init_non_zero_matrix(size_t num_vectors){
    if(num_vectors == 0){
        return NULL;
    }
    non_zero_matrix *non_zero_m = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    if(non_zero_m == NULL){
        printf("Cannot allocate memory\n");
        return NULL;
    }
    non_zero_m->num_vectors = 0;
    if(!change_size_non_zero_matrix(non_zero_m, num_vectors)){
        free(non_zero_m);
        return NULL;
    }
    for(size_t i = 0; i < num_vectors; ++i){
        non_zero_m->matrix[i] = NULL;
    }
    return non_zero_m;
}

bool change_size_non_zero_matrix(non_zero_matrix *non_zero_m, size_t new_size){
    if(non_zero_m == NULL){
        return false;
    }
    if(non_zero_m->num_vectors == new_size){
        return true;
    }
    if(new_size == 0){
        free_non_zero_matrix(non_zero_m);
        return true;
    }
    int **temp = (int **)realloc(non_zero_m->matrix, new_size * sizeof(int *));
    if(temp == NULL){
        printf("Cannot allocate memory\n");
        return false;
    }
    non_zero_m->matrix = temp;
    non_zero_m->num_vectors = new_size;
    return true;
}

void free_non_zero_matrix(non_zero_matrix *non_zero_m){
    if(non_zero_m == NULL){
        return;
    }
    if(non_zero_m->matrix != NULL) {
        for (size_t i = 0; i < non_zero_m->num_vectors; ++i) {
            free(non_zero_m->matrix[i]);
        }
        free(non_zero_m->matrix);
    }
    free(non_zero_m);
}

void print_non_zero_matrix(non_zero_matrix *non_zero_m){
    if(non_zero_m->matrix == NULL || non_zero_m->num_vectors == 0){
        printf("Empty structure\n");
        return;
    }
    printf("Printing structure:\n");
    for(size_t i = 0; i < non_zero_m->num_vectors; ++i){
        if(non_zero_m->matrix[i] == NULL){
            return;
        }
        size_t j = 0;
        while(non_zero_m->matrix[i][j] != 0) {
            printf("%d ", non_zero_m->matrix[i][j]);
            ++j;
        }
        printf("\n");
    }
}

non_zero_matrix *delete_zeros(int **input_matrix, size_t num_rows, size_t num_cols){
    non_zero_matrix *non_zero_m = init_non_zero_matrix(num_rows);
    if(non_zero_m == NULL){
        return NULL;
    }
    size_t num_non_zero_rows = 0;
    for(size_t i = 0; i < num_rows; ++i){
        int *non_zero_vector = (int *)calloc(num_cols + 1, sizeof(int));
        if(non_zero_vector == NULL){
            printf("Cannot allocate memory\n");
            free_non_zero_matrix(non_zero_m);
            return NULL;
        }
        size_t num_non_zero_cols = 0;
        for(size_t j = 0; j < num_cols; ++j){
            if(input_matrix[i][j] != 0){
                non_zero_vector[num_non_zero_cols] = input_matrix[i][j];
                ++num_non_zero_cols;
            }
        }
        if(num_non_zero_cols != 0){
            if(num_non_zero_cols != num_cols) {
                int *temp = (int *)realloc(non_zero_vector, (num_non_zero_cols + 1) * sizeof(int));
                if (temp == NULL) {
                    printf("Cannot realloc memory\n");
                    free(non_zero_vector);
                    free_non_zero_matrix(non_zero_m);
                    return NULL;
                }
                non_zero_vector = temp;
            }
            non_zero_m->matrix[num_non_zero_rows] = non_zero_vector;
            ++num_non_zero_rows;
        } else{
            free(non_zero_vector);
        }
    }
    if(!change_size_non_zero_matrix(non_zero_m, num_non_zero_rows)){
        free_non_zero_matrix(non_zero_m);
        return NULL;
    }
    if(num_non_zero_rows == 0){
        return NULL;
    }
    return non_zero_m;
}

bool is_equal(non_zero_matrix *non_zero_m_1, non_zero_matrix *non_zero_m_2){
    if(non_zero_m_1 == NULL || non_zero_m_2 == NULL){
         if(non_zero_m_1 == NULL && non_zero_m_2 == NULL){
             return true;
         }
         return false;
    }
    if(non_zero_m_1->num_vectors != non_zero_m_2->num_vectors){
        return false;
    }
    for(size_t i = 0; i < non_zero_m_1->num_vectors; ++i){
        size_t j = 0;
        while(non_zero_m_1->matrix[i][j] != 0 && non_zero_m_2->matrix[i][j] != 0){
            if(non_zero_m_1->matrix[i][j] != non_zero_m_2->matrix[i][j]){
                return false;
            }
            ++j;
        }
        if(non_zero_m_1->matrix[i][j] != 0 || non_zero_m_2->matrix[i][j] != 0){
            return false;
        }
    }
    return true;
}
