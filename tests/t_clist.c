#include <criterion/criterion.h>
#include "../includes/c_dlist.h"
#include "../includes/c_helper.h"

Test(linkedlist_test, test_linked_list_int) {
    CircularLinkedListInt *dll = malloc(sizeof(CircularLinkedListInt));
    CircularLinkedListNew(dll, DataCompare, FreeData);

    CircularLinkedListInsert(dll, 9);
    CircularLinkedListInsert(dll, 2);
    CircularLinkedListInsert(dll, 3);
    CircularLinkedListInsert(dll, 4);
    CircularLinkedListInsert(dll, 5);
    CircularLinkedListInsert(dll, 9);
    CircularLinkedListInsert(dll, 9);

    int sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(int*)CircularLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 41, "Expected sum of elements to be 42, got %d", sum);

    CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 9);
    CircularLinkedListInsert(dll, 2);
    CircularLinkedListInsert(dll, 3);
    CircularLinkedListInsert(dll, 4);
    CircularLinkedListInsert(dll, 5);
    CircularLinkedListInsert(dll, 9);
    CircularLinkedListInsert(dll, 9);
    CircularLinkedListReplace(dll, 9, 1);
    CircularLinkedListReplaceAll(dll, 9, 1);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(int*)CircularLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 17, "Expected sum of elements to be 17, got %d", sum);

    int index = CircularLinkedListGetIndex(dll, 9);
    cr_assert_eq(index, -1, "Expected index of 9 to be -1, got %d", index);

    CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 9);
    CircularLinkedListInsert(dll, 9);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(int*)CircularLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 18, "Expected sum of elements to be 18, got %d", sum);
	
	CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 1);
    CircularLinkedListInsert(dll, 2);
    CircularLinkedListInsert(dll, 3);
    CircularLinkedListInsert(dll, 4);
    CircularLinkedListInsert(dll, 5);
	
	int values[] = {1, 2, 3, 4, 5};
	int rvalues[] = {5, 4, 3, 2, 1};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(dll);
	CircularLinkedListIter* riter = CircularLinkedListIterator(dll);
	while (CircularLinkedListNext(dll, iter))
	{
		cr_assert_eq(*(int *)iter->data, values[i], "Expected %d but got %d", values[i], *(int *)iter->data);
	}
	
    CircularLinkedListDelete(dll);
}

Test(linkedlist_test, test_linked_list_double) {
    CircularLinkedListDouble *dll = malloc(sizeof(CircularLinkedListDouble));
    CircularLinkedListNew(dll, DataCompare, FreeData);

    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListInsert(dll, 2.25);
    CircularLinkedListInsert(dll, 3.25);
    CircularLinkedListInsert(dll, 4.25);
    CircularLinkedListInsert(dll, 5.25);
    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListInsert(dll, 9.25);
    
	double sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(double*)CircularLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 42.75, 0.0001, "Expected sum of elements to be 44.25, got %lf", sum);

    CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListInsert(dll, 2.25);
    CircularLinkedListInsert(dll, 3.25);
    CircularLinkedListInsert(dll, 4.25);
    CircularLinkedListInsert(dll, 5.25);
    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListReplace(dll, 9.25, 1.15);
    CircularLinkedListReplaceAll(dll, 9.25, 1.15);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(double*)CircularLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 18.45, 0.0001, "Expected sum of elements to be 18.45, got %lf", sum);

    int index = CircularLinkedListGetIndex(dll, 9.25);
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 9.25);
    CircularLinkedListInsert(dll, 9.25);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        sum += *(double*)CircularLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 18.5, 0.0001, "Expected sum of elements to be 18.5, got %lf", sum);
	
	CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, 1.25);
    CircularLinkedListInsert(dll, 2.25);
    CircularLinkedListInsert(dll, 3.25);
    CircularLinkedListInsert(dll, 4.25);
    CircularLinkedListInsert(dll, 5.25);
	
	double values[] = {1.25, 2.25, 3.25, 4.25, 5.25};
	double rvalues[] = {5.25, 4.25, 3.25, 2.25, 1.25};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(dll);
	CircularLinkedListIter* riter = CircularLinkedListIterator(dll);
	while (CircularLinkedListNext(dll, iter))
	{
		cr_assert_float_eq(*(double *)iter->data, values[i], "Expected %lf but got %lf", values[i], *(double *)iter->data);
	}
	
    CircularLinkedListDelete(dll);
}

Test(linkedlist_test, test_linked_list_string) {
    CircularLinkedListString *dll = malloc(sizeof(CircularLinkedListString));
    CircularLinkedListNew(dll, StringCompare, FreeString);

    char* expected_list[] = {"9.25","2.25","3.25","4.25","5.25","9.25","9.25"};

    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListInsert(dll, "2.25");
    CircularLinkedListInsert(dll, "3.25");
    CircularLinkedListInsert(dll, "4.25");
    CircularLinkedListInsert(dll, "5.25");
    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListInsert(dll, "9.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(dll, i), expected_list[i], "Unexpected string at index %d", i);
    }

    CircularLinkedListClear(dll);

    char* expected_list2[] = {"1.25","2.25","3.25","4.25","5.25","1.25","1.25"};
    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListInsert(dll, "2.25");
    CircularLinkedListInsert(dll, "3.25");
    CircularLinkedListInsert(dll, "4.25");
    CircularLinkedListInsert(dll, "5.25");
    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListReplace(dll, "9.25", "1.25");
    CircularLinkedListReplaceAll(dll, "9.25", "1.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(dll, i), expected_list2[i], "Unexpected string at index %d", i);
    }

    int index = CircularLinkedListGetIndex(dll, "9.25");
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, "9.25");
    CircularLinkedListInsert(dll, "9.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(dll, i), "9.25", "Unexpected string at index %d", i);
    }
	
	CircularLinkedListClear(dll);

    CircularLinkedListInsert(dll, "1.25");
    CircularLinkedListInsert(dll, "2.25");
    CircularLinkedListInsert(dll, "3.25");
    CircularLinkedListInsert(dll, "4.25");
    CircularLinkedListInsert(dll, "5.25");
	
	char* values[] = {"1.25", "2.25", "3.25", "4.25", "5.25"};
	char* rvalues[] = {"5.25", "4.25", "3.25", "2.25", "1.25"};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(dll);
	CircularLinkedListIter* riter = CircularLinkedListIterator(dll);
	while (CircularLinkedListNext(dll, iter))
	{
		cr_assert_str_eq(*(char**)iter->data, values[i], "Expected %s but got %s", values[i], *(char**)iter->data);
	}
	
    CircularLinkedListDelete(dll);
}
