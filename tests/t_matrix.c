#include <criterion/criterion.h>
#include "../includes/c_helper.h"
#include "../includes/c_matrix.h"

Test(MatrixEmpty, invalid_num_rows) {
    Matrix *matrix = MatrixEmpty(0, 5);
    cr_assert_null(matrix, "MatrixEmpty should return NULL when num_rows is 0");
}

Test(MatrixEmpty, invalid_num_cols) {
    Matrix *matrix = MatrixEmpty(5, 0);
    cr_assert_null(matrix, "MatrixEmpty should return NULL when num_cols is 0");
}

Test(MatrixEmptyLike, NULL_matrix) {
	Matrix *matrix = MatrixEmptyLike(NULL);
	cr_assert_null(matrix, "MatrixEmptyLike should return NULL when a NULL matrix is passed");
}

Test(MatrixEmptyLike, valid_matrix) {
	Matrix *m = MatrixAlloc(2, 3);
	MatrixSetValue(m, 0, 0, 1.);
	MatrixSetValue(m, 0, 1, 2.);
	MatrixSetValue(m, 0, 2, 3.);
	MatrixSetValue(m, 1, 0, 4.);
	MatrixSetValue(m, 1, 1, 5.);
	MatrixSetValue(m, 1, 2, 6.);
	Matrix *matrix = MatrixEmptyLike(m);
	cr_assert_not_null(matrix, "MatrixEmptyLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, m->num_rows, "MatrixEmptyLike should set the same number of rows as the passed matrix");
	cr_assert_eq(matrix->num_cols, m->num_cols, "MatrixEmptyLike should set the same number of columns as the passed matrix");
	cr_assert_eq(matrix->is_square, false, "MatrixEmptyLike should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_eq(matrix->data[r][c], 0., "MatrixEmptyLike should initialize all elements to 0");
		}
	}
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixEmpty, v	alid_arguments) {
    Matrix *matrix = MatrixEmpty(3, 4);
    cr_assert_not_null(matrix, "MatrixEmpty should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 3, "MatrixEmpty should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 4, "MatrixEmpty should set the correct number of columns");
    cr_assert_eq(matrix->is_square, false, "MatrixEmpty should set is_square to false for a non-square matrix");
    for (unsigned int r = 0; r < matrix->num_rows; r++) {
        for (unsigned int c = 0; c < matrix->num_cols; c++) {
            cr_assert_eq(matrix->data[r][c], 0., "MatrixEmpty should initialize all elements to 0");
        }
    }
    MatrixFree(matrix);
}

Test(MatrixNew, invalid_num_rows) {
	Matrix *matrix = MatrixNew(0, 5);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_rows is 0");
}

Test(MatrixNew, invalid_num_cols) {
	Matrix *matrix = MatrixNew(5, 0);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_cols is 0");
}

Test(MatrixNew, valid_arguments) {
	Matrix *matrix = MatrixNew(3, 4);
	cr_assert_not_null(matrix, "MatrixNew should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixNew should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixNew should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixNew should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_eq(matrix->data[r][c], 0., "MatrixNew should initialize all elements to 0");
		}
	}
	MatrixFree(matrix);
}

Test(MatrixNewLike, invalid_matrix) {
	Matrix *m = NULL;
	Matrix *matrix = MatrixNewLike(m);
	cr_assert_null(matrix, "MatrixNewLike should return NULL when invalid matrix is passed");
}

