#include "../includes/c_matrix.h"
#include "../includes/c_helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

Matrix* MatrixEmpty(unsigned int num_rows, unsigned int num_cols)
{
	if (num_rows == 0)
	{
		fprintf(stderr, "Invalid 'num_rows=%u' passed\n", num_rows);
		return NULL;
	}

	if (num_cols == 0)
	{
		fprintf(stderr, "Invalid 'num_cols=%u' passed\n", num_cols);
		return NULL;
	}

	Matrix *matrix = malloc(sizeof(Matrix));
	matrix->num_rows = num_rows;
	matrix->num_cols = num_cols;
	matrix->is_square = (num_rows == num_cols) ? true : false;
	matrix->data = malloc(matrix->num_rows* sizeof(*matrix->data));
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		matrix->data[r] = malloc(matrix->num_cols* sizeof(**matrix->data));
	}

	return matrix;
}

Matrix* MatrixEmptyLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixEmpty(m->num_rows, m->num_cols);
	return matrix;
}

Matrix* MatrixNew(unsigned int num_rows, unsigned int num_cols)
{
	if (num_rows == 0)
	{
		fprintf(stderr, "Invalid 'num_rows=%u' passed\n", num_rows);
		return NULL;
	}

	if (num_cols == 0)
	{
		fprintf(stderr, "Invalid 'num_cols=%u' passed\n", num_cols);
		return NULL;
	}

	Matrix *matrix = calloc(1, sizeof(Matrix));
	matrix->num_rows = num_rows;
	matrix->num_cols = num_cols;
	matrix->is_square = (num_rows == num_cols) ? true : false;
	matrix->data = calloc(matrix->num_rows, sizeof(*matrix->data));
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		matrix->data[r] = calloc(matrix->num_cols, sizeof(**matrix->data));
	}

	return matrix;
}

Matrix* MatrixNewLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixNew(m->num_rows, m->num_cols);
	return matrix;
}

Matrix* MatrixRandom(unsigned int num_rows, unsigned int num_cols, double min, double max)
{
	Matrix *matrix = MatrixEmpty(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = min + ((float)rand() / (float)(0x7fff)) *(max - min);
		}
	}

	return matrix;
}

Matrix* MatrixRandomLike(const Matrix *m, double min, double max)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixRandom(m->num_rows, m->num_cols, min, max);
	return matrix;
}

Matrix* MatrixSquare(unsigned int size)
{
	Matrix *matrix = MatrixNew(size, size);
	return matrix;
}

Matrix* MatrixSquareLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NULL;
	}

	Matrix *matrix = MatrixSquare(m->num_rows);
	return matrix;
}

Matrix* MatrixSquareRandom(unsigned int size, double min, double max)
{
	Matrix *matrix = MatrixRandom(size, size, min, max);
	return matrix;
}

Matrix* MatrixSquareRandomLike(const Matrix *m, double min, double max)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NULL;
	}

	Matrix *matrix = MatrixSquareRandom(m->num_rows, min, max);
	return matrix;
}

Matrix* MatrixZero(unsigned int num_rows, unsigned int num_cols)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	return matrix;
}

Matrix* MatrixZeroLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixZero(m->num_rows, m->num_cols);
	return matrix;
}

Matrix* MatrixOne(unsigned int num_rows, unsigned int num_cols)
{
	Matrix *matrix = MatrixEmpty(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = 1.;
		}
	}

	return matrix;
}

Matrix* MatrixOneLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixOne(m->num_rows, m->num_cols);
	return matrix;
}

Matrix* MatrixN(unsigned int num_rows, unsigned int num_cols, double value)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = value;
		}
	}

	return matrix;
}

Matrix* MatrixNLike(const Matrix *m, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	Matrix *matrix = MatrixN(m->num_rows, m->num_cols, value);
	return matrix;
}

Matrix* MatrixIdentity(unsigned int size)
{
	Matrix *matrix = MatrixNew(size, size);
	for (unsigned int i = 0; i < size; i++)
		matrix->data[i][i] = 1.;
	return matrix;
}

Matrix* MatrixIdentityLike(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NULL;
	}

	Matrix *matrix = MatrixIdentity(m->num_rows);
	return matrix;
}

