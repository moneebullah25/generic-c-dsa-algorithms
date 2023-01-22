#include <criterion/criterion.h>
#include "../includes/c_stack.h"

Test(StackInt, PushPop) {
    StackInt *q = malloc(sizeof(StackInt));
    StackNew(q, DataCompare, FreeData);

    StackPush(q, 1);
    StackPush(q, 2);
    StackPush(q, 3);
    StackPush(q, 4);

    StackIter *iter = StackIterator(q);
    int sum = 0;
    while (StackNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 10, "Expected sum of elements to be 10, got %d", sum);

    StackClear(q);

    StackPush(q, 1);
    StackPush(q, 2);
    StackPush(q, 3);
    StackPush(q, 4);
    StackPush(q, 5);

    iter = StackIterator(q);
    sum = 0;
    while (StackNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 15, "Expected sum of elements to be 15, got %d", sum);

    int *five = StackTop(q);
    *five = 6;

    iter = StackIterator(q);
    sum = 0;
    while (StackNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 20, "Expected sum of elements to be 20, got %d", sum);

    StackDelete(q);
}

Test(StackDouble, PushPop) {
    StackDouble *q = malloc(sizeof(StackDouble));
    StackNew(q, DataCompare, FreeData);

    StackPush(q, 1.0);
    StackPush(q, 2.0);
    StackPush(q, 3.0);
    StackPush(q, 4.0);

    StackIter *iter = StackIterator(q);
    double sum = 0;
    while (StackNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 10.0, 0.0001, "Expected sum of elements to be 10.0, got %lf", sum);

    StackClear(q);

    StackPush(q, 1.25);
    StackPush(q, 2.25);
    StackPush(q, 3.25);
    StackPush(q, 4.25);
    StackPush(q, 5.25);

    iter = StackIterator(q);
    sum = 0;
    while (StackNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 16.5, 0.0001, "Expected sum of elements to be 16.5, got %lf", sum);

    double *five = StackTop(q);
    *five = 6.25;
<<<<<<< HEAD

=======
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a
    iter = StackIterator(q);
    sum = 0;
    while (StackNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 22.75, 0.0001, "Expected sum of elements to be 22.75, got %lf", sum);

    StackDelete(q);
<<<<<<< HEAD
    }
=======
}
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a

Test(StackString, PushPop) {
    StackString *q = malloc(sizeof(StackString));
    StackNew(q, StringCompare, FreeString);
<<<<<<< HEAD

=======
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a
    StackPush(q, "111");
    StackPush(q, "211");
    StackPush(q, "311");
    StackPush(q, "411");

    StackIter *iter = StackIterator(q);
    int len = 0;
    while (StackNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 12, "Expected total length of strings to be 12, got %d", len);

    StackClear(q);

    StackPush(q, "111");
    StackPush(q, "211");
    StackPush(q, "311");
    StackPush(q, "411");
    StackPush(q, "511");

    iter = StackIterator(q);
    len = 0;
    while (StackNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 15, "Expected total length of strings to be 15, got %d", len);

    char **five = StackTop(q);
    *five = "611";

    iter = StackIterator(q);
    len = 0;
    while (StackNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 15, "Expected total length of strings to be 15, got %d", len);

    StackDelete(q);
<<<<<<< HEAD
}

=======
}
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a
