#include <gtest/gtest.h>

extern "C" {
#include "non_zero_matrix.h"
#include "matrix.h"
}

const size_t num_rows = 4;
const size_t num_cols = 4;

TEST(test, TestIsEqual){
    int input_matrix_1[num_rows][num_cols] = {
            {1, 2, 3, 0},
            {34, -5, 6, 0},
            {23, 56, 12, 0},
            {12, 45, 0, 0}
    };
    int input_matrix_2[num_rows][num_cols] = {
            {2, 2, 3, 0},
            {0, -5, 6, 0},
            {23, 56, 12, 0},
            {12, 0, 0, 0}
    };
    int **matrix_1 = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        size_t j = 0;
        while(input_matrix_1[i][j] != 0){
            ++j;
        }
        matrix_1[i] = (int *)malloc((j + 1) * sizeof(int));
        for(size_t k = 0; k < j + 1; ++k){
            matrix_1[i][k] = input_matrix_1[i][k];
        }
    }
    int **matrix_equal_1 = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        size_t j = 0;
        while(input_matrix_1[i][j] != 0){
            ++j;
        }
        matrix_equal_1[i] = (int *)malloc((j + 1) * sizeof(int));
        for(size_t k = 0; k < j + 1; ++k){
            matrix_equal_1[i][k] = input_matrix_1[i][k];
        }
    }
    int **matrix_2 = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        size_t j = 0;
        while(input_matrix_2[i][j] != 0){
            ++j;
        }
        matrix_2[i] = (int *)malloc((j + 1) * sizeof(int));
        for(size_t k = 0; k < j + 1; ++k){
            matrix_2[i][k] = input_matrix_2[i][k];
        }
    }
    non_zero_matrix *struct_1 = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    struct_1->matrix = matrix_1;
    struct_1->num_vectors = num_rows;

    non_zero_matrix *struct_equal_1 = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    struct_equal_1->matrix = matrix_equal_1;
    struct_equal_1->num_vectors = num_rows;

    non_zero_matrix *struct_2 = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    struct_2->matrix = matrix_2;
    struct_2->num_vectors = num_rows;

    EXPECT_TRUE(is_equal(struct_1, struct_1));
    EXPECT_TRUE(is_equal(struct_1, struct_equal_1));
    EXPECT_FALSE(is_equal(struct_1, struct_2));

    free_non_zero_matrix(struct_1);
    free_non_zero_matrix(struct_equal_1);
    free_non_zero_matrix(struct_2);
}

TEST(test, SimpleTest){
    int input_matrix[num_rows][num_cols] = {
            {1, 2, 0, 3},
            {34, -5, 6, 0},
            {23, 56, 12, 5},
            {0, 0, 12, 45}
    };
    //Extra zeros won't be in result matrix
    int expected_input_matrix[num_rows][num_cols + 1] = {
            {1, 2, 3, 0, 0},
            {34, -5, 6, 0, 0},
            {23, 56, 12, 5, 0},
            {12, 45, 0, 0, 0}
    };

    matrix *test_matrix = (matrix *)malloc(sizeof(matrix));
    EXPECT_TRUE(init_matrix(test_matrix, num_rows, num_cols));
    EXPECT_TRUE(allocate_matrix(test_matrix));
    for(size_t i = 0; i < num_rows; ++i){
        for(size_t j = 0; j < num_cols; ++j){
            test_matrix->matrix[i][j] = input_matrix[i][j];
        }
    }

    int **expected_matrix = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        size_t j = 0;
        while(expected_input_matrix[i][j] != 0){
            ++j;
        }
        expected_matrix[i] = (int *)malloc((j + 1) * sizeof(int));
        for(size_t k = 0; k < j + 1; ++k){
            expected_matrix[i][k] = expected_input_matrix[i][k];
        }
    }

    non_zero_matrix *expected_struct = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    expected_struct->matrix = expected_matrix;
    expected_struct->num_vectors = num_rows;

    non_zero_matrix *result_struct = delete_zeros(test_matrix->matrix, test_matrix->num_rows, test_matrix->num_cols);

    EXPECT_TRUE(is_equal(expected_struct, result_struct));

    free_non_zero_matrix(expected_struct);
    free_non_zero_matrix(result_struct);
    free_matrix(test_matrix);
}

TEST(test, EmptyInputTest){
    int **test_matrix = NULL;

    non_zero_matrix *result_struct = delete_zeros(test_matrix, num_rows, num_cols);

    EXPECT_EQ(NULL, result_struct);
}

TEST(test, AllZeroTest){
    int input_matrix[num_rows][num_cols] = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    };

    matrix *test_matrix = (matrix *)malloc(sizeof(matrix));
    EXPECT_TRUE(init_matrix(test_matrix, num_rows, num_cols));
    EXPECT_TRUE(allocate_matrix(test_matrix));
    for(size_t i = 0; i < num_rows; ++i){
        for(size_t j = 0; j < num_cols; ++j){
            test_matrix->matrix[i][j] = input_matrix[i][j];
        }
    }

    non_zero_matrix *result_struct = delete_zeros(test_matrix->matrix, test_matrix->num_rows, test_matrix->num_cols);

    EXPECT_EQ(NULL, result_struct);

    free_matrix(test_matrix);
}