Matrix* MatrixEye(unsigned int size, int k)
{
	if (k >= (int)size)
	{
		fprintf(stderr, "Invalid 'k=%u' passed >= %u\n", k, size);
		return NULL;
	}

	Matrix *m = MatrixNew(size, size);
	for (unsigned int i = 0; i < size; i++)
	{
		if (k >= 0 && i + k < size)
		{
			m->data[i][i + k] = 1.0;
		}
		else if (k < 0 && i - k < size)
		{
			m->data[i - k][i] = 1.0;
		}
		else if (k == 0)
		{
			m->data[i][i] = 1.0;
		}
	}

	return m;
}

Matrix* MatrixEyeLike(const Matrix *m, int k)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NULL;
	}

	Matrix *matrix = MatrixEye(m->num_rows, k);
	return matrix;
}

Matrix* MatrixARange(double start, double stop, double step)
{
	if (start >= stop)
	{
		fprintf(stderr, "Invalid 'start=%f' passed >= %f\n", start, stop);
		return NULL;
	}

	if (step == 0)
	{
		fprintf(stderr, "Invalid 'step=%f' passed\n", step);
		return NULL;
	}

	if (step < 0.)
	{
		fprintf(stderr, "Invalid 'step=%f' passed<0.", step);
		return NULL;
	}

	int num_elements = (int)((stop - start) / step);
	if ((num_elements <= 0) || ((num_elements *step) + start > stop))
	{
		fprintf(stderr, "Invalid values for 'start=%f', 'stop=%f', 'step=%f'\n", start, stop, step);
		return NULL;
	}

	Matrix *matrix = MatrixEmpty(1, num_elements);

	double value = start;
	for (unsigned int c = 0; c < matrix->num_cols; c++)
	{
		matrix->data[0][c] = value;
		value += step;
	}

	return matrix;
}

Matrix* MatrixLinearSpace(double start, double stop, unsigned int n)
{
	if (start >= stop)
	{
		fprintf(stderr, "Invalid 'start=%f' passed >= %f\n", start, stop);
		return NULL;
	}

	if (n < 2)
	{
		fprintf(stderr, "Invalid 'n=%u' passed\n", n);
		return NULL;
	}

	Matrix *m = MatrixNew(1, n);
	double step = (stop - start) / (n - 1);
	for (unsigned int i = 0; i < n; i++)
	{
		m->data[0][i] = start + ((double)i *step);
	}

	return m;
}

Matrix* MatrixLogSpace(double start, double stop, unsigned int n)
{
	if (start >= stop)
	{
		fprintf(stderr, "Invalid 'start=%f' passed >= %f\n", start, stop);
		return NULL;
	}

	if (n < 2)
	{
		fprintf(stderr, "Invalid 'n=%u' passed, n should be greater than or equal to 2.\n", n);
		return NULL;
	}

	Matrix *matrix = MatrixEmpty(1, n);
	double base = 10.0;
	double exponent_step = (stop - start) / (n - 1);
	for (unsigned int i = 0; i < n; i++)
	{
		double exponent = start + i * exponent_step;
		matrix->data[0][i] = pow(base, exponent);
	}

	return matrix;
}

Matrix* MatrixGeometrySpace(double start, double stop, unsigned int n)
{
	if (start >= stop)
	{
		fprintf(stderr, "Invalid 'start=%f' passed >= %f\n", start, stop);
		return NULL;
	}

	if (n == 0)
	{
		fprintf(stderr, "Invalid value of 'n' passed\n");
		return NULL;
	}

	Matrix *matrix = MatrixEmpty(1, n);
	double ratio = pow((stop / start), 1.0 / (n - 1));
	double current = start;
	for (unsigned int i = 0; i < n; i++)
	{
		matrix->data[0][i] = current;
		current *= ratio;
	}

	return matrix;
}

Matrix* MatrixFrom(unsigned int num_rows, unsigned int num_cols, unsigned int n_values, const double *values)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	unsigned int values_index;
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			values_index = r *num_cols + c;
			matrix->data[r][c] = (values_index < n_values) ? values[values_index] : 0.;
		}
	}

	return matrix;
}

