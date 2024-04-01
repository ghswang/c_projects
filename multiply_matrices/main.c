#include <stdio.h>
#include <stdlib.h>
#include "mat_multiply.h"


void check_matrix_is_null(int** matrix, const char* matrix_name){
    /*
    print whether matrix has been set to NULL or not
    @matrix: the matrix to check if it has been set to NULL
    @matrix_name: the name of the matrix
    */
    if(matrix == NULL){
        printf("%s set to NULL.\n", matrix_name);
    }else{
        printf("%s was NOT set to NULL!\n", matrix_name);
    }
}

int main() {
    int** matrix_a;
    int num_rows_a, num_cols_a;

    int** matrix_b;
    int num_rows_b, num_cols_b;

    int** matrix_c;
    int num_rows_c, num_cols_c;

    get_matrix_dimensions_from_user("Enter the dimensions of matrix A: ", &num_rows_a, &num_cols_a);
    matrix_a = make_empty_matrix(num_rows_a, num_cols_a);
    printf("Enter Matrix A\n");
    fill_matrix_from_user_input(matrix_a, num_rows_a, num_cols_a);

    get_matrix_dimensions_from_user("Enter the dimensions of matrix B: ", &num_rows_b, &num_cols_b);
    matrix_b = make_empty_matrix(num_rows_b, num_cols_b);
    printf("Enter Matrix B\n");
    fill_matrix_from_user_input(matrix_b, num_rows_b, num_cols_b);


    matrix_c = matrix_multiply(matrix_a,  num_rows_a,  num_cols_a,
                               matrix_b,  num_rows_b,  num_cols_b,
                               &num_rows_c, &num_cols_c);

    printf("A * B = \n");
    print_matrix(matrix_c, num_rows_c, num_cols_c);

    delete_matrix(&matrix_a, num_rows_a, num_cols_a);
    delete_matrix(&matrix_b, num_rows_b, num_cols_b);
    delete_matrix(&matrix_c, num_rows_c, num_cols_c);

    check_matrix_is_null(matrix_a, "matrix_a");
    check_matrix_is_null(matrix_b, "matrix_b");
    check_matrix_is_null(matrix_c, "matrix_c");

    return 0;
}
