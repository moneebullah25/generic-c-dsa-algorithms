#include <criterion/criterion.h>
#include "../includes/c_helper.h"
#include "../includes/c_matrix.h"

Test(MatrixEmpty, InvalidNumRows)
{
	Matrix *matrix = MatrixEmpty(0, 5);
	cr_assert_null(matrix, "MatrixEmpty should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixEmpty, InvalidNumCols)
{
	Matrix *matrix = MatrixEmpty(5, 0);
	cr_assert_null(matrix, "MatrixEmpty should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixEmptyLike, NullMatrix)
{
	Matrix *matrix = MatrixEmptyLike(NULL);
	cr_assert_null(matrix, "MatrixEmptyLike should return NULL when a NULL matrix is passed");
	MatrixFree(matrix);
}

Test(MatrixEmptyLike, ValidMatrix)
{
	Matrix *m = MatrixAlloc(2, 3);
	MatrixSet(m, 0, 0, 1.);
	MatrixSet(m, 0, 1, 2.);
	MatrixSet(m, 0, 2, 3.);
	MatrixSet(m, 1, 0, 4.);
	MatrixSet(m, 1, 1, 5.);
	MatrixSet(m, 1, 2, 6.);
	Matrix *matrix = MatrixEmptyLike(m);
	cr_assert_not_null(matrix, "MatrixEmptyLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, m->num_rows, "MatrixEmptyLike should set the same number of rows as the passed matrix");
	cr_assert_eq(matrix->num_cols, m->num_cols, "MatrixEmptyLike should set the same number of columns as the passed matrix");
	cr_assert_eq(matrix->is_square, false, "MatrixEmptyLike should set is_square to false for a non-square matrix");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(MatrixGet(matrix, r, c), 0., "MatrixEmptyLike should initialize all elements to 0");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixEmpty, ValidArguments)
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
			cr_assert_eq(MatrixGet(matrix, r, c), 0., "MatrixEmpty should initialize all elements to 0");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixNew, InvalidNumRows)
{
	Matrix *matrix = MatrixNew(0, 5);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixNew, InvalidNumCols)
{
	Matrix *matrix = MatrixNew(5, 0);
	cr_assert_null(matrix, "MatrixNew should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixNew, ValidArguments)
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
			cr_assert_eq(MatrixGet(matrix, r, c), 0., "MatrixNew should initialize all elements to 0");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixNewLike, InValidMatrix)
{
	Matrix *m = NULL;
	Matrix *matrix = MatrixNewLike(m);
	cr_assert_null(matrix, "MatrixNewLike should return NULL when invalid matrix is passed");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixNewLike, ValidMatrix)
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
			cr_assert_eq(MatrixGet(matrix, r, c) 0., "MatrixNewLike should initialize all elements to 0");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixRandom, InvalidNumRows)
{
	Matrix *matrix = MatrixRandom(0, 5, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_rows is 0");
	MatrixFree(matrix);
}

Test(MatrixRandom, InvalidNumCols)
{
	Matrix *matrix = MatrixRandom(5, 0, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandom should return NULL when num_cols is 0");
	MatrixFree(matrix);
}

Test(MatrixRandom, ValidArguments)
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
			cr_assert_geq(MatrixGet(matrix, r, c), min, "MatrixRandom should generate values greater than or equal to the minimum");
			cr_assert_leq(MatrixGet(matrix, r, c), max, "MatrixRandom should generate values less than or equal to the maximum");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixRandomLike, InValidMatrix)
{
	Matrix *m = NULL;
	Matrix *matrix = MatrixRandomLike(m, -1.0, 1.0);
	cr_assert_null(matrix, "MatrixRandomLike should return NULL when an invalid matrix is passed");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixRandomLike, ValidMatrix)
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
			cr_assert_geq(MatrixGet(matrix, r, c), min, "MatrixRandomLike should generate values greater than or equal to the minimum");
			cr_assert_leq(MatrixGet(matrix, r, c), max, "MatrixRandomLike should generate values less than or equal to the maximum");
		}
	}

	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquare, ValidSize)
{
	Matrix *matrix = MatrixSquare(3);
	cr_assert_not_null(matrix, "MatrixSquare should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixSquare should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixSquare should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixSquare should set is_square to true for a square matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareLike, InValidMatrix)
{
	Matrix *matrix = MatrixSquareLike(NULL);
	cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareLike, NonSquareMatrix)
{
	Matrix *m = MatrixNew(2, 3);
	Matrix *matrix = MatrixSquareLike(m);
	cr_assert_null(matrix, "MatrixSquareLike should return NULL when passed a non-square matrix");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixSquareLike, ValidMatrix)
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

Test(MatrixSquareRandom, ValidSizeAndRange)
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
			if (MatrixGet(matrix, r, c) < min || MatrixGet(matrix, r, c) > max)
			{
				in_range = false;
				break;
			}
		}
	}

	cr_assert_eq(in_range, true, "MatrixSquareRandom should set all elements within the specified range");

	MatrixFree(matrix);
}

Test(MatrixSquareRandom, InValidSize)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandom(0, min, max);
	cr_assert_null(matrix, "MatrixSquareRandom should return NULL when passed an invalid size");
	MatrixFree(matrix);
}

