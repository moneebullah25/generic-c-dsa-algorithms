#ifndef _C_MATRIX_HEADER_
#define _C_MATRIX_HEADER_

#include "c_helper.h"

typedef struct {
	unsigned int num_rows, num_cols;
	double** data;
	bool is_square;
}Matrix;

/* Matrix Allocation */
/**
Function that creates and returns a new matrix with given number of rows and columns and all values set to 0.
@param num_rows number of rows in the new matrix
@param num_cols number of columns in the new matrix
@return pointer to the newly created matrix
Requirements:
	- num_rows and num_cols should be greater than 0
Time complexity: O(num_rows * num_cols)
Space complexity: O(num_rows * num_cols)
*/
Matrix* MatrixNew(unsigned int num_rows, unsigned int num_cols);

/**
Function that creates and returns a new matrix with given number of rows and columns and all values set randomly within a specified range.
@param num_rows number of rows in the new matrix
@param num_cols number of columns in the new matrix
@param min minimum value for the randomly generated values
@param max maximum value for the randomly generated values
@return pointer to the newly created matrix
Requirements:
	- num_rows and num_cols should be greater than 0
Time complexity: O(num_rows * num_cols)
Space complexity: O(num_rows * num_cols)
*/
Matrix* MatrixRandom(unsigned int num_rows, unsigned int num_cols, double min, double max);

/**
Function that creates and returns a new square matrix with given size and all values set to 0.
@param size number of rows and columns in the new matrix
@return pointer to the newly created square matrix
Requirements:
	- size should be greater than 0
Time complexity: O(size^2)
Space complexity: O(size^2)
*/
Matrix* MatrixSquare(unsigned int size);

/**
Function that creates and returns a new square matrix with given size and all values set randomly within a specified range.
@param size number of rows and columns in the new matrix
@param min minimum value for the randomly generated values
@param max maximum value for the randomly generated values
@return pointer to the newly created square matrix
Requirements:
	- size should be greater than 0
Time complexity: O(size^2)
Space complexity: O(size^2)
*/
Matrix* MatrixSquareRandom(unsigned int size, double min, double max);

/**
Function that creates and returns a new matrix with given number of rows and columns and all values set to 0.
@param num_rows number of rows in the new matrix
@param num_cols number of columns in the new matrix
@return pointer to the newly created matrix
Requirements:
	- num_rows and num_cols should be greater than 0
Time complexity: O(num_rows * num_cols)
Space complexity: O(num_rows * num_cols)
*/
Matrix* MatrixZero(unsigned int num_rows, unsigned int num_cols);

/**
Function that creates and returns a new matrix with given number of rows and columns and all values set to 1.
@param num_rows number of rows in the new matrix
@param num_cols number of columns in the new matrix
@return pointer to the newly created matrix
Requirements:
	- num_rows and num_cols should be greater than 0
Time complexity: O(num_rows * num_cols)
Space complexity: O(num_rows * num_cols)
*/
Matrix* MatrixOne(unsigned int num_rows, unsigned int num_cols);

/**
Function that creates and returns a new matrix with all elements set to a given value.
@param num_rows the number of rows in the matrix
@param num_cols the number of columns in the matrix
@param value the value to initialize all elements in the matrix with
Requirements:
	- num_rows and num_cols should be positive values
Time complexity: O(mn), where m is the number of rows and n is the number of columns
Space complexity: O(mn), where m is the number of rows and n is the number of columns
*/
Matrix* MatrixN(unsigned int num_rows, unsigned int num_cols, double value);

/**
Function that creates and returns a new identity matrix with given size.
An identity matrix is a square matrix with 1's on the main diagonal and 0's everywhere else.
@param size the size of the matrix (number of rows and columns)
Requirements:
	- size should be a positive value
Time complexity: O(n^2), where n is the size of the matrix
Space complexity: O(n^2), where n is the size of the matrix
*/
Matrix* MatrixIdentity(unsigned int size);

/**
Function that creates and returns a new matrix from a given array of values.
The array of values is stored in the matrix in row-major order.
@param num_rows the number of rows in the matrix
@param num_cols the number of columns in the matrix
@param n_values the number of values in the input array
@param values the array of values to initialize the matrix with
Requirements:
	- num_rows, num_cols and n_values should be positive values
	- n_values should be equal to num_rows * num_cols
	- values should not be a nullptr
Time complexity: O(mn), where m is the number of rows and n is the number of columns
Space complexity: O(mn), where m is the number of rows and n is the number of columns
*/
Matrix* MatrixFrom(unsigned int num_rows, unsigned int num_cols, unsigned int n_values, double *values);

/**
Function that creates and returns a new matrix from values stored in a given file.
@param file the name of the file to read the matrix values from
Requirements:
	- file should not be a nullptr
	- file should contain a valid matrix
Time complexity: O(mn), where m is the number of rows and n is the number of columns
Space complexity: O(mn), where m is the number of rows and n is the number of columns
*/
Matrix* MatrixFromFile(const char* file);

/**
Function that creates and returns a copy of a given matrix.
@param m the matrix to copy
Requirements:
m should not be a nullptr
Time complexity: O(mn), where m is the number of rows and n is the number of columns
Space complexity: O(mn), where m is the number of rows and n is the number of columns
*/
Matrix* MatrixCopy(Matrix* m);

/* Matrix Basic */
bool IsMatrixEqualDimension(Matrix* m1, Matrix* m2);
void PrintMatrix(Matrix* m, const char* data_format);
bool IsMatrixInvertible(Matrix* m);

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
Matrix* MatrixBroadcastRows(Matrix* m, unsigned int row);
Matrix* MatrixBroadcastColumns(Matrix* m, unsigned int col);
Matrix* MatrixBroadcastRowsAndColumns(Matrix* m, unsigned int row, unsigned int col);

/* Matrix Operatons */
Matrix* MatrixAdd(Matrix* m1, Matrix* m2);
Matrix* MatrixSubtract(Matrix* m1, Matrix* m2);
Matrix* MatrixMultiply(Matrix* m1, Matrix* m2);
Matrix* MatrixAddWithBroadcast(Matrix* m1, Matrix* m2);
Matrix* MatrixSubtractWithBroadcast(Matrix* m1, Matrix* m2);
void MatrixTranspose(Matrix* m);
double MatrixTrace(Matrix* m);
double MatrixDeterminant(Matrix* m);
void MatrixRowEchelon(Matrix* m);
void MatrixReducedRowEchelon(Matrix* m);
Matrix* MatrixRowEchelonGet(Matrix* m);
Matrix* MatrixReducedRowEchelonGet(Matrix* m);
double MatrixColumnL2Norm(Matrix* m, unsigned int col);
Matrix* MatrixL2Norm(Matrix* m);

/* Matrix Dispose */
void MatrixFree(Matrix* m);

#endif /* _C_MATRIX_HEADER_ */