#include <criterion/criterion.h>
#include "../includes/c_dlist.h"
#include "../includes/c_helper.h"

Test(linkedlist_test, test_linked_list_int) {
    DoublyLinkedListInt *dll = malloc(sizeof(DoublyLinkedListInt));
    DoublyLinkedListNew(dll, DataCompare, FreeData);

    DoublyLinkedListInsertAtHead(dll, 0);
    DoublyLinkedListInsertAtHead(dll, 1);
    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListInsertAtTail(dll, 2);
    DoublyLinkedListInsertAtTail(dll, 3);
    DoublyLinkedListInsertAtTail(dll, 4);
    DoublyLinkedListInsertAtTail(dll, 5);
    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListInsertAtTail(dll, 9);

    int sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(int*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 42, "Expected sum of elements to be 42, got %d", sum);

    DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListInsertAtTail(dll, 2);
    DoublyLinkedListInsertAtTail(dll, 3);
    DoublyLinkedListInsertAtTail(dll, 4);
    DoublyLinkedListInsertAtTail(dll, 5);
    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListReplace(dll, 9, 1);
    DoublyLinkedListReplaceAll(dll, 9, 1);

    sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(int*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 17, "Expected sum of elements to be 17, got %d", sum);

    int index = DoublyLinkedListGetIndex(dll, 9);
    cr_assert_eq(index, -1, "Expected index of 9 to be -1, got %d", index);

    DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 9);
    DoublyLinkedListInsertAtTail(dll, 9);

    sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(int*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_eq(sum, 18, "Expected sum of elements to be 18, got %d", sum);
	
	DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 1);
    DoublyLinkedListInsertAtTail(dll, 2);
    DoublyLinkedListInsertAtTail(dll, 3);
    DoublyLinkedListInsertAtTail(dll, 4);
    DoublyLinkedListInsertAtTail(dll, 5);
	
	int values[] = {1, 2, 3, 4, 5};
	int rvalues[] = {5, 4, 3, 2, 1};
	int i = 0;
	DoublyLinkedListIter* iter = DoublyLinkedListIterator(dll);
	DoublyLinkedListIter* riter = DoublyLinkedListIterator(dll);
	while (DoublyLinkedListNext(dll, iter))
	{
		cr_assert_eq(*(int *)iter->data, values[i], "Expected %d but got %d", values[i], *(int *)iter->data);
        i++;
	}
    i=0;
	while (DoublyLinkedListBack(dll, riter))
	{
		cr_assert_eq(*(int *)riter->data, rvalues[i], "Expected %d but got %d", rvalues[i], *(int *)iter->data);
        i++;
	}
	
    DoublyLinkedListDelete(dll);
}

Test(linkedlist_test, test_linked_list_double) {
    DoublyLinkedListDouble *dll = malloc(sizeof(DoublyLinkedListDouble));
    DoublyLinkedListNew(dll, DataCompare, FreeData);

    DoublyLinkedListInsertAtHead(dll, 0.25);
    DoublyLinkedListInsertAtHead(dll, 1.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListInsertAtTail(dll, 2.25);
    DoublyLinkedListInsertAtTail(dll, 3.25);
    DoublyLinkedListInsertAtTail(dll, 4.25);
    DoublyLinkedListInsertAtTail(dll, 5.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);
    
	double sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(double*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 44.25, 0.0001, "Expected sum of elements to be 44.25, got %lf", sum);

    DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListInsertAtTail(dll, 2.25);
    DoublyLinkedListInsertAtTail(dll, 3.25);
    DoublyLinkedListInsertAtTail(dll, 4.25);
    DoublyLinkedListInsertAtTail(dll, 5.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListReplace(dll, 9.25, 1.15);
    DoublyLinkedListReplaceAll(dll, 9.25, 1.15);

    sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(double*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 18.45, 0.0001, "Expected sum of elements to be 18.45, got %lf", sum);

    int index = DoublyLinkedListGetIndex(dll, 9.25);
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 9.25);
    DoublyLinkedListInsertAtTail(dll, 9.25);

    sum = 0;
    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        sum += *(double*)DoublyLinkedListAt(dll, i);
    }
    cr_assert_float_eq(sum, 18.5, 0.0001, "Expected sum of elements to be 18.5, got %lf", sum);
	
	DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, 1.25);
    DoublyLinkedListInsertAtTail(dll, 2.25);
    DoublyLinkedListInsertAtTail(dll, 3.25);
    DoublyLinkedListInsertAtTail(dll, 4.25);
    DoublyLinkedListInsertAtTail(dll, 5.25);
	
	double values[] = {1.25, 2.25, 3.25, 4.25, 5.25};
	double rvalues[] = {5.25, 4.25, 3.25, 2.25, 1.25};
	int i = 0;
	DoublyLinkedListIter* iter = DoublyLinkedListIterator(dll);
	DoublyLinkedListIter* riter = DoublyLinkedListIterator(dll);
	while (DoublyLinkedListNext(dll, iter))
	{
		cr_assert_float_eq(*(double *)iter->data, values[i], 0.01, "Expected %lf but got %lf", values[i], *(double *)iter->data);
        i++;
    }
    i=0;
	while (DoublyLinkedListBack(dll, riter))
	{
		cr_assert_float_eq(*(double *)riter->data, rvalues[i], 0.01, "Expected %lf but got %lf", rvalues[i], *(double *)iter->data);
        i++;
    }
	
    DoublyLinkedListDelete(dll);
}