Test(MatrixSquareRandomLike, InValidMatrix)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixSquareRandomLike(NULL, min, max);
	cr_assert_null(matrix, "MatrixSquareRandomLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixSquareRandomLike, NotSquareMatrix)
{
	double min = -1.0;
	double max = 1.0;
	Matrix *matrix = MatrixNew(2, 3);
	cr_assert_null(MatrixSquareRandomLike(matrix, min, max), "MatrixSquareRandomLike should return NULL when passed a non-square matrix");
	MatrixFree(matrix);
}

Test(MatrixZero, ValidSize)
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
			cr_assert_eq(MatrixGet(matrix, r, c), 0.0, "MatrixZero should initialize all elements to zero");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixZeroLike, InValidMatrix)
{
	Matrix *matrix = MatrixZeroLike(NULL);
	cr_assert_null(matrix, "MatrixZeroLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixOne, ValidSize)
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
			cr_assert_eq(MatrixGet(matrix, r, c), 1., "MatrixOne should set all elements to 1");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixOneLike, InValidMatrix)
{
	Matrix *matrix = MatrixOneLike(NULL);
	cr_assert_null(matrix, "MatrixOneLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixN, ValidSizeAndValue)
{
	Matrix *matrix = MatrixN(2, 3, 5.);
	cr_assert_not_null(matrix, "MatrixN should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 2, "MatrixN should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixN should set the correct number of columns");
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			cr_assert_eq(MatrixGet(matrix, r, c), 5., "MatrixN should set all elements to the given value");
		}
	}

	MatrixFree(matrix);
}

Test(MatrixNLike, InValidMatrix)
{
	Matrix *matrix = MatrixNLike(NULL, 10.);
	cr_assert_null(matrix, "MatrixNLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixIdentity, ValidSize)
{
	Matrix *matrix = MatrixIdentity(3);
	cr_assert_not_null(matrix, "MatrixIdentity should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 3, "MatrixIdentity should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 3, "MatrixIdentity should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixIdentity should set is_square to true for a square matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 0), 1.0, "MatrixIdentity should set the diagonal elements to 1");
	cr_assert_eq(MatrixGet(matrix, 1, 1), 1.0, "MatrixIdentity should set the diagonal elements to 1");
	cr_assert_eq(MatrixGet(matrix, 2, 2), 1.0, "MatrixIdentity should set the diagonal elements to 1");
	MatrixFree(matrix);
}

Test(MatrixIdentityLike, InValidMatrix)
{
	Matrix *matrix = MatrixIdentityLike(NULL);
	cr_assert_null(matrix, "MatrixIdentityLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixIdentityLike, NonSquareMatrix)
{
	Matrix *matrix = MatrixNew(2, 3);
	Matrix *identity = MatrixIdentityLike(matrix);
	cr_assert_null(identity, "MatrixIdentityLike should return NULL when passed a non-square matrix");
	MatrixFree(matrix);
	MatrixFree(identity);
}

Test(MatrixEye, ValidK)
{
	Matrix *matrix = MatrixEye(4, 1);
	cr_assert_not_null(matrix, "MatrixEye should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 4, "MatrixEye should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixEye should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixEye should set is_square to true for a square matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 1), 1.0, "MatrixEye should set the correct value for k = 1");
	cr_assert_eq(MatrixGet(matrix, 1, 2), 1.0, "MatrixEye should set the correct value for k = 1");
	cr_assert_eq(MatrixGet(matrix, 2, 3), 1.0, "MatrixEye should set the correct value for k = 1");
	cr_assert_eq(MatrixGet(matrix, 3, 3), 1.0, "MatrixEye should set the correct value for k = 1");
	MatrixFree(matrix);
}

Test(MatrixEye, InValidK)
{
	Matrix *matrix = MatrixEye(4, 4);
	cr_assert_null(matrix, "MatrixEye should return NULL for an invalid k");
	MatrixFree(matrix);
}

Test(MatrixEyeLike, ValidK)
{
	Matrix *m = MatrixSquare(4);
	Matrix *matrix = MatrixEyeLike(m, -1);
	cr_assert_not_null(matrix, "MatrixEyeLike should return a non-NULL pointer");
	cr_assert_eq(matrix->num_rows, 4, "MatrixEyeLike should set the correct number of rows");
	cr_assert_eq(matrix->num_cols, 4, "MatrixEyeLike should set the correct number of columns");
	cr_assert_eq(matrix->is_square, true, "MatrixEyeLike should set is_square to true for a square matrix");
	cr_assert_eq(MatrixGet(matrix, 1, 0), 1.0, "MatrixEyeLike should set the correct value for k = -1");
	cr_assert_eq(MatrixGet(matrix, 2, 1), 1.0, "MatrixEyeLike should set the correct value for k = -1");
	cr_assert_eq(MatrixGet(matrix, 3, 2), 1.0, "MatrixEyeLike should set the correct value for k = -1");
	cr_assert_eq(MatrixGet(matrix, 0, 0), 1.0, "MatrixEyeLike should set the correct value for k = -1");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixEyeLike, InValidMatrix)
{
	Matrix *matrix = MatrixEyeLike(NULL, 1);
	cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed an invalid matrix");
	MatrixFree(matrix);
}

Test(MatrixEyeLike, NonSquareMatrix)
{
	Matrix *m = MatrixNew(3, 4);
	Matrix *matrix = MatrixEyeLike(m, 1);
	cr_assert_null(matrix, "MatrixEyeLike should return NULL when passed a non-square matrix");
	MatrixFree(m);
	MatrixFree(matrix);
}

Test(MatrixARange, InValidStartStopValues)
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

Test(MatrixLinearSpace, InValidN)
{
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 1;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed n<2");

	MatrixFree(matrix);
}

Test(MatrixLinearSpace, InValidStartStop)
{
	double start = 1.0;
	double stop = 0.0;
	unsigned int n = 10;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	cr_assert_null(matrix, "MatrixLinearSpace should return NULL when passed start >= stop");
	MatrixFree(matrix);
}

Test(MatrixLinearSpace, BasicTest)
{
	double start = 0.0;
	double stop = 1.0;
	unsigned int n = 5;
	Matrix *matrix = MatrixLinearSpace(start, stop, n);
	double expected[] = { 0.0, 0.25, 0.5, 0.75, 1.0 };

	for (unsigned int i = 0; i < n; i++)
	{
		cr_assert_double_eq(MatrixGet(matrix, 0, i), expected[i], 1e-6, "MatrixLinearSpace output for element %d is %f but expected %f", i, MatrixGet(matrix, 0, i), expected[i]);
	}

	MatrixFree(matrix);
}

Test(MatrixLogSpace, InValidN)
{
	Matrix *matrix = MatrixLogSpace(1.0, 10.0, 1);
	cr_assert_null(matrix, "MatrixLogSpace should return NULL when passed n<2");
	MatrixFree(matrix);
}

Test(MatrixLogSpace, InValidStartStop)
{
	Matrix *matrix1 = MatrixLogSpace(10.0, 1.0, 5);
	cr_assert_null(matrix1, "MatrixLogSpace should return NULL when passed start >= stop");

	Matrix *matrix2 = MatrixLogSpace(1.0, 1.0, 5);
	cr_assert_null(matrix2, "MatrixLogSpace should return NULL when passed start == stop");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(MatrixLogSpace, ValidInputs)
{
	Matrix *matrix = MatrixLogSpace(1.0, 10.0, 5);

	cr_assert_not_null(matrix, "MatrixLogSpace should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
	cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

	cr_assert_eq(MatrixGet(matrix, 0, 0), 10.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 1), 31.622776601683793, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 2), 100.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 3), 316.22776601683796, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 4), 1000.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixGeometrySpace, InValidN)
{
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 0);
	cr_assert_null(matrix, "MatrixGeometrySpace should return NULL when passed n == 0");

	MatrixFree(matrix);
}

Test(MatrixGeometrySpace, InValidStartStop)
{
	Matrix *matrix1 = MatrixGeometrySpace(10.0, 1.0, 5);
	cr_assert_null(matrix1, "MatrixGeometrySpace should return NULL when passed start >= stop");

	Matrix *matrix2 = MatrixGeometrySpace(1.0, 1.0, 5);
	cr_assert_null(matrix2, "MatrixGeometrySpace should return NULL when passed start == stop");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(MatrixGeometrySpace, ValidInputs)
{
	Matrix *matrix = MatrixGeometrySpace(1.0, 10.0, 5);
	cr_assert_not_null(matrix, "MatrixGeometrySpace should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 1, "Matrix should have 1 row");
	cr_assert_eq(matrix->num_cols, 5, "Matrix should have 5 columns");

	cr_assert_eq(MatrixGet(matrix, 0, 0), 1.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 1), 2.5118864315095824, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 2), 6.309573444801933, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 3), 15.848931924611133, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 4), 39.810717055349734, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixFrom, InValidValues)
{
	const double values[] = { 1.0, 2.0, 3.0 };

	Matrix *matrix = MatrixFrom(2, 2, 1, values);
	cr_assert_null(matrix, "MatrixFrom should return NULL when passed n_values < num_rows *num_cols");

	MatrixFree(matrix);
}

Test(MatrixFrom, ValidValues)
{
	const double values[] = { 1.0, 2.0, 3.0, 4.0 };

	Matrix *matrix = MatrixFrom(2, 2, 4, values);

	cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
	cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

	cr_assert_eq(MatrixGet(matrix, 0, 0), 1.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 1), 2.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 1, 0), 3.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 1, 1), 4.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixFrom, EmptyValues)
{
	const double values[] = {};

	Matrix *matrix = MatrixFrom(2, 2, 0, values);

	cr_assert_not_null(matrix, "MatrixFrom should return a non-null matrix");

	cr_assert_eq(matrix->num_rows, 2, "Matrix should have 2 rows");
	cr_assert_eq(matrix->num_cols, 2, "Matrix should have 2 columns");

	cr_assert_eq(MatrixGet(matrix, 0, 0), 0.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 0, 1), 0.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 1, 0), 0.0, "Incorrect value in matrix");
	cr_assert_eq(MatrixGet(matrix, 1, 1), 0.0, "Incorrect value in matrix");

	MatrixFree(matrix);
}

Test(MatrixCopy, NonNullInput)
{
	double data[4] = { 1.0, 2.0, 3.0, 4.0 };

	Matrix *m1 = MatrixFrom(2, 2, 4, data);

	Matrix *m2 = MatrixCopy(m1);

	cr_assert_eq(m2->num_rows, m1->num_rows, "Copied matrix has incorrect number of rows");
	cr_assert_eq(m2->num_cols, m1->num_cols, "Copied matrix has incorrect number of columns");

	cr_assert_eq(MatrixGet(m2, 0, 0), MatrixGet(m1, 0, 0), "Incorrect value in copied matrix");
	cr_assert_eq(MatrixGet(m2, 0, 1), MatrixGet(m1, 0, 1), "Incorrect value in copied matrix");
	cr_assert_eq(MatrixGet(m2, 1, 0), MatrixGet(m1, 1, 0), "Incorrect value in copied matrix");
	cr_assert_eq(MatrixGet(m2, 1, 1), MatrixGet(m1, 1, 1), "Incorrect value in copied matrix");

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixCopy, NullInput)
{
	Matrix *m = NULL;
	Matrix *copy = MatrixCopy(m);
	cr_assert_null(copy, "Copying a null matrix should return a null matrix");
	MatrixFree(m);
	MatrixFree(copy);
}

Test(IsMatrixEqualDim, SameDimensions)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(2, 3);

	cr_assert(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have same dimensions");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, DifferentRows)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(3, 3);

	cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different rows");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(IsMatrixEqualDim, DifferentColumns)
{
	Matrix *matrix1 = MatrixNew(2, 3);
	Matrix *matrix2 = MatrixNew(2, 2);

	cr_assert_not(IsMatrixEqualDim(matrix1, matrix2), "Matrices should have different columns");

	MatrixFree(matrix1);
	MatrixFree(matrix2);
}

Test(PrintMatrix, ValidInput)
{
	Matrix *matrix = MatrixNew(2, 2);
	MatrixGet(matrix, 0, 0) = 1.0;
	MatrixGet(matrix, 0, 1) = 2.0;
	MatrixGet(matrix, 1, 0) = 3.0;
	MatrixGet(matrix, 1, 1) = 4.0;

	PrintMatrix(matrix, "%.2f");

	MatrixFree(matrix);
}

Test(PrintMatrix, InValidInput)
{
	PrintMatrix(NULL, "%.2f");
}

Test(IsMatrixInvertible, InvertibleMatrix)
{
	Matrix *matrix = MatrixNew(2, 2);
	MatrixGet(matrix, 0, 0) = 1.0;
	MatrixGet(matrix, 0, 1) = 2.0;
	MatrixGet(matrix, 1, 0) = 3.0;
	MatrixGet(matrix, 1, 1) = 4.0;

	cr_assert(IsMatrixInvertible(matrix), "Matrix should be invertible");

	MatrixFree(matrix);
}

Test(IsMatrixInvertible, NonInvertibleMatrix)
{
	Matrix *matrix = MatrixNew(2, 2);
	MatrixGet(matrix, 0, 0) = 1.0;
	MatrixGet(matrix, 0, 1) = 2.0;
	MatrixGet(matrix, 1, 0) = 2.0;
	MatrixGet(matrix, 1, 1) = 4.0;

	cr_assert_not(IsMatrixInvertible(matrix), "Matrix should not be invertible");

	MatrixFree(matrix);
}

Test(IsMatrixInvertible, InValidInput)
{
	cr_assert_not(IsMatrixInvertible(NULL), "NULL matrix should not be invertible");
}

Test(MatrixGet, Tests)
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

Test(MatrixColumnGet, ValidInput)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *column = MatrixColumnGet(m, 1);
	cr_assert(column != NULL, "MatrixColumnGet should return non-NULL");

	cr_assert_eq(column->num_rows, 2, "Matrix column has incorrect number of rows");
	cr_assert_eq(column->num_cols, 1, "Matrix column has incorrect number of columns");

	cr_assert_eq(MatrixGet(column, 0, 0), 2, "Matrix column has incorrect value at row 0, col 0");
	cr_assert_eq(MatrixGet(column, 1, 0), 5, "Matrix column has incorrect value at row 1, col 0");

	MatrixFree(m);
	MatrixFree(column);
}

Test(MatrixColumnGet, InValidInput)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *column = MatrixColumnGet(m, 3);
	cr_assert(column == NULL, "MatrixColumnGet should return NULL for invalid column index");

	MatrixFree(m);
}

Test(MatrixRowGet, ValidInput)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *row = MatrixRowGet(m, 0);
	cr_assert(row != NULL, "MatrixRowGet should return non-NULL");

	cr_assert_eq(row->num_rows, 1, "Matrix row has incorrect number of rows");
	cr_assert_eq(row->num_cols, 3, "Matrix row has incorrect number of columns");

	cr_assert_eq(MatrixGet(row, 0, 0), 1, "Matrix row has incorrect value at row 0, col 0");
	cr_assert_eq(MatrixGet(row, 0, 1), 2, "Matrix row has incorrect value at row 0, col 1");
	cr_assert_eq(MatrixGet(row, 0, 2), 3, "Matrix row has incorrect value at row 0, col 2");

	MatrixFree(m);
	MatrixFree(row);
}