Test(MatrixNewLike, valid_matrix) {
	Matrix *m = MatrixNew(3, 4);
	Matrix *matrix = MatrixNewLike(m);
	cr_assert_not_null(matrix, "MatrixNewLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, m->num_rows, "MatrixNewLike should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, m->num_cols, "MatrixNewLike should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixNewLike should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_eq(matrix->data[r][c], 0., "MatrixNewLike should initialize all elements to 0");
		}
	}
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixRandom, invalid_num_rows) {
	Matrix *matrix = MatrixRandom(0, 5, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_rows is 0");
}

Test(MatrixRandom, invalid_num_cols) {
	Matrix *matrix = MatrixRandom(5, 0, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_cols is 0");
}

Test(MatrixRandom, valid_arguments) {
	unsigned int num_rows = 3;
	unsigned int num_cols = 4;
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixRandom(num_rows, num_cols, min, max);
	cr_assert_not_null(matrix, "MatrixRandom should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, num_rows, "MatrixRandom should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, num_cols, "MatrixRandom should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixRandom should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_geq(matrix->data[r][c], min, "MatrixRandom should generate values greater than or equal to the minimum");
			cr_assert_leq(matrix->data[r][c], max, "MatrixRandom should generate values less than or equal to the maximum");
		}
	}
	MatrixFree(matrix);
}

Test(MatrixRandomLike, invalid_matrix) {
	Matrix *m = NULL;
	Matrix *matrix = MatrixRandomLike(m, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandomLike should return NULL when an invalid matrix is passed");
}

Test(MatrixRandomLike, valid_matrix) {
	unsigned int num_rows = 3;
	unsigned int num_cols = 4;
	double min = -1.0;
	double max = 1.0;
	Matrix *m = MatrixNew(num_rows, num_cols);
	Matrix *matrix = MatrixRandomLike(m, min, max);
	cr_assert_not_null(matrix, "MatrixRandomLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, num_rows, "MatrixRandomLike should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, num_cols, "MatrixRandomLike should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixRandomLike should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_geq(matrix->data[r][c], min, "MatrixRandomLike should generate values greater than or equal to the minimum");
			cr_assert_leq(matrix->data[r][c], max, "MatrixRandomLike should generate values less than or equal to the maximum");
		}
	}
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquare, valid_size) {
    Matrix *matrix = MatrixSquare(3);
    cr_assert_not_null(matrix, "MatrixSquare should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 3, "MatrixSquare should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 3, "MatrixSquare should set the correct number of columns");
    cr_assert_eq(matrix->is_square, true, "MatrixSquare should set is_square to true for a square matrix");
    MatrixFree(matrix);
}

Test(MatrixSquareLike, invalid_matrix) {
    Matrix *matrix = MatrixSquareLike(NULL);
    cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed an invalid matrix");
}

Test(MatrixSquareLike, non_square_matrix) {
    Matrix *m = MatrixNew(2, 3);
    Matrix *matrix = MatrixSquareLike(m);
    cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed a non-square matrix");
    MatrixFree(m);
}

Test(MatrixSquareLike, valid_matrix) {
    Matrix *m = MatrixSquare(4);
    Matrix *matrix = MatrixSquareLike(m);
    cr_assert_not_null(matrix, "MatrixSquareLike should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 4, "MatrixSquareLike should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 4, "MatrixSquareLike should set the correct number of columns");
    cr_assert_eq(matrix->is_square, true, "MatrixSquareLike should set is_square to true for a square matrix");
    MatrixFree(m);
    MatrixFree(matrix);
}

Test(MatrixSquareRandom, valid_size_and_range) {
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandom(3, min, max);
	cr_assert_not_null(matrix, "MatrixSquareRandom should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixSquareRandom should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixSquareRandom should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixSquareRandom should set is_square to true for a square matrix");
	bool in_range = true;
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			if (matrix->data[r][c] < min || matrix->data[r][c] > max) {
				in_range = false;
				break;
			}
		}
	}
	cr_assert_eq(in_range, true, "MatrixSquareRandom should set all elements within the specified range");

	MatrixFree(matrix);
}

Test(MatrixSquareRandom, invalid_size) {
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandom(0, min, max);
	cr_assert_null(matrix, "MatrixSquareRandom should return NULL when passed an invalid size");
}

Test(MatrixSquareRandomLike, invalid_matrix) {
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandomLike(NULL, min, max);
	cr_assert_null(matrix, "MatrixSquareRandomLike should return NULL when passed an invalid matrix");
}

Test(MatrixSquareRandomLike, not_square_matrix) {
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixNew(2, 3);
	cr_assert_null(MatrixSquareRandomLike(matrix, min, max), "MatrixSquareRandomLike should return NULL when passed a non-square matrix");
	MatrixFree(matrix);
}

Test(MatrixZero, valid_size) {
	Matrix *matrix = MatrixZero(3, 2);
	cr_assert_not_null(matrix, "MatrixZero should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixZero should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 2, "MatrixZero should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixZero should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++) {
		for (unsigned int c = 0; c < matrix->num_cols; c++) {
			cr_assert_eq(matrix->data[r][c], 0.0, "MatrixZero should initialize all elements to zero");
		}
	}
	MatrixFree(matrix);
}

Test(MatrixZeroLike, invalid_matrix) {
	Matrix *matrix = MatrixZeroLike(NULL);
	cr_assert_null(matrix, "MatrixZeroLike should return NULL when passed an invalid matrix");
}

