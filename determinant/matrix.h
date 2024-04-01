#ifndef MATRIX_H
	#define MATRIX_H

	typedef struct Matrix_struct {
		int dim;
		double** matrix;
	} Matrix;

	Matrix Create_And_Populate_Matrix(FILE* fp);
	void Delete_Matrix(Matrix* m);
#endif