Test(MatrixRowGet, InValidInput)
{
	double values[] = { 1, 2, 3, 4, 5, 6 };

	Matrix *m = MatrixFrom(2, 3, 6, values);

	Matrix *row = MatrixRowGet(m, 2);
	cr_assert(row == NULL, "MatrixRowGet should return NULL for invalid row index");

	MatrixFree(m);
}

Test(MatrixSet, NullMatrix)
{
	Matrix *m = NULL;
	MatrixSet(m, 0, 0, 1.0);

	cr_assert(1);
}

Test(MatrixSet, InvalidRow)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 2, 0, 1.0);

	MatrixFree(m);
	cr_assert(1);
}

Test(MatrixSet, InvalidCol)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 2, 1.0);

	MatrixFree(m);
	cr_assert(1);
}

Test(MatrixSet, ValidSet)
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
			cr_assert_eq(MatrixGet(m, i, j), 1.);
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
			cr_assert_eq(MatrixGet(m, i, j), 0.);
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
				cr_assert_eq(MatrixGet(m, i, j), 1.);
			}
			else
			{
				cr_assert_eq(MatrixGet(m, i, j), 0.);
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
				cr_assert_eq(MatrixGet(m, i, j), 1.);
			}
			else
			{
				cr_assert_eq(MatrixGet(m, i, j), 0.);
			}
		}
	}

	MatrixFree(m);
}

Test(MatrixRowMultiplyValue, InValidMatrixPassed)
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

Test(MatrixColumnAddValue, NullMatrix)
{
	Matrix *m = NULL;
	MatrixColumnAddValue(m, 0, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValue, InvalidCol)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValue(m, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'col=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValue, ValidInput)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0];
	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValue(m, 2, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 5.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 9.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 13.0, 0.001);
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, NullMatrix)
{
	Matrix *m = NULL;
	MatrixRowMultiplyRow(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, InvalidWhereRow)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, InvalidRow)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 2, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'row=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowMultiplyRow, ValidInput)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowMultiplyRow(m, 1, 0, 2.0);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 8.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 10.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 12.0, 0.001);
	MatrixFree(m);
}

Test(MatrixRowAddRow, NullMatrix)
{
	Matrix *m = NULL;
	MatrixRowAddRow(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixRowAddRow, InvalidWhereRow)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowAddRow(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixRowAddRow, InvalidRow)
{
	double data[] =[1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	Matrix *m = MatrixFrom(3, 3, 9, data);
	MatrixRowAddRow(m, 2, 4, 2.0);
	cr_assert_stderr_eq_str("Invalid 'row=4' passed >= 3\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, NullMatrix)
{
	Matrix *m = NULL;
	MatrixColumnMultiplyColumn(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, InvalidWhere)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, InvalidCol)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 5, 2.0);
	cr_assert_stderr_eq_str("Invalid 'col=5' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, ValidInput)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 1, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 18.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 36.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 54.0, 0.001);
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, NullMatrix)
{
	Matrix *m = NULL;
	MatrixColumnAddValueColumn(m, 0, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, InvalidWhere)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 4, 1, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, InvalidCol)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 4, 2, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, InvalidValue)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 2, 1, NAN);
	cr_assert_stderr_eq_str("Invalid 'value=nan' passed\n");
	MatrixFree(m);
}

Test(MatrixColumnAddValueColumn, ValidInput)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnAddValueColumn(m, 2, 1, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 7.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 11.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 15.0, 0.001);
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, InvalidWhere)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 4, 2, 2.0);
	cr_assert_stderr_eq_str("Invalid 'where=4' passed >= 4\n");
	MatrixFree(m);
}

Test(MatrixColumnMultiplyColumn, InvalidValue)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixColumnMultiplyColumn(m, 2, 1, INFINITY);
	cr_assert_stderr_eq_str("Invalid 'value=inf' passed\n");
	MatrixFree(m);
}

Test(MatrixWholeMultiply, NullMatrix)
{
	Matrix *m = NULL;
	MatrixWholeMultiply(m, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixWholeMultiply, ValidInput)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixWholeMultiply(m, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 2.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 12.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 3), 24.0, 0.001);
	MatrixFree(m);
}

Test(MatrixWholeAdd, NullMatrix)
{
	Matrix *m = NULL;
	MatrixWholeAdd(m, 2.0);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
	MatrixFree(m);
}

Test(MatrixWholeAdd, ValidInput)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };

	Matrix *m = MatrixFrom(3, 4, 12, data);
	MatrixWholeAdd(m, 2.0);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 3.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 9.0, 0.001);
	cr_assert_float_eq(MatrixGet(m, 2, 3), 14.0, 0.001);
	MatrixFree(m);
}

Test(MatrixRowRemove, InValidMatrix)
{
	Matrix *m = NULL;
	Matrix *result = MatrixRowRemove(m, 0);
	cr_assert_null(result, "Expected NULL when passing invalid matrix, but got non-NULL");
}

Test(MatrixRowRemove, InvalidRow)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix *m = MatrixFrom(2, 3, 6, data);
	Matrix *result = MatrixRowRemove(m, 2);
	cr_assert_null(result, "Expected NULL when passing invalid row, but got non-NULL");
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixRowRemove, RemoveFirstRow)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix *m = MatrixFrom(2, 3, 6, data);
	Matrix *result = MatrixRowRemove(m, 0);
	double expected_data[] = { 4.0, 5.0, 6.0 };

	Matrix *expected = MatrixFrom(1, 3, 3, expected_data);
	assert_matrix_equal(result, expected);
	MatrixFree(m);
	MatrixFree(result);
	MatrixFree(expected);
}

Test(MatrixColumnRemove, InValidMatrix)
{
	Matrix *m = NULL;
	Matrix *result = MatrixColumnRemove(m, 0);
	cr_assert_null(result, "Expected NULL when passing invalid matrix, but got non-NULL");
}

Test(MatrixColumnRemove, InvalidCol)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix *m = MatrixFrom(2, 3, 6, data);
	Matrix *result = MatrixColumnRemove(m, 3);
	cr_assert_null(result, "Expected NULL when passing invalid column, but got non-NULL");
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixColumnRemove, RemoveFirstCol)
{
	double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	Matrix *m = MatrixFrom(2, 3, 6, data);
	Matrix *result = MatrixColumnRemove(m, 0);
	double expected_data[] = { 2.0, 3.0, 5.0, 6.0 };

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
			if (m1->data[i][j] != MatrixGet(m2, i, j))
			{
				criterion_assert_fail(					format_string("Matrices not equal at row=%u, col=%u: expected %lf, but got %lf",
						i, j, MatrixGet(m1, i, j), MatrixGet(m2, i, j)));
				return;
			}
		}
	}

	criterion_assert(1);
}