Matrix* MatrixFromFile(const char *file)
{
	FILE *f = fopen(file, "r");
	if (f == NULL)
	{
		fprintf(stderr, "Couldn't open file '%s'\n", file);
		return NULL;
	}

	unsigned int num_rows = 0, num_cols = 0;
	fscanf(f, "%d", &num_rows);
	fscanf(f, "%d", &num_cols);
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			fscanf(f, "%lf\t", &matrix->data[r][c]);
		}
	}

	fclose(f);
	return matrix;
}

Matrix* MatrixCopy(const Matrix *m)
{
	Matrix *matrix = MatrixNew(m->num_rows, m->num_cols);
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			matrix->data[r][c] = m->data[r][c];
		}
	}

	return matrix;
}

/*Matrix Basic */
bool IsMatrixEqualDim(const Matrix *m1, const Matrix *m2)
{
	return (m1->num_rows == m2->num_rows) &&
		(m1->num_cols == m2->num_cols);
}

void PrintMatrix(const Matrix *m, const char *data_format)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	printf("%u %u\n", m->num_rows, m->num_cols);
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		fprintf(stdout, "\n");
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			fprintf(stdout, data_format, m->data[r][c]);
		}

		fprintf(stdout, "\n");
	}

	fprintf(stdout, "\n");
}

bool IsMatrixInvertible(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return false;
	}

	double determinant = MatrixDeterminant(m);
	return (determinant != 0);
}

/*Matrix Accessing and Modifying */
double MatrixGet(const Matrix *m, unsigned row, unsigned col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return false;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return 0.;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return 0.;
	}

	return m->data[row][col];
}

Matrix* MatrixColumnGet(const Matrix *m, unsigned int col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return false;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m->num_rows, 1);
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		matrix->data[r][0] = m->data[r][col];
	}

	return matrix;
}

Matrix* MatrixRowGet(const Matrix *m, unsigned int row)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return false;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return NULL;
	}

	Matrix *matrix = MatrixNew(1, m->num_cols);
	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		matrix->data[0][c] = m->data[row][c];
	}

	return matrix;
}

void MatrixSet(Matrix *m, unsigned int row, unsigned int col, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return;
	}

	m->data[row][col] = value;
}

void MatrixAllSet(Matrix *m, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			m->data[r][c] = value;
		}
	}
}

void MatrixDiagonalSet(Matrix *m, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return;
	}

	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		m->data[i][i] = value;
	}
}

void MatrixRowMultiplyValue(Matrix *m, unsigned int row, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return;
	}

	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		m->data[row][c] *= value;
	}
}

void MatrixRowAddValue(Matrix *m, unsigned int row, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return;
	}

	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		m->data[row][c] += value;
	}
}

void MatrixColumnMultiplyValue(Matrix *m, unsigned int col, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		m->data[r][col] *= value;
	}
}

void MatrixColumnAddValue(Matrix *m, unsigned int col, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		m->data[r][col] += value;
	}
}

void MatrixRowMultiplyRow(Matrix *m, unsigned int where, unsigned int row, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (where >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'where=%u' passed >= %u\n", where, m->num_rows);
		return;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return;
	}

	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		m->data[where][c] *= value *m->data[row][c];
	}
}

void MatrixRowAddRow(Matrix *m, unsigned int where, unsigned int row, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (where >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'where=%u' passed >= %u\n", where, m->num_rows);
		return;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return;
	}

	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		m->data[where][c] += value *m->data[row][c];
	}
}

void MatrixColumnMultiplyColumn(Matrix *m, unsigned int where, unsigned int col, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (where >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'where=%u' passed >= %u\n", where, m->num_cols);
		return;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		m->data[r][where] *= value *m->data[r][col];
	}
}

void MatrixColumnAddValueColumn(Matrix *m, unsigned int where, unsigned int col, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (where >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'where=%u' passed >= %u\n", where, m->num_cols);
		return;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		m->data[r][where] += value *m->data[r][col];
	}
}

void MatrixWholeMultiply(Matrix *m, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			m->data[r][c] *= value;
		}
	}
}

void MatrixWholeAdd(Matrix *m, double value)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			m->data[r][c] += value;
		}
	}
}

Matrix* MatrixRowRemove(const Matrix *m, unsigned int row)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	if (row >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed >= %u\n", row, m->num_rows);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m->num_rows - 1, m->num_cols);
	for (unsigned int i = 0, k = 0; i < m->num_rows; i++)
	{
		if (row != i)
		{
			for (unsigned int j = 0; j < m->num_cols; j++)
			{
				matrix->data[k][j] = m->data[i][j];
			}

			k++;
		}
	}

	return matrix;
}

