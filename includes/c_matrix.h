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
/**
Function that checks if two matrices have equal dimensions.
The function asserts that the matrix pointers m1 and m2 are not null.
@param m1 pointer to the first matrix
@param m2 pointer to the second matrix
Requirements:
	- m1 and m2 pointers should not be nullptr
Time complexity: O(1)
Space complexity: O(1)
@return true if the number of rows and columns of the two matrices are equal, false otherwise
*/
bool IsMatrixEqualDim(Matrix* m1, Matrix* m2);

/**
Function that prints a matrix to the console.
The function asserts that the matrix pointer m and the data format string are not null.
@param m pointer to the matrix to be printed
@param data_format string that specifies the format of the matrix data
Requirements:
	 - m pointer should not be nullptr
	 - data_format string should not be nullptr
Time complexity: O(mn) where m and n are the number of rows and columns of the matrix respectively
Space complexity: O(1)
*/
void PrintMatrix(Matrix* m, const char* data_format);

/**
Function that checks if a matrix is invertible.
The function asserts that the matrix pointer m is not null.
@param m pointer to the matrix
Requirements:
	- m pointer should not be nullptr
Time complexity: O(mn^3) where m and n are the number of rows and columns of the matrix respectively
Space complexity: O(1)
@return true if the matrix is invertible, false otherwise
*/
bool IsMatrixInvertible(Matrix* m);

/* Matrix Accessing and Modifying */
/**
Returns the value stored at the specified row and column in the matrix.
Time complexity: O(1)
Space complexity: O(1)
@param m Pointer to the matrix.
Requirements:
	- m pointer should not be nullptr
@param row Row index of the desired value.
@param col Column index of the desired value.
@return The value stored at the specified row and column in the matrix.
*/
double MatrixGet(Matrix* m, unsigned row, unsigned col);

/**

Returns a column from the matrix as a new matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(m)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param col Column index to extract from the matrix.
@return A new matrix representing the specified column from the input matrix.
*/
Matrix* MatrixColumnGet(Matrix* m, unsigned int col);

/**
Returns a row from the matrix as a new matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(n)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param row Row index to extract from the matrix.
@return A new matrix representing the specified row from the input matrix.
*/
Matrix* MatrixRowGet(Matrix* m, unsigned int row);

/**
Sets the value at the specified row and column in the matrix.
Time complexity: O(1)
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param row Row index of the value to set.
@param col Column index of the value to set.
@param value The value to set at the specified row and column in the matrix.
*/
void MatrixSet(Matrix* m, unsigned int row, unsigned int col, double value);

/**
Sets all values in the matrix to a specified value.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param value The value to set all values in the matrix to.
*/
void MatrixAllSet(Matrix* m, double value);

/**
Sets all diagonal values in the matrix to a specified value.
Time complexity: O(min(m, n)), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param value The value to set all diagonal values in the matrix to.
*/
void MatrixDiagonalSet(Matrix* m, double value);

/**
Multiplies all values in a specified row of the matrix by a specified value.
Time complexity: O(n), where n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param row Row index of the values to multiply.
@param value The value to multiply all values in the specified row of the matrix by.
*/
void MatrixRowMultiplyValue(Matrix* m, unsigned int row, double value);

/**
Add all values in a specified row of the matrix by a specified value.
Time complexity: O(n), where n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param row Row index of the values to multiply.
@param value The value to multiply all values in the specified row of the matrix by.
*/
void MatrixRowAddValue(Matrix* m, unsigned int row, double value);

/**
Multiplies all values in a specified column of the matrix by a specified value.
Time complexity: O(n), where n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param col Column index of the values to multiply.
@param value The value to multiply all values in the specified row of the matrix by.
*/
void MatrixColumnMultiplyValue(Matrix* m, unsigned int col, double value);

/**
Add all values in a specified column of the matrix by a specified value.
Time complexity: O(n), where n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param col Column index of the values to multiply.
@param value The value to multiply all values in the specified row of the matrix by.
*/
void MatrixColumnAddValue(Matrix* m, unsigned int col, double value);

/**
Function that is used to multiply a row to another row (with a multiplicator).
This will do the following: m->data[where][...] *= m->data[row][...] * value. 
The results will be kept in a new matrix. Matrix m remains unchanged.
@param m pointer to the matrix
@param where index of the row to be multiplied
@param row index of the row to be multiplied by value
@param value value to multiply the row by
Requirements:
	- m pointer should not be nullptr
Time complexity: O(n), where n is the number of columns in the matrix
Space complexity: O(1)
*/
void MatrixRowMultiplyRow(Matrix* m, unsigned int where, unsigned int row, double value);