Test(MatrixRowSwap, ValidInput)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixRowSwap(m, 0, 1);

	cr_assert_eq(MatrixGet(m, 0, 0), 3.0, "Expected row 0, column 0 to be 3.0");
	cr_assert_eq(MatrixGet(m, 0, 1), 4.0, "Expected row 0, column 1 to be 4.0");
	cr_assert_eq(MatrixGet(m, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(m, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");

	MatrixFree(m);
}

Test(MatrixRowSwap, InValidInput)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixRowSwap(m, 0, 2);

	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
	cr_assert_eq(MatrixGet(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
	cr_assert_eq(MatrixGet(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

	MatrixFree(m);
}

Test(MatrixColumnSwap, ValidInput)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixColumnSwap(m, 0, 1);

	cr_assert_eq(MatrixGet(m, 0, 0), 2.0, "Expected row 0, column 0 to be 2.0");
	cr_assert_eq(MatrixGet(m, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
	cr_assert_eq(MatrixGet(m, 1, 0), 4.0, "Expected row 1, column 0 to be 4.0");
	cr_assert_eq(MatrixGet(m, 1, 1), 3.0, "Expected row 1, column 1 to be 3.0");

	MatrixFree(m);
}

Test(MatrixColumnSwap, InValidMatrix)
{
	Matrix *m = NULL;
	MatrixColumnSwap(m, 0, 1);
	MatrixFree(m);
}

Test(MatrixColumnSwap, InvalidCol)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixColumnSwap(m, 0, 2);

	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
	cr_assert_eq(MatrixGet(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
	cr_assert_eq(MatrixGet(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

	MatrixFree(m);
}

Test(MatrixColumnSwap, SameCol)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixColumnSwap(m, 1, 1);

	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(m, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");
	cr_assert_eq(MatrixGet(m, 1, 0), 3.0, "Expected row 1, column 0 to be 3.0");
	cr_assert_eq(MatrixGet(m, 1, 1), 4.0, "Expected row 1, column 1 to be 4.0");

	MatrixFree(m);
}

Test(MatrixBroadcastRows, InValidInputNullMatrix)
{
	Matrix *result = MatrixBroadcastRows(NULL, 3);
	cr_assert_null(result, "Expected NULL result for invalid input: NULL matrix");
	MatrixFree(result);
}

Test(MatrixBroadcastRows, InValidInput_num_rows_not_1)
{
	Matrix *m = MatrixNew(2, 2);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);

	Matrix *result = MatrixBroadcastRows(m, 3);

	cr_assert_null(result, "Expected NULL result for invalid input: num_rows not 1");
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRows, InValidInputRowLessThanNumRows)
{
	Matrix *m = MatrixNew(1, 2);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);

	Matrix *result = MatrixBroadcastRows(m, 1);

	cr_assert_null(result, "Expected NULL result for invalid input: row less than num_rows");
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRows, ValidInput)
{
	Matrix *m = MatrixNew(1, 2);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);

	Matrix *result = MatrixBroadcastRows(m, 3);

	cr_assert_not_null(result, "Expected non-NULL result for valid input");

	cr_assert_eq(result->num_rows, 3, "Expected num_rows to be 3");
	cr_assert_eq(result->num_cols, 2, "Expected num_cols to be 2");

	cr_assert_eq(MatrixGet(result, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 0, 1), 2.0, "Expected row 0, column 1 to be 2.0");

	cr_assert_eq(MatrixGet(result, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");

	cr_assert_eq(MatrixGet(result, 2, 0), 1.0, "Expected row 2, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 2, 1), 2.0, "Expected row 2, column 1 to be 2.0");

	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastColumns, ValidInput)
{
	Matrix *m = MatrixNew(2, 1);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 1, 0, 2.0);

	Matrix *broadcasted = MatrixBroadcastColumns(m, 3);

	cr_assert_eq(broadcasted->num_rows, 2, "Expected num_rows to be 2");
	cr_assert_eq(broadcasted->num_cols, 3, "Expected num_cols to be 3");

	cr_assert_eq(MatrixGet(broadcasted, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(broadcasted, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
	cr_assert_eq(MatrixGet(broadcasted, 0, 2), 1.0, "Expected row 0, column 2 to be 1.0");
	cr_assert_eq(MatrixGet(broadcasted, 1, 0), 2.0, "Expected row 1, column 0 to be 2.0");
	cr_assert_eq(MatrixGet(broadcasted, 1, 1), 2.0, "Expected row 1, column 1 to be 2.0");
	cr_assert_eq(MatrixGet(broadcasted, 1, 2), 2.0, "Expected row 1, column 2 to be 2.0");

	MatrixFree(m);
	MatrixFree(broadcasted);
}

Test(MatrixBroadcastColumns, InValidInput)
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

Test(MatrixBroadcastRowsAndColumns, InValidMatrix)
{
	Matrix *m = NULL;

	Matrix *result = MatrixBroadcastRowsAndColumns(m, 2, 2);
	cr_assert_null(result, "Expected NULL matrix to be returned for invalid input");

	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, InvalidRow)
{
	Matrix *m = MatrixNew(1, 2);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);

	Matrix *result = MatrixBroadcastRowsAndColumns(m, 0, 2);
	cr_assert_null(result, "Expected NULL matrix to be returned for invalid row");

	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, InvalidCol)
{
	Matrix *m = MatrixNew(1, 2);

	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);

	Matrix *result = MatrixBroadcastRowsAndColumns(m, 2, 0);
	cr_assert_null(result, "Expected NULL matrix to be returned for invalid column");

	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixBroadcastRowsAndColumns, ValidInput)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 1.0);

	Matrix *result = MatrixBroadcastRowsAndColumns(m, 3, 2);

	cr_assert_not_null(result, "Expected non-NULL matrix to be returned for valid input");
	cr_assert_eq(result->num_rows, 3, "Expected number of rows to be 3");
	cr_assert_eq(result->num_cols, 2, "Expected number of columns to be 2");
	cr_assert_eq(MatrixGet(result, 0, 0), 1.0, "Expected row 0, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 0, 1), 1.0, "Expected row 0, column 1 to be 1.0");
	cr_assert_eq(MatrixGet(result, 1, 0), 1.0, "Expected row 1, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 1, 1), 1.0, "Expected row 1, column 1 to be 1.0");
	cr_assert_eq(MatrixGet(result, 2, 0), 1.0, "Expected row 2, column 0 to be 1.0");
	cr_assert_eq(MatrixGet(result, 2, 1), 1.0, "Expected row 2, column 1 to be 1.0");

	MatrixFree(m);
	MatrixFree(result);
}

Test(matrix_row_stack, ValidMatrices)
{
	Matrix *m1 = MatrixNew(2, 3);
	Matrix *m2 = MatrixNew(2, 3);

	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			MatrixGet(m1, i, j) = i *m1->num_cols + j + 1;
			MatrixGet(m2, i, j) = (i + m1->num_rows) *m2->num_cols + j + 1;
		}
	}

	Matrix *result = MatrixRowStack(m1, m2);

	cr_assert_eq(result->num_rows, 4);
	cr_assert_eq(result->num_cols, 3);

	cr_assert_eq(MatrixGet(result, 0, 0), 1);
	cr_assert_eq(MatrixGet(result, 0, 1), 2);
	cr_assert_eq(MatrixGet(result, 0, 2), 3);
	cr_assert_eq(MatrixGet(result, 1, 0), 4);
	cr_assert_eq(MatrixGet(result, 1, 1), 5);
	cr_assert_eq(MatrixGet(result, 1, 2), 6);
	cr_assert_eq(MatrixGet(result, 2, 0), 7);
	cr_assert_eq(MatrixGet(result, 2, 1), 8);
	cr_assert_eq(MatrixGet(result, 2, 2), 9);
	cr_assert_eq(MatrixGet(result, 3, 0), 10);
	cr_assert_eq(MatrixGet(result, 3, 1), 11);
	cr_assert_eq(MatrixGet(result, 3, 2), 12);

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(matrix_row_stack, InValidMatrices)
{
	Matrix *m1 = MatrixNew(2, 3);
	Matrix *m2 = MatrixNew(2, 2);

	Matrix *result = MatrixRowStack(m1, m2);
	cr_assert_null(result);

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, NullMatrix1)
{
	Matrix *m1 = NULL;
	Matrix *m2 = MatrixNew(2, 2);

	Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for NULL m1");

	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, NullMatrix2)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = NULL;

	Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for NULL m2");

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, DifferentNumRows)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(3, 2);

	Matrix *result = MatrixColumnStack(m1, m2);
	cr_assert_null(result, "MatrixColumnStack returned non-NULL result for matrices with different numbers of rows");

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixColumnStack, SameNumRowsAndCols)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 2);

	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);
	MatrixSet(m2, 0, 0, 5.0);
	MatrixSet(m2, 0, 1, 6.0);
	MatrixSet(m2, 1, 0, 7.0);
	MatrixSet(m2, 1, 1, 8.0);

	Matrix *result = MatrixColumnStack(m1, m2);

	cr_assert_not_null(result, "MatrixColumnStack returned NULL for valid matrices");
	cr_assert_eq(result->num_rows, 2, "Result has incorrect number of rows");
	cr_assert_eq(result->num_cols, 4, "Result has incorrect number of columns");
	cr_assert_eq(MatrixGet(result, 0, 0), 1.0, "Result has incorrect value at (0, 0)");
	cr_assert_eq(MatrixGet(result, 0, 1), 2.0, "Result has incorrect value at (0, 1)");
	cr_assert_eq(MatrixGet(result, 0, 2), 5.0, "Result has incorrect value at (0, 2)");
	cr_assert_eq(MatrixGet(result, 0, 3), 6.0, "Result has incorrect value at (0, 3)");
	cr_assert_eq(MatrixGet(result, 1, 0), 3.0, "Result has incorrect value at (1, 0)");
	cr_assert_eq(MatrixGet(result, 1, 1), 4.0, "Result has incorrect value at (1, 1)");
	cr_assert_eq(MatrixGet(result, 1, 2), 7.0, "Result has incorrect value at (1, 2)");
	cr_assert_eq(MatrixGet(result, 1, 3), 15.0, "Result has incorrect value at (1, 3)");

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixAdd, SameDimensions)
{
	Matrix *m1 = MatrixNew(3, 3);
	Matrix *m2 = MatrixNew(3, 3);

	// Set the values of the matrices
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 0, 2, 3.0);
	MatrixSet(m1, 1, 0, 4.0);
	MatrixSet(m1, 1, 1, 5.0);
	MatrixSet(m1, 1, 2, 6.0);
	MatrixSet(m1, 2, 0, 7.0);
	MatrixSet(m1, 2, 1, 8.0);
	MatrixSet(m1, 2, 2, 9.0);
	MatrixSet(m2, 0, 0, 9.0);
	MatrixSet(m2, 0, 1, 8.0);
	MatrixSet(m2, 0, 2, 7.0);
	MatrixSet(m2, 1, 0, 6.0);
	MatrixSet(m2, 1, 1, 5.0);
	MatrixSet(m2, 1, 2, 4.0);
	MatrixSet(m2, 2, 0, 3.0);
	MatrixSet(m2, 2, 1, 2.0);
	MatrixSet(m2, 2, 2, 1.0);

	// Add the matrices
	Matrix *result = MatrixAdd(m1, m2);

	// Check the result
	cr_assert_not_null(result);
	cr_assert_eq(MatrixGet(result, 0, 0), 10.0);
	cr_assert_eq(MatrixGet(result, 0, 1), 10.0);
	cr_assert_eq(MatrixGet(result, 0, 2), 10.0);
	cr_assert_eq(MatrixGet(result, 1, 0), 10.0);
	cr_assert_eq(MatrixGet(result, 1, 1), 10.0);
	cr_assert_eq(MatrixGet(result, 1, 2), 10.0);
	cr_assert_eq(MatrixGet(result, 2, 0), 10.0);
	cr_assert_eq(MatrixGet(result, 2, 1), 10.0);
	cr_assert_eq(MatrixGet(result, 2, 2), 10.0);

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
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 1, 0, 3.0);
	MatrixSet(m2, 1, 1, 4.0);
	Matrix *result = MatrixSubtract(m1, m2);
	cr_assert_not_null(result);
	cr_assert_eq(MatrixGet(result, 0, 0), 0.0);
	cr_assert_eq(MatrixGet(result, 0, 1), 0.0);
	cr_assert_eq(MatrixGet(result, 1, 0), 0.0);
	cr_assert_eq(MatrixGet(result, 1, 1), 0.0);
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
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 0, 2, 3.0);
	MatrixSet(m1, 1, 0, 4.0);
	MatrixSet(m1, 1, 1, 5.0);
	MatrixSet(m1, 1, 2, 6.0);
	MatrixSet(m2, 0, 0, 7.0);
	MatrixSet(m2, 0, 1, 8.0);
	MatrixSet(m2, 1, 0, 9.0);
	MatrixSet(m2, 1, 1, 10.0);
	MatrixSet(m2, 2, 0, 11.0);
	MatrixSet(m2, 2, 1, 12.0);

	Matrix *result = MatrixMultiply(m1, m2);

	cr_assert_not_null(result, "Result should not be null");

	cr_assert_eq(MatrixGet(result, 0, 0), 58.0, "Expected 58 but got %d", MatrixGet(result, 0, 0));
	cr_assert_eq(MatrixGet(result, 0, 1), 64.0, "Expected 64 but got %d", MatrixGet(result, 0, 1));
	cr_assert_eq(MatrixGet(result, 1, 0), 139.0, "Expected 139 but got %d", MatrixGet(result, 1, 0));
	cr_assert_eq(MatrixGet(result, 1, 1), 154.0, "Expected 154 but got %d", MatrixGet(result, 1, 1));

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixElementWiseMultiply, Multiply)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 2);

	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 4.0);
	MatrixSet(m1, 1, 0, 6.0);
	MatrixSet(m1, 1, 1, 8.0);

	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 3.0);
	MatrixSet(m2, 1, 0, 5.0);
	MatrixSet(m2, 1, 1, 7.0);

	Matrix *result = MatrixElementWiseMultiply(m1, m2);

	cr_assert_not_null(result, "Result matrix should not be NULL");

	cr_assert_eq(MatrixGet(result, 0, 0), 2.0);
	cr_assert_eq(MatrixGet(result, 0, 1), 12.0);
	cr_assert_eq(MatrixGet(result, 1, 0), 30.0);
	cr_assert_eq(MatrixGet(result, 1, 1), 56.0);

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