Matrix* MatrixColumnRemove(const Matrix *m, unsigned int col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m->num_rows, m->num_cols - 1);
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		for (unsigned int j = 0, k = 0; j < m->num_cols; j++)
		{
			if (col != j)
			{
				matrix->data[i][k++] = m->data[i][j];
			}
		}
	}

	return matrix;
}

void MatrixRowSwap(Matrix *m, unsigned int row1, unsigned int row2)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (row1 >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row1=%u' passed >= %u\n", row1, m->num_rows);
		return;
	}

	if (row2 >= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row2=%u' passed >= %u\n", row2, m->num_rows);
		return;
	}

	if (row1 == row2)
		return;
	double *temp = m->data[row1];
	m->data[row1] = m->data[row2];
	m->data[row2] = temp;
}

void MatrixColumnSwap(Matrix *m, unsigned int col1, unsigned int col2)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	if (col1 >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col1=%u' passed >= %u\n", col1, m->num_cols);
		return;
	}

	if (col2 >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col2=%u' passed >= %u\n", col2, m->num_cols);
		return;
	}

	if (col1 == col2)
		return;
	double temp;
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		temp = m->data[r][col1];
		m->data[r][col1] = m->data[r][col2];
		m->data[r][col2] = temp;
	}
}

Matrix* MatrixBroadcastRows(const Matrix *m, unsigned int row)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	if (m->num_rows != 1)
	{
		fprintf(stderr, "Can't broadcast 'm->num_rows != 1'%u\n", m->num_rows);
		return NULL;
	}

	if (row <= m->num_rows)
	{
		fprintf(stderr, "Invalid 'row=%u' passed <= %u\n", row, m->num_rows);
		return NULL;
	}

	Matrix *matrix = MatrixNew(row, m->num_cols);
	for (unsigned int c = 0; c < matrix->num_cols; c++)
		matrix->data[0][c] = m->data[0][c];

	for (unsigned int r = 1; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			matrix->data[r][c] = m->data[0][c];
		}
	}

	return matrix;
}

