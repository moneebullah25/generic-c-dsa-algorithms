
#include <stdio.h>
#include <stdlib.h>

#include "./includes/c_vector.h"
#include "./includes/c_queue.h"
#include "./includes/c_stack.h"
#include "./includes/c_sort.h"
#include "./includes/c_list.h"
#include "./includes/c_map.h"

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
		void* target = LinearSearch((void*)&i, (void*)&arr, (int)8, (int)sizeof(int), &DataCompare);
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
	char* find_abcd = (char*)LinearSearch(&abcd, &str, 5, sizeof(char*), &StringCompare);
	printf("%s : \n", "Searching for value abcd using Linear Search in array");
	printf("&abcd=%p\n", find_abcd);

	printf("-----------------------------------------------------------\n");
	printf("-----------------Linear Search End-------------------------\n");
	printf("-----------------------------------------------------------\n\n");
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

	BubbleSort(&arr, sizeof(int), 8, &DataCompare);

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

	BubbleSort(&str, sizeof(char*), 5, &StringCompare);

	for (int i = 0; i < 5; i++)
		printf("%p %s ", &(str[i]), str[i]);
	printf("\n");

	printf("-----------------------------------------------------------\n");
	printf("-----------------Bubble Search End-------------------------\n");
	printf("-----------------------------------------------------------\n\n");
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

	BubbleSort(&arr, sizeof(int), 8, &DataCompare);
	printf("%s : ", "After Sorting array of 8 integers using Bubble Sort");
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// Linear Search
	printf("%s : \n", "Searching for values 0 - 4 using Binary Search in array and replacing them with 0");
	for (int i = 0; i < 5; i++)
	{
		void* target = BinarySearch((void*)&i, (void*)&arr, 0, (int)8, (int)sizeof(int), &DataCompare);
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
	char* find_abcd = (char*)BinarySearch(&abcd, &str, 0, 5, sizeof(char*), &StringCompare);
	printf("Searching for value abcd using Binary Search in array : \n");
	printf("&abcd=%p\n", find_abcd);
	printf("-----------------------------------------------------------\n");
	printf("-----------------Binary Search End-------------------------\n");
	printf("-----------------------------------------------------------\n\n");
}
void testVector(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Vector Test Start-------------------------\n");
	printf("-----------------------------------------------------------\n");
	// Vector int
	Vector* a = malloc(sizeof(Vector));
	VectorNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		VectorPushBack(a, &i);
	}

	printf("Printing Vector Values : \n");

	unsigned int out;
	for (unsigned int i = 0; i < VectorSize(a); i++)
	{
		VectorAt(a, i, &out);
		printf("%u ", out);
	}
	VectorDispose(a, &FreeData);

	printf("Printing Vector Values after Disposing : \n");
	for (unsigned int i = 0; i < VectorSize(a); i++)
	{
		VectorAt(a, i, &out);
		printf("%u ", out);
	}
	printf("-----------------------------------------------------------\n");
	printf("-----------------Vector Test End---------------------------\n");
	printf("-----------------------------------------------------------\n\n");
}
void testQueue(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Queue Test Start--------------------------\n");
	printf("-----------------------------------------------------------\n");
	Queue* a = malloc(sizeof(Queue));
	QueueNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		QueuePush(a, &i);
	}

	printf("Printing all Queue Popped Values : \n");

	unsigned int out;
	for ( ; QueueSize(a) > 0; )
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}
	QueueDispose(a, &FreeData);

	printf("Printing all Queue Popped Values after Disposing : \n");
	for (; QueueSize(a) > 0;)
	{
		QueuePop(a, &out);
		printf("%u ", out);
	}
	printf("-----------------------------------------------------------\n");
	printf("-----------------Queue Test End----------------------------\n");
	printf("-----------------------------------------------------------\n\n");
}
void testStack(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------Stack Test Start--------------------------\n");
	printf("-----------------------------------------------------------\n");
	// Stack int
	Stack* a = malloc(sizeof(Stack));
	StackNew(a, sizeof(unsigned int));
	for (unsigned int i = size; i > 0; i--)
	{
		StackPush(a, &i);
	}

	printf("Printing all Stack Popped Values : \n");
	unsigned int out;
	for (; StackSize(a) > 0;)
	{
		StackPop(a, &out);
		printf("%u ", out);
	}
	StackDispose(a, &FreeData);


	printf("Printing all Stack Popped Values after Disposing : \n");
	for (; StackSize(a) > 0;)
	{
		StackPop(a, &out);
		printf("%u ", out);
	}
	printf("-----------------------------------------------------------\n");
	printf("-----------------Stack Test End----------------------------\n");
	printf("-----------------------------------------------------------\n\n");
}
void testList(unsigned int size)
{
	printf("-----------------------------------------------------------\n");
	printf("-----------------List Test Start---------------------------\n");
	printf("-----------------------------------------------------------\n");
	LinkedList* ll = malloc(sizeof(LinkedList));
	LinkedListNew(ll, sizeof(unsigned int));

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
		LinkedListReplace(ll, &i, &val, &DataCompare);
		printf("(%u->%u) ", i, val);
	}

	printf("\nPrinting Selected Values\n");
	for (unsigned int i = 0; i < size; i++)
	{
		if (LinkedListAt(ll, LinkedListGetIndex(ll, &i, &DataCompare)) != NULL)
			printf("%u ", *((unsigned int *)LinkedListAt(ll, LinkedListGetIndex(ll, &i, &DataCompare))->elem));
	}

	printf("\nPrinting All values Start fron Head to Tail\n");
	for (unsigned int i = 0; i < size; i++)
	{
		if (LinkedListAt(ll, i) != NULL)
			printf("%u ", *((unsigned int *)LinkedListAt(ll, i)->elem));
	}
	printf("\n");
	printf("-----------------------------------------------------------\n");
	printf("-----------------List Test End-----------------------------\n");
	printf("-----------------------------------------------------------\n\n");
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

	QuickSort(arr, 4, 0, size -1, &DataCompare);

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

	MergeSort(arr, 4, 0, size - 1, &DataCompare);

	printf("After Sorting the Array : ");

	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n");

	printf("-----------------------------------------------------------\n");
	printf("-----------------Merge Sort End----------------------------\n");
	printf("-----------------------------------------------------------\n");
}