Test(MatrixAddWithBroadcast, InValidInput)
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
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 1, 0, 2.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	Matrix *expected = MatrixNew(2, 2);
	MatrixSet(expected, 0, 0, 2.0);
	MatrixSet(expected, 0, 1, 3.0);
	MatrixSet(expected, 1, 0, 3.0);
	MatrixSet(expected, 1, 1, 4.0);
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
	MatrixSet(m3, 0, 0, 1.0);
	MatrixSet(m3, 0, 1, 2.0);
	MatrixSet(m3, 1, 0, 3.0);
	MatrixSet(m3, 1, 1, 4.0);

	MatrixSet(m4, 0, 0, 5.0);
	MatrixSet(m4, 0, 1, 6.0);
	MatrixSet(m4, 1, 0, 7.0);
	MatrixSet(m4, 1, 1, 8.0);
	Matrix *expected2 = MatrixNew(2, 2);
	MatrixSet(expected2, 0, 0, 6.0);
	MatrixSet(expected2, 0, 1, 8.0);
	MatrixSet(expected2, 1, 0, 10.0);
	MatrixSet(expected2, 1, 1, 12.0);
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
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 1, 0, 2.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	Matrix *expected = MatrixNew(2, 2);
	MatrixSet(expected, 0, 0, 2.0);
	MatrixSet(expected, 0, 1, 3.0);
	MatrixSet(expected, 1, 0, 3.0);
	MatrixSet(expected, 1, 1, 4.0);
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
	MatrixSet(m3, 0, 0, 1.0);
	MatrixSet(m3, 0, 1, 2.0);
	MatrixSet(m3, 1, 0, 3.0);
	MatrixSet(m3, 1, 1, 4.0);
	MatrixSet(m4, 0, 0, 5.0);
	MatrixSet(m4, 0, 1, 6.0);
	MatrixSet(m4, 1, 0, 7.0);
	MatrixSet(m4, 1, 1, 8.0);
	Matrix *expected2 = MatrixNew(2, 2);
	MatrixSet(expected2, 0, 0, 6.0);
	MatrixSet(expected2, 0, 1, 8.0);
	MatrixSet(expected2, 1, 0, 10.0);
	MatrixSet(expected2, 1, 1, 12.0);
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
	MatrixSet(m1, 0, 0, 5.0);
	MatrixSet(m1, 0, 1, 7.0);
	MatrixSet(m1, 0, 2, 3.0);
	MatrixSet(m1, 1, 0, 8.0);
	MatrixSet(m1, 1, 1, 1.0);
	MatrixSet(m1, 1, 2, 2.0);
	MatrixSet(m2, 0, 0, 2.0);
	MatrixSet(m2, 0, 1, 3.0);
	MatrixSet(m2, 0, 2, 1.0);

	Matrix *expected_result = MatrixNew(2, 3);
	MatrixSet(expected_result, 0, 0, 3.0);
	MatrixSet(expected_result, 0, 1, 4.0);
	MatrixSet(expected_result, 0, 2, 2.0);
	MatrixSet(expected_result, 1, 0, 6.0);
	MatrixSet(expected_result, 1, 1, -2.0);
	MatrixSet(expected_result, 1, 2, 1.0);

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

Test(matrix_multiply_with_broadcast, NullMatrix)
{
	Matrix *m1 = NULL;
	Matrix *m2 = NULL;
	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);

	cr_assert_null(result, "Expected null result when passing null matrices");
}

Test(MatrixMultiplyWithBroadcast, IncompatibleMatrices)
{
	Matrix *m1 = MatrixNew(3, 2);
	Matrix *m2 = MatrixNew(2, 3);
	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);

	cr_assert_null(result, "Expected null result when passing incompatible matrices");

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixMultiplyWithBroadcast, BroadcastCol)
{
	Matrix *m1 = MatrixNew(2, 1);
	Matrix *m2 = MatrixNew(1, 3);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 0, 1, 5.0);
	MatrixSet(m2, 0, 2, 6.0);
	Matrix *expected = MatrixNew(2, 3);
	MatrixSet(expected, 0, 0, 8.0);
	MatrixSet(expected, 0, 1, 10.0);
	MatrixSet(expected, 0, 2, 12.0);
	MatrixSet(expected, 1, 0, 12.0);
	MatrixSet(expected, 1, 1, 15.0);
	MatrixSet(expected, 1, 2, 18.0);
	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);

	cr_assert(MatrixIsEqual(expected, result), "Expected matrices to be equal");

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixMultiplyWithBroadcast, BroadcastRows)
{
	Matrix *m1 = MatrixNew(1, 3);
	Matrix *m2 = MatrixNew(3, 2);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 3.0);
	MatrixSet(m1, 0, 2, 4.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 1, 0, 2.0);
	MatrixSet(m2, 2, 0, 3.0);
	MatrixSet(m2, 0, 1, 4.0);
	MatrixSet(m2, 1, 1, 5.0);
	MatrixSet(m2, 2, 1, 6.0);
	Matrix *expected = MatrixNew(1, 2);
	MatrixSet(expected, 0, 0, 20.0);
	MatrixSet(expected, 0, 1, 32.0);
	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);

	cr_assert(MatrixIsEqual(expected, result), "Expected matrices to be equal");

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixMultiplyWithBroadcast, SameDimensions)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);
	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 0, 1, 3.0);
	MatrixSet(m2, 1, 0, 2.0);
	MatrixSet(m2, 1, 1, 1.0);

	Matrix *expected = MatrixNew(2, 2);
	MatrixSet(expected, 0, 0, 8.0);
	MatrixSet(expected, 0, 1, 5.0);
	MatrixSet(expected, 1, 0, 20.0);
	MatrixSet(expected, 1, 1, 13.0);

	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);
	cr_assert(MatrixAreEqual(expected, result), "Multiplication with broadcast failed");
	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixMultiplyWithBroadcast, M1ColsLessThanM2Rows)
{
	Matrix *m1 = MatrixNew(2, 1);
	Matrix *m2 = MatrixNew(1, 2);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 0, 1, 3.0);

	Matrix *expected = MatrixNew(2, 2);
	MatrixSet(expected, 0, 0, 8.0);
	MatrixSet(expected, 0, 1, 6.0);
	MatrixSet(expected, 1, 0, 12.0);
	MatrixSet(expected, 1, 1, 9.0);

	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);
	cr_assert(MatrixAreEqual(expected, result), "Multiplication with broadcast failed");
	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixMultiplyWithBroadcast, M1ColsGreaterThanM2Rows)
{
	Matrix *m1 = MatrixNew(1, 2);
	Matrix *m2 = MatrixNew(2, 1);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 3.0);
	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 1, 0, 5.0);

	Matrix *expected = MatrixNew(2, 1);
	MatrixSet(expected, 0, 0, 23.0);
	MatrixSet(expected, 1, 0, 32.0);

	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);
	cr_assert(MatrixAreEqual(expected, result), "Multiplication with broadcast failed");
	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixMultiplyWithBroadcast, M1M2Broadcasting)
{
	Matrix *m1 = MatrixNew(2, 1);
	Matrix *m2 = MatrixNew(1, 3);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 1, 0, 2.0);
	MatrixSet(m2, 0, 0, 3.0);
	MatrixSet(m2, 0, 1, 4.0);
	MatrixSet(m2, 0, 2, 5.0);

	Matrix *result = MatrixMultiplyWithBroadcast(m1, m2);
	cr_assert(result != NULL);
	cr_assert_eq(result->num_rows, 2);
	cr_assert_eq(result->num_cols, 3);
	cr_assert_float_eq(MatrixGet(result, 0, 0), 3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(result, 0, 1), 4.0, 1e-6);
	cr_assert_float_eq(MatrixGet(result, 0, 2), 5.0, 1e-6);
	cr_assert_float_eq(MatrixGet(result, 1, 0), 6.0, 1e-6);
	cr_assert_float_eq(MatrixGet(result, 1, 1), 8.0, 1e-6);
	cr_assert_float_eq(MatrixGet(result, 1, 2), 10.0, 1e-6);

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(result);
}

Test(MatrixElementWiseMultiplyWithBroadcast, InValidMatrixM1)
{
	Matrix *m1 = NULL;
	Matrix *m2 = MatrixNew(3, 3);
	cr_assert_null(MatrixElementWiseMultiplyWithBroadcast(m1, m2));
	MatrixFree(m2);
}

Test(MatrixElementWiseMultiplyWithBroadcast, InValidMatrixM2)
{
	Matrix *m1 = MatrixNew(3, 3);
	Matrix *m2 = NULL;
	cr_assert_null(MatrixElementWiseMultiplyWithBroadcast(m1, m2));
	MatrixFree(m1);
}