Matrix* MatrixBroadcastColumns(const Matrix *m, unsigned int col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	if (m->num_cols != 1)
	{
		fprintf(stderr, "Can't broadcast 'm->num_cols != 1'%u\n", m->num_rows);
		return NULL;
	}

	if (col <= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed <= %u\n", col, m->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m->num_rows, col);
	for (unsigned int r = 0; r < matrix->num_rows; r++)
		matrix->data[r][0] = m->data[r][0];

	for (unsigned int c = 1; c < matrix->num_cols; c++)
	{
		for (unsigned int r = 0; r < matrix->num_rows; r++)
		{
			matrix->data[r][c] = m->data[r][0];
		}
	}

	return matrix;
}

Matrix* MatrixBroadcastRowsAndColumns(const Matrix *m, unsigned int row, unsigned int col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	if (m->num_rows != 1)
	{
		fprintf(stderr, "Can't broadcast 'm->num_rows != 1'%u\n", m->num_rows);
		return NULL;
	}

	if (m->num_cols != 1)
	{
		fprintf(stderr, "Can't broadcast 'm->num_cols != 1'%u\n", m->num_rows);
		return NULL;
	}

	Matrix *matrix = MatrixBroadcastRows(m, row);
	matrix = MatrixBroadcastColumns(matrix, col);
	return matrix;
}

Matrix* MatrixRowStack(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (m1->num_cols != m2->num_cols)
	{
		fprintf(stderr, "Can't stack rows m1->num_cols!=m2->num_cols %u!=%u\n", m1->num_cols, m2->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixEmpty(m1->num_rows + m2->num_rows, m1->num_cols);
	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			matrix->data[i][j] = m1->data[i][j];
		}
	}

	for (unsigned int i = 0; i < m2->num_rows; i++)
	{
		for (unsigned int j = 0; j < m2->num_cols; j++)
		{
			matrix->data[m1->num_rows + i][j] = m2->data[i][j];
		}
	}

	return matrix;
}

Matrix* MatrixColumnStack(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (m1->num_rows != m2->num_rows)
	{
		fprintf(stderr, "Can't stack columns m1->num_cols != m2->num_cols %u!=%u\n", m1->num_cols, m2->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixEmpty(m1->num_rows, m1->num_cols + m2->num_cols);
	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			matrix->data[i][j] = m1->data[i][j];
		}
	}

	for (unsigned int i = 0; i < m2->num_rows; i++)
	{
		for (unsigned int j = 0; j < m2->num_cols; j++)
		{
			matrix->data[i][m1->num_cols + j] = m2->data[i][j];
		}
	}

	return matrix;
}

/*Matrix Operatons */
Matrix* MatrixAdd(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (!IsMatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' &'m2(%u, %u)' are not equivalent\n",
			m1->num_rows, m1->num_cols, m2->num_rows, m2->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m1->num_rows, m1->num_cols);
	for (unsigned int r = 0; r < m1->num_rows; r++)
	{
		for (unsigned int c = 0; c < m1->num_cols; c++)
		{
			matrix->data[r][c] = m1->data[r][c] + m2->data[r][c];
		}
	}

	return matrix;
}

Matrix* MatrixSubtract(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (!IsMatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' &'m2(%u, %u)' are not equivalent\n",
			m1->num_rows, m1->num_cols, m2->num_rows, m2->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m1->num_rows, m1->num_cols);
	for (unsigned int r = 0; r < m1->num_rows; r++)
	{
		for (unsigned int c = 0; c < m1->num_cols; c++)
		{
			matrix->data[r][c] = m1->data[r][c] - m2->data[r][c];
		}
	}

	return matrix;
}

Matrix* MatrixMultiply(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (m1->num_cols != m2->num_rows)
	{
		fprintf(stderr, "Matrix 'm1->cols=%u' &'m2->rows=%u' are not equal; can't mulitply\n",
			m1->num_cols, m2->num_rows);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m1->num_rows, m2->num_cols);
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			for (unsigned int i = 0; i < m1->num_cols; i++)
			{
				matrix->data[r][c] += m1->data[r][i] * m2->data[i][c];
			}
		}
	}

	return matrix;
}

Matrix* MatrixElementWiseMultiply(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	if (!IsMatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' &'m2(%u, %u)' are not equivalent\n",
			m1->num_rows, m1->num_cols, m2->num_rows, m2->num_cols);
		return NULL;
	}

	Matrix *matrix = MatrixNew(m1->num_rows, m1->num_cols);
	for (unsigned int r = 0; r < m1->num_rows; r++)
	{
		for (unsigned int c = 0; c < m1->num_cols; c++)
		{
			matrix->data[r][c] = m1->data[r][c] + m2->data[r][c];
		}
	}

	return matrix;
}

Matrix* MatrixAddWithBroadcast(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	Matrix *matrix1 = MatrixCopy(m1);
	Matrix *matrix2 = MatrixCopy(m2);
	if (!IsMatrixEqualDim(matrix1, matrix2))
	{
		unsigned int max_row = (matrix1->num_rows < matrix2->num_rows) ? matrix2->num_rows : matrix1->num_rows;
		unsigned int max_col = (matrix1->num_cols < matrix2->num_cols) ? matrix2->num_cols : matrix1->num_cols;
		matrix1 = (matrix1->num_rows < max_row) ? MatrixBroadcastRows(matrix1, max_row) : matrix1;
		matrix1 = (matrix1->num_cols < max_col) ? MatrixBroadcastColumns(matrix1, max_col) : matrix1;
		matrix2 = (matrix2->num_rows < max_row) ? MatrixBroadcastRows(matrix2, max_row) : matrix2;
		matrix2 = (matrix2->num_cols < max_col) ? MatrixBroadcastColumns(matrix2, max_col) : matrix2;
	}

	Matrix *result = MatrixAdd(matrix1, matrix2);
	MatrixFree(matrix1);
	MatrixFree(matrix2);
	return result;
}

