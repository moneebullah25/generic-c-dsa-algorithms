#include <criterion/criterion.h>
#include "../includes/c_queue.h"

Test(queue_test, test_queue_int) {
    QueueInt *q = malloc(sizeof(QueueInt));
    QueueNew(q, DataCompare, FreeData);

    QueuePush(q, 1);
    QueuePush(q, 2);
    QueuePush(q, 3);
    QueuePush(q, 4);

    QueueIter *iter = QueueIterator(q);
    int sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 10, "Expected sum of elements to be 10, got %d", sum);

    QueueClear(q);

    QueuePush(q, 1);
    QueuePush(q, 2);
    QueuePush(q, 3);
    QueuePush(q, 4);
    QueuePush(q, 5);

    iter = QueueIterator(q);
    sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 15, "Expected sum of elements to be 15, got %d", sum);

    int *five = QueueTop(q);
    *five = 6;

    iter = QueueIterator(q);
    sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(int *)iter->data;
    }
    cr_assert_eq(sum, 20, "Expected sum of elements to be 20, got %d", sum);

    QueueDelete(q);
}

Test(queue_test, test_queue_double) {
    QueueDouble *q = malloc(sizeof(QueueDouble));
    QueueNew(q, DataCompare, FreeData);

    QueuePush(q, 1.0);
    QueuePush(q, 2.0);
    QueuePush(q, 3.0);
    QueuePush(q, 4.0);

    QueueIter *iter = QueueIterator(q);
    double sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 10.0, 0.0001, "Expected sum of elements to be 10.0, got %lf", sum);

    QueueClear(q);

    QueuePush(q, 1.25);
    QueuePush(q, 2.25);
    QueuePush(q, 3.25);
    QueuePush(q, 4.25);
    QueuePush(q, 5.25);

    iter = QueueIterator(q);
    sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 16.5, 0.0001, "Expected sum of elements to be 16.5, got %lf", sum);

    double *five = QueueTop(q);
    *five = 6.25;
    
	iter = QueueIterator(q);
    sum = 0;
    while (QueueNext(q, iter)) {
        sum += *(double *)iter->data;
    }
    cr_assert_float_eq(sum, 22.75, 0.0001, "Expected sum of elements to be 22.75, got %lf", sum);

    QueueDelete(q);
    
}

Test(queue_test, test_queue_string) {
    QueueString *q = malloc(sizeof(QueueString));
    QueueNew(q, StringCompare, FreeString);
    QueuePush(q, "111");
    QueuePush(q, "211");
    QueuePush(q, "311");
    QueuePush(q, "411");

    QueueIter *iter = QueueIterator(q);
    int len = 0;
    while (QueueNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 12, "Expected total length of strings to be 12, got %d", len);

    QueueClear(q);

    QueuePush(q, "111");
    QueuePush(q, "211");
    QueuePush(q, "311");
    QueuePush(q, "411");
    QueuePush(q, "511");

    iter = QueueIterator(q);
    len = 0;
    while (QueueNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 15, "Expected total length of strings to be 15, got %d", len);

    char **five = QueueTop(q);
    *five = "611";

    iter = QueueIterator(q);
    len = 0;
    while (QueueNext(q, iter)) {
        len += strlen(*(char **)iter->data);
    }
    cr_assert_eq(len, 15, "Expected total length of strings to be 15, got %d", len);

    QueueDelete(q);
}
