#include <stdio.h>
#include <stdlib.h>
#include "mat_multiply.h"

void get_matrix_dimensions_from_user(char* prompt, int* num_rows, int* num_cols){
	/*
	Display the given prompt to the user, then read two integers from the
	user storing the result in num_rows and num_cols
	@prompt: The prompt to show to the user
	@num_rows: the address of where to store the first number entered by the user
	@num_cols: the address of where to store the second number entered by the user
	@returns: nothing
	@modifies: num_rows, num_cols
	*/

	printf("%s", prompt);
	scanf("%d %d", num_rows, num_cols);
	printf("\n");
}

int** make_empty_matrix(int row_dim, int col_dim) {
	/*
	Dynamically create a row_dim X col_dim matrix
	A matrix here is an array of array of integers
	You do not need to initialize the values of the numbers in
	the matrix but you can if you want
	@row_dim: the number of rows the matrix should have
	@col_dum: the number of columns the matrix should have
	@returns: a row_dim X col_dim matrix of integers
	@modifies: nothing
	*/

	int** emptyMatrix = (int**)malloc(row_dim * sizeof(int*));
	for (int i = 0; i < row_dim; ++i) {
		emptyMatrix[i] = (int*)malloc(col_dim * sizeof(int));
	}

	return emptyMatrix;
}

void fill_matrix_from_user_input(int** matrix, int row_dim, int col_dim) {
	/*
	Fill in the row_dim X col_dim matrix with values entered by the user
	The user will enter in row_dim rows that each have col_dim elements in it.
	For example if row_dim = 3 and col_dim = 4 the user could enter something like
	11 25 43 45
	10 45 63 17
	-8 25 -9 24

	These values should be stored into matrix
	@matrix: the matrix to be filled in
	@row_dim: the number of rows matrix has
	@col_dum: the number of columns matrix has
	@returns: nothing
	@modifies: matrix
	*/

	for (int i = 0; i < row_dim; ++i) {
		for (int j = 0; j < col_dim; ++j) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

int** matrix_multiply(int** matrix_a, int num_rows_a, int num_cols_a,
											int** matrix_b, int num_rows_b, int num_cols_b,
											int* out_num_rows_c, int* out_num_cols_c) {
	/*
	Multiply matrix_a and matrix_b together, returning the resulting matrix
	Set out_num_rows_c to be the number of rows in the resulting matrix
	Set out_num_cols_c to be the number of cols in the resulting matrix
	@matrix_a: the A in C = A X B
	@num_rows_a: the number of rows in matrix a
	@num_cols_a: the number of columns in matrix a
	@matrix_b: the B in C = A X B
	@num_rows_b: the number of rows in matrix b
	@num_cols_b: the number of columns in matrix b
	@out_num_rows_c: where to store the number of rows of the resulting matrix
	@out_num_cols_c: where to store the number of columns of the resulting matrix
	@returns: matrix_a X matrix_b
	@modifies: out_num_rows_c, out_num_cols_c
	*/

	*out_num_rows_c = num_rows_a;
	*out_num_cols_c = num_cols_b;

	int i, j, m;

	int** matrix_c = (int**)calloc(*out_num_rows_c, sizeof(int*));
	for (i = 0; i < *out_num_rows_c; ++i) {
		matrix_c[i] = (int*)calloc(*out_num_cols_c, sizeof(int));
	}

	for (i = 0; i < *out_num_rows_c; ++i) {
		for (j = 0; j < *out_num_cols_c; ++j) {
			m = 0;
			do {
				matrix_c[i][j] += matrix_a[i][m] * matrix_b[m][j];
				++m;
			} while (m < num_cols_a);
		}
	}

	return matrix_c;
}

void print_matrix(int** matrix, int row_dim, int col_dim) {
	/*
	Print matrix to the screen
	@matrix: the matrix to be printed
	@row_dim: the number of rows in matrix
	@col_dim: the number of columns in matrix
	@returns: nothing
	@modifies: nothing
	*/

	for (int i = 0; i < row_dim; ++i) {
		for (int j = 0; j < col_dim; ++j) {
			((j == col_dim - 1)) ? printf("%d\n", matrix[i][j]) : printf("%d ", matrix[i][j]);
		}
	}

	printf("\n");
}

void delete_matrix(int*** matrix, int row_dim, int col_dim) {
	/*
	Delete matrix AND set it to NULL.
	@matrix: the address of the matrix to be deleted
	@row_dim: the number of rows in matrix
	@col_dim: the number of columns in matrix
	@returns: nothing
	@modifies: matrix
	*/

	for (int i = 0; i < row_dim; ++i) {
		free((*matrix)[i]);
	}

	free(*matrix);

	*matrix = NULL;
}