Matrix* MatrixSubtractWithBroadcast(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	Matrix *matrix1 = MatrixCopy(m1);
	Matrix *matrix2 = MatrixCopy(m2);
	if (!IsMatrixEqualDim(matrix1, matrix2))
	{
		unsigned int max_row = (matrix1->num_rows < matrix2->num_rows) ? matrix2->num_rows : matrix1->num_rows;
		unsigned int max_col = (matrix1->num_cols < matrix2->num_cols) ? matrix2->num_cols : matrix1->num_cols;
		matrix1 = (matrix1->num_rows < max_row) ? MatrixBroadcastRows(matrix1, max_row) : matrix1;
		matrix1 = (matrix1->num_cols < max_col) ? MatrixBroadcastColumns(matrix1, max_col) : matrix1;
		matrix2 = (matrix2->num_rows < max_row) ? MatrixBroadcastRows(matrix2, max_row) : matrix2;
		matrix2 = (matrix2->num_cols < max_col) ? MatrixBroadcastColumns(matrix2, max_col) : matrix2;
	}

	Matrix *result = MatrixSubtract(matrix1, matrix2);
	MatrixFree(matrix1);
	MatrixFree(matrix2);
	return result;
}

Matrix* MatrixMultiplyWithBroadcast(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	Matrix *matrix1 = MatrixCopy(m1);
	Matrix *matrix2 = MatrixCopy(m2);
	if (matrix1->num_cols != matrix2->num_rows)
	{
		unsigned int max_diff = (matrix1->num_cols < matrix2->num_rows) ? matrix2->num_rows : matrix1->num_cols;
		matrix1 = (matrix1->num_cols < max_diff) ? MatrixBroadcastColumns(matrix1, max_diff) : matrix1;
		matrix2 = (matrix2->num_rows < max_diff) ? MatrixBroadcastRows(matrix2, max_diff) : matrix2;
	}

	Matrix *result = MatrixMultiply(matrix1, matrix2);
	MatrixFree(matrix1);
	MatrixFree(matrix2);
	return result;
}

Matrix* MatrixElementWiseMultiplyWithBroadcast(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NULL;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NULL;
	}

	Matrix *matrix1 = MatrixCopy(m1);
	Matrix *matrix2 = MatrixCopy(m2);
	if (!IsMatrixEqualDim(matrix1, matrix2))
	{
		unsigned int max_row = (matrix1->num_rows < matrix2->num_rows) ? matrix2->num_rows : matrix1->num_rows;
		unsigned int max_col = (matrix1->num_cols < matrix2->num_cols) ? matrix2->num_cols : matrix1->num_cols;
		matrix1 = (matrix1->num_rows < max_row) ? MatrixBroadcastRows(matrix1, max_row) : matrix1;
		matrix1 = (matrix1->num_cols < max_col) ? MatrixBroadcastColumns(matrix1, max_col) : matrix1;
		matrix2 = (matrix2->num_rows < max_row) ? MatrixBroadcastRows(matrix2, max_row) : matrix2;
		matrix2 = (matrix2->num_cols < max_col) ? MatrixBroadcastColumns(matrix2, max_col) : matrix2;
	}

	Matrix *result = MatrixElementWiseMultiply(matrix1, matrix2);
	MatrixFree(matrix1);
	MatrixFree(matrix2);
	return result;
}

void MatrixTranspose(Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			double temp = m->data[r][c];
			m->data[r][c] = m->data[c][r];
			m->data[c][r] = temp;
		}
	}
}

double MatrixTrace(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NAN;
	}

	if (!m->is_square)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NAN;
	}

	double trace = 0;
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		trace += m->data[i][i];
	}

	return trace;
}

double MatrixDeterminant(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NAN;
	}

	if (m->num_rows != m->num_cols)
	{
		fprintf(stderr, "'m' is not a square matrix\n");
		return NAN;
	}

	if (m->num_rows == 1)
	{
		return m->data[0][0];
	}

	if (m->num_rows == 2)
	{
		return (m->data[0][0] * m->data[1][1]) - (m->data[0][1] * m->data[1][0]);
	}

	double det = 0.0;
	for (unsigned int i = 0; i < m->num_cols; i++)
	{
		Matrix *subMatrix = MatrixNew(m->num_rows - 1, m->num_cols - 1);
		for (unsigned int row = 1; row < m->num_rows; row++)
		{
			int subRow = 0;
			for (unsigned int col = 0; col < m->num_cols; col++)
			{
				if (col == i)
				{
					continue;
				}

				subMatrix->data[subRow][col - (col > i)] = m->data[row][col];
			}

			subRow++;
		}

		det += pow(-1, i) *m->data[0][i] * MatrixDeterminant(subMatrix);
		MatrixFree(subMatrix);
	}

	return det;
}

