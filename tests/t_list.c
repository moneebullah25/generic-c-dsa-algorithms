#include <criterion/criterion.h>
#include "../includes/c_list.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

Test(linkedlist_test, test_linked_list_int) {
    LinkedListInt *ll = malloc(sizeof(LinkedListInt));
    LinkedListNew(ll, IntDataCompare, FreeData);

    LinkedListInsertAtHead(ll, 0);
    LinkedListInsertAtHead(ll, 1);
    LinkedListInsertAtTail(ll, 9);
    LinkedListInsertAtTail(ll, 2);
    LinkedListInsertAtTail(ll, 3);
    LinkedListInsertAtTail(ll, 4);
    LinkedListInsertAtTail(ll, 5);
    LinkedListInsertAtTail(ll, 9);
    LinkedListInsertAtTail(ll, 9);

    int sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(int*)LinkedListAt(ll, i);
    }
    cr_assert_eq(sum, 42, "Expected sum of elements to be 42, got %d", sum);

    LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 9);
    LinkedListInsertAtTail(ll, 2);
    LinkedListInsertAtTail(ll, 3);
    LinkedListInsertAtTail(ll, 4);
    LinkedListInsertAtTail(ll, 5);
    LinkedListInsertAtTail(ll, 9);
    LinkedListInsertAtTail(ll, 9);
    LinkedListReplace(ll, 9, 1);
    LinkedListReplaceAll(ll, 9, 1);

    sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(int*)LinkedListAt(ll, i);
    }
    cr_assert_eq(sum, 17, "Expected sum of elements to be 17, got %d", sum);

    int index = LinkedListGetIndex(ll, 9);
    cr_assert_eq(index, -1, "Expected index of 9 to be -1, got %d", index);

    LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 9);
    LinkedListInsertAtTail(ll, 9);

    sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(int*)LinkedListAt(ll, i);
    }
    cr_assert_eq(sum, 18, "Expected sum of elements to be 18, got %d", sum);

	LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 1);
    LinkedListInsertAtTail(ll, 2);
    LinkedListInsertAtTail(ll, 3);
    LinkedListInsertAtTail(ll, 4);
    LinkedListInsertAtTail(ll, 5);
	
	int values[] = {1, 2, 3, 4, 5};
	int i = 0;
	LinkedListIter* iter = LinkedListIterator(ll);
	while (LinkedListNext(ll, iter))
	{
		cr_assert_eq(*(int *)iter->data, values[i], "Expected %d but got %d", values[i], *(int *)iter->data);
        i++;
	}
	
    LinkedListDelete(ll);
}

Test(linkedlist_test, test_linked_list_double) {
    LinkedListDouble *ll = malloc(sizeof(LinkedListDouble));
    LinkedListNew(ll, DoubleDataCompare, FreeData);

    LinkedListInsertAtHead(ll, 0.25);
    LinkedListInsertAtHead(ll, 1.25);
    LinkedListInsertAtTail(ll, 9.25);
    LinkedListInsertAtTail(ll, 2.25);
    LinkedListInsertAtTail(ll, 3.25);
    LinkedListInsertAtTail(ll, 4.25);
    LinkedListInsertAtTail(ll, 5.25);
    LinkedListInsertAtTail(ll, 9.25);
    LinkedListInsertAtTail(ll, 9.25);
    
	double sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(double*)LinkedListAt(ll, i);
    }
    cr_assert_float_eq(sum, 44.25, 0.0001, "Expected sum of elements to be 44.25, got %lf", sum);

    LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 9.25);
    LinkedListInsertAtTail(ll, 2.25);
    LinkedListInsertAtTail(ll, 3.25);
    LinkedListInsertAtTail(ll, 4.25);
    LinkedListInsertAtTail(ll, 5.25);
    LinkedListInsertAtTail(ll, 9.25);
    LinkedListInsertAtTail(ll, 9.25);
    LinkedListReplace(ll, 9.25, 1.15);
    LinkedListReplaceAll(ll, 9.25, 1.15);

    sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(double*)LinkedListAt(ll, i);
    }
    cr_assert_float_eq(sum, 18.45, 0.0001, "Expected sum of elements to be 18.45, got %lf", sum);

    int index = LinkedListGetIndex(ll, 9.25);
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 9.25);
    LinkedListInsertAtTail(ll, 9.25);

    sum = 0;
    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        sum += *(double*)LinkedListAt(ll, i);
    }
    cr_assert_float_eq(sum, 18.5, 0.0001, "Expected sum of elements to be 18.5, got %lf", sum);
	
	LinkedListClear(ll);

    LinkedListInsertAtTail(ll, 1.25);
    LinkedListInsertAtTail(ll, 2.25);
    LinkedListInsertAtTail(ll, 3.25);
    LinkedListInsertAtTail(ll, 4.25);
    LinkedListInsertAtTail(ll, 5.25);
	
	double values[] = {1.25, 2.25, 3.25, 4.25, 5.25};
	int i = 0;
	LinkedListIter* iter = LinkedListIterator(ll);
	while (LinkedListNext(ll, iter))
	{
		cr_assert_float_eq(*(double *)iter->data, values[i], 0.0001, "Expected %lf but got %lf", values[i], *(double *)iter->data);
        i++;
    }
	
    LinkedListDelete(ll);
}

