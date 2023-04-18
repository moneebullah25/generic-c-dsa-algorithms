#include <criterion/criterion.h>
#include "../includes/c_helper.h"
#include "../includes/c_matrix.h"

Test(MatrixEmpty, invalid_num_rows)
{
	Matrix *matrix = MatrixEmpty(0, 5);
	cr_assert_null(matrix, "MatrixEmpty should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixEmpty, invalid_num_cols)
{
	Matrix *matrix = MatrixEmpty(5, 0);
	cr_assert_null(matrix, "MatrixEmpty should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixEmptyLike, NULL_matrix)
{
	Matrix *matrix = MatrixEmptyLike(NULL);
	cr_assert_null(matrix, "MatrixEmptyLike should return NULL when a NULL matrix is passed");
	MatrixFree(matrix);
}

Test(MatrixEmptyLike, valid_matrix)
{
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
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 0., "MatrixEmptyLike should initialize all elements to 0");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixEmpty, v alid_arguments)
{
	Matrix *matrix = MatrixEmpty(3, 4);
	cr_assert_not_null(matrix, "MatrixEmpty should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixEmpty should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixEmpty should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixEmpty should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 0., "MatrixEmpty should initialize all elements to 0");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixNew, invalid_num_rows)
{
	Matrix *matrix = MatrixNew(0, 5);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixNew, invalid_num_cols)
{
	Matrix *matrix = MatrixNew(5, 0);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixNew, valid_arguments)
{
	Matrix *matrix = MatrixNew(3, 4);
	cr_assert_not_null(matrix, "MatrixNew should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixNew should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixNew should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixNew should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 0., "MatrixNew should initialize all elements to 0");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixNewLike, invalid_matrix)
{
	Matrix *m = NULL;
	Matrix *matrix = MatrixNewLike(m);
	cr_assert_null(matrix, "MatrixNewLike should return NULL when invalid matrix is passed");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixNewLike, valid_matrix)
{
	Matrix *m = MatrixNew(3, 4);
	Matrix *matrix = MatrixNewLike(m);
	cr_assert_not_null(matrix, "MatrixNewLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, m->num_rows, "MatrixNewLike should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, m->num_cols, "MatrixNewLike should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixNewLike should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 0., "MatrixNewLike should initialize all elements to 0");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixRandom, invalid_num_rows)
{
	Matrix *matrix = MatrixRandom(0, 5, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixRandom, invalid_num_cols)
{
	Matrix *matrix = MatrixRandom(5, 0, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixRandom, valid_arguments)
{
	unsigned int num_rows = 3;
	unsigned int num_cols = 4;
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixRandom(num_rows, num_cols, min, max);
	cr_assert_not_null(matrix, "MatrixRandom should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, num_rows, "MatrixRandom should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, num_cols, "MatrixRandom should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixRandom should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_geq(matrix->data[r][c], min, "MatrixRandom should generate values greater than or equal to the minimum");
			cr_assert_leq(matrix->data[r][c], max, "MatrixRandom should generate values less than or equal to the maximum");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixRandomLike, invalid_matrix)
{
	Matrix *m = NULL;
	Matrix *matrix = MatrixRandomLike(m, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandomLike should return NULL when an invalid matrix is passed");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixRandomLike, valid_matrix)
{
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
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_geq(matrix->data[r][c], min, "MatrixRandomLike should generate values greater than or equal to the minimum");
			cr_assert_leq(matrix->data[r][c], max, "MatrixRandomLike should generate values less than or equal to the maximum");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquare, valid_size)
{
	Matrix *matrix = MatrixSquare(3);
	cr_assert_not_null(matrix, "MatrixSquare should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixSquare should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixSquare should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixSquare should set is_square to true for a square matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareLike, invalid_matrix)
{
	Matrix *matrix = MatrixSquareLike(NULL);
	cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareLike, non_square_matrix)
{
	Matrix *m = MatrixNew(2, 3);
	Matrix *matrix = MatrixSquareLike(m);
	cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed a non-square matrix");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquareLike, valid_matrix)
{
	Matrix *m = MatrixSquare(4);
	Matrix *matrix = MatrixSquareLike(m);
	cr_assert_not_null(matrix, "MatrixSquareLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 4, "MatrixSquareLike should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixSquareLike should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixSquareLike should set is_square to true for a square matrix");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquareRandom, valid_size_and_range)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandom(3, min, max);
	cr_assert_not_null(matrix, "MatrixSquareRandom should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixSquareRandom should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixSquareRandom should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixSquareRandom should set is_square to true for a square matrix");
	bool in_range = true;
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			if (matrix->data[r][c] < min || matrix->data[r][c] > max)
			{
				in_range = false;
				break;
			}
		}
	}

	cr_assert_eq(in_range, true, "MatrixSquareRandom should set all elements within the specified range");

	MatrixFree(matrix);
}

Test(MatrixSquareRandom, invalid_size)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandom(0, min, max);
	cr_assert_null(matrix, "MatrixSquareRandom should return NULL when passed an invalid size");
	MatrixFree(matrix);
}

Test(MatrixSquareRandomLike, invalid_matrix)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandomLike(NULL, min, max);
	cr_assert_null(matrix, "MatrixSquareRandomLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareRandomLike, not_square_matrix)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixNew(2, 3);
	cr_assert_null(MatrixSquareRandomLike(matrix, min, max), "MatrixSquareRandomLike should return NULL when passed a non-square matrix");
	MatrixFree(matrix);
}

Test(MatrixZero, valid_size)
{
	Matrix *matrix = MatrixZero(3, 2);
	cr_assert_not_null(matrix, "MatrixZero should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixZero should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 2, "MatrixZero should set the correct number of columns");
	cr_assert_eq(matrix->is_square, false, "MatrixZero should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(matrix->data[r][c], 0.0, "MatrixZero should initialize all elements to zero");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixZeroLike, invalid_matrix)
{
	Matrix *matrix = MatrixZeroLike(NULL);
	cr_assert_null(matrix, "MatrixZeroLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixOne, valid_size)
{
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

Test(MatrixOneLike, invalid_matrix)
{
	Matrix *matrix = MatrixOneLike(NULL);
	cr_assert_null(matrix, "MatrixOneLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixN, valid_size_and_value)
{
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

Test(MatrixNLike, invalid_matrix)
{
	Matrix *matrix = MatrixNLike(NULL, 10.);
	cr_assert_null(matrix, "MatrixNLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixIdentity, valid_size)
{
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

Test(MatrixIdentityLike, invalid_matrix)
{
	Matrix *matrix = MatrixIdentityLike(NULL);
	cr_assert_null(matrix, "MatrixIdentityLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixIdentityLike, non_square_matrix)
{
	Matrix *matrix = MatrixNew(2, 3);
	Matrix *identity = MatrixIdentityLike(matrix);
	cr_assert_null(identity, "MatrixIdentityLike should return NULL when passed a non-square matrix");
	MatrixFree(matrix);
	MatrixFree(identity);
}

Test(MatrixEye, valid_k)
{
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

Test(MatrixEye, invalid_k)
{
	Matrix *matrix = MatrixEye(4, 4);
	cr_assert_null(matrix, "MatrixEye should return NULL for an invalid k");
	MatrixFree(matrix);
}

Test(MatrixEyeLike, valid_k)
{
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

Test(MatrixEyeLike, invalid_matrix)
{
	Matrix *matrix = MatrixEyeLike(NULL, 1);
	cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixEyeLike, non_square_matrix)
{
	Matrix *m = MatrixNew(3, 4);
	Matrix *matrix = MatrixEyeLike(m, 1);
	cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed a non-square matrix");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixARange, invalid_start_stop_values)
{
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

	MatrixFree(matrix);
}

Test(MatrixLinearSpace, invalid_n)
{
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 1;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed n<2");

	MatrixFree(matrix);
}

Test(MatrixLinearSpace, invalid_start_stop)
{
	double start = 1.0;
	double stop = 0.0;
	unsigned int n = 10;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed start >= stop");
	MatrixFree(matrix);
}

Test(MatrixLinearSpace, basic_test)
{
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 5;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	double expected[] = { 0.0, 0.25, 0.5, 0.75, 1.0 };

	for (unsigned int i = 0; i < n; i++)
	{
		cr_assert_double_eq(matrix->data[0][i], expected[i], 1e-6, "MatrixLinearSpace output for element %d is %f but expected %f", i, matrix->data[0][i], expected[i]);
	}

	MatrixFree(matrix);
}

Test(MatrixLogSpace, invalid_n)
{
	Matrix *matrix = MatrixLogSpace(1.0, 10.0, 1);
	cr_assert_null(matrix, "MatrixLogSpace should return NULL when passed n<2");
	MatrixFree(matrix);
}

Test(MatrixLogSpace, invalid_start_stop)
{
	Matrix *matrix1 = MatrixLogSpace(10.0, 1.0, 5);
	cr_assert_null(matrix1, "MatrixLogSpace should return NULL when passed start >= stop");

	Matrix *matrix2 = MatrixLogSpace(1.0, 1.0, 5);
	cr_assert_null(matrix2, "MatrixLogSpace should return NULL when passed start == stop");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(MatrixLogSpace, valid_inputs)
{
	Matrix *matrix = MatrixLogSpace(1.0, 10.0, 5);

	cr_assert_not_null(matrix, "MatrixLogSpace should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
	cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

	cr_assert_eq(matrix->data[0][0], 10.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][1], 31.622776601683793, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][2], 100.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][3], 316.22776601683796, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][4], 1000.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixGeometrySpace, invalid_n)
{
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 0);
	cr_assert_null(matrix, "MatrixGeometrySpace should return NULL when passed n == 0");

	MatrixFree(matrix);
}

Test(MatrixGeometrySpace, invalid_start_stop)
{
	Matrix *matrix1 = MatrixGeometrySpace(10.0, 1.0, 5);
	cr_assert_null(matrix1, "MatrixGeometrySpace should return NULL when passed start >= stop");

	Matrix *matrix2 = MatrixGeometrySpace(1.0, 1.0, 5);
	cr_assert_null(matrix2, "MatrixGeometrySpace should return NULL when passed start == stop");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(MatrixGeometrySpace, valid_inputs)
{
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 5);
	cr_assert_not_null(matrix, "MatrixGeometrySpace should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
	cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

	cr_assert_eq(matrix->data[0][0], 1.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][1], 2.5118864315095824, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][2], 6.309573444801933, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][3], 15.848931924611133, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][4], 39.810717055349734, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixFrom, invalid_values)
{
	const double values[] = { 1.0, 2.0, 3.0 };

	Matrix *matrix = MatrixFrom(2, 2, 1, values);
	cr_assert_null(matrix, "MatrixFrom should return NULL when passed n_values < num_rows *num_cols");

	MatrixFree(matrix);
}

Test(MatrixFrom, valid_values)
{
	const double values[] = { 1.0, 2.0, 3.0, 4.0 };

	Matrix *matrix = MatrixFrom(2, 2, 4, values);

	cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
	cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

	cr_assert_eq(matrix->data[0][0], 1.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][1], 2.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[1][0], 3.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[1][1], 4.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixFrom, empty_values)
{
	const double values[] = {};

	Matrix *matrix = MatrixFrom(2, 2, 0, values);

	cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
	cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

	cr_assert_eq(matrix->data[0][0], 0.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[0][1], 0.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[1][0], 0.0, "Incorrect value in matrix");
	cr_assert_eq(matrix->data[1][1], 0.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixCopy, non_null_input)
{

	double data[4] = { 1.0, 2.0, 3.0, 4.0 };

	Matrix *m1 = MatrixFrom(2, 2, 4, data);

	Matrix *m2 = MatrixCopy(m1);

	cr_assert_eq(m2->num_rows, m1->num_rows, "Copied matrix has incorrect number of rows");
	cr_assert_eq(m2->num_cols, m1->num_cols, "Copied matrix has incorrect number of columns");

	cr_assert_eq(m2->data[0][0], m1->data[0][0], "Incorrect value in copied matrix");
	cr_assert_eq(m2->data[0][1], m1->data[0][1], "Incorrect value in copied matrix");
	cr_assert_eq(m2->data[1][0], m1->data[1][0], "Incorrect value in copied matrix");
	cr_assert_eq(m2->data[1][1], m1->data[1][1], "Incorrect value in copied matrix");

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixCopy, null_input)
{
	Matrix *m = NULL;
	Matrix *copy = MatrixCopy(m);
	cr_assert_null(copy, "Copying a null matrix should return a null matrix");
	MatrixFree(m);
	MatrixFree(copy);
}

Test(IsMatrixEqualDim, same_dimensions)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(2, 3);

	cr_assert(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have same dimensions");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, different_rows)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(3, 3);

	cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different rows");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, different_columns)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(2, 2);

	cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different columns");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(PrintMatrix, valid_input)
{
	Matrix *matrix = MatrixNew(2, 2);
	matrix->data[0][0] = 1.0;
	matrix->data[0][1] = 2.0;
	matrix->data[1][0] = 3.0;
	matrix->data[1][1] = 4.0;

	PrintMatrix(matrix, "%.2f");

	MatrixFree(matrix);
}

Test(PrintMatrix, invalid_input)
{
	PrintMatrix(NULL, "%.2f");
}

Test(IsMatrixInvertible, invertible_matrix)
{
	Matrix *matrix = MatrixNew(2, 2);
	matrix->data[0][0] = 1.0;
	matrix->data[0][1] = 2.0;
	matrix->data[1][0] = 3.0;
	matrix->data[1][1] = 4.0;

	cr_assert(IsMatrixInvertible(matrix), "Matrix should be invertible");

	MatrixFree(matrix);
}

Test(IsMatrixInvertible, non_invertible_matrix)
{
	Matrix *matrix = MatrixNew(2, 2);
	matrix->data[0][0] = 1.0;
	matrix->data[0][1] = 2.0;
	matrix->data[1][0] = 2.0;
	matrix->data[1][1] = 4.0;

	cr_assert_not(IsMatrixInvertible(matrix), "Matrix should not be invertible");

	MatrixFree(matrix);
}

Test(IsMatrixInvertible, invalid_input)
{
	cr_assert_not(IsMatrixInvertible(NULL), "NULL matrix should not be invertible");
}

Test(MatrixGet, tests)
{

	double values1[] = { 1., 2., 3., 4. };

	Matrix *m1 = MatrixFrom(2, 2, 4, values1);
	double elem1 = MatrixGet(m1, 1, 0);
	assert(elem1 == 3.);

	double values2[] = { 1., 2., 3., 4., 5., 6., 7., 8., 9. };

	Matrix *m2 = MatrixFrom(3, 3, 9, values2);
	double elem2 = MatrixGet(m2, 2, 2);
	assert(elem2 == 9.);

	Matrix *m3 = MatrixNew(0, 0);
	double elem3 = MatrixGet(m3, 0, 0);
	assert(elem3 == NAN);

	double values4[] = { 1., 2., 3., 4. };

	Matrix *m4 = MatrixFrom(2, 2, 4, values4);
	double elem4 = MatrixGet(m4, 2, 1);
	assert(elem4 == NAN);

	double values5[] = { 1., 2., 3., 4. };

	Matrix *m5 = MatrixFrom(2, 2, 4, values5);
	double elem5 = MatrixGet(m5, 1, 2);
	assert(elem5 == NAN);

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(m3);
	MatrixFree(m4);
	MatrixFree(m5);
}

Test(MatrixColumnGet, valid_input)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *column = MatrixColumnGet(m, 1);
	cr_assert(column != NULL, "MatrixColumnGet should return non-NULL");

	cr_assert_eq(column->num_rows, 2, "Matrix column has incorrect number of rows");
	cr_assert_eq(column->num_cols, 1, "Matrix column has incorrect number of columns");

	cr_assert_eq(column->data[0][0], 2, "Matrix column has incorrect value at row 0, col 0");
	cr_assert_eq(column->data[1][0], 5, "Matrix column has incorrect value at row 1, col 0");

	MatrixFree(m);
	MatrixFree(column);
}

Test(MatrixColumnGet, invalid_input)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *column = MatrixColumnGet(m, 3);
	cr_assert(column == NULL, "MatrixColumnGet should return NULL for invalid column index");

	MatrixFree(m);
}

Test(MatrixRowGet, valid_input)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *row = MatrixRowGet(m, 0);
	cr_assert(row != NULL, "MatrixRowGet should return non-NULL");

	cr_assert_eq(row->num_rows, 1, "Matrix row has incorrect number of rows");
	cr_assert_eq(row->num_cols, 3, "Matrix row has incorrect number of columns");

	cr_assert_eq(row->data[0][0], 1, "Matrix row has incorrect value at row 0, col 0");
	cr_assert_eq(row->data[0][1], 2, "Matrix row has incorrect value at row 0, col 1");
	cr_assert_eq(row->data[0][2], 3, "Matrix row has incorrect value at row 0, col 2");

	MatrixFree(m);
	MatrixFree(row);
}

Test(MatrixRowGet, invalid_input)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *row = MatrixRowGet(m, 2);
	cr_assert(row == NULL, "MatrixRowGet should return NULL for invalid row index");

	MatrixFree(m);
}

Test(MatrixSet, test_null_matrix)
{

	Matrix *m = NULL;
	MatrixSet(m, 0, 0, 1.0);

	cr_assert(1);
}

Test(MatrixSet, test_invalid_row)
{

	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 2, 0, 1.0);

	MatrixFree(m);
	cr_assert(1);
}

Test(MatrixSet, test_invalid_col)
{

	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 2, 1.0);

	MatrixFree(m);
	cr_assert(1);
}

Test(MatrixSet, test_valid_set)
{

	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	cr_assert_eq(MatrixGet(m, 0, 0), 1.0);
	MatrixFree(m);
}

Test(MatrixAllSet, NullMatrix)
{
	Matrix *m = NULL;
	MatrixAllSet(m, 1.);
	cr_assert(1);	
}

Test(MatrixAllSet, SetAllElements)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixAllSet(m, 1.);
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		for (unsigned int j = 0; j < m->num_cols; j++)
		{
			cr_assert_eq(m->data[i][j], 1.);
		}
	}

	MatrixFree(m);
}

Test(MatrixAllSet, SetZeroElements)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixAllSet(m, 0.);
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		for (unsigned int j = 0; j < m->num_cols; j++)
		{
			cr_assert_eq(m->data[i][j], 0.);
		}
	}

	MatrixFree(m);
}

Test(MatrixDiagonalSet, NullMatrix)
{
	Matrix *m = NULL;
	MatrixDiagonalSet(m, 1.);
	cr_assert(1);	
}

Test(MatrixDiagonalSet, NonSquareMatrix)
{
	Matrix *m = MatrixNew(2, 3);
	MatrixDiagonalSet(m, 1.);
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		for (unsigned int j = 0; j < m->num_cols; j++)
		{
			if (i == j)
			{
				cr_assert_eq(m->data[i][j], 1.);
			}
			else
			{
				cr_assert_eq(m->data[i][j], 0.);
			}
		}
	}

	MatrixFree(m);
}

Test(MatrixDiagonalSet, SetDiagonalElements)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixDiagonalSet(m, 1.);
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		for (unsigned int j = 0; j < m->num_cols; j++)
		{
			if (i == j)
			{
				cr_assert_eq(m->data[i][j], 1.);
			}
			else
			{
				cr_assert_eq(m->data[i][j], 0.);
			}
		}
	}

	MatrixFree(m);
}

Test(MatrixRowMultiplyValue, InvalidMatrixPassed)
{
	Matrix *m = NULL;
	MatrixRowMultiplyValue(m, 0, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
}

Test(MatrixRowMultiplyValue, InvalidRowPassed)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixRowMultiplyValue(m, 2, 2.0);
	cr_assert_stderr_eq_str("Invalid 'row=2' passed >= 2\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyValue, MultiplyByOne)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixRowMultiplyValue(m, 0, 1.0);
	cr_assert_eq(MatrixGet(m, 0, 0), 1.0);
	cr_assert_eq(MatrixGet(m, 0, 1), 2.0);
	cr_assert_eq(MatrixGet(m, 1, 0), 3.0);
	cr_assert_eq(MatrixGet(m, 1, 1), 4.0);
	MatrixFree(m);
}

Test(MatrixRowMultiplyValue, MultiplyByTwo)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixRowMultiplyValue(m, 0, 2.0);
	cr_assert_eq(MatrixGet(m, 0, 0), 2.0);
	cr_assert_eq(MatrixGet(m, 0, 1), 4.0);
	cr_assert_eq(MatrixGet(m, 1, 0), 3.0);
	cr_assert_eq(MatrixGet(m, 1, 1), 4.0);
	MatrixFree(m);
}

Test(MatrixRowAddValue, NullMatrix)
{
	Matrix *m = NULL;
	MatrixRowAddValue(m, 0, 1.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
}

Test(MatrixRowAddValue, InvalidRow)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixRowAddValue(m, 3, 1.0);
	cr_assert_stderr_eq_str("Invalid 'row=3' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowAddValue, RowAddition)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixRowAddValue(m, 0, 1.0);
	cr_assert_double_eq(MatrixGet(m, 0, 0), 2.0, 1e-6);
	cr_assert_double_eq(MatrixGet(m, 0, 1), 3.0, 1e-6);
	cr_assert_double_eq(MatrixGet(m, 0, 2), 4.0, 1e-6);
	MatrixFree(m);
}

Test(MatrixColumnMultiplyValue, NullMatrix)
{
	Matrix *m = NULL;
	MatrixColumnMultiplyValue(m, 0, 2.0);

}

Test(MatrixColumnMultiplyValue, InvalidColumn)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyValue(m, 4, 2.0);

	MatrixFree(m);
}

Test(MatrixColumnMultiplyValue, ValidData)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyValue(m, 1, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 4.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 12.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 20.0, 1e-6);
	MatrixFree(m);
}

Test(MatrixColumnAddValue, null_matrix)
{
	Matrix *m = NULL;
	MatrixColumnAddValue(m, 0, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValue, invalid_column)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValue(m, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'col=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValue, valid_input)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValue(m, 2, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 5.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 9.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 13.0, 0.001);
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, null_matrix)
{
	Matrix *m = NULL;
	MatrixRowMultiplyRow(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, invalid_where_row)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, invalid_row)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 2, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'row=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, valid_input)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 1, 0, 2.0);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 8.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 10.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 12.0, 0.001);
	MatrixFree(m);
}

Test(MatrixRowAddRow, null_matrix)
{
	Matrix *m = NULL;
	MatrixRowAddRow(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixRowAddRow, invalid_where_row)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowAddRow(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowAddRow, invalid_row)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowAddRow(m, 2, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'row=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, null_matrix)
{
	Matrix* m = NULL;
	MatrixColumnMultiplyColumn(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, invalid_where)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, invalid_col)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 5, 2.0);
	cr_assert_stderr_eq_str("Invalid 'col=5' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, valid_input)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 1, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 18.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 36.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 54.0, 0.001);
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, null_matrix)
{
	Matrix* m = NULL;
	MatrixColumnAddValueColumn(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, invalid_where)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, invalid_col)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 4, 2, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, invalid_value)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 2, 1, NAN);
	cr_assert_stderr_eq_str("Invalid 'value=nan' passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, valid_input)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 2, 1, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 7.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 11.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 15.0, 0.001);
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, invalid_where)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 4, 2, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, invalid_value)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
	Matrix* m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 1, INFINITY);
	cr_assert_stderr_eq_str("Invalid 'value=inf' passed\n");
	MatrixFree(m);
}

Test(MatrixWholeMultiply, null_matrix)
{
    Matrix* m = NULL;
    MatrixWholeMultiply(m, 2.0);
    cr_assert_stderr_eq_str("Invalid matrix passed\n");
    MatrixFree(m);
}

Test(MatrixWholeMultiply, valid_input)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    Matrix* m = MatrixFrom(3, 4, 12, data);
    MatrixWholeMultiply(m, 2.0);
    cr_assert_float_eq(MatrixGet(m, 0, 0), 2.0, 0.001);
    cr_assert_float_eq(MatrixGet(m, 1, 2), 12.0, 0.001);
    cr_assert_float_eq(MatrixGet(m, 2, 3), 24.0, 0.001);
    MatrixFree(m);
}

Test(MatrixWholeAdd, null_matrix)
{
    Matrix* m = NULL;
    MatrixWholeAdd(m, 2.0);
    cr_assert_stderr_eq_str("Invalid matrix passed\n");
    MatrixFree(m);
}

Test(MatrixWholeAdd, valid_input)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    Matrix* m = MatrixFrom(3, 4, 12, data);
    MatrixWholeAdd(m, 2.0);
    cr_assert_float_eq(MatrixGet(m, 0, 0), 3.0, 0.001);
    cr_assert_float_eq(MatrixGet(m, 1, 2), 9.0, 0.001);
    cr_assert_float_eq(MatrixGet(m, 2, 3), 14.0, 0.001);
    MatrixFree(m);
}

Test(MatrixRowRemove, invalid_matrix)
{
    Matrix *m = NULL;
    Matrix *result = MatrixRowRemove(m, 0);
    cr_assert_null(result, "Expected NULL when passing invalid matrix, but got non-NULL");
}

Test(MatrixRowRemove, invalid_row)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix *m = MatrixFrom(2, 3, 6, data);
    Matrix *result = MatrixRowRemove(m, 2);
    cr_assert_null(result, "Expected NULL when passing invalid row, but got non-NULL");
    MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixRowRemove, remove_first_row)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix *m = MatrixFrom(2, 3, 6, data);
    Matrix *result = MatrixRowRemove(m, 0);
    double expected_data[] = {4.0, 5.0, 6.0};
    Matrix *expected = MatrixFrom(1, 3, 3, expected_data);
    assert_matrix_equal(result, expected);
    MatrixFree(m);
    MatrixFree(result);
    MatrixFree(expected);
}

Test(MatrixColumnRemove, invalid_matrix)
{
    Matrix *m = NULL;
    Matrix *result = MatrixColumnRemove(m, 0);
    cr_assert_null(result, "Expected NULL when passing invalid matrix, but got non-NULL");
}

Test(MatrixColumnRemove, invalid_column)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix *m = MatrixFrom(2, 3, 6, data);
    Matrix *result = MatrixColumnRemove(m, 3);
    cr_assert_null(result, "Expected NULL when passing invalid column, but got non-NULL");
    MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixColumnRemove, remove_first_column)
{
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix *m = MatrixFrom(2, 3, 6, data);
    Matrix *result = MatrixColumnRemove(m, 0);
    double expected_data[] = {2.0, 3.0, 5.0, 6.0};
    Matrix *expected = MatrixFrom(2, 2, 4, expected_data);
    assert_matrix_equal(result, expected);
    MatrixFree(m);
    MatrixFree(result);
    MatrixFree(expected);
}

void assert_matrix_equal(Matrix *m1, Matrix *m2)
{
    cr_assert_eq(m1->num_rows, m2->num_rows, "Expected matrix rows to match, but got %u and %u", m1->num_rows, m2->num_rows);
    cr_assert_eq(m1->num_cols, m2->num_cols, "Expected matrix columns to match, but got %u and %u", m1->num_cols, m2->num_cols);
    for (unsigned int i = 0; i < m1->num_rows; i++)
    {
        for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			if (m1->data[i][j] != m2->data[i][j])
			{
				criterion_assert_fail(
				format_string("Matrices not equal at row=%u, col=%u: expected %lf, but got %lf",
				i, j, m1->data[i][j], m2->data[i][j]));
				return;
			}
		}
	}
	criterion_assert(1);
}

Test(MatrixRowSwap, valid_input)
{

    Matrix *m = MatrixNew(2, 2);
    MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    MatrixSetValue(m, 1, 0, 3.0);
    MatrixSetValue(m, 1, 1, 4.0);
    MatrixRowSwap(m, 0, 1);

    cr_assert_eq(MatrixGetValue(m, 0, 0), 3.0, "Expected row 0, column 0 to be 3.0");
    cr_assert_eq(MatrixGetValue(m, 0, 1), 4.0, "Expected row 0, column 1 to be 4.0");
    cr_assert_eq(MatrixGetValue(m, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(m, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");

    MatrixFree(m);
}

Test(MatrixRowSwap, invalid_input)
{

    Matrix *m = MatrixNew(2, 2);
    MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    MatrixSetValue(m, 1, 0, 3.0);
    MatrixSetValue(m, 1, 1, 4.0);
    MatrixRowSwap(m, 0, 2);

    cr_assert_eq(MatrixGetValue(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
    cr_assert_eq(MatrixGetValue(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
    cr_assert_eq(MatrixGetValue(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

    MatrixFree(m);
}

Test(MatrixColumnSwap, valid_input)
{

    Matrix *m = MatrixNew(2, 2);
    MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    MatrixSetValue(m, 1, 0, 3.0);
    MatrixSetValue(m, 1, 1, 4.0);
    MatrixColumnSwap(m, 0, 1);

    cr_assert_eq(MatrixGetValue(m, 0, 0), 2.0, "Expected row 0, column 0 to be 2.0");
    cr_assert_eq(MatrixGetValue(m, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
    cr_assert_eq(MatrixGetValue(m, 1, 0), 4.0, "Expected row 1, column 0 to be 4.0");
	cr_assert_eq(MatrixGetValue(m, 1, 1), 3.0, "Expected row 1, column 1 to be 3.0");

	MatrixFree(m);
}

Test(MatrixColumnSwap, invalid_matrix)
{
	Matrix *m = NULL;
	MatrixColumnSwap(m, 0, 1);
	MatrixFree(m);
}

Test(MatrixColumnSwap, invalid_column)
{

	Matrix *m = MatrixNew(2, 2);
	MatrixSetValue(m, 0, 0, 1.0);
	MatrixSetValue(m, 0, 1, 2.0);
	MatrixSetValue(m, 1, 0, 3.0);
	MatrixSetValue(m, 1, 1, 4.0);
	MatrixColumnSwap(m, 0, 2);

	cr_assert_eq(MatrixGetValue(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGetValue(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
	cr_assert_eq(MatrixGetValue(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
	cr_assert_eq(MatrixGetValue(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

	MatrixFree(m);
}

Test(MatrixColumnSwap, same_column)
{

	Matrix *m = MatrixNew(2, 2);
	MatrixSetValue(m, 0, 0, 1.0);
	MatrixSetValue(m, 0, 1, 2.0);
	MatrixSetValue(m, 1, 0, 3.0);
	MatrixSetValue(m, 1, 1, 4.0);
	MatrixColumnSwap(m, 1, 1);

	cr_assert_eq(MatrixGetValue(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGetValue(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
	cr_assert_eq(MatrixGetValue(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
	cr_assert_eq(MatrixGetValue(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

	MatrixFree(m);
}

Test(MatrixBroadcastRows, invalid_input_null_matrix)
{
    Matrix *result = MatrixBroadcastRows(NULL, 3);
    cr_assert_null(result, "Expected NULL result for invalid input: NULL matrix");
	MatrixFree(result);
}

Test(MatrixBroadcastRows, invalid_input_num_rows_not_1)
{
    Matrix *m = MatrixNew(2, 2);
    
	MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    MatrixSetValue(m, 1, 0, 3.0);
    MatrixSetValue(m, 1, 1, 4.0);

    Matrix *result = MatrixBroadcastRows(m, 3);

    cr_assert_null(result, "Expected NULL result for invalid input: num_rows not 1");
    MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRows, invalid_input_row_less_than_num_rows)
{
    Matrix *m = MatrixNew(1, 2);
    
	MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);

    Matrix *result = MatrixBroadcastRows(m, 1);

    cr_assert_null(result, "Expected NULL result for invalid input: row less than num_rows");
    MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRows, valid_input)
{
    Matrix *m = MatrixNew(1, 2);
    
	MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);

    Matrix *result = MatrixBroadcastRows(m, 3);

    cr_assert_not_null(result, "Expected non-NULL result for valid input");

    cr_assert_eq(result->num_rows, 3, "Expected num_rows to be 3");
    cr_assert_eq(result->num_cols, 2, "Expected num_cols to be 2");

    cr_assert_eq(MatrixGetValue(result, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");

    cr_assert_eq(MatrixGetValue(result, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");

    cr_assert_eq(MatrixGetValue(result, 2, 0), 1.0, "Expected row 2, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 2, 1), 2.0, "Expected row 2, column 1 to be 2.0");

    MatrixFree(m);
    MatrixFree(result);
}

Test(MatrixBroadcastColumns, valid_input)
{

	Matrix *m = MatrixNew(2, 1);
	
	MatrixSetValue(m, 0, 0, 1.0);
	MatrixSetValue(m, 1, 0, 2.0);
	
	Matrix *broadcasted = MatrixBroadcastColumns(m, 3);

	cr_assert_eq(broadcasted->num_rows, 2, "Expected num_rows to be 2");
	cr_assert_eq(broadcasted->num_cols, 3, "Expected num_cols to be 3");

	cr_assert_eq(MatrixGetValue(broadcasted, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGetValue(broadcasted, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
	cr_assert_eq(MatrixGetValue(broadcasted, 0, 2), 1.0, "Expected row 0, column 2 to be 1.0");
	cr_assert_eq(MatrixGetValue(broadcasted, 1, 0), 2.0, "Expected row 1, column 0 to be 2.0");
	cr_assert_eq(MatrixGetValue(broadcasted, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");
	cr_assert_eq(MatrixGetValue(broadcasted, 1, 2), 2.0, "Expected row 1, column 2 to be 2.0");

	MatrixFree(m);
	MatrixFree(broadcasted);
}

Test(MatrixBroadcastColumns, invalid_input)
{

	Matrix *m = NULL;
	Matrix *broadcasted = MatrixBroadcastColumns(m, 2);

	cr_assert_null(broadcasted, "Expected a NULL matrix to be returned");

	m = MatrixNew(2, 2);
	broadcasted = MatrixBroadcastColumns(m, 3);

	cr_assert_null(broadcasted, "Expected a NULL matrix to be returned");

	broadcasted = MatrixBroadcastColumns(m, 0);

	cr_assert_null(broadcasted, "Expected a NULL matrix to be returned");

	MatrixFree(m);
	MatrixFree(broadcasted);
}

Test(MatrixBroadcastRowsAndColumns, invalid_matrix)
{
    Matrix *m = NULL;
    
	Matrix *result = MatrixBroadcastRowsAndColumns(m, 2, 2);
    cr_assert_null(result, "Expected NULL matrix to be returned for invalid input");
	
	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, invalid_row)
{
    Matrix *m = MatrixNew(1, 2);
    
	MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    
	Matrix *result = MatrixBroadcastRowsAndColumns(m, 0, 2);
    cr_assert_null(result, "Expected NULL matrix to be returned for invalid row");
    
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, invalid_col)
{
    Matrix *m = MatrixNew(1, 2);
    
	MatrixSetValue(m, 0, 0, 1.0);
    MatrixSetValue(m, 0, 1, 2.0);
    
	Matrix *result = MatrixBroadcastRowsAndColumns(m, 2, 0);
    cr_assert_null(result, "Expected NULL matrix to be returned for invalid column");
    
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, valid_input)
{
    Matrix *m = MatrixNew(1, 1);
    MatrixSetValue(m, 0, 0, 1.0);
    
	Matrix *result = MatrixBroadcastRowsAndColumns(m, 3, 2);
    
	cr_assert_not_null(result, "Expected non-NULL matrix to be returned for valid input");
    cr_assert_eq(result->num_rows, 3, "Expected number of rows to be 3");
    cr_assert_eq(result->num_cols, 2, "Expected number of columns to be 2");
    cr_assert_eq(MatrixGetValue(result, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 1, 1), 1.0, "Expected row 1, column 1 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 2, 0), 1.0, "Expected row 2, column 0 to be 1.0");
    cr_assert_eq(MatrixGetValue(result, 2, 1), 1.0, "Expected row 2, column 1 to be 1.0");
    
	MatrixFree(m);
    MatrixFree(result);
}

Test(matrix_row_stack, valid_matrices)
{

    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(2, 3);

    for (unsigned int i = 0; i < m1->num_rows; i++)
    {
        for (unsigned int j = 0; j < m1->num_cols; j++)
        {
            m1->data[i][j] = i * m1->num_cols + j + 1;
            m2->data[i][j] = (i + m1->num_rows) * m2->num_cols + j + 1;
        }
    }

    Matrix *result = MatrixRowStack(m1, m2);

    cr_assert_eq(result->num_rows, 4);
    cr_assert_eq(result->num_cols, 3);

    cr_assert_eq(result->data[0][0], 1);
    cr_assert_eq(result->data[0][1], 2);
    cr_assert_eq(result->data[0][2], 3);
    cr_assert_eq(result->data[1][0], 4);
    cr_assert_eq(result->data[1][1], 5);
    cr_assert_eq(result->data[1][2], 6);
    cr_assert_eq(result->data[2][0], 7);
    cr_assert_eq(result->data[2][1], 8);
    cr_assert_eq(result->data[2][2], 9);
    cr_assert_eq(result->data[3][0], 10);
    cr_assert_eq(result->data[3][1], 11);
    cr_assert_eq(result->data[3][2], 12);

    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(result);
}

Test(matrix_row_stack, invalid_matrices)
{

    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(2, 2);

    Matrix *result = MatrixRowStack(m1, m2);
    cr_assert_null(result);

    MatrixFree(m1);
    MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, NullMatrix1) {
    Matrix *m1 = NULL;
    Matrix *m2 = MatrixNew(2, 2);
	
    Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for NULL m1");
    
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, NullMatrix2) {
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = NULL;
	
    Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for NULL m2");
    
	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, DifferentNumRows) {
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(3, 2);
    
	Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for matrices with different numbers of rows");
    
	MatrixFree(m1);
    MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, SameNumRowsAndCols) {
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(2, 2);
    
	MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 0, 1, 2);
    MatrixSet(m1, 1, 0, 3);
    MatrixSet(m1, 1, 1, 4);
    MatrixSet(m2, 0, 0, 5);
    MatrixSet(m2, 0, 1, 6);
    MatrixSet(m2, 1, 0, 7);
    MatrixSet(m2, 1, 1, 8);
    
	Matrix *result = MatrixColumnStack(m1, m2);
    
	cr_assert_not_null(result, "MatrixColumnStack returned NULL for valid matrices");
    cr_assert_eq(result->num_rows, 2, "Result has incorrect number of rows");
    cr_assert_eq(result->num_cols, 4, "Result has incorrect number of columns");
    cr_assert_eq(MatrixGet(result, 0, 0), 1, "Result has incorrect value at (0, 0)");
    cr_assert_eq(MatrixGet(result, 0, 1), 2, "Result has incorrect value at (0, 1)");
    cr_assert_eq(MatrixGet(result, 0, 2), 5, "Result has incorrect value at (0, 2)");
    cr_assert_eq(MatrixGet(result, 0, 3), 6, "Result has incorrect value at (0, 3)");
    cr_assert_eq(MatrixGet(result, 1, 0), 3, "Result has incorrect value at (1, 0)");
    cr_assert_eq(MatrixGet(result, 1, 1), 4, "Result has incorrect value at (1, 1)");
    cr_assert_eq(MatrixGet(result, 1, 2), 7, "Result has incorrect value at (1, 2)");
    cr_assert_eq(MatrixGet(result, 1, 3), 15, "Result has incorrect value at (1, 3)");
    
	MatrixFree(m1);
    MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixAdd, SameDimensions)
{
    Matrix *m1 = MatrixNew(3, 3);
    Matrix *m2 = MatrixNew(3, 3);

    // Set the values of the matrices
    MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 0, 1, 2);
    MatrixSet(m1, 0, 2, 3);
    MatrixSet(m1, 1, 0, 4);
    MatrixSet(m1, 1, 1, 5);
    MatrixSet(m1, 1, 2, 6);
    MatrixSet(m1, 2, 0, 7);
    MatrixSet(m1, 2, 1, 8);
    MatrixSet(m1, 2, 2, 9);
    MatrixSet(m2, 0, 0, 9);
    MatrixSet(m2, 0, 1, 8);
    MatrixSet(m2, 0, 2, 7);
    MatrixSet(m2, 1, 0, 6);
    MatrixSet(m2, 1, 1, 5);
    MatrixSet(m2, 1, 2, 4);
    MatrixSet(m2, 2, 0, 3);
    MatrixSet(m2, 2, 1, 2);
    MatrixSet(m2, 2, 2, 1);

    // Add the matrices
    Matrix *result = MatrixAdd(m1, m2);

    // Check the result
    cr_assert_not_null(result);
    cr_assert_eq(MatrixGet(result, 0, 0), 10);
    cr_assert_eq(MatrixGet(result, 0, 1), 10);
    cr_assert_eq(MatrixGet(result, 0, 2), 10);
    cr_assert_eq(MatrixGet(result, 1, 0), 10);
    cr_assert_eq(MatrixGet(result, 1, 1), 10);
    cr_assert_eq(MatrixGet(result, 1, 2), 10);
    cr_assert_eq(MatrixGet(result, 2, 0), 10);
    cr_assert_eq(MatrixGet(result, 2, 1), 10);
    cr_assert_eq(MatrixGet(result, 2, 2), 10);

    // Clean up
    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(result);
}

// Test adding two matrices with different dimensions
Test(MatrixAdd, DifferentDimensions)
{
    // Create two matrices
    Matrix *m1 = MatrixNew(3, 3);
    Matrix *m2 = MatrixNew(2, 2);

    // Add the matrices
    Matrix *result = MatrixAdd(m1, m2);

    // Check that the result is NULL
    cr_assert_null(result);

    // Clean up
    MatrixFree(m1);
    MatrixFree(m2);
}

Test(MatrixSubtract, NullMatrix1)
{
    Matrix *m1 = NULL;
    Matrix *m2 = MatrixNew(2, 2);
    Matrix *result = MatrixSubtract(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m2);
}

Test(MatrixSubtract, NullMatrix2)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = NULL;
    Matrix *result = MatrixSubtract(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m1);
}

Test(MatrixSubtract, UnequalDimensions)
{
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(2, 2);
    Matrix *result = MatrixSubtract(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m1);
    MatrixDelete(m2);
}

Test(MatrixSubtract, Subtract)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(2, 2);
    MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 0, 1, 2);
    MatrixSet(m1, 1, 0, 3);
    MatrixSet(m1, 1, 1, 4);
    MatrixSet(m2, 0, 0, 1);
    MatrixSet(m2, 0, 1, 2);
    MatrixSet(m2, 1, 0, 3);
    MatrixSet(m2, 1, 1, 4);
    Matrix *result = MatrixSubtract(m1, m2);
    cr_assert_not_null(result);
    cr_assert_eq(MatrixGet(result, 0, 0), 0);
    cr_assert_eq(MatrixGet(result, 0, 1), 0);
    cr_assert_eq(MatrixGet(result, 1, 0), 0);
    cr_assert_eq(MatrixGet(result, 1, 1), 0);
    MatrixDelete(m1);
    MatrixDelete(m2);
    MatrixDelete(result);
}

Test(MatrixMultiply, NullMatrix1)
{
    Matrix *m1 = NULL;
    Matrix *m2 = MatrixNew(2, 3);
    Matrix *result = MatrixMultiply(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m2);
}

Test(MatrixMultiply, NullMatrix2)
{
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = NULL;
    Matrix *result = MatrixMultiply(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m1);
}

Test(MatrixMultiply, UnequalDimensions)
{
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(4, 5);
    Matrix *result = MatrixMultiply(m1, m2);
    cr_assert_null(result);
    MatrixDelete(m1);
    MatrixDelete(m2);
}

Test(MatrixMultiply, Multiply)
{
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(3, 2);
    MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 0, 1, 2);
    MatrixSet(m1, 0, 2, 3);
    MatrixSet(m1, 1, 0, 4);
	MatrixSet(m1, 1, 1, 5);
	MatrixSet(m1, 1, 2, 6);
	MatrixSet(m2, 0, 0, 7);
	MatrixSet(m2, 0, 1, 8);
	MatrixSet(m2, 1, 0, 9);
	MatrixSet(m2, 1, 1, 10);
	MatrixSet(m2, 2, 0, 11);
	MatrixSet(m2, 2, 1, 12);

	Matrix *result = MatrixMultiply(m1, m2);

	cr_assert_not_null(result, "Result should not be null");

	cr_assert_eq(MatrixGet(result, 0, 0), 58, "Expected 58 but got %d", MatrixGet(result, 0, 0));
	cr_assert_eq(MatrixGet(result, 0, 1), 64, "Expected 64 but got %d", MatrixGet(result, 0, 1));
	cr_assert_eq(MatrixGet(result, 1, 0), 139, "Expected 139 but got %d", MatrixGet(result, 1, 0));
	cr_assert_eq(MatrixGet(result, 1, 1), 154, "Expected 154 but got %d", MatrixGet(result, 1, 1));

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixElementWiseMultiply, Multiply)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(2, 2);

    MatrixSet(m1, 0, 0, 2);
    MatrixSet(m1, 0, 1, 4);
    MatrixSet(m1, 1, 0, 6);
    MatrixSet(m1, 1, 1, 8);

    MatrixSet(m2, 0, 0, 1);
    MatrixSet(m2, 0, 1, 3);
    MatrixSet(m2, 1, 0, 5);
    MatrixSet(m2, 1, 1, 7);

    Matrix *result = MatrixElementWiseMultiply(m1, m2);

    cr_assert_not_null(result, "Result matrix should not be NULL");

    cr_assert_eq(MatrixGet(result, 0, 0), 2);
    cr_assert_eq(MatrixGet(result, 0, 1), 12);
    cr_assert_eq(MatrixGet(result, 1, 0), 30);
    cr_assert_eq(MatrixGet(result, 1, 1), 56);

    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(result);
}

Test(MatrixElementWiseMultiply, NullInput)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = NULL;

    Matrix *result = MatrixElementWiseMultiply(m1, m2);

    cr_assert_null(result, "Result matrix should be NULL when one of the inputs is NULL");

    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(result);
}

Test(MatrixElementWiseMultiply, DifferentDimensions)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(2, 3);

    Matrix *result = MatrixElementWiseMultiply(m1, m2);

    cr_assert_null(result, "Result matrix should be NULL when the dimensions are not equal");

    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(result);
}

Test(MatrixAddWithBroadcast, InvalidInput)
{
    // Test with NULL input
    Matrix *result = MatrixAddWithBroadcast(NULL, NULL);
    cr_assert_null(result, "Failed to catch NULL input");

    // Test with mismatched dimensions
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(3, 2);
    Matrix *result2 = MatrixAddWithBroadcast(m1, m2);
    cr_assert_null(result2, "Failed to catch mismatched dimensions");
    MatrixFree(m1);
    MatrixFree(m2);
}

Test(MatrixAddWithBroadcast, AddMatricesWithDifferentSizes)
{
    // Test with matrices of different sizes
    Matrix *m1 = MatrixNew(2, 1);
    Matrix *m2 = MatrixNew(1, 2);
    MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 1, 0, 2);
    MatrixSet(m2, 0, 0, 1);
    MatrixSet(m2, 0, 1, 2);
    Matrix *expected = MatrixNew(2, 2);
    MatrixSet(expected, 0, 0, 2);
    MatrixSet(expected, 0, 1, 3);
    MatrixSet(expected, 1, 0, 3);
    MatrixSet(expected, 1, 1, 4);
    Matrix *result = MatrixAddWithBroadcast(m1, m2);
    MatrixEquals(expected, result, 1e-6);
    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(expected);
    MatrixFree(result);

}

Test(MatrixAddWithBroadcast, AddMatricesWithSameSizes)
{ 
    // Test with matrices of the same size
    Matrix *m3 = MatrixNew(2, 2);
    Matrix *m4 = MatrixNew(2, 2);
    MatrixSet(m3, 0, 0, 1);
    MatrixSet(m3, 0, 1, 2);
    MatrixSet(m3, 1, 0, 3);
    MatrixSet(m3, 1, 1, 4);
    MatrixSet(m4, 0, 0, 5);
    MatrixSet(m4, 0, 1, 6);
    MatrixSet(m4, 1, 0, 7);
    MatrixSet(m4, 1, 1, 8);
    Matrix *expected2 = MatrixNew(2, 2);
    MatrixSet(expected2, 0, 0, 6);
    MatrixSet(expected2, 0, 1, 8);
    MatrixSet(expected2, 1, 0, 10);
    MatrixSet(expected2, 1, 1, 12);
    Matrix *result2 = MatrixAddWithBroadcast(m3, m4);
    MatrixEquals(expected2, result2, 1e-6);
    MatrixFree(m3);
    MatrixFree(m4);
    MatrixFree(expected2);
    MatrixFree(result2);
}

Test(MatrixSubtractWithBroadcast, SubtractMatricesWithDifferentSizes)
{
    // Test with matrices of different sizes
    Matrix *m1 = MatrixNew(2, 1);
    Matrix *m2 = MatrixNew(1, 2);
    MatrixSet(m1, 0, 0, 1);
    MatrixSet(m1, 1, 0, 2);
    MatrixSet(m2, 0, 0, 1);
    MatrixSet(m2, 0, 1, 2);
    Matrix *expected = MatrixNew(2, 2);
    MatrixSet(expected, 0, 0, 2);
    MatrixSet(expected, 0, 1, 3);
    MatrixSet(expected, 1, 0, 3);
    MatrixSet(expected, 1, 1, 4);
    Matrix *result = MatrixAddWithBroadcast(m1, m2);
    MatrixEquals(expected, result, 1e-6);
    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(expected);
    MatrixFree(result);

}

Test(MatrixSubtractWithBroadcast, SubtractMatricesWithSameSizes)
{ 
    // Test with matrices of the same size
    Matrix *m3 = MatrixNew(2, 2);
    Matrix *m4 = MatrixNew(2, 2);
    MatrixSet(m3, 0, 0, 1);
    MatrixSet(m3, 0, 1, 2);
    MatrixSet(m3, 1, 0, 3);
    MatrixSet(m3, 1, 1, 4);
    MatrixSet(m4, 0, 0, 5);
    MatrixSet(m4, 0, 1, 6);
    MatrixSet(m4, 1, 0, 7);
    MatrixSet(m4, 1, 1, 8);
    Matrix *expected2 = MatrixNew(2, 2);
    MatrixSet(expected2, 0, 0, 6);
    MatrixSet(expected2, 0, 1, 8);
    MatrixSet(expected2, 1, 0, 10);
    MatrixSet(expected2, 1, 1, 12);
    Matrix *result2 = MatrixAddWithBroadcast(m3, m4);
    MatrixEquals(expected2, result2, 1e-6);
    MatrixFree(m3);
    MatrixFree(m4);
    MatrixFree(expected2);
    MatrixFree(result2);
}

Test(MatrixSubtractWithBroadcast, Subtract)
{
    Matrix *m1 = MatrixNew(2, 3);
    Matrix *m2 = MatrixNew(1, 3);
    MatrixSet(m1, 0, 0, 5);
    MatrixSet(m1, 0, 1, 7);
    MatrixSet(m1, 0, 2, 3);
    MatrixSet(m1, 1, 0, 8);
    MatrixSet(m1, 1, 1, 1);
    MatrixSet(m1, 1, 2, 2);
    MatrixSet(m2, 0, 0, 2);
    MatrixSet(m2, 0, 1, 3);
    MatrixSet(m2, 0, 2, 1);

    Matrix *expected_result = MatrixNew(2, 3);
    MatrixSet(expected_result, 0, 0, 3);
    MatrixSet(expected_result, 0, 1, 4);
    MatrixSet(expected_result, 0, 2, 2);
    MatrixSet(expected_result, 1, 0, 6);
    MatrixSet(expected_result, 1, 1, -2);
    MatrixSet(expected_result, 1, 2, 1);

    Matrix *result = MatrixSubtractWithBroadcast(m1, m2);
    cr_assert(MatrixAreEqual(expected_result, result), "Expected matrix and result matrix are not equal");

    MatrixFree(m1);
    MatrixFree(m2);
    MatrixFree(expected_result);
    MatrixFree(result);
}

Test(MatrixSubtractWithBroadcast, ErrorNullM1)
{
    Matrix *m1 = NULL;
    Matrix *m2 = MatrixNew(1, 1);

    cr_assert_null(MatrixSubtractWithBroadcast(m1, m2), "Expected NULL matrix when passing NULL matrix m1");

    MatrixFree(m2);
}

Test(MatrixSubtractWithBroadcast, ErrorNullM2)
{
    Matrix *m1 = MatrixNew(1, 1);
    Matrix *m2 = NULL;

    cr_assert_null(MatrixSubtractWithBroadcast(m1, m2), "Expected NULL matrix when passing NULL matrix m2");

    MatrixFree(m1);
}

Test(MatrixSubtractWithBroadcast, ErrorNotEqualDim)
{
    Matrix *m1 = MatrixNew(2, 2);
    Matrix *m2 = MatrixNew(1, 1);

    cr_assert_null(MatrixSubtractWithBroadcast(m1, m2), "Expected NULL matrix when matrices have not equal dimensions");

    MatrixFree(m1);
    MatrixFree(m2);
}













Test(matrix_test, matrix_operations)
{
	{
		double values1[] = { 1., 2., 3., 4., 5., 1. };

		double values2[] = { 2., 4. };

		Matrix *a = MatrixFrom(3, 2, 6, values1);
		Matrix *b = MatrixFrom(2, 1, 2, values2);
		Matrix *res = MatrixMultiply(a, b);
		cr_assert_float_eq(MatrixGet(res, 1, 0), 22., 0.001);
	}

	{
		double values[] = { 1., 3., 5., 9., 1., 3., 1., 7., 4., 3., 9., 7., 5., 2., 0., 9. };

		Matrix *ref = MatrixFrom(4, 4, 16, values);
		Matrix *re = MatrixRowEchelonGet(ref);
		cr_assert_float_eq(MatrixTrace(re), 4., 0.001);
	}

	{
		double values[] = { 1., 1., 1., 1., 1., 0., -3., -6., 4., 9., -1., -2., -1., 3., 1., -2., -3., 0., 3., -1., 1., 4., 5., -9., -7., };

		Matrix *ref = MatrixFrom(5, 5, 25, values);
		Matrix *re = MatrixReducedRowEchelonGet(ref);
		cr_assert_float_eq(MatrixTrace(re), 4., 0.001);
	}

	{
		double values[] = { 1. };

		Matrix *m = MatrixFrom(1, 1, 1, values);
		Matrix *bm = MatrixBroadcastRowsAndColumns(m, 10, 10);
		cr_assert_float_eq(MatrixTrace(bm), 10., 0.001);
	}

	{
		double values[] = { 0., 10., 20., 30. };

		double values1[] = { 1., 2., 3., 4. };

		Matrix *m = MatrixFrom(4, 1, 4, values);
		Matrix *m1 = MatrixFrom(1, 4, 4, values1);
		Matrix *res = MatrixAddWithBroadcast(m, m1);
		cr_assert_float_eq(MatrixTrace(res), 70., 0.001);
	}
}