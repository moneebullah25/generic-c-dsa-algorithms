
#include <stdio.h>
#include <stdlib.h>

#include "c_vector.h"
#include "c_queue.h"
#include "c_stack.h"
#include "c_sort.h"
#include "c_list.h"

void testLinearSearch()
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Linear Search Start-----------------------\n");
	printf("-----------------------------------------------------------\n");
	// LinearSearch with generic c method
	printf("%s : ", "Declaring array or 8 integers");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	printf("\n");

	// Linear Search
	printf("%s : \n", "Searching for values 0 - 4 using Linear Search in array and replacing them with 0");
	for (int i = 0; i < 5; i++)
	{
		void* target = LinearSearch((void*)&i, (void*)&arr, (int)8, (int)sizeof(int), &data_compare);
		if (target){
			printf("%s %d : %p\n", "Getting Acual Address of int ", i, target);
			printf("%s %d with 0\n", "Replacing Value of int ", i);
			*((int*)target) = 0;
		}
		else
			printf("%s \n", "Target Address Not Found");
	}

	printf("%s : ", "After Replacing");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	printf("\n");

	printf("%s : ", "Declaring array or 5 string(char*)");
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	for (int i = 0; i < 5; i++)
		printf("%p %s ", &(str[i]), str[i]);

	printf("\n");

	// Linear Search
	char* abcd = "abcd\0";
	char* find_abcd = (char*)LinearSearch(&abcd, &str, 5, sizeof(char*), &string_compare);
	printf("%s : \n", "Searching for value abcd using Linear Search in array");
	printf("&abcd=%p\n", find_abcd);

	printf("-----------------------------------------------------------\n");
	printf("-----------------Linear Search End-------------------------\n");
	printf("-----------------------------------------------------------\n");
}
void testBubbleSort()
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Bubble Search Start-----------------------\n");
	printf("-----------------------------------------------------------\n");
	// Sorting
	printf("%s : ", "Sorting array of 8 integers using Bubble Sort");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	BubbleSort(&arr, sizeof(int), 8, &data_compare);

	printf("%s : ", "After Sorting array of 8 integers using Bubble Sort");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// Sorting
	printf("Sorting array of 5 strings using Bubble Sort");
	printf("%s : ", "Declaring array or 5 string(char*)");
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	for (int i = 0; i < 5; i++)
		printf("%s ", str[i]);
	printf("\n");

	BubbleSort(&str, sizeof(char*), 5, &string_compare);

	for (int i = 0; i < 5; i++)
		printf("%p %s ", &(str[i]), str[i]);
	printf("\n");

	printf("-----------------------------------------------------------\n");
	printf("-----------------Bubble Search End-------------------------\n");
	printf("-----------------------------------------------------------\n");
}
void testBinarySearch()
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Binary Search Start-----------------------\n");
	printf("-----------------------------------------------------------\n");
	// LinearSearch with generic c method
	printf("%s : ", "Declaring array of 8 integers");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	printf("\n");

	BubbleSort(&arr, sizeof(int), 8, &data_compare);
	printf("%s : ", "After Sorting array of 8 integers using Bubble Sort");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// Linear Search
	printf("%s : \n", "Searching for values 0 - 4 using Binary Search in array and replacing them with 0");
	for (int i = 0; i < 5; i++)
	{
		void* target = BinarySearch((void*)&i, (void*)&arr, 0, (int)8, (int)sizeof(int), &data_compare);
		if (target){
			printf("%s %d : %p\n", "Getting Acual Address of int ", i, target);
			printf("%s %d with 0\n", "Replacing Value of int ", i);
			*((int*)target) = 0;
		}
		else
			printf("%s \n", "Target Address Not Found");
	}

	printf("%s : ", "After Replacing");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	printf("\n");

	printf("%s : ", "Declaring array or 5 string(char*)");
	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	for (int i = 0; i < 5; i++)
		printf("%p %s ", &(str[i]), str[i]);

	printf("\n");

	// Linear Search
	char* abcd = "abcd\0";
	char* find_abcd = (char*)BinarySearch(&abcd, &str, 0, 5, sizeof(char*), &string_compare);
	printf("Searching for value abcd using Binary Search in array : \n");
	printf("&abcd=%p\n", find_abcd);
	printf("-----------------------------------------------------------\n");
	printf("-----------------Binary Search End-------------------------\n");
	printf("-----------------------------------------------------------\n");
}
void testVector(unsigned int size)
{
	// Vector int
	Vector* a = malloc(sizeof(Vector));
	VectorNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		VectorPushBack(a, &i);
	}

	printf("Printing Vector Values : \n");

	unsigned int out;
	for (unsigned int i = 0; i < size; i++)
	{
		VectorAt(a, i, &out);
		printf("%u ", out);
	}
	VectorDispose(a, &data_free);

	printf("Printing Vector Values after Disposing : \n");
	for (unsigned int i = 0; i < size; i++)
	{
		VectorAt(a, i, &out);
		printf("%u ", out);
	}
}
void testQueue(unsigned int size)
{
	// Vector int
	Queue* a = malloc(sizeof(Queue));
	QueueNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		QueuePush(a, &i);
	}

	printf("Printing all Queue Popped Values : \n");

	unsigned int out;
	for (unsigned int i = 0; i < size; i++)
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}
	QueueDispose(a, &data_free);

	printf("Printing all Queue Popped Values after Disposing : \n");
	for (unsigned int i = 0; i < size; i++)
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}


	QueueNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		QueuePush(a, &i);
	}

	printf("Printing all Queue Popped Values : \n");

	for (unsigned int i = 0; i < size; i++)
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}
	QueueDispose(a, &data_free);

	printf("Printing all Queue Popped Values after Disposing : \n");
	for (unsigned int i = 0; i < size; i++)
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}
}
void testStack(unsigned int size)
{
	// Stack int
	Stack* a = malloc(sizeof(Stack));
	StackNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		StackPush(a, &i);
	}

	printf("Printing all Stack Popped Values : \n");
	unsigned int out;
	for (unsigned int i = 0; i < size; i++)
	{
		StackPop(a, &out);
		printf("%u ", out);
	}
	StackDispose(a, &data_free);


	printf("Printing all Stack Popped Values after Disposing : \n");
	for (unsigned int i = 0; i < size; i++)
	{
		StackPop(a, &out);
		printf("%u ", out);
	}
}
void testList(unsigned int size)
{
	LinkedList* ll = malloc(sizeof(LinkedList));
	LinkedListNew(ll, sizeof(unsigned int));

	printf("Inserting Values\n");
	for (unsigned int i = 0; i < size; i++)
	{
		if (i%2)
			LinkedListInsertAtTail(ll, &i);
		else
			LinkedListInsertAtHead(ll, &i);
	}

	printf("Changing Values\n");
	unsigned int val = MAX_UNSIGNED;
	for (unsigned int i = 0; i < size; i += 10)
	{
		LinkedListReplace(ll, &i, &val, &data_compare);
	}

	printf("Printing Values\n");
	for (unsigned int i = 0; i < size; i++)
	{
		if (LinkedListAt(ll, LinkedListGetIndex(ll, &i, &data_compare)) != NULL)
			printf("%u", LinkedListAt(ll, LinkedListGetIndex(ll, &i, &data_compare))->elem);
	}
}
void testQuickSort(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Quick Sort Start--------------------------\n");
	printf("-----------------------------------------------------------\n");
	printf("Declaring array of %u unsigned integers : ", size);
	unsigned value = size;
	unsigned int* arr = malloc(size * sizeof(unsigned int));
	for (unsigned int i = 0; i < size; i++)
	{
		arr[i] = value;
		value--;
	}	
	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n Sorting the Array \n");

	QuickSort(arr, 4, 0, size -1, &data_compare);

	printf("After Sorting the Array : ");

	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n");

	printf("-----------------------------------------------------------\n");
	printf("-----------------Quick Sort End----------------------------\n");
	printf("-----------------------------------------------------------\n");
}
void testMergeSort(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Merge Sort Start--------------------------\n");
	printf("-----------------------------------------------------------\n");
	printf("Declaring array of %u unsigned integers : ", size);
	unsigned value = size;
	unsigned int* arr = malloc(size * sizeof(unsigned int));
	for (unsigned int i = 0; i < size; i++)
	{
		arr[i] = value;
		value--;
	}
	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n Sorting the Array \n");

	MergeSort(arr, 4, 0, size - 1, &data_compare);

	printf("After Sorting the Array : ");

	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n");

	printf("-----------------------------------------------------------\n");
	printf("-----------------Merge Sort End----------------------------\n");
	printf("-----------------------------------------------------------\n");
}

int main()
{
	testBinarySearch();
	testBubbleSort();
	testLinearSearch();
	testVector(1000);
	testQueue(1000);
	testStack(1000);
	testList(1000);
	testQuickSort(100); // don't works well for values greater than 100 
	testMergeSort(100); // don't works well for values greater than 100 
    
}