Test(MatrixOne, valid_size) {
	Matrix *matrix = MatrixOne(2, 3);
	cr_assert_not_null(matrix, "MatrixOne should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 2, "MatrixOne should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixOne should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixOne should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 1., "MatrixOne should set all elements to 1");
		}
	}
	MatrixFree(matrix);
}

Test(MatrixOneLike, invalid_matrix) {
	Matrix *matrix = MatrixOneLike(NULL);
	cr_assert_null(matrix, "MatrixOneLike should return NULL when passed an invalid matrix");
}

Test(MatrixN, valid_size_and_value) {
    Matrix *matrix = MatrixN(2, 3, 5.);
    cr_assert_not_null(matrix, "MatrixN should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 2, "MatrixN should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 3, "MatrixN should set the correct number of columns");
    for (unsigned int r = 0; r < matrix->num_rows; r++)
    {
        for (unsigned int c = 0; c < matrix->num_cols; c++)
        {
            cr_assert_eq(matrix->data[r][c], 5., "MatrixN should set all elements to the given value");
        }
    }
    MatrixFree(matrix);
}

Test(MatrixNLike, invalid_matrix) {
    Matrix *matrix = MatrixNLike(NULL, 10.);
    cr_assert_null(matrix, "MatrixNLike should return NULL when passed an invalid matrix");
}

Test(MatrixIdentity, valid_size) {
    Matrix *matrix = MatrixIdentity(3);
    cr_assert_not_null(matrix, "MatrixIdentity should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 3, "MatrixIdentity should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 3, "MatrixIdentity should set the correct number of columns");
    cr_assert_eq(matrix->is_square, true, "MatrixIdentity should set is_square to true for a square matrix");
    cr_assert_eq(matrix->data[0][0], 1.0, "MatrixIdentity should set the diagonal elements to 1");
    cr_assert_eq(matrix->data[1][1], 1.0, "MatrixIdentity should set the diagonal elements to 1");
    cr_assert_eq(matrix->data[2][2], 1.0, "MatrixIdentity should set the diagonal elements to 1");
    MatrixFree(matrix);
}

Test(MatrixIdentityLike, invalid_matrix) {
    Matrix *matrix = MatrixIdentityLike(NULL);
    cr_assert_null(matrix, "MatrixIdentityLike should return NULL when passed an invalid matrix");
}

Test(MatrixIdentityLike, non_square_matrix) {
    Matrix *matrix = MatrixNew(2, 3);
    Matrix *identity = MatrixIdentityLike(matrix);
    cr_assert_null(identity, "MatrixIdentityLike should return NULL when passed a non-square matrix");
    MatrixFree(matrix);
}

Test(MatrixEye, valid_k) {
    Matrix *matrix = MatrixEye(4, 1);
    cr_assert_not_null(matrix, "MatrixEye should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 4, "MatrixEye should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 4, "MatrixEye should set the correct number of columns");
    cr_assert_eq(matrix->is_square, true, "MatrixEye should set is_square to true for a square matrix");
    cr_assert_eq(matrix->data[0][1], 1.0, "MatrixEye should set the correct value for k = 1");
    cr_assert_eq(matrix->data[1][2], 1.0, "MatrixEye should set the correct value for k = 1");
    cr_assert_eq(matrix->data[2][3], 1.0, "MatrixEye should set the correct value for k = 1");
    cr_assert_eq(matrix->data[3][3], 1.0, "MatrixEye should set the correct value for k = 1");
    MatrixFree(matrix);
}

Test(MatrixEye, invalid_k) {
    Matrix *matrix = MatrixEye(4, 4);
    cr_assert_null(matrix, "MatrixEye should return NULL for an invalid k");
}

Test(MatrixEyeLike, valid_k) {
    Matrix *m = MatrixSquare(4);
    Matrix *matrix = MatrixEyeLike(m, -1);
    cr_assert_not_null(matrix, "MatrixEyeLike should return a non-NULL pointer");
    cr_assert_eq(matrix->num_rows, 4, "MatrixEyeLike should set the correct number of rows");
    cr_assert_eq(matrix->num_cols, 4, "MatrixEyeLike should set the correct number of columns");
    cr_assert_eq(matrix->is_square, true, "MatrixEyeLike should set is_square to true for a square matrix");
    cr_assert_eq(matrix->data[1][0], 1.0, "MatrixEyeLike should set the correct value for k = -1");
    cr_assert_eq(matrix->data[2][1], 1.0, "MatrixEyeLike should set the correct value for k = -1");
    cr_assert_eq(matrix->data[3][2], 1.0, "MatrixEyeLike should set the correct value for k = -1");
    cr_assert_eq(matrix->data[0][0], 1.0, "MatrixEyeLike should set the correct value for k = -1");
    MatrixFree(m);
    MatrixFree(matrix);
}