Test(MatrixElementWiseMultiplyWithBroadcast, SameDimensions)
{
	Matrix *m1 = MatrixNew(3, 3);
	Matrix *m2 = MatrixNew(3, 3);

	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 1, 1, 3.0);
	MatrixSet(m1, 2, 2, 4.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 1, 1, 2.0);
	MatrixSet(m2, 2, 2, 3.0);

	Matrix *expected = MatrixNew(3, 3);
	MatrixSet(expected, 0, 0, 2.0);
	MatrixSet(expected, 1, 1, 6.0);
	MatrixSet(expected, 2, 2, 12.0);

	Matrix *result = MatrixElementWiseMultiplyWithBroadcast(m1, m2);
	cr_assert(MatrixIsEqual(expected, result));

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixElementWiseMultiplyWithBroadcast, M1M2Broadcasting)
{
	Matrix *m1 = MatrixNew(2, 1);
	Matrix *m2 = MatrixNew(1, 3);

	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 0, 1, 5.0);
	MatrixSet(m2, 0, 2, 6.0);

	Matrix *expected = MatrixNew(2, 3);
	MatrixSet(expected, 0, 0, 8.0);
	MatrixSet(expected, 0, 1, 10.0);
	MatrixSet(expected, 0, 2, 12.0);
	MatrixSet(expected, 1, 0, 12.0);
	MatrixSet(expected, 1, 1, 15.0);
	MatrixSet(expected, 1, 2, 18.0);

	Matrix *result = MatrixElementWiseMultiplyWithBroadcast(m1, m2);
	cr_assert(MatrixIsEqual(expected, result));

	MatrixFree(m1);
	MatrixFree(m2);
	MatrixFree(expected);
	MatrixFree(result);
}

Test(MatrixTranspose, SquareMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 1, 0, 4.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, 6.0);
	MatrixSet(m, 2, 0, 7.0);
	MatrixSet(m, 2, 1, 8.0);
	MatrixSet(m, 2, 2, 9.0);

	MatrixTranspose(m);

	cr_assert_eq(m->num_rows, 3);
	cr_assert_eq(m->num_cols, 3);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 1), 4.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 7.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 5.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 8.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 0), 3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 1), 6.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 9.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixTranspose, RectangularMatrix)
{
	Matrix *m = MatrixNew(2, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 1, 0, 4.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, 6.0);

	MatrixTranspose(m);

	cr_assert_eq(m->num_rows, 3);
	cr_assert_eq(m->num_cols, 2);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 1), 4.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 5.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 0), 3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 1), 6.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixTranspose, NullMatrix)
{
	Matrix *m = NULL;
	MatrixTranspose(m);
	cr_assert_null(m, "Expected NULL matrix after calling MatrixTranspose on NULL matrix");
}

Test(MatrixTranspose, SquareMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 1, 0, 4.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, 6.0);
	MatrixSet(m, 2, 0, 7.0);
	MatrixSet(m, 2, 1, 8.0);
	MatrixSet(m, 2, 2, 9.0);

	MatrixTranspose(m);

	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, "Expected element at (0,0) to be 1 after transposition");
	cr_assert_eq(MatrixGet(m, 0, 1), 4.0, "Expected element at (0,1) to be 4 after transposition");
	cr_assert_eq(MatrixGet(m, 0, 2), 7.0, "Expected element at (0,2) to be 7 after transposition");
	cr_assert_eq(MatrixGet(m, 1, 0), 2.0, "Expected element at (1,0) to be 2 after transposition");
	cr_assert_eq(MatrixGet(m, 1, 1), 5.0, "Expected element at (1,1) to be 5 after transposition");
	cr_assert_eq(MatrixGet(m, 1, 2), 8.0, "Expected element at (1,2) to be 8 after transposition");
	cr_assert_eq(MatrixGet(m, 2, 0), 3.0, "Expected element at (2,0) to be 3 after transposition");
	cr_assert_eq(MatrixGet(m, 2, 1), 6.0, "Expected element at (2,1) to be 6 after transposition");
	cr_assert_eq(MatrixGet(m, 2, 2), 9.0, "Expected element at (2,2) to be 9 after transposition");

	MatrixFree(m);
}

Test(MatrixTrace, NullMatrix)
{
	Matrix *m = NULL;
	double trace = MatrixTrace(m);
	cr_assert(isnan(trace), "Expected NaN trace value after calling MatrixTrace on NULL matrix");
}

Test(MatrixTrace, NonSquareMatrix)
{
	Matrix *m = MatrixNew(2, 3);
	double trace = MatrixTrace(m);
	cr_assert(isnan(trace), "Expected NaN trace value after calling MatrixTrace on non-square matrix");

	MatrixFree(m);
}

Test(MatrixTrace, SquareMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 1, 0, 4.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, 6.0);
	MatrixSet(m, 2, 0, 7.0);
	MatrixSet(m, 2, 1, 8.0);
	MatrixSet(m, 2, 2, 9.0);

	double trace = MatrixTrace(m);
	cr_assert_eq(trace, 15);

	MatrixFree(m);
}

Test(MatrixDeterminant, NullMatrix)
{
	double det = MatrixDeterminant(NULL);
	cr_assert(isnan(det), "Determinant should be NaN for NULL matrix");
}

Test(MatrixDeterminant, NonSquareMatrix)
{
	Matrix *m = MatrixNew(2, 3);
	double det = MatrixDeterminant(m);
	MatrixFree(m);
	cr_assert(isnan(det), "Determinant should be NaN for non-square matrix");
}

Test(MatrixDeterminant, OnexOneMatrix)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 5);
	double det = MatrixDeterminant(m);
	MatrixFree(m);
	cr_assert_eq(det, 5.0, "Determinant of 1x1 matrix should be the only element");
}

Test(MatrixDeterminant, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, 3.0);
	MatrixSet(m, 1, 0, 1.0);
	MatrixSet(m, 1, 1, 4.0);
	double det = MatrixDeterminant(m);
	MatrixFree(m);
	cr_assert_eq(det, 5.0, "Determinant of 2x2 matrix should be 2 * 4 - 3 *1 = 5");
}

Test(MatrixDeterminant, ThreexThreeMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 1, 0, 4.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, 6.0);
	MatrixSet(m, 2, 0, 7.0);
	MatrixSet(m, 2, 1, 8.0);
	MatrixSet(m, 2, 2, 9.0);
	double det = MatrixDeterminant(m);
	MatrixFree(m);
	cr_assert_eq(det, 0.0, "Determinant of 3x3 matrix should be 0");
}

Test(MatrixDeterminant, NonSquareMatrix)
{
	Matrix *m = MatrixNew(3, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);
	MatrixSet(m, 2, 0, 5.0);
	MatrixSet(m, 2, 1, 6.0);

	double det = MatrixDeterminant(m);
	cr_assert(isnan(det), "Expected determinant of NaN for non-square matrix");
	MatrixFree(m);
}

Test(MatrixDeterminant, OnexOneMatrix)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 5);

	double det = MatrixDeterminant(m);
	cr_assert_eq(det, 5, "Expected determinant of 5 for 1x1 matrix");
	MatrixFree(m);
}

Test(MatrixDeterminant, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 1, 0, 3.0);
	MatrixSet(m, 1, 1, 4.0);

	double det = MatrixDeterminant(m);
	cr_assert_eq(det, -2, "Expected determinant of -2 for 2x2 matrix");
	MatrixFree(m);
}

Test(MatrixDeterminant, FivexFiveMatrix)
{
	Matrix *m = MatrixNew(5, 5);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 0, 3, 4.0);
	MatrixSet(m, 0, 4, 5.0);
	MatrixSet(m, 1, 0, 6.0);
	MatrixSet(m, 1, 1, 7.0);
	MatrixSet(m, 1, 2, 8.0);
	MatrixSet(m, 1, 3, 9.0);
	MatrixSet(m, 1, 4, 10.0);
	MatrixSet(m, 2, 0, 11.0);
	MatrixSet(m, 2, 1, 12.0);
	MatrixSet(m, 2, 2, 13.0);
	MatrixSet(m, 2, 3, 14.0);
	MatrixSet(m, 2, 4, 15.0);
	MatrixSet(m, 3, 0, 16.0);
	MatrixSet(m, 3, 1, 17.0);
	MatrixSet(m, 3, 2, 18.0);
	MatrixSet(m, 3, 3, 19.0);
	MatrixSet(m, 3, 4, 20.0);
	MatrixSet(m, 4, 0, 21.0);
	MatrixSet(m, 4, 1, 22.0);
	MatrixSet(m, 4, 2, 23.0);
	MatrixSet(m, 4, 3, 24.0);
	MatrixSet(m, 4, 4, 25.0);

	double det = MatrixDeterminant(m);
	cr_assert_eq(det, -12.0);
	MatrixFree(m);
}

Test(MatrixRowEchelon, NullMatrix)
{
	Matrix *m = NULL;
	MatrixRowEchelon(m);
	cr_assert(true);
}

Test(MatrixRowEchelon, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, 4.0);
	MatrixSet(m, 1, 0, 1.0);
	MatrixSet(m, 1, 1, 2.0);

	MatrixRowEchelon(m);

	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 1), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 0.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixRowEchelon, ThreexThreeMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, 4.0);
	MatrixSet(m, 0, 2, 6.0);
	MatrixSet(m, 1, 0, 1.0);
	MatrixSet(m, 1, 1, 2.0);
	MatrixSet(m, 1, 2, 3.0);
	MatrixSet(m, 2, 0, 4.0);
	MatrixSet(m, 2, 1, 5.0);
	MatrixSet(m, 2, 2, 6.0);

	MatrixRowEchelon(m);

	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 1), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 2), 3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 0.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixReducedRowEchelon, InValidMatrix)
{
	Matrix *m = NULL;
	MatrixReducedRowEchelon(m);
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
}

Test(MatrixReducedRowEchelon, OnexOneMatrix)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 3.0);
	MatrixReducedRowEchelon(m);
	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, "Expected the matrix to be reduced to[1]");
	MatrixFree(m);
}

Test(MatrixReducedRowEchelon, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, -1.0);
	MatrixSet(m, 1, 0, -4.0);
	MatrixSet(m, 1, 1, 2.0);
	MatrixReducedRowEchelon(m);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m, 0, 1), -0.5, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m, 1, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m, 1, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	MatrixFree(m);
}

Test(MatrixReducedRowEchelon, ThreexThreeMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, -1.0);
	MatrixSet(m, 1, 0, 2.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, -4.0);
	MatrixSet(m, 2, 0, -1.0);
	MatrixSet(m, 2, 1, -4.0);
	MatrixSet(m, 2, 2, 7.0);
	MatrixReducedRowEchelon(m);
	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 0, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 0, 2), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 1, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 1, 1), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 1, 2), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 2, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 2, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m, 2, 2), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	MatrixFree(m);
}