void MatrixRowEchelon(Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	unsigned int lead = 0;
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		if (m->num_cols <= lead)
			return;

		unsigned int i = r;
		while (MatrixGet(m, i, lead) == 0)
		{
			i++;
			if (i == m->num_rows)
			{
				i = r;
				lead++;
				if (m->num_cols == lead)
					return;
			}
		}

		MatrixRowSwap(m, i, r);

		if (MatrixGet(m, r, lead) != 0)
		{
			double val = MatrixGet(m, r, lead);
			MatrixRowMultiplyValue(m, r, 1.0 / val);
		}

		for (unsigned int i = 0; i < m->num_rows; i++)
		{
			if (i != r)
			{
				double c = MatrixGet(m, i, lead);
				for (unsigned int j = 0; j < m->num_cols; j++)
				{
					m->data[i][j] -= c *m->data[r][j];
				}
			}
		}

		lead++;
	}
}

void MatrixReducedRowEchelon(Matrix *m)
{
	if (m == NULL && IsMatrixInvertible(m) == false)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	unsigned int lead = 0;
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		if (m->num_cols <= lead)
			return;
		unsigned int i = r;
		while (MatrixGet(m, i, lead) == 0)
		{
			i++;
			if (i == m->num_rows)
			{
				i = r;
				lead++;
				if (m->num_cols == lead)
					return;
			}
		}

		MatrixRowSwap(m, i, r);
		double value = MatrixGet(m, r, lead);
		MatrixRowMultiplyValue(m, r, 1.0 / value);
		for (unsigned int j = 0; j < m->num_rows; j++)
		{
			if (j != r)
			{
				value = MatrixGet(m, j, lead);
				for (unsigned int c = 0; c < m->num_cols; c++)
				{
					m->data[j][c] -= value *m->data[r][c];
				}
			}
		}

		lead++;
	}
}

Matrix* MatrixRowEchelonGet(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	Matrix *matrix = MatrixCopy(m);
	unsigned int lead = 0;
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		if (matrix->num_cols <= lead)
			return matrix;

		unsigned int i = r;
		while (MatrixGet(matrix, i, lead) == 0)
		{
			i++;
			if (i == matrix->num_rows)
			{
				i = r;
				lead++;
				if (matrix->num_cols == lead)
					return matrix;
			}
		}

		MatrixRowSwap(matrix, i, r);

		if (MatrixGet(matrix, r, lead) != 0)
		{
			double val = MatrixGet(matrix, r, lead);
			MatrixRowMultiplyValue(matrix, r, 1.0 / val);
		}

		for (unsigned int i = 0; i < matrix->num_rows; i++)
		{
			if (i != r)
			{
				double c = MatrixGet(matrix, i, lead);
				for (unsigned int j = 0; j < matrix->num_cols; j++)
				{
					matrix->data[i][j] -= c *matrix->data[r][j];
				}
			}
		}

		lead++;
	}

	return matrix;
}

Matrix* MatrixReducedRowEchelonGet(const Matrix *m)
{
	if (m == NULL && IsMatrixInvertible(m) == false)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	Matrix *matrix = MatrixCopy(m);
	unsigned int lead = 0;
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		if (matrix->num_cols <= lead)
			return matrix;
		unsigned int i = r;
		while (MatrixGet(matrix, i, lead) == 0)
		{
			i++;
			if (i == matrix->num_rows)
			{
				i = r;
				lead++;
				if (matrix->num_cols == lead)
					return matrix;
			}
		}

		MatrixRowSwap(matrix, i, r);
		double value = MatrixGet(matrix, r, lead);
		MatrixRowMultiplyValue(matrix, r, 1.0 / value);
		for (unsigned int j = 0; j < matrix->num_rows; j++)
		{
			if (j != r)
			{
				value = MatrixGet(matrix, j, lead);
				for (unsigned int c = 0; c < matrix->num_cols; c++)
				{
					matrix->data[j][c] -= value *matrix->data[r][c];
				}
			}
		}

		lead++;
	}

	return matrix;
}