Test(MatrixEyeLike, invalid_matrix) {
    Matrix *matrix = MatrixEyeLike(NULL, 1);
    cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed an invalid matrix");
}

Test(MatrixEyeLike, non_square_matrix) {
    Matrix *m = MatrixNew(3, 4);
    Matrix *matrix = MatrixEyeLike(m, 1);
    cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed a non-square matrix");
    MatrixFree(m);
}

Test(MatrixARange, invalid_start_stop_values) {
	Matrix *matrix = MatrixARange(5, 1, 1);
	cr_assert_null(matrix, "MatrixARange should return NULL when passed invalid start and stop values");

	matrix = MatrixARange(1, 5, -1);
	cr_assert_null(matrix, "MatrixARange should return NULL when passed invalid step value");

	matrix = MatrixARange(1, 5, 0);
	cr_assert_null(matrix, "MatrixARange should return NULL when passed invalid step value");

	matrix = MatrixARange(1, 5, 2);
	cr_assert_not_null(matrix, "MatrixARange should return a valid matrix when passed valid start, stop, and step values");

	matrix = MatrixARange(1, 5, 1);
	cr_assert_not_null(matrix, "MatrixARange should return a valid matrix when passed valid start, stop, and step values");

	matrix = MatrixARange(1, 6, 2);
	cr_assert_not_null(matrix, "MatrixARange should return a valid matrix when passed valid start, stop, and step values");

	matrix = MatrixARange(-3, 3, 2);
	cr_assert_not_null(matrix, "MatrixARange should return a valid matrix when passed valid start, stop, and step values");
}

Test(MatrixLinearSpace, invalid_n) {
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 1;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed n < 2");
}

Test(MatrixLinearSpace, invalid_start_stop) {
	double start = 1.0;
	double stop = 0.0;
	unsigned int n = 10;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed start >= stop");
}

Test(MatrixLinearSpace, basic_test) {
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 5;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	double expected[] = {0.0, 0.25, 0.5, 0.75, 1.0};
	for (unsigned int i = 0; i < n; i++) {
		cr_assert_double_eq(matrix->data[0][i], expected[i], 1e-6, "MatrixLinearSpace output for element %d is %f but expected %f", i, matrix->data[0][i], expected[i]);
	}
	MatrixFree(matrix);
}

Test(matrix_test, test_matrix_initialization)
{
    Matrix* a = MatrixIdentity(4);
    cr_assert_float_eq(MatrixTrace(a), 4., 0.001);
    
    Matrix* i = MatrixZero(4, 4);
    cr_assert_float_eq(MatrixTrace(i), 0., 0.001);
        
    Matrix* s = MatrixSquare(1);
    cr_assert_float_eq(MatrixTrace(s), 0., 0.001);
    
    Matrix* o = MatrixOne(9, 9);
    cr_assert_float_eq(MatrixTrace(o), 9., 0.001);
}

Test(MatrixLogSpace, invalid_n) {
    Matrix *matrix = MatrixLogSpace(1.0, 10.0, 1);
    cr_assert_null(matrix, "MatrixLogSpace should return NULL when passed n < 2");
}

Test(MatrixLogSpace, invalid_start_stop) {
    Matrix *matrix1 = MatrixLogSpace(10.0, 1.0, 5);
    cr_assert_null(matrix1, "MatrixLogSpace should return NULL when passed start >= stop");

    Matrix *matrix2 = MatrixLogSpace(1.0, 1.0, 5);
    cr_assert_null(matrix2, "MatrixLogSpace should return NULL when passed start == stop");
}

Test(MatrixLogSpace, valid_inputs) {
    Matrix *matrix = MatrixLogSpace(1.0, 10.0, 5);

    cr_assert_not_null(matrix, "MatrixLogSpace should return a non-null matrix");

    // Check the dimensions of the matrix
    cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
    cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

    // Check the values of the matrix
    cr_assert_eq(matrix->data[0][0], 10.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][1], 31.622776601683793, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][2], 100.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][3], 316.22776601683796, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][4], 1000.0, "Incorrect value in matrix");

    MatrixFree(matrix);
}