Test(MatrixReducedRowEchelon, FourxFourMatrix)
{
	Matrix *m = MatrixNew(4, 4);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 3.0);
	MatrixSet(m, 0, 2, 1.0);
	MatrixSet(m, 0, 3, 9.0);
	MatrixSet(m, 1, 0, 2.0);
	MatrixSet(m, 1, 1, 6.0);
	MatrixSet(m, 1, 2, 1.0);
	MatrixSet(m, 1, 3, 2.0);
	MatrixSet(m, 2, 0, 1.0);
	MatrixSet(m, 2, 1, 1.0);
	MatrixSet(m, 2, 2, 2.0);
	MatrixSet(m, 2, 3, 7.0);
	MatrixSet(m, 3, 0, 3.0);
	MatrixSet(m, 3, 1, 1.0);
	MatrixSet(m, 3, 2, 1.0);
	MatrixSet(m, 3, 3, 8.0);

	MatrixReducedRowEchelon(m);

	cr_assert_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 0, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 0, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 0, 3), -2.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 1, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 1, 1), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 1, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 1, 3), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 2, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 2, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 2, 2), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 2, 3), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 3, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 3, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 3, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m, 3, 3), 0.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixReducedRowEchelon, NonSquareMatrix)
{
	Matrix *m = MatrixNew(3, 4);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 0, 3, 4.0);
	MatrixSet(m, 1, 0, 5.0);
	MatrixSet(m, 1, 1, 6.0);
	MatrixSet(m, 1, 2, 7.0);
	MatrixSet(m, 1, 3, 8.0);
	MatrixSet(m, 2, 0, 9.0);
	MatrixSet(m, 2, 1, 10.0);
	MatrixSet(m, 2, 2, 11.0);
	MatrixSet(m, 2, 3, 12.0);

	MatrixReducedRowEchelon(m);

	cr_assert_float_eq(MatrixGet(m, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 2), -1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 0, 3), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 1), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 2), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 1, 3), -3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 2), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m, 2, 3), 0.0, 1e-6);

	MatrixFree(m);
}

Test(MatrixRowEchelonGet, NullMatrix)
{
	Matrix *m = NULL;
	Matrix *m1 = MatrixRowEchelonGet(m);
	cr_assert_null(m1, "Expected NULL matrix after calling MatrixRowEchelonGet on NULL matrix");
	cr_assert(true);
}

Test(MatrixRowEchelonGet, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, 4.0);
	MatrixSet(m, 1, 0, 1.0);
	MatrixSet(m, 1, 1, 2.0);

	Matrix *m1 = MatrixRowEchelonGet(m);

	cr_assert_float_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 1), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 1), 0.0, 1e-6);

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixRowEchelonGet, ThreexThreeMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, 4.0);
	MatrixSet(m, 0, 2, 6.0);
	MatrixSet(m, 1, 0, 1.0);
	MatrixSet(m, 1, 1, 2.0);
	MatrixSet(m, 1, 2, 3.0);
	MatrixSet(m, 2, 0, 4.0);
	MatrixSet(m, 2, 1, 5.0);
	MatrixSet(m, 2, 2, 6.0);

	Matrix *m1 = MatrixRowEchelonGet(m);

	cr_assert_float_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 1), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 2), 3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 1), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 2), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 2), 0.0, 1e-6);

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixReducedRowEchelonGet, InValidMatrix)
{
	Matrix *m = NULL;
	Matrix *m1 = MatrixReducedRowEchelonGet(m);
	cr_assert_null(m1, "Expected NULL matrix after calling MatrixReducedRowEchelonGet on NULL matrix");
	cr_assert_stderr_eq_str("Invalid matrix passed\n");
}

Test(MatrixReducedRowEchelonGet, OnexOneMatrix)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 3.0);

	Matrix *m1 = MatrixReducedRowEchelonGet(m);
	cr_assert_eq(MatrixGet(m1, 0, 0), 1.0, "Expected the matrix to be reduced to[1]");

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixReducedRowEchelonGet, TwoxTwoMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixSet(m, 0, 0, 2.0);
	MatrixSet(m, 0, 1, -1.0);
	MatrixSet(m, 1, 0, -4.0);
	MatrixSet(m, 1, 1, 2.0);

	Matrix *m1 = MatrixReducedRowEchelonGet(m);
	cr_assert_float_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m1, 0, 1), -0.5, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");
	cr_assert_float_eq(MatrixGet(m1, 1, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, -0.5], [0, 0]]");

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixReducedRowEchelonGetGet, ThreexThreeMatrix)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, -1.0);
	MatrixSet(m, 1, 0, 2.0);
	MatrixSet(m, 1, 1, 5.0);
	MatrixSet(m, 1, 2, -4.0);
	MatrixSet(m, 2, 0, -1.0);
	MatrixSet(m, 2, 1, -4.0);
	MatrixSet(m, 2, 2, 7.0);

	Matrix *m1 = MatrixReducedRowEchelonGetGet(m);
	cr_assert_float_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 0, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 0, 2), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 1, 1), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 1, 2), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 2, 0), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 2, 1), 0.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");
	cr_assert_float_eq(MatrixGet(m1, 2, 2), 1.0, 1e-6, "Expected the matrix to be reduced to[[1, 0, 0], [0, 1, 0], [0, 0, 1]]");

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixReducedRowEchelonGetGet, FourxFourMatrix)
{
	Matrix *m = MatrixNew(4, 4);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 3.0);
	MatrixSet(m, 0, 2, 1.0);
	MatrixSet(m, 0, 3, 9.0);
	MatrixSet(m, 1, 0, 2.0);
	MatrixSet(m, 1, 1, 6.0);
	MatrixSet(m, 1, 2, 1.0);
	MatrixSet(m, 1, 3, 2.0);
	MatrixSet(m, 2, 0, 1.0);
	MatrixSet(m, 2, 1, 1.0);
	MatrixSet(m, 2, 2, 2.0);
	MatrixSet(m, 2, 3, 7.0);
	MatrixSet(m, 3, 0, 3.0);
	MatrixSet(m, 3, 1, 1.0);
	MatrixSet(m, 3, 2, 1.0);
	MatrixSet(m, 3, 3, 8.0);

	Matrix *m1 = MatrixReducedRowEchelonGetGet(m);

	cr_assert_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 0, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 0, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 0, 3), -2.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 1, 1), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 1, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 1, 3), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 2, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 2, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 2, 2), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 2, 3), 1.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 3, 0), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 3, 1), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 3, 2), 0.0, 1e-6);
	cr_assert_eq(MatrixGet(m1, 3, 3), 0.0, 1e-6);

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixReducedRowEchelonGetGet, NonSquareMatrix)
{
	Matrix *m = MatrixNew(3, 4);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 0, 3, 4.0);
	MatrixSet(m, 1, 0, 5.0);
	MatrixSet(m, 1, 1, 6.0);
	MatrixSet(m, 1, 2, 7.0);
	MatrixSet(m, 1, 3, 8.0);
	MatrixSet(m, 2, 0, 9.0);
	MatrixSet(m, 2, 1, 10.0);
	MatrixSet(m, 2, 2, 11.0);
	MatrixSet(m, 2, 3, 12.0);

	Matrix *m1 = MatrixReducedRowEchelonGetGet(m);

	cr_assert_float_eq(MatrixGet(m1, 0, 0), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 2), -1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 0, 3), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 1), 1.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 2), 2.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 1, 3), -3.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 0), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 1), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 2), 0.0, 1e-6);
	cr_assert_float_eq(MatrixGet(m1, 2, 3), 0.0, 1e-6);

	MatrixFree(m);
	MatrixFree(m1);
}

Test(MatrixColumnL2Norm, NullMatrix)
{
	double result = MatrixColumnL2Norm(NULL, 0);
	cr_assert_true(isnan(result), "Expected NaN for NULL matrix");
}

Test(MatrixColumnL2Norm, InValidColumn)
{
	Matrix *m = MatrixNew(3, 3);
	double result = MatrixColumnL2Norm(m, 3);
	MatrixFree(m);
	cr_assert_true(isnan(result), "Expected NaN for invalid column");
}

Test(MatrixColumnL2Norm, SingleCol)
{
	Matrix *m = MatrixNew(3, 1);
	MatrixSetValue(m, 0, 0, 1.0);
	MatrixSetValue(m, 1, 0, 2.0);
	MatrixSetValue(m, 2, 0, 3.0);

	double result = MatrixColumnL2Norm(m, 0);

	MatrixFree(m);

	cr_assert_float_eq(result, sqrt(14.0), 1e-6, "Expected column L2 norm to be sqrt(14)");
}

Test(MatrixColumnL2Norm, MultipleCol)
{
	Matrix *m = MatrixNew(3, 3);
	MatrixSetValue(m, 0, 0, 1.0);
	MatrixSetValue(m, 0, 1, 2.0);
	MatrixSetValue(m, 0, 2, -1.0);
	MatrixSetValue(m, 1, 0, 2.0);
	MatrixSetValue(m, 1, 1, 5.0);
	MatrixSetValue(m, 1, 2, -4.0);
	MatrixSetValue(m, 2, 0, -1.0);
	MatrixSetValue(m, 2, 1, -4.0);
	MatrixSetValue(m, 2, 2, 7.0);

	double norm0 = MatrixColumnL2Norm(m, 0);
	double norm1 = MatrixColumnL2Norm(m, 1);
	double norm2 = MatrixColumnL2Norm(m, 2);

	MatrixFree(m);

	cr_assert_float_eq(norm0, sqrt(6.0), 1e-6, "Expected column L2 norm to be sqrt(6)");
	cr_assert_float_eq(norm1, sqrt(45.0), 1e-6, "Expected column L2 norm to be sqrt(45)");
	cr_assert_float_eq(norm2, sqrt(66.0), 1e-6, "Expected column L2 norm to be sqrt(66)");
}

Test(MatrixL2Norm, NullMatrix)
{
	Matrix *m = NULL;
	Matrix *result = MatrixL2Norm(m);
	cr_assert_null(result);
}

