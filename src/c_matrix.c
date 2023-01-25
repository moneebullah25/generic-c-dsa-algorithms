#include "c_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Matrix *MatrixNew(unsigned int num_rows, unsigned int num_cols)
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

Matrix *MatrixRandom(unsigned int num_rows, unsigned int num_cols, double min, double max)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = min + ((float)rand() / (float)(0x7fff)) * (max - min);
		}
	}
	return matrix;
}

Matrix *MatrixSquare(unsigned int size)
{
	Matrix *matrix = MatrixNew(size, size);
	return matrix;
}

Matrix *MatrixSquareRandom(unsigned int size, double min, double max)
{
	Matrix *matrix = MatrixRandom(size, size, min, max);
	return matrix;
}

Matrix *MatrixZero(unsigned int num_rows, unsigned int num_cols)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	return matrix;
}

Matrix *MatrixOne(unsigned int num_rows, unsigned int num_cols)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = 1.;
		}
	}
	return matrix;
}

Matrix *MatrixN(unsigned int num_rows, unsigned int num_cols, double value)
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

Matrix *MatrixIdentity(unsigned int size)
{
	Matrix *matrix = MatrixNew(size, size);
	for (unsigned int i = 0; i < size; i++)
		matrix->data[i][i] = 1.;
	return matrix;
}

Matrix *MatrixFrom(unsigned int num_rows, unsigned int num_cols, unsigned int n_values, double *values)
{
	Matrix *matrix = MatrixNew(num_rows, num_cols);
	unsigned int values_index;
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			values_index = r * num_cols + c;
			matrix->data[r][c] = (values_index < n_values) ? values[values_index] : 0.;
		}
	}
	return matrix;
}

Matrix *MatrixFromFile(const char *file)
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

Matrix *MatrixCopy(Matrix *m)
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

/* Matrix Basic */
bool MatrixEqualDim(Matrix *m1, Matrix *m2)
{
	return (m1->num_rows == m2->num_rows) &&
		   (m1->num_cols == m2->num_cols);
}

void PrintMatrix(Matrix *m, const char *data_format)
{
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

/* Matrix Accessing and Modifying */
double MatrixGet(Matrix *m, unsigned row, unsigned col)
{
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

Matrix *MatrixColumnGet(Matrix *m, unsigned int col)
{
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

Matrix *MatrixRowGet(Matrix *m, unsigned int row)
{
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
	m->data[row][col] = value;
}

void MatrixAllSet(Matrix *m, double value)
{
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
	if (!m->is_square)
	{
		fprintf(stderr, "Can't set diagonals 'm' is not a square matrix\n");
		return;
	}
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		m->data[i][i] = value;
	}
}

void MatrixRowMultiplyValue(Matrix *m, unsigned int row, double value)
{
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
		m->data[where][c] *= value * m->data[row][c];
	}
}

void MatrixRowAddRow(Matrix *m, unsigned int where, unsigned int row, double value)
{
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
		m->data[where][c] += value * m->data[row][c];
	}
}

void MatrixColumnMultiplyColumn(Matrix *m, unsigned int where, unsigned int col, double value)
{
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
		m->data[r][where] *= value * m->data[r][col];
	}
}

void MatrixColumnAddValueColumn(Matrix *m, unsigned int where, unsigned int col, double value)
{
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
		m->data[r][where] += value * m->data[r][col];
	}
}

void MatrixWholeMultiply(Matrix *m, double value)
{
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
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			m->data[r][c] += value;
		}
	}
}

Matrix *MatrixRowRemove(Matrix *m, unsigned int row)
{
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

Matrix *MatrixColumnRemove(Matrix *m, unsigned int col)
{
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

/* Matrix Operatons */
Matrix *MatrixAdd(Matrix *m1, Matrix *m2)
{
	if (!MatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' & 'm2(%u, %u)' are not equivalent\n",
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

Matrix *MatrixSubtract(Matrix *m1, Matrix *m2)
{
	if (!MatrixEqualDim(m1, m2))
	{
		fprintf(stderr, "Matrix 'm1(%u, %u)' & 'm2(%u, %u)' are not equivalent\n",
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

Matrix *MatrixMultiply(Matrix *m1, Matrix *m2)
{
	if (m1->num_cols != m2->num_rows)
	{
		fprintf(stderr, "Matrix 'm1->cols=%u' & 'm2->rows=%u' are not equal; can't mulitply\n",
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

void MatrixTranspose(Matrix *m)
{
	for (unsigned int r = 0; r < m->num_rows; r++)
	{
		for (unsigned int c = 0; c < m->num_cols; c++)
		{
			m->data[r][c] = m->data[c][r];
		}
	}
}

double MatrixTrace(Matrix *m)
{
	if (!m->is_square)
	{
		fprintf(stderr, "Can't trace 'm' is not a square matrix\n");
		return;
	}
	double trace = 0;
	for (unsigned int i = 0; i < m->num_rows; i++)
	{
		trace += m->data[i][i];
	}
	return trace;
}

double MatrixDeterminant(Matrix* m)
{

}

Matrix* MatrixRowEchelon(Matrix* m)
{

}

Matrix* MatrixReducedRowEchelon(Matrix* m)
{

}