Test(MatrixGeometrySpace, invalid_n) {
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 0);
	cr_assert_null(matrix, "MatrixGeometrySpace should return NULL when passed n == 0");
}

Test(MatrixGeometrySpace, invalid_start_stop) {
	Matrix *matrix1 = MatrixGeometrySpace(10.0, 1.0, 5);
	cr_assert_null(matrix1, "MatrixGeometrySpace should return NULL when passed start >= stop");

Matrix *matrix2 = MatrixGeometrySpace(1.0, 1.0, 5);
	cr_assert_null(matrix2, "MatrixGeometrySpace should return NULL when passed start == stop");
}

Test(MatrixGeometrySpace, valid_inputs) {
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 5);
	cr_assert_not_null(matrix, "MatrixGeometrySpace should return a non-null matrix");

	// Check the dimensions of the matrix
	cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
	cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

	// Check the values of the matrix
	cr_assert_eq(matrix->data[0][0], 1.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][1], 2.5118864315095824, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][2], 6.309573444801933, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][3], 15.848931924611133, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][4], 39.810717055349734, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixFrom, invalid_values) {
    const double values[] = {1.0, 2.0, 3.0};
    Matrix *matrix = MatrixFrom(2, 2, 1, values);
    cr_assert_null(matrix, "MatrixFrom should return NULL when passed n_values < num_rows * num_cols");

    MatrixFree(matrix);
}

Test(MatrixFrom, valid_values) {
    const double values[] = {1.0, 2.0, 3.0, 4.0};
    Matrix *matrix = MatrixFrom(2, 2, 4, values);

    cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

    // Check the dimensions of the matrix
    cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
    cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

    // Check the values of the matrix
    cr_assert_eq(matrix->data[0][0], 1.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][1], 2.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[1][0], 3.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[1][1], 4.0, "Incorrect value in matrix");

    MatrixFree(matrix);
}

Test(MatrixFrom, empty_values) {
    const double values[] = {};
    Matrix *matrix = MatrixFrom(2, 2, 0, values);

    cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

    // Check the dimensions of the matrix
    cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
    cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

    // Check that all values are set to 0
    cr_assert_eq(matrix->data[0][0], 0.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[0][1], 0.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[1][0], 0.0, "Incorrect value in matrix");
    cr_assert_eq(matrix->data[1][1], 0.0, "Incorrect value in matrix");

    MatrixFree(matrix);
}

Test(MatrixCopy, non_null_input) {
    // Create a matrix to copy
    double data[4] = {1.0, 2.0, 3.0, 4.0};
    Matrix *m1 = MatrixFrom(2, 2, 4, data);

    // Copy the matrix
    Matrix *m2 = MatrixCopy(m1);

    // Check the dimensions of the copied matrix
    cr_assert_eq(m2->num_rows, m1->num_rows, "Copied matrix has incorrect number of rows");
    cr_assert_eq(m2->num_cols, m1->num_cols, "Copied matrix has incorrect number of columns");

    // Check the values of the copied matrix
    cr_assert_eq(m2->data[0][0], m1->data[0][0], "Incorrect value in copied matrix");
    cr_assert_eq(m2->data[0][1], m1->data[0][1], "Incorrect value in copied matrix");
    cr_assert_eq(m2->data[1][0], m1->data[1][0], "Incorrect value in copied matrix");
    cr_assert_eq(m2->data[1][1], m1->data[1][1], "Incorrect value in copied matrix");

    // Free the matrices
    MatrixFree(m1);
    MatrixFree(m2);
}

Test(MatrixCopy, null_input) {
    Matrix *m = NULL;
    Matrix *copy = MatrixCopy(m);
    cr_assert_null(copy, "Copying a null matrix should return a null matrix");
}

