/*
This program is responsible for the set-up
and clean-up of the certain square matrix
specified by the user
*/

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/*
This function creates and populates a certain square
matrix specified from the user's text file
@FILE* fp: file pointer to the user's text file opened in read mode
@return: matrix with the user's specifications (from their text file)
*/
Matrix Create_And_Populate_Matrix(FILE* fp) {
	Matrix user_matrix;
	int i, j;

	fscanf(fp, "%d %d", &user_matrix.dim, &user_matrix.dim);
	
	user_matrix.matrix = (double**)malloc(user_matrix.dim * sizeof(double*));
	for (i = 0; i < user_matrix.dim; ++i) {
		user_matrix.matrix[i] = (double*)malloc(user_matrix.dim * sizeof(double));
	}

	for (i = 0; i < user_matrix.dim; ++i) {
		for (j= 0; j < user_matrix.dim; ++j) {
			fscanf(fp, "%lf", &user_matrix.matrix[i][j]);
		}
	}

	return user_matrix;
}

/*
This function deletes a square matrix
@Matrix* m: address of square matrix
*/
void Delete_Matrix(Matrix* m) {
	for (int i = 0; i < m->dim; ++i) {
		free(m->matrix[i]);
	}

	free(m->matrix);
}