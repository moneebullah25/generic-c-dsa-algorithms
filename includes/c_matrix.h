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

/* Matrix Basic */
bool MatrixEqualDim(Matrix* m1, Matrix* m2);
void PrintMatrix(Matrix* m, const char* data_format);

/* Matrix Accessing and Modifying */
double MatrixGet(Matrix* m, unsigned row, unsigned col);
Matrix* MatrixColumnGet(Matrix* m, unsigned int col);
Matrix* MatrixRowGet(Matrix* m, unsigned int row);
void MatrixSet(Matrix* m, unsigned int row, unsigned int col, double value);
void MatrixAllSet(Matrix* m, double value);
void MatrixDiagonalSet(Matrix* m, double value);
void MatrixRowMultiplyValue(Matrix* m, unsigned int row, double value);
void MatrixRowAddValue(Matrix* m, unsigned int row, double value);
void MatrixColumnMultiplyValue(Matrix* m, unsigned int col, double value);
void MatrixColumnAddValue(Matrix* m, unsigned int col, double value);
void MatrixRowMultiplyRow(Matrix* m, unsigned int where, unsigned int row, double value);
void MatrixRowAddRow(Matrix* m, unsigned int where, unsigned int row, double value);
void MatrixColumnMultiplyColumn(Matrix* m, unsigned int where, unsigned int col, double value);
void MatrixColumnAddValueColumn(Matrix* m, unsigned int where, unsigned int col, double value);
void MatrixWholeMultiply(Matrix* m, double value);
void MatrixWholeAdd(Matrix* m, double value);
Matrix* MatrixRowRemove(Matrix* m, unsigned int row);
Matrix* MatrixColumnRemove(Matrix* m, unsigned int col);
void MatrixRowSwap(Matrix* m, unsigned int row1, unsigned int row2);
void MatrixColumnSwap(Matrix* m, unsigned int col1, unsigned int col2);

/* Matrix Operatons */
Matrix* MatrixAdd(Matrix* m1, Matrix* m2);
Matrix* MatrixSubtract(Matrix* m1, Matrix* m2);
Matrix* MatrixMultiply(Matrix* m1, Matrix* m2);
void MatrixTranspose(Matrix* m);
double MatrixTrace(Matrix* m);
double MatrixDeterminant(Matrix* m);
Matrix* MatrixRowEchelon(Matrix* m);
Matrix* MatrixReducedRowEchelon(Matrix* m);

#endif /* _C_MATRIX_HEADER_ */