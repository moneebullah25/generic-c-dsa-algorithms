#include <criterion/criterion.h>
#include "../includes/c_vector.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

Test(vector_test, test_vector_int)
{
    VectorInt *v = malloc(sizeof(VectorInt));
    VectorNew(v, IntDataCompare, FreeData);
    VectorPush(v, 1);
    VectorPush(v, 2);
    VectorPush(v, 3);
    VectorPush(v, 4);

    VectorIter *iter = VectorIterator(v);
    int i = 1;
    while (VectorNext(v, iter))
    {
        cr_assert_eq(*(int *)iter->data, i, "Expected %d but got %d", i, *(int *)iter->data);
        i++;
    }

    VectorClear(v);

    VectorPush(v, 1);
    VectorPush(v, 2);
    VectorPush(v, 3);
    VectorPush(v, 4);
    VectorPush(v, 5);

    iter = VectorIterator(v);
    i = 1;
    while (VectorNext(v, iter))
    {
        cr_assert_eq(*(int *)iter->data, i, "Expected %d but got %d", i, *(int *)iter->data);
        i++;
    }

    int *out;
    for (unsigned int i = 0; i < VectorSize(v); i++)
    {
        out = VectorAt(v, i);
        cr_assert_eq(*out, i + 1, "Expected %d but got %d", i + 1, *out);
    }

    int *five = VectorGet(v, 5);
    *five = 6;

    iter = VectorIterator(v);
    i = 1;
    while (VectorNext(v, iter))
    {
        if (i != 5)
        {
            cr_assert_eq(*(int *)iter->data, i, "Expected %d but got %d", i, *(int *)iter->data);
        }
        else
        {
            cr_assert_eq(*(int *)iter->data, i + 1, "Expected %d but got %d", i + 1, *(int *)iter->data);
        }
        i++;
    }

    VectorDelete(v);
}

Test(vector_test, test_vector_double)
{
    VectorDouble *v = malloc(sizeof(VectorDouble));
    VectorNew(v, DoubleDataCompare, FreeData);
    VectorPush(v, 1.0);
    VectorPush(v, 2.0);
    VectorPush(v, 3.0);
    VectorPush(v, 4.0);

    VectorIter *iter = VectorIterator(v);
    double i = 1.0;
    while (VectorNext(v, iter))
    {
        cr_assert_float_eq(*(double *)iter->data, i, 1e-9, "Expected %lf but got %lf", i, *(double *)iter->data);
        i=i+1;
    }

    VectorClear(v);

    VectorPush(v, 1.25);
    VectorPush(v, 2.25);
    VectorPush(v, 3.25);
    VectorPush(v, 4.25);
    VectorPush(v, 5.25);

    iter = VectorIterator(v);
    double j = 1.25;
    while (VectorNext(v, iter))
    {
        cr_assert_float_eq(*(double *)iter->data, j, 1e-9, "Expected %lf but got %lf", j, *(double *)iter->data);
        j += 1;
    }

    double *out;
    for (unsigned int i = 0; i < VectorSize(v); i++)
    {
        out = VectorAt(v, i);
        cr_assert_float_eq(*out, i + 1.25, 1e-9, "Expected %lf but got %lf", i + 1.25, *out);
    }

    double *five = VectorGet(v, 5.25);
    *five = 6.25;

    iter = VectorIterator(v);
    j = 1.25;
    while (VectorNext(v, iter))
    {
        if (j == 5.25)
        {
            cr_assert_float_eq(*(double *)iter->data, 6.25, 1e-9, "Expected 6.25 but got %lf", *(double *)iter->data);
        }
        else
        {
            cr_assert_float_eq(*(double *)iter->data, j, 1e-9, "Expected %lf but got %lf", j, *(double *)iter->data);
        }
        j += 1;
    }

    VectorDelete(v);
}

Test(vector_test, test_vector_string)
{
    VectorString *v = malloc(sizeof(VectorString));
    VectorNew(v, StringCompare, FreeString);
    VectorPush(v, "111");
    VectorPush(v, "211");
    VectorPush(v, "311");
    VectorPush(v, "411");

    VectorIter *iter = VectorIterator(v);
    char *expected[] = {"111", "211", "311", "411"};
    int i = 0;
    while (VectorNext(v, iter))
    {
        cr_assert_str_eq(*(char **)iter->data, expected[i], "Expected %s but got %s", expected[i], *(char **)iter->data);
        i++;
    }

    VectorClear(v);

    VectorPush(v, "111");
    VectorPush(v, "211");
    VectorPush(v, "311");
    VectorPush(v, "411");
    VectorPush(v, "511");

    iter = VectorIterator(v);
    char *expected_after_clear[] = {"111", "211", "311", "411", "511"};
    i = 0;
    while (VectorNext(v, iter))
    {
        cr_assert_str_eq(*(char **)iter->data, expected_after_clear[i], "Expected %s but got %s", expected_after_clear[i], *(char **)iter->data);
        i++;
    }

    char *out;
    for (unsigned int i = 0; i < VectorSize(v); i++)
    {
        out = *(char **)VectorAt(v, i);
        cr_assert_str_eq(out, expected_after_clear[i], "Expected %s but got %s", expected_after_clear[i], out);
    }

    char **five = VectorGet(v, "511");
    *five = "611";

    iter = VectorIterator(v);
    char *expected_after_modification[] = {"111", "211", "311", "411", "611"};
    i = 0;
    while (VectorNext(v, iter))
    {
        cr_assert_str_eq(*(char **)iter->data, expected_after_modification[i], "Expected %s but got %s", expected_after_modification[i], *(char **)iter->data);
        i++;
    }

    VectorDelete(v);
}
