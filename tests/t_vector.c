#include <criterion/criterion.h>
#include "../includes/c_vector.h"
#include <stdlib.h>
#include <stdio.h>

Test(Vector_Test, test_int_vector) {
    VectorInt *v = malloc(sizeof(VectorInt));
<<<<<<< HEAD
    VectorNew(v, memcmp, free);
=======
    VectorNew(v, DataCompare, FreeData);
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a

    VectorPush(v, 1);
    VectorPush(v, 2);
    VectorPush(v, 3);
    VectorPush(v, 4);

    VectorIter *iter = VectorIterator(v);
    int i = 1;
    while (VectorNext(v, iter)) {
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
    while (VectorNext(v, iter)) {
        cr_assert_eq(*(int *)iter->data, i, "Expected %d but got %d", i, *(int *)iter->data);
        i++;
    }

    int *out;
    for (unsigned int i = 0; i < VectorSize(v); i++) {
        out = VectorAt(v, i);
        cr_assert_eq(*out, i+1, "Expected %d but got %d", i+1, *out);
    }

    int *five = VectorGet(v, 5);
    *five = 6;

    iter = VectorIterator(v);
    i = 1;
    while (VectorNext(v, iter)) {
        if (i == 6) {
            cr_assert_eq(*(int *)iter->data, 6, "Expected 6 but got %d", *(int *)iter->data);
        } else {
            cr_assert_eq(*(int *)iter->data, i, "Expected %d but got %d", i, *(int *)iter->data);
        }
        i++;
    }

    VectorDelete(v);
}

Test(Vector_Test, test_double_vector) {
    VectorDouble *v = malloc(sizeof(VectorDouble));
<<<<<<< HEAD
    VectorNew(v, memcmp, free);
=======
    VectorNew(v, DataCompare, FreeData);
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a

    VectorPush(v, 1.0);
    VectorPush(v, 2.0);
    VectorPush(v, 3.0);
    VectorPush(v, 4.0);

    VectorIter *iter = VectorIterator(v);
    double i = 1.0;
    while (VectorNext(v, iter)) {
        cr_assert_float_eq(*(double *)iter->data, i, 1e-9, "Expected %lf but got %lf", i, *(double *)iter->data);
        i++;
    }

    VectorClear(v);

    VectorPush(v, 1.25);
    VectorPush(v, 2.25);
    VectorPush(v, 3.25);
    VectorPush(v, 4.25);
    VectorPush(v, 5.25);

    iter = VectorIterator(v);
    double j = 1.25;
    while (VectorNext(v, iter)) {
        cr_assert_float_eq(*(double *)iter->data, j, 1e-9, "Expected %lf but got %lf", j, *(double *)iter->data);
        j += 1;
    }

    double *out;
    for (unsigned int i = 0; i < VectorSize(v); i++) {
        out = VectorAt(v, i);
        cr_assert_float_eq(*out, i+1.25, 1e-9, "Expected %lf but got %lf", i+1.25, *out);
    }

    double *five = VectorGet(v, 5);
    *five = 6.25;

    iter = VectorIterator(v);
    j = 1.25;
    while (VectorNext(v, iter)) {
        if (j == 6.25) {
            cr_assert_float_eq(*(double *)iter->data, 6.25, 1e-9, "Expected 6.25 but got %lf", *(double *)iter->data);
        } else {
            cr_assert_float_eq(*(double *)iter->data, j, 1e-9, "Expected %lf but got %lf", j, *(double *)iter->data);
        }
        j += 1;
    }

    VectorDelete(v);

}

Test(Vector_Test, test_string_vector) {
    VectorString *v = malloc(sizeof(VectorString));
<<<<<<< HEAD
    VectorNew(v, strncmp, free);
=======
    VectorNew(v, StringCompare, FreeString);
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a
    VectorPush(v, "111");
    VectorPush(v, "211");
    VectorPush(v, "311");
    VectorPush(v, "411");

    VectorIter *iter = VectorIterator(v);
    char *expected[] = {"111", "211", "311", "411"};
    int i = 0;
    while (VectorNext(v, iter)) {
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
    while (VectorNext(v, iter)) {
        cr_assert_str_eq(*(char **)iter->data, expected_after_clear[i], "Expected %s but got %s", expected_after_clear[i], *(char **)iter->data);
        i++;
    }

    char *out;
    for (unsigned int i = 0; i < VectorSize(v); i++) {
        out = *(char**)VectorAt(v, i);
        cr_assert_str_eq(out, expected_after_clear[i], "Expected %s but got %s", expected_after_clear[i], out);
    }

    char *five = VectorGet(v, "511");
    five = "611";

    iter = VectorIterator(v);
    char *expected_after_modification[] = {"111", "211", "311", "411", "611"};
    i = 0;
    while (VectorNext(v, iter)) {
        cr_assert_str_eq(*(char **)iter->data, expected_after_modification[i], "Expected %s but got %s", expected_after_modification[i], *(char **)iter->data);
        i++;
    }

    VectorDelete(v);
}