void testMap()
{
	printf("-----------------------------------------------------------\n");
	printf("---------------------Maps Start----------------------------\n");
	printf("-----------------------------------------------------------\n");
	{
		MapStringInt* m = malloc(sizeof(Map));
		MapNew(m, HashFunctionStr, LinearProbing, StringCompare);

		MapSet(m, "Muneeb\0", 21);
		MapSet(m, "Moiz\0", 15);
		MapSet(m, "Moaaz\0", 45);
		MapSet(m, "Arif\0", 75);

		MapIter* iter = MapIterator(m);
		while (iter != NULL){
			printf("%s -> %d, HASH: %d \n", *(char**)iter->node.key,
				*(int*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}

		MapSet(m, "Kashif\0", 43);

		iter = MapIterator(m);
		while (iter != NULL){
			printf("%s -> %d, HASH: %d \n", *(char**)iter->node.key,
				*(int*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}

		void* age = MapGet(m, "Moiz\0");
		*(int*)age = 16;

		iter = MapIterator(m);
		while (iter != NULL){
			printf("%s -> %d, HASH: %d \n", *(char**)iter->node.key,
				*(int*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}
		MapDelete(m);
	}
	{
	MapInt* m = malloc(sizeof(Map));
	MapNew(m, HashFunctionInt, LinearProbing, DataCompare);

	MapSet(m, 1, 21);
	MapSet(m, 2, 15);
	MapSet(m, 3, 15);
	MapSet(m, 4, 15);

	MapIter* iter = MapIterator(m);
	while (iter != NULL){
		printf("%d -> %d, HASH: %d \n", *(int*)iter->node.key,
			*(int*)iter->node.value, iter->keyindex);
		iter = MapNext(m, iter);
	}

	MapSet(m, 5, 43);

	iter = MapIterator(m);
	while (iter != NULL){
		printf("%d -> %d, HASH: %d \n", *(int*)iter->node.key,
			*(int*)iter->node.value, iter->keyindex);
		iter = MapNext(m, iter);
	}

	void* age = MapGet(m, 2);
	*(int*)age = 16;

	iter = MapIterator(m);
	while (iter != NULL){
		printf("%d -> %d, HASH: %d \n", *(int*)iter->node.key,
			*(int*)iter->node.value, iter->keyindex);
		iter = MapNext(m, iter);
	}
	MapDelete(m);
}
	{
		MapDouble* m = malloc(sizeof(Map));
		MapNew(m, HashFunctionInt, LinearProbing, DataCompare);

		MapSet(m, 1.0, 21.25);
		MapSet(m, 2.0, 15.25);
		MapSet(m, 3.0, 15.25);
		MapSet(m, 4.0, 15.25);

		MapIter* iter = MapIterator(m);
		while (iter != NULL){
			printf("%lf -> %lf, HASH: %d \n", *(double*)iter->node.key,
				*(double*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}

		MapSet(m, 5.0, 43.0);

		iter = MapIterator(m);
		while (iter != NULL){
			printf("%lf -> %lf, HASH: %d \n", *(double*)iter->node.key,
				*(double*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}

		void* age = MapGet(m, 2.0);
		*(double*)age = 16.00;

		iter = MapIterator(m);
		while (iter != NULL){
			printf("%lf -> %lf, HASH: %d \n", *(double*)iter->node.key,
				*(double*)iter->node.value, iter->keyindex);
			iter = MapNext(m, iter);
		}
		MapDelete(m);
	}
	
	printf("-----------------------------------------------------------\n");
	printf("---------------------Maps End------------------------------\n");
	printf("-----------------------------------------------------------\n");
}

int main()
{
	testBinarySearch();
	testBubbleSort();
	testLinearSearch();
	testVector(100);
	testQueue(100);
	testStack(100);
	testList(25);
	testMap();
	testQuickSort(100); // don't works well for values greater than 100 
	testMergeSort(100); // don't works well for values greater than 100 
    
}
