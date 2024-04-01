/*
This program is responsible for determinant-related
calculations corresponding to the certain square
matrix specified by the user
*/

#include <stdio.h>
#include <stdlib.h>

#include "determinant.h"
#include "matrix.h"

/*
This recursive function calculates the determinant
of the user's specified square matrix
@Matrix user_matrix: initially, it is the user's specified square matrix;
								recursively, it eventually becomes a 2x2
								sub-matrix within the user's specified matrix
@return: value of the determinant of the user's specified square matrix
*/
double Calc_Determinant(Matrix user_matrix) {
	double det = 0;
	int i, j, k, z, sign = 1;

	if (user_matrix.dim == 1) {
		return user_matrix.matrix[0][0];
	}
	else if (user_matrix.dim == 2) {
		return Calc_2x2_Determinant(user_matrix);
	}
	else {
		for (i = 0; i < user_matrix.dim; ++i) {
			Matrix sub_matrix;
			
			sub_matrix.dim = user_matrix.dim - 1;
			sub_matrix.matrix = (double**)malloc(sub_matrix.dim * sizeof(double*));
			for (j = 0; j < (sub_matrix.dim); ++j) {
				sub_matrix.matrix[j] = (double*)malloc(sub_matrix.dim * sizeof(double));
			}

			for (j = 1; j < user_matrix.dim; ++j) {
				for (k = 0; k < user_matrix.dim; ++k) {
					if (k == i) {
						continue;
					}

					z = (k < i) ? k: (k - 1);
					sub_matrix.matrix[j - 1][z] = user_matrix.matrix[j][k];
				}
			}

			det += sign * user_matrix.matrix[0][i] * Calc_Determinant(sub_matrix);
			sign *= -1;

			Delete_Matrix(&sub_matrix);
		}
	} 

	return det;
}

/*
This function calculates the determinant
of a matrix of order 2
@Matrix user_matrix: a 2x2 matrix
@return: value of the determinant of the 2x2 matrix
*/
double Calc_2x2_Determinant(Matrix user_matrix) {
	return user_matrix.matrix[0][0] * user_matrix.matrix[1][1] - user_matrix.matrix[0][1] * user_matrix.matrix[1][0];
}