double MatrixColumnL2Norm(const Matrix *m, unsigned int col)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NAN;
	}

	if (col >= m->num_cols)
	{
		fprintf(stderr, "Invalid 'col=%u' passed >= %u\n", col, m->num_cols);
		return NAN;
	}

	double doublesum = 0.0;
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		doublesum += (m->data[r][col] * m->data[r][col]);
	}

	return sqrt(doublesum);
}

Matrix* MatrixL2Norm(const Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return NULL;
	}

	Matrix *matrix = MatrixNew(1, m->num_cols);
	double square_sum;
	for (unsigned int c = 0; c < m->num_cols; c++)
	{
		square_sum = 0.0;
		for (unsigned int r = 0; r < m->num_rows; r++)
		{
			square_sum += m->data[r][c] * m->data[r][c];
		}

		matrix->data[0][c] = sqrt(square_sum);
	}

	return matrix;
}

double MatrixCosineSimilarity(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NAN;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NAN;
	}

	double dot_product = 0.0;
	double m1_norm = 0.0;
	double m2_norm = 0.0;

	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		dot_product += m1->data[i][0] * m2->data[i][0];
		m1_norm += m1->data[i][0] * m1->data[i][0];
		m2_norm += m2->data[i][0] * m2->data[i][0];
	}

	double denominator = sqrt(m1_norm *m2_norm);

	if (denominator == 0)
	{
		return 0.0;
	}

	return dot_product / denominator;
}

double MatrixTSSSSimilarity(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NAN;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NAN;
	}

	if (!IsMatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' &'m2(%u, %u)' are not equivalent\n",
			m1->num_rows, m1->num_cols, m2->num_rows, m2->num_cols);
		return NAN;
	}

	if (m1->num_rows != 1)
	{
		fprintf(stderr, "Not a row matrix 'm1->num_rows != 1'%u\n", m1->num_rows);
		return NULL;
	}

	if (m2->num_rows != 1)
	{
		fprintf(stderr, "Not a row matrix 'm2->num_rows != 1'%u\n", m2->num_rows);
		return NULL;
	}

	if (m1->num_cols != m2->num_cols)
	{
		fprintf(stderr, "Not a row matrix 'm1->num_cols != m2->num_cols'%u!=%u\n", m1->num_cols, m2->num_cols);
		return -1;
	}

	// Compute the TSSS distance
	double tsss_distance = MatrixEuclideanDistance(m1, m2);

	// Compute the variance of the two time series
	double var_m1 = MatrixColumnL2Norm(m1, 0) / m1->num_cols;
	double var_m2 = MatrixColumnL2Norm(m2, 0) / m2->num_cols;

	// Compute the TS-SS similarity
	double ts_ss_similarity = 1 - tsss_distance / sqrt(m1->num_cols *var_m1 *var_m2);

	return ts_ss_similarity;
}

double MatrixEuclideanDistance(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NAN;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NAN;
	}

	double sum_squares = 0.0;
	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			double diff = m1->data[i][j] - m2->data[i][j];
			sum_squares += diff * diff;
		}
	}

	return sqrt(sum_squares);
}

double MatrixManhattanDistance(const Matrix *m1, const Matrix *m2)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NAN;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NAN;
	}

	double dist = 0.0;
	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			dist += fabs(m1->data[i][j] - m2->data[i][j]);
		}
	}

	return dist;
}

double MatrixMinkowskiDistance(const Matrix *m1, const Matrix *m2, int p)
{
	if (m1 == NULL)
	{
		fprintf(stderr, "Invalid matrix m1 passed\n");
		return NAN;
	}

	if (m2 == NULL)
	{
		fprintf(stderr, "Invalid matrix m2 passed\n");
		return NAN;
	}

	double dist = 0.0;
	for (unsigned int i = 0; i < m1->num_rows; i++)
	{
		for (unsigned int j = 0; j < m1->num_cols; j++)
		{
			dist += pow(fabs(m1->data[i][j] - m2->data[i][j]), p);
		}
	}

	return pow(dist, 1.0 / p);
}

/*Matrix Dispose */
void MatrixFree(Matrix *m)
{
	if (m == NULL)
	{
		fprintf(stderr, "Invalid matrix passed\n");
		return;
	}

	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		free(m->data[i]);
	}

	free(m->data);
	free(m);
}