Test(MatrixL2Norm, SingleElementMatrix)
{
	Matrix *m = MatrixNew(1, 1);
	MatrixSet(m, 0, 0, 3.0);
	Matrix *result = MatrixL2Norm(m);
	cr_assert_not_null(result);
	cr_assert_eq(result->num_rows, 1);
	cr_assert_eq(result->num_cols, 1);
	cr_assert_float_eq(MatrixGet(result, 0, 0), 3.0, 1e-6);
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixL2Norm, MultipleElementsMatrix)
{
	Matrix m = MatrixNew(3, 4);
	MatrixSet(m, 0, 0, 1.0);
	MatrixSet(m, 0, 1, 2.0);
	MatrixSet(m, 0, 2, 3.0);
	MatrixSet(m, 0, 3, 4.0);
	MatrixSet(m, 1, 0, 5.0);
	MatrixSet(m, 1, 1, 6.0);
	MatrixSet(m, 1, 2, 7.0);
	MatrixSet(m, 1, 3, 8.0);
	MatrixSet(m, 2, 0, 9.0);
	MatrixSet(m, 2, 1, 10.0);
	MatrixSet(m, 2, 2, 11.0);
	MatrixSet(m, 2, 3, 12.0);
	Matrix result = MatrixL2Norm(m);
	cr_assert_not_null(result);
	cr_assert_eq(result->num_rows, 1);
	cr_assert_eq(result->num_cols, 4);
	cr_assert_float_eq(MatrixGet(result, 0, 0), sqrt(11 + 55 + 99), 1e-6);
	cr_assert_float_eq(MatrixGet(result, 0, 1), sqrt(22 + 66 + 1010), 1e-6);
	cr_assert_float_eq(MatrixGet(result, 0, 2), sqrt(33 + 77 + 1111), 1e-6);
	cr_assert_float_eq(MatrixGet(result, 0, 3), sqrt(44 + 88 + 1212), 1e-6);
	MatrixFree(m);
	MatrixFree(result);
}

Test(MatrixCosineSimilarity, NullMatrixM1)
{
	Matrix *m = MatrixNew(3, 4);
	double result = MatrixCosineSimilarity(NULL, m);
	cr_assert_true(isnan(result));
	MatrixFree(m);
}

Test(MatrixCosineSimilarity, NullMatrixM2)
{
	Matrix *m = MatrixNew(3, 4);
	double result = MatrixCosineSimilarity(m, NULL);
	cr_assert_true(isnan(result));
	MatrixFree(m);
}

Test(MatrixCosineSimilarity, EmptyMatrix)
{
	Matrix *m1 = MatrixNew(0, 0);
	Matrix *m2 = MatrixNew(0, 0);

	double result = MatrixCosineSimilarity(m1, m2);
	cr_assert_float_eq(result, 0.0, 1e-6);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixCosineSimilarity, SingleColumnMatrix)
{
	Matrix *m1 = MatrixNew(3, 1);
	Matrix *m2 = MatrixNew(3, 1);

	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 1, 0, 2.0);
	MatrixSet(m1, 2, 0, 3.0);

	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 1, 0, 5.0);
	MatrixSet(m2, 2, 0, 6.0);

	double result = MatrixCosineSimilarity(m1, m2);
	cr_assert_float_eq(result, 0.9746318462, 1e-6);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixCosineSimilarity, MultipleColumnsMatrix)
{
	Matrix *m1 = MatrixNew(3, 2);
	Matrix *m2 = MatrixNew(3, 2);

	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 2.0);
	MatrixSet(m1, 1, 1, 3.0);
	MatrixSet(m1, 2, 0, 3.0);
	MatrixSet(m1, 2, 1, 4.0);

	MatrixSet(m2, 0, 0, 4.0);
	MatrixSet(m2, 0, 1, 3.0);
	MatrixSet(m2, 1, 0, 2.0);
	MatrixSet(m2, 1, 1, 1.0);
	MatrixSet(m2, 2, 0, 1.0);
	MatrixSet(m2, 2, 1, 3.0);

	double result = MatrixCosineSimilarity(m1, m2);
	cr_assert_float_eq(result, 0.8116496589, 1e-6);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixTSSSimilarity, SameMatrix)
{
	double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
	Matrix *m1 = MatrixFrom(1, 9, 9, data);
	Matrix *m2 = MatrixFrom(1, 9, 9, data);

	double result = MatrixTSSSimilarity(&*m1, &*m2);

	cr_assert_eq(result, 1.0, "Expected TS-SS similarity of 1.0, but got %f", result);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixTSSSimilarity, DifferentMatrices)
{
	double data1 = {1.0, 2.0, 3.0, 4.0};
	double data2 = {1.0, 2.0, 3.0};
	Matrix *m1 = MatrixFrom(1, 4, 4, data1);
	Matrix *m2 = MatrixFrom(1, 3, 3, data2);

	double result = MatrixTSSSimilarity(&*m1, &*m2);

	cr_assert(isnan(result), "Expected NAN, but got %f", result);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixTSSSimilarity, DifferentDimensions)
{
	double data1 = {1.0, 2.0, 3.0};
	double data2 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	Matrix *m1 = MatrixFrom(1, 3, 3, data1);
	Matrix *m2 = MatrixFrom(2, 3, 6, data2);

	double result = MatrixTSSSimilarity(&*m1, &*m2);

	cr_assert(isnan(result), "Expected NAN, but got %f", result);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixTSSSimilarity, OneElementDifferent)
{
	double data1 = {1.0, 2.0, 3.0};
	double data2 = {1.0, 2.5, 3.0};
	Matrix *m1 = MatrixFrom(1, 3, 3, data1);
	Matrix *m2 = MatrixFrom(1, 3, 3, data2);

	double result = MatrixTSSSimilarity(&*m1, &*m2);

	cr_assert(result > 0.5, "Expected TS-SS similarity > 0.5, but got %f", result);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixEuclideanDistance, InvalidMatrix)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = NULL;

	double result1 = MatrixEuclideanDistance(m1, m2);
	cr_assert_true(isnan(result1), "Expected result to be NaN");

	double result2 = MatrixEuclideanDistance(m2, m1);
	cr_assert_true(isnan(result2), "Expected result to be NaN");

	MatrixFree(m1);
}

Test(MatrixEuclideanDistance, SameMatrix)
{
	Matrix *m1 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);

	double result = MatrixEuclideanDistance(m1, m1);
	cr_assert_float_eq(result, 0.0, 1e-6, "Expected result to be 0");

	MatrixFree(m1);
}

Test(MatrixEuclideanDistance, DifferentMatrix)
{
	Matrix *m1 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);

	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m2, 0, 0, 2.0);
	MatrixSet(m2, 0, 1, 3.0);
	MatrixSet(m2, 1, 0, 4.0);
	MatrixSet(m2, 1, 1, 5.0);

	double result = MatrixEuclideanDistance(m1, m2);
	cr_assert_float_eq(result, sqrt(10), 1e-6, "Expected result to be sqrt(10)");

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixManhattanDistance, NullMatrices)
{
	Matrix *m1 = NULL;
	Matrix *m2 = NULL;
	cr_assert(isnan(MatrixManhattanDistance(m1, m2)));
}

Test(MatrixManhattanDistance, DifferentDimensions)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(3, 3);
	cr_assert(isnan(MatrixManhattanDistance(m1, m2)));
	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixManhattanDistance, ZeroDistance)
{
	Matrix *m1 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);

	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 1, 0, 3.0);
	MatrixSet(m2, 1, 1, 4.0);

	cr_assert_eq(MatrixManhattanDistance(m1, m2), 0.0);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixManhattanDistance, PositiveDistance)
{
	Matrix *m1 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 1.0);
	MatrixSet(m1, 0, 1, 2.0);
	MatrixSet(m1, 1, 0, 3.0);
	MatrixSet(m1, 1, 1, 4.0);

	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m2, 0, 0, 0.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 1, 0, 3.0);
	MatrixSet(m2, 1, 1, 5.0);

	cr_assert_eq(MatrixManhattanDistance(m1, m2), 2.0);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixMinkowskiDistance, NullMatrix1)
{
	Matrix *m1 = NULL;
	Matrix *m2 = MatrixNew(2, 2);
	cr_assert_nan(MatrixMinkowskiDistance(m1, m2, 2));
	MatrixFree(m2);
}

Test(MatrixMinkowskiDistance, NullMatrix2)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = NULL;
	cr_assert_nan(MatrixMinkowskiDistance(m1, m2, 2));
	MatrixFree(m1);
}

Test(MatrixMinkowskiDistance, DifferentDimensions)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 3);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 3.0);
	MatrixSet(m1, 1, 0, 4.0);
	MatrixSet(m1, 1, 1, 5.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 0, 2, 3.0);
	MatrixSet(m2, 1, 0, 4.0);
	MatrixSet(m2, 1, 1, 5.0);
	MatrixSet(m2, 1, 2, 6.0);
	cr_assert_nan(MatrixMinkowskiDistance(m1, m2, 2));
	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixMinkowskiDistance, P1)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 3.0);
	MatrixSet(m1, 1, 0, 4.0);
	MatrixSet(m1, 1, 1, 5.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 1, 0, 3.0);
	MatrixSet(m2, 1, 1, 4.0);
	cr_assert_eq(MatrixMinkowskiDistance(m1, m2, 1), 5.0);
	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixMinkowskiDistance, P2)
{
	Matrix *m1 = MatrixNew(2, 2);
	Matrix *m2 = MatrixNew(2, 2);
	MatrixSet(m1, 0, 0, 2.0);
	MatrixSet(m1, 0, 1, 3.0);
	MatrixSet(m1, 1, 0, 4.0);
	MatrixSet(m1, 1, 1, 5.0);
	MatrixSet(m2, 0, 0, 1.0);
	MatrixSet(m2, 0, 1, 2.0);
	MatrixSet(m2, 1, 0, 3.0);
	MatrixSet(m2, 1, 1, 4.0);

	double result = MatrixMinkowskiDistance(m1, m2, 2);
	double expected = 1.73205080757;

	cr_assert_float_eq(result, expected, 0.00001);

	MatrixFree(m1);
	MatrixFree(m2);
}

Test(MatrixFree, ValidMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	MatrixFree(m);
	cr_assert_null(m->data, "Matrix data should be freed");
	cr_assert_null(m, "Matrix pointer should be freed");
}

Test(MatrixFree, NullMatrix)
{
	Matrix *m = NULL;
	MatrixFree(m);
	cr_assert_null(m, "Matrix pointer should be NULL");
}

Test(MatrixFree, InvalidMatrix)
{
	Matrix *m = MatrixNew(2, 2);
	m->data = NULL;
	MatrixFree(m);
	cr_assert_null(m, "Matrix pointer should be NULL");
}