/**
Function that is used to add a row to another row (with a multiplicator).
This will do the following: m->data[where][...] += m->data[row][...] * value. 
The results will be kept in a new matrix. Matrix m remains unchanged.
@param m pointer to the matrix
@param where index of the row to be multiplied
@param row index of the row to be multiplied by value
@param value value to multiply the row by
Requirements:
	- m pointer should not be nullptr
Time complexity: O(n), where n is the number of columns in the matrix
Space complexity: O(1)
*/
void MatrixRowAddRow(Matrix* m, unsigned int where, unsigned int row, double value);

/**
Function that is used to multiply a column to another column (with a multiplicator).
This will do the following: m->data[column][where] *= m->data[...][column] * value. 
The results will be kept in a new matrix. Matrix m remains unchanged.
@param m pointer to the matrix
@param where index of the column to be multiplied
@param col index of the column to be multiplied by value
@param value value to multiply the column by
Requirements:
	- m pointer should not be nullptr
Time complexity: O(n), where n is the number of columns in the matrix
Space complexity: O(1)
*/
void MatrixColumnMultiplyColumn(Matrix* m, unsigned int where, unsigned int col, double value);

/**
Function that is used to add a column to another column (with a multiplicator).
This will do the following: m->data[column][where] *= m->data[...][column] * value. 
The results will be kept in a new matrix. Matrix m remains unchanged.
@param m pointer to the matrix
@param where index of the column to be multiplied
@param col index of the column to be multiplied by value
@param value value to multiply the column by
Requirements:
	- m pointer should not be nullptr
Time complexity: O(n), where n is the number of columns in the matrix
Space complexity: O(1)
*/
void MatrixColumnAddValueColumn(Matrix* m, unsigned int where, unsigned int col, double value);

/**
Multiplies all values in the matrix with a specified value.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param value The value to set all values in the matrix to.
*/
void MatrixWholeMultiply(Matrix* m, double value);

/**
Add all values in the matrix with a specified value.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
@param m Pointer to the matrix.
@param value The value to set all values in the matrix to.
*/
void MatrixWholeAdd(Matrix* m, double value);

/**
Remove a specific row from a matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(m-1)n
Requirements:
	- m pointer should not be nullptr
	- row value should be less than the number of rows in the matrix
@param m Pointer to the matrix.
@param row The row to be removed from the matrix.
@return Pointer to the matrix with the specified row removed.
*/
Matrix* MatrixRowRemove(Matrix* m, unsigned int row);

/**
Remove a specific column from a matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(m)(n-1)
Requirements:
	- m pointer should not be nullptr
	- col value should be less than the number of columns in the matrix
@param m Pointer to the matrix.
@param col The column to be removed from the matrix.
@return Pointer to the matrix with the specified column removed.
*/
Matrix* MatrixColumnRemove(Matrix* m, unsigned int col);

/**
Swap two rows of a matrix.
Time complexity: O(n), where n is the number of columns in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
	- row1 and row2 values should be less than the number of rows in the matrix
@param m Pointer to the matrix.
@param row1 The first row to be swapped.
@param row2 The second row to be swapped.
*/
void MatrixRowSwap(Matrix* m, unsigned int row1, unsigned int row2);

/**
Swap two columns of a matrix.
Time complexity: O(m), where m is the number of rows in the matrix.
Space complexity: O(1)
Requirements:
	- m pointer should not be nullptr
	- col1 and col2 values should be less than the number of columns in the matrix
@param m Pointer to the matrix.
@param col1 The first column to be swapped.
@param col2 The second column to be swapped.
*/
void MatrixColumnSwap(Matrix* m, unsigned int col1, unsigned int col2);

/**
Broadcast the row of a matrix to row passed as argument and return that new matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(mn)
Requirements:
	- m pointer should not be nullptr
	- row value that new matrix will have that number of rows
@param m Pointer to the matrix.
@param row The number of rows that new broadcasted matrix will have
@return Pointer to the matrix with the specified row broadcasted to all other rows.
*/
Matrix* MatrixBroadcastRows(Matrix* m, unsigned int row);

/**
Broadcast the column of a matrix to column passed as argument and return that new matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(mn)
Requirements:
	- m pointer should not be nullptr
	- col value that new matrix will have that number of columns
@param m Pointer to the matrix.
@param col The number of columns that new broadcasted matrix will have
@return Pointer to the matrix with the specified row broadcasted to all other rows.
*/
Matrix* MatrixBroadcastColumns(Matrix* m, unsigned int col);

/**
Broadcast the row of a matrix to row passed as argument and return that new matrix. 
And then Broadcast the column of a matrix to column passed as argument and return that new matrix.
Time complexity: O(mn), where m is the number of rows and n is the number of columns in the matrix.
Space complexity: O(mn)
Requirements:
	- m pointer should not be nullptr
	- row value that new matrix will have that number of rows
	- col value that new matrix will have that number of columns
@param m Pointer to the matrix.
@param row The number of rows that new broadcasted matrix will have
@param col The number of columns that new broadcasted matrix will have
@return Pointer to the matrix with the specified row broadcasted to all other rows.
*/
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