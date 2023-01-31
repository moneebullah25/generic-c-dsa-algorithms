
#include <stdio.h>
#include <stdlib.h>

#include "./includes/c_vector.h"
#include "./includes/c_queue.h"
#include "./includes/c_stack.h"
#include "./includes/c_sort.h"
#include "./includes/c_list.h"
#include "./includes/c_map.h"
#include "./includes/c_matrix.h"

void testLinearSearch()
{
	printf("-----------------Linear Search Start-----------------------\n");
	printf("%s : ", "Declaring array or 8 integers");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	printf("\n");

	// Linear Search
	printf("%s : \n", "Searching for values 0 - 4 using Linear Search in array and replacing them with 0");
	for (int i = 0; i < 5; i++)
	{
		void* target = LinearSearch((void*)&i, (void*)arr, 8, sizeof(int), DataCompare);
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
	// Address returned by LinearSearch will be 2 hops away
	char* find_abcd = (char*)LinearSearch(&abcd, str, 5, sizeof(char*), StringCompare);
	printf("%s \n", *(char**)find_abcd);
	printf("%s : \n", "Searching for value abcd using Linear Search in array");
	printf("&abcd=%p\n", find_abcd);
	printf("-----------------Linear Search End-------------------------\n");
}
void testBubbleSort()
{
	printf("-----------------Bubble Sort Start-------------------------\n");
	printf("%s : ", "Sorting array of 8 integers using Bubble Sort");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");

	BubbleSort(&arr, sizeof(int), 8, DataCompare, MemorySwap);

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

	BubbleSort(&str, sizeof(char*), 5, StringCompare, StringSwap);

	for (int i = 0; i < 5; i++)
		printf("%p %s ", &(str[i]), str[i]);
	printf("\n");

	printf("-----------------Bubble Sort End---------------------------\n");
}
void testBinarySearch()
{
	printf("-----------------Binary Search Start-----------------------\n");
	// LinearSearch with generic c method
	printf("%s : ", "Declaring array of 8 integers");
	int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	BubbleSort(&arr, sizeof(int), 8, &DataCompare, &MemorySwap);
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
	printf("-----------------Binary Search End-------------------------\n");
}
void testVector(unsigned int size)
{
	printf("-----------------Vector Test Start-------------------------\n");
	{
		VectorInt *v = malloc(sizeof(VectorInt));
		VectorNew(v, DataCompare, FreeData);

		VectorPush(v, 1);
		VectorPush(v, 2);
		VectorPush(v, 3);
		VectorPush(v, 4);

		VectorIter *iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%d ", *(int *)iter->data);

		VectorClear(v);

		VectorPush(v, 1);
		VectorPush(v, 2);
		VectorPush(v, 3);
		VectorPush(v, 4);
		VectorPush(v, 5);

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%d ", *(int *)iter->data);

		int *out;
		for (unsigned int i = 0; i < VectorSize(v); i++)
		{
			out = VectorAt(v, i);
			printf("%d ", *out);
		}

		int *five = VectorGet(v, 5);
		*five = 6;

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%d ", *(int *)iter->data);

		VectorDelete(v);
	}
	{
		VectorDouble *v = malloc(sizeof(VectorDouble));
		VectorNew(v, DataCompare, FreeData);

		VectorPush(v, 1.0);
		VectorPush(v, 2.0);
		VectorPush(v, 3.0);
		VectorPush(v, 4.0);

		VectorIter *iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%lf ", *(double *)iter->data);

		VectorClear(v);

		VectorPush(v, 1.25);
		VectorPush(v, 2.25);
		VectorPush(v, 3.25);
		VectorPush(v, 4.25);
		VectorPush(v, 5.25);

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%lf ", *(double *)iter->data);

		double *out;
		for (unsigned int i = 0; i < VectorSize(v); i++)
		{
			out = VectorAt(v, i);
			printf("%lf ", *out);
		}

		double *five = VectorGet(v, 5.25);
		*five = 6.25;

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%lf ", *(double *)iter->data);

		VectorDelete(v);
	}
	{
		VectorString *v = malloc(sizeof(VectorString));
		VectorNew(v, StringCompare, FreeString);

		VectorPush(v, "111");
		VectorPush(v, "211");
		VectorPush(v, "311");
		VectorPush(v, "411");

		VectorIter *iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%s ", *(char **)iter->data);

		VectorClear(v);

		VectorPush(v, "111");
		VectorPush(v, "211");
		VectorPush(v, "311");
		VectorPush(v, "411");
		VectorPush(v, "511");

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%s ", *(char **)iter->data);

		char *out;
		for (unsigned int i = 0; i < VectorSize(v); i++)
		{
			out = *(char**)VectorAt(v, i);
			printf("%s ", out);
		}

		char **five = VectorGet(v, "511");
		*five = "611";

		iter = VectorIterator(v);
		while (VectorNext(v, iter))
			printf("%s ", *(char **)iter->data);

		VectorDelete(v);
	}
	printf("-----------------Vector Test End---------------------------\n");
}
void testQueue(unsigned int size)
{
	printf("-----------------Queue Test Start-------------------------\n");
	{
		QueueInt *q = malloc(sizeof(QueueInt));
		QueueNew(q, DataCompare, FreeData);

		QueuePush(q, 1);
		QueuePush(q, 2);
		QueuePush(q, 3);
		QueuePush(q, 4);

		QueueIter *iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%d ", *(int *)iter->data);

		QueueClear(q);

		QueuePush(q, 1);
		QueuePush(q, 2);
		QueuePush(q, 3);
		QueuePush(q, 4);
		QueuePush(q, 5);

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%d ", *(int *)iter->data);

		int *five = QueueTop(q);
		*five = 6;

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%d ", *(int *)iter->data);

		QueueDelete(q);
	}
	{
		QueueDouble *q = malloc(sizeof(QueueDouble));
		QueueNew(q, DataCompare, FreeData);

		QueuePush(q, 1.0);
		QueuePush(q, 2.0);
		QueuePush(q, 3.0);
		QueuePush(q, 4.0);

		QueueIter *iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		QueueClear(q);

		QueuePush(q, 1.25);
		QueuePush(q, 2.25);
		QueuePush(q, 3.25);
		QueuePush(q, 4.25);
		QueuePush(q, 5.25);

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		double *five = QueueTop(q);
		*five = 6.25;

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		QueueDelete(q);
	}
	{
		QueueString *q = malloc(sizeof(QueueString));
		QueueNew(q, StringCompare, FreeString);

		QueuePush(q, "111");
		QueuePush(q, "211");
		QueuePush(q, "311");
		QueuePush(q, "411");

		QueueIter *iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%s ", *(char **)iter->data);

		QueueClear(q);

		QueuePush(q, "111");
		QueuePush(q, "211");
		QueuePush(q, "311");
		QueuePush(q, "411");
		QueuePush(q, "511");

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%s ", *(char **)iter->data);

		char **five = QueueTop(q);
		*five = "611";

		iter = QueueIterator(q);
		while (QueueNext(q, iter))
			printf("%s ", *(char **)iter->data);

		QueueDelete(q);
	}
	printf("\n-----------------Queue Test End---------------------------\n");
}
void testStack(unsigned int size)
{
	printf("-----------------Stack Test Start--------------------------\n");
	{
		StackInt *q = malloc(sizeof(StackInt));
		StackNew(q, DataCompare, FreeData);

		StackPush(q, 1);
		StackPush(q, 2);
		StackPush(q, 3);
		StackPush(q, 4);

		StackIter *iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%d ", *(int *)iter->data);

		StackClear(q);

		StackPush(q, 1);
		StackPush(q, 2);
		StackPush(q, 3);
		StackPush(q, 4);
		StackPush(q, 5);

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%d ", *(int *)iter->data);

		int *five = StackTop(q);
		*five = 6;

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%d ", *(int *)iter->data);

		StackDelete(q);
	}
	{
		StackDouble *q = malloc(sizeof(StackDouble));
		StackNew(q, DataCompare, FreeData);

		StackPush(q, 1.0);
		StackPush(q, 2.0);
		StackPush(q, 3.0);
		StackPush(q, 4.0);

		StackIter *iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		StackClear(q);

		StackPush(q, 1.25);
		StackPush(q, 2.25);
		StackPush(q, 3.25);
		StackPush(q, 4.25);
		StackPush(q, 5.25);

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		double *five = StackTop(q);
		*five = 6.25;

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%lf ", *(double *)iter->data);

		StackDelete(q);
	}
	{
		StackString *q = malloc(sizeof(StackString));
		StackNew(q, StringCompare, FreeString);

		StackPush(q, "111");
		StackPush(q, "211");
		StackPush(q, "311");
		StackPush(q, "411");

		StackIter *iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%s ", *(char **)iter->data);

		StackClear(q);

		StackPush(q, "111");
		StackPush(q, "211");
		StackPush(q, "311");
		StackPush(q, "411");
		StackPush(q, "511");

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%s ", *(char **)iter->data);

		char **five = StackTop(q);
		*five = (char *) "611";

		iter = StackIterator(q);
		while (StackNext(q, iter))
			printf("%s ", *(char **)iter->data);

		StackDelete(q);
	}
	printf("\n-----------------Stack Test End----------------------------\n");
}
void testList(unsigned int size)
{
	printf("-----------------List Test Start---------------------------\n");
	{
		LinkedListInt *ll = malloc(sizeof(LinkedListInt));
		LinkedListNew(ll, DataCompare, FreeData);

		LinkedListInsertAtHead(ll, 0);
		LinkedListInsertAtHead(ll, 1);
		LinkedListInsertAtTail(ll, 9);
		LinkedListInsertAtTail(ll, 2);
		LinkedListInsertAtTail(ll, 3);
		LinkedListInsertAtTail(ll, 4);
		LinkedListInsertAtTail(ll, 5);
		LinkedListInsertAtTail(ll, 9);
		LinkedListInsertAtTail(ll, 9);

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%d ", *(int*)LinkedListAt(ll, i));
		printf("\n");

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

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%d ", *(int*)LinkedListAt(ll, i));
		printf("\n");

		int index = LinkedListGetIndex(ll, 9);
		printf("%d\n", index);

		LinkedListClear(ll);

		LinkedListInsertAtTail(ll, 9);
		LinkedListInsertAtTail(ll, 9);

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%d ", *(int*)LinkedListAt(ll, i));
		printf("\n");
		LinkedListDelete(ll);
	}
	{
		LinkedListDouble *ll = malloc(sizeof(LinkedListDouble));
		LinkedListNew(ll, DataCompare, FreeData);

		LinkedListInsertAtHead(ll, 0.25);
		LinkedListInsertAtHead(ll, 1.25);
		LinkedListInsertAtTail(ll, 9.25);
		LinkedListInsertAtTail(ll, 2.25);
		LinkedListInsertAtTail(ll, 3.25);
		LinkedListInsertAtTail(ll, 4.25);
		LinkedListInsertAtTail(ll, 5.25);
		LinkedListInsertAtTail(ll, 9.25);
		LinkedListInsertAtTail(ll, 9.25);

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%lf ", *(double*)LinkedListAt(ll, i));
		printf("\n");

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

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%lf ", *(double*)LinkedListAt(ll, i));
		printf("\n");

		int index = LinkedListGetIndex(ll, 9.25);
		printf("%d\n", index);

		LinkedListClear(ll);

		LinkedListInsertAtTail(ll, 9);
		LinkedListInsertAtTail(ll, 9);

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%lf ", *(double*)LinkedListAt(ll, i));
		printf("\n");
		LinkedListDelete(ll);
	}
	{
		LinkedListString *ll = malloc(sizeof(LinkedListString));
		LinkedListNew(ll, StringCompare, FreeString);

		LinkedListInsertAtHead(ll, "0.25");
		LinkedListInsertAtHead(ll, "1.25");
		LinkedListInsertAtTail(ll, "9.25");
		LinkedListInsertAtTail(ll, "2.25");
		LinkedListInsertAtTail(ll, "3.25");
		LinkedListInsertAtTail(ll, "4.25");
		LinkedListInsertAtTail(ll, "5.25");
		LinkedListInsertAtTail(ll, "9.25");
		LinkedListInsertAtTail(ll, "9.25");

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%s ", *(char**)LinkedListAt(ll, i));
		printf("\n");

		LinkedListClear(ll);

		LinkedListInsertAtTail(ll, "9.25");
		LinkedListInsertAtTail(ll, "2.25");
		LinkedListInsertAtTail(ll, "3.25");
		LinkedListInsertAtTail(ll, "4.25");
		LinkedListInsertAtTail(ll, "5.25");
		LinkedListInsertAtTail(ll, "9.25");
		LinkedListInsertAtTail(ll, "9.25");
		LinkedListReplace(ll, "9.25", "1.25");
		LinkedListReplaceAll(ll, "9.25", "1.25");

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%s ", *(char**)LinkedListAt(ll, i));
		printf("\n");

		int index = LinkedListGetIndex(ll, "9.25");
		printf("%d\n", index);

		LinkedListClear(ll);

		LinkedListInsertAtTail(ll, "9.25");
		LinkedListInsertAtTail(ll, "9.25");

		for (unsigned int i = 0; i < LinkedListSize(ll); i++)
			printf("%s ", *(char**)LinkedListAt(ll, i));
		printf("\n");

		LinkedListDelete(ll);
	}
	printf("\n-----------------List Test End-----------------------------\n");
}
void testQuickSort(unsigned int size)
{
	printf("-----------------Quick Sort Start--------------------------\n");
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

	QuickSort(arr, sizeof(unsigned int), 0, size-1, DataCompare, MemorySwap);

	printf("After Sorting the Array : ");

	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n");

	printf("-----------------Quick Sort End----------------------------\n");
}
void testMergeSort(unsigned int size)
{
	printf("-----------------Merge Sort Start--------------------------\n");
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

	MergeSort(arr, 4, 0, size-1, DataCompare, MemorySwap);

	printf("After Sorting the Array : ");

	for (unsigned int i = 0; i < size; i++)
		printf("%u ", arr[i]);

	printf("\n");
	printf("-----------------Merge Sort End----------------------------\n");
}
void testMap()
{
	printf("---------------------Maps Start----------------------------\n");
	{
		MapInt *m = malloc(sizeof(Map));
		MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

		MapSet(m, 0, 21);
		MapSet(m, 2, 15);
		MapSet(m, 3, 15);
		MapSet(m, 4, 15);

		MapIter *iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%d -> %d, HASH: %d \n", *(int *)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		MapSet(m, 5, 43);

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%d -> %d, HASH: %d \n", *(int *)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		void *age = MapGet(m, 2);
		*(int *)age = 16;

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%d -> %d, HASH: %d \n", *(int *)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		MapDelete(m);
	}
	{
		MapDouble *m = malloc(sizeof(Map));
		MapNew(m, HashFunctionInt, LinearProbing, DataCompare, FreeData, FreeData);

		MapSet(m, 1.0, 21.25);
		MapSet(m, 2.0, 15.25);
		MapSet(m, 3.0, 15.25);
		MapSet(m, 4.0, 15.25);

		MapIter *iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%lf -> %lf, HASH: %d \n", *(double *)iter->node.key,
				   *(double *)iter->node.value, iter->keyindex);

		MapSet(m, 5.0, 43.0);

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%lf -> %lf, HASH: %d \n", *(double *)iter->node.key,
				   *(double *)iter->node.value, iter->keyindex);

		void *age = MapGet(m, 2.0);
		*(double *)age = 16.00;

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%lf -> %lf, HASH: %d \n", *(double *)iter->node.key,
				   *(double *)iter->node.value, iter->keyindex);

		MapDelete(m);
	}
	{
		MapStringInt *m = malloc(sizeof(Map));
		MapNew(m, HashFunctionStr, LinearProbing, StringCompare, FreeString, FreeData);

		MapSet(m, "Muneeb\0", 21);
		MapSet(m, "Moiz\0", 15);
		MapSet(m, "Moaaz\0", 45);
		MapSet(m, "Arif\0", 75);

		MapIter *iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%s -> %d, HASH: %d \n", *(char **)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		MapSet(m, "Kashif\0", 43);

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%s -> %d, HASH: %d \n", *(char **)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		void *age = MapGet(m, "Moiz\0");
		*(int *)age = 16;

		iter = MapIterator(m);
		while (MapNext(m, iter))
			printf("%s -> %d, HASH: %d \n", *(char **)iter->node.key,
				   *(int *)iter->node.value, iter->keyindex);

		MapDelete(m);
	}

	printf("---------------------Maps End------------------------------\n");
}

