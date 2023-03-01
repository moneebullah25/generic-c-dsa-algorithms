#include <criterion/criterion.h>
#include "../includes/c_clist.h"
#include "../includes/c_helper.h"

Test(clinkedlist_test, test_clinkedlist_int) {
    CircularLinkedListInt *cll = malloc(sizeof(CircularLinkedListInt));
    CircularLinkedListNew(cll, DataCompare, FreeData);

    CircularLinkedListInsert(cll, 9);
    CircularLinkedListInsert(cll, 2);
    CircularLinkedListInsert(cll, 3);
    CircularLinkedListInsert(cll, 4);
    CircularLinkedListInsert(cll, 5);
    CircularLinkedListInsert(cll, 9);
    CircularLinkedListInsert(cll, 9);

    int sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(int*)CircularLinkedListAt(cll, i);
    }
    cr_assert_eq(sum, 41, "Expected sum of elements to be 42, got %d", sum);

    CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 9);
    CircularLinkedListInsert(cll, 2);
    CircularLinkedListInsert(cll, 3);
    CircularLinkedListInsert(cll, 4);
    CircularLinkedListInsert(cll, 5);
    CircularLinkedListInsert(cll, 9);
    CircularLinkedListInsert(cll, 9);
    CircularLinkedListReplace(cll, 9, 1);
    CircularLinkedListReplaceAll(cll, 9, 1);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(int*)CircularLinkedListAt(cll, i);
    }
    cr_assert_eq(sum, 17, "Expected sum of elements to be 17, got %d", sum);

    int index = CircularLinkedListGetIndex(cll, 9);
    cr_assert_eq(index, -1, "Expected index of 9 to be -1, got %d", index);

    CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 9);
    CircularLinkedListInsert(cll, 9);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(int*)CircularLinkedListAt(cll, i);
    }
    cr_assert_eq(sum, 18, "Expected sum of elements to be 18, got %d", sum);
	
	CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 1);
    CircularLinkedListInsert(cll, 2);
    CircularLinkedListInsert(cll, 3);
    CircularLinkedListInsert(cll, 4);
    CircularLinkedListInsert(cll, 5);
	
	int values[] = {1, 2, 3, 4, 5};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(cll);
	while (CircularLinkedListNext(cll, iter))
	{
		cr_assert_eq(*(int *)iter->data, values[i], "Expected %d but got %d", values[i], *(int *)iter->data);
        i++;
	}
	
    CircularLinkedListDelete(cll);
}

Test(clinkedlist_test, test_clinkedlist_double) {
    CircularLinkedListDouble *cll = malloc(sizeof(CircularLinkedListDouble));
    CircularLinkedListNew(cll, DataCompare, FreeData);

    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListInsert(cll, 2.25);
    CircularLinkedListInsert(cll, 3.25);
    CircularLinkedListInsert(cll, 4.25);
    CircularLinkedListInsert(cll, 5.25);
    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListInsert(cll, 9.25);
    
	double sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(double*)CircularLinkedListAt(cll, i);
    }
    cr_assert_float_eq(sum, 42.75, 0.0001, "Expected sum of elements to be 44.25, got %lf", sum);

    CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListInsert(cll, 2.25);
    CircularLinkedListInsert(cll, 3.25);
    CircularLinkedListInsert(cll, 4.25);
    CircularLinkedListInsert(cll, 5.25);
    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListReplace(cll, 9.25, 1.15);
    CircularLinkedListReplaceAll(cll, 9.25, 1.15);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(double*)CircularLinkedListAt(cll, i);
    }
    cr_assert_float_eq(sum, 18.45, 0.0001, "Expected sum of elements to be 18.45, got %lf", sum);

    int index = CircularLinkedListGetIndex(cll, 9.25);
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 9.25);
    CircularLinkedListInsert(cll, 9.25);

    sum = 0;
    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        sum += *(double*)CircularLinkedListAt(cll, i);
    }
    cr_assert_float_eq(sum, 18.5, 0.0001, "Expected sum of elements to be 18.5, got %lf", sum);
	
	CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, 1.25);
    CircularLinkedListInsert(cll, 2.25);
    CircularLinkedListInsert(cll, 3.25);
    CircularLinkedListInsert(cll, 4.25);
    CircularLinkedListInsert(cll, 5.25);
	
	double values[] = {1.25, 2.25, 3.25, 4.25, 5.25};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(cll);
	while (CircularLinkedListNext(cll, iter))
	{
		cr_assert_float_eq(*(double *)iter->data, values[i], 0.0001, "Expected %lf but got %lf", values[i], *(double *)iter->data);
        i++;
    }
	
    CircularLinkedListDelete(cll);
}

Test(clinkedlist_test, test_clinkedlist_string) {
    CircularLinkedListString *cll = malloc(sizeof(CircularLinkedListString));
    CircularLinkedListNew(cll, StringCompare, FreeString);

    char* expected_list[] = {"9.25","2.25","3.25","4.25","5.25","9.25","9.25"};

    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListInsert(cll, "2.25");
    CircularLinkedListInsert(cll, "3.25");
    CircularLinkedListInsert(cll, "4.25");
    CircularLinkedListInsert(cll, "5.25");
    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListInsert(cll, "9.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(cll, i), expected_list[i], "Unexpected string at index %d", i);
    }

    CircularLinkedListClear(cll);

    char* expected_list2[] = {"1.25","2.25","3.25","4.25","5.25","1.25","1.25"};
    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListInsert(cll, "2.25");
    CircularLinkedListInsert(cll, "3.25");
    CircularLinkedListInsert(cll, "4.25");
    CircularLinkedListInsert(cll, "5.25");
    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListReplace(cll, "9.25", "1.25");
    CircularLinkedListReplaceAll(cll, "9.25", "1.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(cll, i), expected_list2[i], "Unexpected string at index %d", i);
    }

    int index = CircularLinkedListGetIndex(cll, "9.25");
    cr_assert_eq(index, -1, "Expected index of 9.25 to be -1, got %d", index);

    CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, "9.25");
    CircularLinkedListInsert(cll, "9.25");

    for (unsigned int i = 0; i < CircularLinkedListSize(cll); i++) {
        cr_assert_str_eq(*(char**)CircularLinkedListAt(cll, i), "9.25", "Unexpected string at index %d", i);
    }
	
	CircularLinkedListClear(cll);

    CircularLinkedListInsert(cll, "1.25");
    CircularLinkedListInsert(cll, "2.25");
    CircularLinkedListInsert(cll, "3.25");
    CircularLinkedListInsert(cll, "4.25");
    CircularLinkedListInsert(cll, "5.25");
	
	char* values[] = {"1.25", "2.25", "3.25", "4.25", "5.25"};
	int i = 0;
	CircularLinkedListIter* iter = CircularLinkedListIterator(cll);
	while (CircularLinkedListNext(cll, iter))
	{
		cr_assert_str_eq(*(char**)iter->data, values[i], "Expected %s but got %s", values[i], *(char**)iter->data);
        i++;
	}
	
    CircularLinkedListDelete(cll);
}