Test(linkedlist_test, test_linked_list_string) {
    DoublyLinkedListString *dll = malloc(sizeof(DoublyLinkedListString));
    DoublyLinkedListNew(dll, StringCompare, FreeString);

    char* expected_list[] = {"1.25","0.25","9.25","2.25","3.25","4.25","5.25","9.25","9.25"};
    DoublyLinkedListInsertAtHead(dll, "0.25");
    DoublyLinkedListInsertAtHead(dll, "1.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListInsertAtTail(dll, "2.25");
    DoublyLinkedListInsertAtTail(dll, "3.25");
    DoublyLinkedListInsertAtTail(dll, "4.25");
    DoublyLinkedListInsertAtTail(dll, "5.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");

    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)DoublyLinkedListAt(dll, i), expected_list[i], "Unexpected string at index %d", i);
    }

    DoublyLinkedListClear(dll);

    char* expected_list2[] = {"1.25","2.25","3.25","4.25","5.25","1.25","1.25"};
    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListInsertAtTail(dll, "2.25");
    DoublyLinkedListInsertAtTail(dll, "3.25");
    DoublyLinkedListInsertAtTail(dll, "4.25");
    DoublyLinkedListInsertAtTail(dll, "5.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListReplace(dll, "9.25", "1.25");
    DoublyLinkedListReplaceAll(dll, "9.25", "1.25");

    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)DoublyLinkedListAt(dll, i), expected_list2[i], "Unexpected string at index %d", i);
    }

    int index = DoublyLinkedListGetIndex(dll, "9.25");
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, "9.25");
    DoublyLinkedListInsertAtTail(dll, "9.25");

    for (unsigned int i = 0; i < DoublyLinkedListSize(dll); i++) {
        cr_assert_str_eq(*(char**)DoublyLinkedListAt(dll, i), "9.25", "Unexpected string at index %d", i);
    }
	
	DoublyLinkedListClear(dll);

    DoublyLinkedListInsertAtTail(dll, "1.25");
    DoublyLinkedListInsertAtTail(dll, "2.25");
    DoublyLinkedListInsertAtTail(dll, "3.25");
    DoublyLinkedListInsertAtTail(dll, "4.25");
    DoublyLinkedListInsertAtTail(dll, "5.25");
	
	char* values[] = {"1.25", "2.25", "3.25", "4.25", "5.25"};
	char* rvalues[] = {"5.25", "4.25", "3.25", "2.25", "1.25"};
	int i = 0;
	DoublyLinkedListIter* iter = DoublyLinkedListIterator(dll);
	DoublyLinkedListIter* riter = DoublyLinkedListIterator(dll);
	while (DoublyLinkedListNext(dll, iter))
	{
		cr_assert_str_eq(*(char**)iter->data, values[i], "Expected %s but got %s", values[i], *(char**)iter->data);
        i++;
	}
    i=0;
	while (DoublyLinkedListBack(dll, riter))
	{
		cr_assert_str_eq(*(char**)riter->data, rvalues[i], "Expected %s but got %s", rvalues[i], *(char**)iter->data);
        i++;
	}

    DoublyLinkedListDelete(dll);
}
