#pragma warning(disable:4996)

#include <stdio.h>
#include "c_matrix.h"


int main()
{
	Matrix* a = MatrixIdentity(4);
	PrintMatrix(a, "%lf\t\t");
	Matrix* i = MatrixZero(1, 4);
	PrintMatrix(i, "%lf\t\t");
	Matrix* r = MatrixRandom(4, 5, 0, 1);
	PrintMatrix(r, "%lf\t\t");
	Matrix* s = MatrixSquare(1);
	PrintMatrix(s, "%lf\t\t");
	Matrix* sr = MatrixSquareRandom(5, -1., 10.);
	PrintMatrix(sr, "%lf\t\t");
	Matrix* o = MatrixOne(9, 9);
	PrintMatrix(o, "%lf\t\t");
	Matrix* n = MatrixN(3, 12, 0.891231);
	PrintMatrix(n, "%lf\t\t");
}