TEST(test, NoZeroTest){
    int input_matrix[num_rows][num_cols] = {
            {1, 2, 4, 3},
            {34, -5, 6, -9},
            {23, 56, 12, 5},
            {-5, 36, 12, 45}
    };
    //Extra zeros won't be in result matrix
    int expected_input_matrix[num_rows][num_cols + 1] = {
            {1, 2, 4, 3, 0},
            {34, -5, 6, -9, 0},
            {23, 56, 12, 5, 0},
            {-5, 36, 12, 45, 0}
    };

    matrix *test_matrix = (matrix *)malloc(sizeof(matrix));
    EXPECT_TRUE(init_matrix(test_matrix, num_rows, num_cols));
    EXPECT_TRUE(allocate_matrix(test_matrix));
    for(size_t i = 0; i < num_rows; ++i){
        for(size_t j = 0; j < num_cols; ++j){
            test_matrix->matrix[i][j] = input_matrix[i][j];
        }
    }

    int **expected_matrix = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        expected_matrix[i] = (int *)malloc((num_cols + 1) * sizeof(int));
        for(size_t k = 0; k < num_cols + 1; ++k){
            expected_matrix[i][k] = expected_input_matrix[i][k];
        }
    }

    non_zero_matrix *expected_struct = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    expected_struct->matrix = expected_matrix;
    expected_struct->num_vectors = num_rows;

    non_zero_matrix *result_struct = delete_zeros(test_matrix->matrix, test_matrix->num_rows, test_matrix->num_cols);

    EXPECT_TRUE(is_equal(expected_struct, result_struct));

    free_non_zero_matrix(expected_struct);
    free_non_zero_matrix(result_struct);
    free_matrix(test_matrix);
}

TEST(test, ZeroRowTest){
    int input_matrix[num_rows][num_cols] = {
            {1, 2, 4, 3},
            {0, 0, 0, 0},
            {23, 56, 12, 5},
            {-5, 36, 12, 45}
    };
    //Extra zeros won't be in result matrix
    int expected_input_matrix[num_rows - 1][num_cols + 1] = {
            {1, 2, 4, 3, 0},
            {23, 56, 12, 5, 0},
            {-5, 36, 12, 45, 0}
    };

    matrix *test_matrix = (matrix *)malloc(sizeof(matrix));
    EXPECT_TRUE(init_matrix(test_matrix, num_rows, num_cols));
    EXPECT_TRUE(allocate_matrix(test_matrix));
    for(size_t i = 0; i < num_rows; ++i){
        for(size_t j = 0; j < num_cols; ++j){
            test_matrix->matrix[i][j] = input_matrix[i][j];
        }
    }

    int **expected_matrix = (int **)malloc((num_rows - 1) * sizeof(int *));
    for(size_t i = 0; i < num_rows - 1; ++i){
        expected_matrix[i] = (int *)malloc((num_cols + 1) * sizeof(int));
        for(size_t k = 0; k < num_cols + 1; ++k){
            expected_matrix[i][k] = expected_input_matrix[i][k];
        }
    }

    non_zero_matrix *expected_struct = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    expected_struct->matrix = expected_matrix;
    expected_struct->num_vectors = num_rows - 1;

    non_zero_matrix *result_struct = delete_zeros(test_matrix->matrix, test_matrix->num_rows, test_matrix->num_cols);

    EXPECT_TRUE(is_equal(expected_struct, result_struct));

    free_non_zero_matrix(expected_struct);
    free_non_zero_matrix(result_struct);
    free_matrix(test_matrix);
}

TEST(test, ZeroColumnTest){
    int input_matrix[num_rows][num_cols] = {
            {1, 2, 0, 3},
            {34, -5, 0, -9},
            {23, 56, 0, 5},
            {-5, 36, 0, 45}
    };
    //Extra zeros won't be in result matrix
    int expected_input_matrix[num_rows][num_cols] = {
            {1, 2, 3, 0},
            {34, -5, -9, 0},
            {23, 56, 5, 0},
            {-5, 36, 45, 0}
    };

    matrix *test_matrix = (matrix *)malloc(sizeof(matrix));
    EXPECT_TRUE(init_matrix(test_matrix, num_rows, num_cols));
    EXPECT_TRUE(allocate_matrix(test_matrix));
    for(size_t i = 0; i < num_rows; ++i){
        for(size_t j = 0; j < num_cols; ++j){
            test_matrix->matrix[i][j] = input_matrix[i][j];
        }
    }

    int **expected_matrix = (int **)malloc(num_rows * sizeof(int *));
    for(size_t i = 0; i < num_rows; ++i){
        expected_matrix[i] = (int *)malloc((num_cols) * sizeof(int));
        for(size_t k = 0; k < num_cols; ++k){
            expected_matrix[i][k] = expected_input_matrix[i][k];
        }
    }

    non_zero_matrix *expected_struct = (non_zero_matrix *)malloc(sizeof(non_zero_matrix));
    expected_struct->matrix = expected_matrix;
    expected_struct->num_vectors = num_rows;

    non_zero_matrix *result_struct = delete_zeros(test_matrix->matrix, test_matrix->num_rows, test_matrix->num_cols);

    EXPECT_TRUE(is_equal(expected_struct, result_struct));

    free_non_zero_matrix(expected_struct);
    free_non_zero_matrix(result_struct);
    free_matrix(test_matrix);
}