void testMatrix()
{
	printf("---------------------Matrix Start--------------------------\n");
	Matrix* a = MatrixIdentity(4);
	PrintMatrix(a, "%lf\t");
	Matrix* i = MatrixZero(1, 4);
	PrintMatrix(i, "%lf\t");
	Matrix* r = MatrixRandom(4, 5, 0, 1);
	PrintMatrix(r, "%lf\t");
	Matrix* s = MatrixSquare(1);
	PrintMatrix(s, "%lf\t");
	Matrix* sr = MatrixSquareRandom(5, -1., 10.);
	PrintMatrix(sr, "%lf\t");
	Matrix* o = MatrixOne(9, 9);
	PrintMatrix(o, "%lf\t");
	Matrix* n = MatrixN(3, 12, 0.891231);
	PrintMatrix(n, "%lf\t");

	{
		double values[] = { 1., 3., 5., 9., 1., 3., 1., 7., 4., 3., 9., 7., 5., 2., 0., 9. };
		Matrix* ref = MatrixFrom(4, 4, 16, values);
		PrintMatrix(ref, "%lf\t");
		Matrix* re = MatrixRowEchelonGet(ref);
		PrintMatrix(re, "%lf\t");
	}
	{
		double values[] = { 0., -3., -6., 4., 9., -1., -2., -1., 3., 1., -2., -3., 0., 3., -1., 1., 4., 5., -9., -7., };
		Matrix* ref = MatrixFrom(4, 5, 20, values);
		PrintMatrix(ref, "%lf\t");
		Matrix* re = MatrixReducedRowEchelonGet(ref);
		PrintMatrix(re, "%lf\t");
	}
	{
		double values[] = { 1. };
		Matrix* m = MatrixFrom(1, 1, 1, values);
		Matrix* bm = MatrixBroadcastRowsAndColumns(m, 10, 10);
		PrintMatrix(bm, "%.1f\t");
	}
	{
		double values[] = { 0., 10., 20., 30. };
		double values1[] = { 1., 2., 3. };
		Matrix* m = MatrixFrom(4, 1, 4, values);
		Matrix* m1 = MatrixFrom(1, 3, 3, values1);
		Matrix* res = MatrixAddWithBroadcast(m, m1);
		PrintMatrix(res, "%.1f\t");
	}
	printf("---------------------Matrix End--------------------------\n");
}

int main()
{
	testStack(100);
	testQueue(100);
	testMap();
	testVector(100);
	testBinarySearch();
	testBubbleSort();
	testLinearSearch();
	testList(25);
	testMatrix();
	testQuickSort(200); // don't works well for values greater than 200
	testMergeSort(200); // don't works well for values greater than 200
}