Test(linkedlist_test, test_linked_list_string) {
    LinkedListString *ll = malloc(sizeof(LinkedListString));
    LinkedListNew(ll, StringCompare, FreeString);

    char* expected_list[] = {"1.25","0.25","9.25","2.25","3.25","4.25","5.25","9.25","9.25"};
    LinkedListInsertAtHead(ll, "0.25");
    LinkedListInsertAtHead(ll, "1.25");
    LinkedListInsertAtTail(ll, "9.25");
    LinkedListInsertAtTail(ll, "2.25");
    LinkedListInsertAtTail(ll, "3.25");
    LinkedListInsertAtTail(ll, "4.25");
    LinkedListInsertAtTail(ll, "5.25");
    LinkedListInsertAtTail(ll, "9.25");
    LinkedListInsertAtTail(ll, "9.25");

    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        cr_assert_str_eq(*(char**)LinkedListAt(ll, i), expected_list[i], "Unexpected string at index %d", i);
    }

    LinkedListClear(ll);

    char* expected_list2[] = {"1.25","2.25","3.25","4.25","5.25","1.25","1.25"};
    LinkedListInsertAtTail(ll, "9.25");
    LinkedListInsertAtTail(ll, "2.25");
    LinkedListInsertAtTail(ll, "3.25");
    LinkedListInsertAtTail(ll, "4.25");
    LinkedListInsertAtTail(ll, "5.25");
    LinkedListInsertAtTail(ll, "9.25");
    LinkedListInsertAtTail(ll, "9.25");
    LinkedListReplace(ll, "9.25", "1.25");
    LinkedListReplaceAll(ll, "9.25", "1.25");

    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        cr_assert_str_eq(*(char**)LinkedListAt(ll, i), expected_list2[i], "Unexpected string at index %d", i);
    }

    int index = LinkedListGetIndex(ll, "9.25");
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    LinkedListClear(ll);

    LinkedListInsertAtTail(ll, "9.25");
    LinkedListInsertAtTail(ll, "9.25");

    for (unsigned int i = 0; i < LinkedListSize(ll); i++) {
        cr_assert_str_eq(*(char**)LinkedListAt(ll, i), "9.25", "Unexpected string at index %d", i);
    }
	
	LinkedListClear(ll);

    LinkedListInsertAtTail(ll, "1.25");
    LinkedListInsertAtTail(ll, "2.25");
    LinkedListInsertAtTail(ll, "3.25");
    LinkedListInsertAtTail(ll, "4.25");
    LinkedListInsertAtTail(ll, "5.25");
	
	char* values[] = {"1.25", "2.25", "3.25", "4.25", "5.25"};
	int i = 0;
	LinkedListIter* iter = LinkedListIterator(ll);
	while (LinkedListNext(ll, iter))
	{
		cr_assert_str_eq(*(char**)iter->data, values[i], "Expected %s but got %s", values[i], *(char**)iter->data);
        i++;
	}
	
    LinkedListDelete(ll);
}
