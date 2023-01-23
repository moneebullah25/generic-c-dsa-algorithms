#include <criterion/criterion.h>
#include "../includes/c_sort.h"

Test(linear_search_test, test_linear_search_int) {
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	int key = 4;
	int* target = (int*)LinearSearch((void*)&key, (void*)arr, 8, sizeof(int), DataCompare);
	int expected = 4;
	cr_assert_eq(*target, expected, "Error: Linear search returned incorrect value for int test.");
}

Test(linear_search_test, test_linear_search_double) {
	double arr[8] = { 8.1, 7.2, 6.3, 5.4, 4.5, 3.6, 2.7, 1.8 };
	double key = 4.5;
	double* target = (double*)LinearSearch((void*)&key, (void*)arr, 8, sizeof(double), DataCompare);
	double expected = 4.5;
	cr_assert_float_eq(*target, expected, 0.00001, "Error: Linear search returned incorrect value for double test.");
}

Test(linear_search_test, test_linear_search_string) {
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	char* key = "abcd\0";
	char** target = (char**)LinearSearch((void*)&key, (void*)str, 5, sizeof(char*), StringCompare);
	char* expected = "abcd\0";
	cr_assert_str_eq(*target, expected, "Error: Linear search returned incorrect value for string test.");
}

Test(bubble_sort_test, test_bubble_sort_int) {
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	BubbleSort((void*)arr, sizeof(int), 8, DataCompare, MemorySwap);
	int expected[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(int), "Error: Bubble sort returned incorrect value for int test.");
}

Test(bubble_sort_test, test_bubble_sort_double) {
	double arr[8] = { 8.1, 7.2, 6.3, 5.4, 4.5, 3.6, 2.7, 1.8 };
	BubbleSort((void*)arr, sizeof(double), 8, DataCompare, MemorySwap);
	double expected[8] = { 1.8, 2.7, 3.6, 4.5, 5.4, 6.3, 7.2, 8.1 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(double), "Error: bubble sort returned incorrect value for double test.");
}

Test(bubble_sort_test, test_bubble_sort_string) {
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	BubbleSort((void*)str, sizeof(char*), 5, StringCompare, StringSwap);
	char* expected[5] = { "ABC\0", "aad\0", "ab\0", "abc\0", "abcd\0" };
	cr_assert_arr_eq(str, expected, sizeof(str) / sizeof(char*), "Error: bubble sort returned incorrect value for string test.");
}

Test(binary_search_test, test_binary_search_int) {
	int arr[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int key = 4;
	int* target = (int*)BinarySearch((void*)&key, (void*)arr, 0, 8, sizeof(int), DataCompare);
	int expected = 4;
	cr_assert_eq(*target, expected, "Error: Binary search returned incorrect value for int test.");
}

Test(binary_search_test, test_binary_search_double) {
	double arr[8] = { 1.8, 2.7, 3.6, 4.5, 5.4, 6.3, 7.2, 8.1 };
	double key = 4.5;
	double* target = (double*)BinarySearch((void*)&key, (void*)arr, 0, 8, sizeof(double), DataCompare);
	double expected = 4.5;
	cr_assert_float_eq(*target, expected, 0.00001, "Error: Binary search returned incorrect value for double test.");
}

Test(binary_search_test, test_binary_search_string) {
	char* str[5] = { "ABC\0", "aad\0", "ab\0", "abc\0", "abcd\0" };
	char* key = "abcd\0";
	char** target = (char**)BinarySearch((void*)&key, (void*)str, 0, 5, sizeof(char*), StringCompare);
	char* expected = "abcd\0";
	cr_assert_str_eq(*target, expected, "Error: Binary search returned incorrect value for string test.");
}

Test(quick_sort_test, test_quick_sort_int)
{
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	QuickSort((void*)arr, sizeof(int), 0, 8, DataCompare, MemorySwap);
	int expected[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(int), "Error: Bubble sort returned incorrect value for int test.");
}

Test(quick_sort_test, test_quick_sort_double)
{
	double arr[8] = { 8.1, 7.2, 6.3, 5.4, 4.5, 3.6, 2.7, 1.8 };
	QuickSort((void*)arr, sizeof(double), 0, 8, DataCompare, MemorySwap);
	double expected[8] = { 1.8, 2.7, 3.6, 4.5, 5.4, 6.3, 7.2, 8.1 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(double), "Error: bubble sort returned incorrect value for double test.");
}

Test(quick_sort_test, test_quick_sort_string)
{
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	QuickSort((void*)str, sizeof(char*), 0, 5, StringCompare, StringSwap);
	char* expected[5] = { "ABC\0", "aad\0", "ab\0", "abc\0", "abcd\0" };
	cr_assert_arr_eq(str, expected, sizeof(str) / sizeof(char*), "Error: bubble sort returned incorrect value for string test.");
}

Test(merge_sort_test, test_merge_sort_int)
{
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	MergeSort((void*)arr, sizeof(int), 0, 8, DataCompare, MemorySwap);
	int expected[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(int), "Error: Bubble sort returned incorrect value for int test.");
}

Test(merge_sort_test, test_merge_sort_double)
{
	double arr[8] = { 8.1, 7.2, 6.3, 5.4, 4.5, 3.6, 2.7, 1.8 };
	MergeSort((void*)arr, sizeof(double), 0, 8, DataCompare, MemorySwap);
	double expected[8] = { 1.8, 2.7, 3.6, 4.5, 5.4, 6.3, 7.2, 8.1 };
	cr_assert_arr_eq(arr, expected, sizeof(arr) / sizeof(double), "Error: bubble sort returned incorrect value for double test.");
}

Test(merge_sort_test, test_merge_sort_string)
{
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	MergeSort((void*)str, sizeof(char*), 0, 5, StringCompare, StringSwap);
	char* expected[5] = { "ABC\0", "aad\0", "ab\0", "abc\0", "abcd\0" };
	cr_assert_arr_eq(str, expected, sizeof(str) / sizeof(char*), "Error: bubble sort returned incorrect value for string test.");
}