Test(IsMatrixEqualDim, same_dimensions) {
    Matrix *matrix1 = MatrixNew(2, 3);
    Matrix *matrix2 = MatrixNew(2, 3);

    cr_assert(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have same dimensions");

    MatrixFree(matrix1);
    MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, different_rows) {
    Matrix *matrix1 = MatrixNew(2, 3);
    Matrix *matrix2 = MatrixNew(3, 3);

    cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different rows");

    MatrixFree(matrix1);
    MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, different_columns) {
    Matrix *matrix1 = MatrixNew(2, 3);
    Matrix *matrix2 = MatrixNew(2, 2);

    cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different columns");

    MatrixFree(matrix1);
    MatrixFree(matrix2);
}

Test(PrintMatrix, valid_input) {
    Matrix *matrix = MatrixNew(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 3.0;
    matrix->data[1][1] = 4.0;

    PrintMatrix(matrix, "%.2f");

    MatrixFree(matrix);
}

Test(PrintMatrix, invalid_input) {
    PrintMatrix(NULL, "%.2f");
}

Test(IsMatrixInvertible, invertible_matrix) {
    Matrix *matrix = MatrixNew(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 3.0;
    matrix->data[1][1] = 4.0;

    cr_assert(IsMatrixInvertible(matrix), "Matrix should be invertible");

    MatrixFree(matrix);
}

Test(IsMatrixInvertible, non_invertible_matrix) {
    Matrix *matrix = MatrixNew(2, 2);
    matrix->data[0][0] = 1.0;
    matrix->data[0][1] = 2.0;
    matrix->data[1][0] = 2.0;
    matrix->data[1][1] = 4.0;

    cr_assert_not(IsMatrixInvertible(matrix), "Matrix should not be invertible");

    MatrixFree(matrix);
}

Test(IsMatrixInvertible, invalid_input) {
    cr_assert_not(IsMatrixInvertible(NULL), "NULL matrix should not be invertible");
}

Test(MatrixGet, tests) {
	// Test 1: Get element from a 2x2 matrix
	double values1[] = { 1., 2., 3., 4. };
	Matrix *m1 = MatrixFrom(2, 2, 4, values1);
	double elem1 = MatrixGet(m1, 1, 0);
	assert(elem1 == 3.);

	// Test 2: Get element from a 3x3 matrix
	double values2[] = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };
	Matrix *m2 = MatrixFrom(3, 3, 9, values2);
	double elem2 = MatrixGet(m2, 2, 2);
	assert(elem2 == 9.);

	// Test 3: Get element from an empty matrix
	Matrix *m3 = MatrixNew(0, 0);
	double elem3 = MatrixGet(m3, 0, 0);
	assert(elem3 == 0.);

	// Test 4: Get element from an out-of-bounds row
	double values4[] = { 1., 2., 3., 4. };
	Matrix *m4 = MatrixFrom(2, 2, 4, values4);
	double elem4 = MatrixGet(m4, 2, 1);
	assert(elem4 == 0.);

	// Test 5: Get element from an out-of-bounds column
	double values5[] = { 1., 2., 3., 4. };
	Matrix *m5 = MatrixFrom(2, 2, 4, values5);
	double elem5 = MatrixGet(m5, 1, 2);
	assert(elem5 == 0.);
}

Test(matrix_test, matrix_operations)
{
    {
        double values1[] = { 1., 2., 3., 4., 5., 1. };
        double values2[] = { 2., 4. };
        Matrix* a = MatrixFrom(3, 2, 6, values1);
        Matrix* b = MatrixFrom(2, 1, 2, values2);
        Matrix* res = MatrixMultiply(a, b);
        cr_assert_float_eq(MatrixGet(res, 1, 0), 22., 0.001);
    }
    {
        double values[] = { 1., 3., 5., 9., 1., 3., 1., 7., 4., 3., 9., 7., 5., 2., 0., 9. };
        Matrix* ref = MatrixFrom(4, 4, 16, values);
        Matrix* re = MatrixRowEchelonGet(ref);
        cr_assert_float_eq(MatrixTrace(re), 4., 0.001);
    }
    {
        double values[] = { 1., 1., 1., 1., 1., 0., -3., -6., 4., 9., -1., -2., -1., 3., 1., -2., -3., 0., 3., -1., 1., 4., 5., -9., -7., };
        Matrix* ref = MatrixFrom(5, 5, 25, values);
        Matrix* re = MatrixReducedRowEchelonGet(ref);
        cr_assert_float_eq(MatrixTrace(re), 4., 0.001);

    }
    {
        double values[] = { 1. };
        Matrix* m = MatrixFrom(1, 1, 1, values);
        Matrix* bm = MatrixBroadcastRowsAndColumns(m, 10, 10);
        cr_assert_float_eq(MatrixTrace(bm), 10., 0.001);
    }
    {
        double values[] = { 0., 10., 20., 30. };
        double values1[] = { 1., 2., 3., 4.};
        Matrix* m = MatrixFrom(4, 1, 4, values);
        Matrix* m1 = MatrixFrom(1, 4, 4, values1);
        Matrix* res = MatrixAddWithBroadcast(m, m1);
        cr_assert_float_eq(MatrixTrace(res), 70., 0.001);
    }
}

