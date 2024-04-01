/*
This program calculates the determinant of
a certain square matrix specified from the
user's text file
*/

#include <stdio.h>

#include "matrix.h"
#include "determinant.h"

int main(int argc, char** argv) {
	FILE* fp = fopen(argv[1], "r");
	
	Matrix user_matrix = Create_And_Populate_Matrix(fp);
	fclose(fp);

	printf("The determinant is %.2lf.\n\n", Calc_Determinant(user_matrix));
	
	Delete_Matrix(&user_matrix);

	return 0;
}