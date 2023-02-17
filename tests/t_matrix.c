#include <criterion/criterion.h>
#include "../includes/c_helper.h"
#include "../includes/c_matrix.h"

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

