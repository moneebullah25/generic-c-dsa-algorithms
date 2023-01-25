#include "c_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	Matrix* matrix = calloc(1, sizeof(Matrix));
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

Matrix* MatrixRandom(unsigned int num_rows, unsigned int num_cols, double min, double max)
{
	Matrix* matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = min + ((float)rand() / (float)(0x7fff)) * (max - min);
		}
	}
	return matrix;
}

Matrix* MatrixSquare(unsigned int size)
{
	Matrix* matrix = MatrixNew(size, size);
	return matrix;
}

Matrix* MatrixSquareRandom(unsigned int size, double min, double max)
{
	Matrix* matrix = MatrixRandom(size, size, min, max);
	return matrix;
}

Matrix* MatrixZero(unsigned int num_rows, unsigned int num_cols)
{
	Matrix* matrix = MatrixNew(num_rows, num_cols);
	return matrix;
}

Matrix* MatrixOne(unsigned int num_rows, unsigned int num_cols)
{
	Matrix* matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = 1.;
		}
	}
	return matrix;
}

Matrix* MatrixN(unsigned int num_rows, unsigned int num_cols, double value)
{
	Matrix* matrix = MatrixNew(num_rows, num_cols);
	for (unsigned int r = 0; r < num_rows; r++)
	{
		for (unsigned int c = 0; c < num_cols; c++)
		{
			matrix->data[r][c] = value;
		}
	}
	return matrix;
}

Matrix* MatrixIdentity(unsigned int size)
{
	Matrix* matrix = MatrixNew(size, size);
	for (unsigned int i = 0; i < size; i++)
		matrix->data[i][i] = 1.;
	return matrix;
}

Matrix* MatrixFrom(unsigned int num_rows, unsigned int num_cols, unsigned int n_values, double *values)
{
	Matrix* matrix = MatrixNew(num_rows, num_cols);
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

Matrix* MatrixFromFile(const char* file)
{
	FILE *f = fopen(file, "r");
	if (f == NULL) {
		fprintf(stderr, "Couldn't open file '%s'", file);
		return NULL;
	}
	unsigned int num_rows = 0, num_cols = 0;
	fscanf(f, "%d", &num_rows);
	fscanf(f, "%d", &num_cols);
	Matrix* matrix = MatrixNew(num_rows, num_cols);
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

Matrix* MatrixCopy(Matrix* m)
{
	Matrix* matrix = MatrixNew(m->num_rows, m->num_cols);
	for (unsigned int r = 0; r < matrix->num_rows; r++)
	{
		for (unsigned int c = 0; c < matrix->num_cols; c++)
		{
			matrix->data[r][c] = m->data[r][c];
		}
	}
	return matrix;
}


void PrintMatrix(Matrix* m, const char* data_format)
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