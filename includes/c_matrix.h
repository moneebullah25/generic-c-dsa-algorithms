#ifndef _C_MATRIX_HEADER_
#define _C_MATRIX_HEADER_

#include "c_helper.h"

typedef struct {
	unsigned int num_rows, num_cols;
	double** data;
	bool is_square;
}Matrix;

/* Matrix Allocation */
Matrix* MatrixNew(unsigned int num_rows, unsigned int num_cols);
Matrix* MatrixRandom(unsigned int num_rows, unsigned int num_cols, double min, double max);
Matrix* MatrixSquare(unsigned int size);
Matrix* MatrixSquareRandom(unsigned int size, double min, double max);
Matrix* MatrixZero(unsigned int num_rows, unsigned int num_cols);
Matrix* MatrixOne(unsigned int num_rows, unsigned int num_cols);
Matrix* MatrixN(unsigned int num_rows, unsigned int num_cols, double value);
Matrix* MatrixIdentity(unsigned int size);
Matrix* MatrixFrom(unsigned int num_rows, unsigned int num_cols, unsigned int n_values, double *values);
Matrix* MatrixFromFile(const char* file);
Matrix* MatrixCopy(Matrix* m);

void PrintMatrix(Matrix* m, const char* data_format);

#endif /* _C_MATRIX_HEADER_ */