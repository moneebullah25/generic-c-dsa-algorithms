
#include <stdio.h>
#include <stdlib.h>

#include "c_vector.h"
#include "c_queue.h"
#include "c_stack.h"
#include "c_sort.h"
#include "c_list.h"

int main()
{
	// LinearSearch with generic c method
	int arr[8] = { 1, 12, 3, 9, 5, 6, 7, 8 };
	int nine = 9;
	void* find_nine = LinearSearch((void*)&nine, (void*)&arr, (int)8, (int)sizeof(int), &data_compare);
	printf("%d \n", *((int*)(find_nine)));

	char* str[5] = { "abc\0", "ABC\0", "ab\0", "aad\0", "abcd\0" };
	char* abcd = "abcd\0";
	// Address returned by LinearSearch will be 2 hops away
	char* find_abcd = (char*)LinearSearch(&abcd, &str, 5, sizeof(char*), &string_compare);
	printf("%s \n", *(char**)find_abcd);

	// Vector
	Vector* a=malloc(sizeof(Vector));
	VectorNew(a, sizeof(unsigned int));
	for (unsigned int i = 400; i > 0; i--)
	{
		VectorPushBack(a, &i);
	}
	printf("Sorting\n");
	BubbleSort(a->elems, a->elemsize, a->logicallen, &data_compare);
	unsigned int out;
	for (unsigned int i = 0; i < 400; i++)
	{
        VectorAt(a, i, &out);
		printf("%d ", out);
	}
    VectorDispose(a, &data_free);

    // Queue
    Queue* q = malloc(sizeof(Queue));
	QueueNew(q, sizeof(unsigned int));
    for (unsigned int i = 0; i < 2000000; i++)
	{
		QueuePush(q, &i);
	}
	for (unsigned int i = 0; i < 2000000; i++)
	{
        QueuePop(q, &out);
		//printf("%d ", out);
	}
    QueueDispose(q, &data_free);

    // Stack
    Stack* s = malloc(sizeof(Stack));
	StackNew(s, sizeof(unsigned int));
    for (unsigned int i = 0; i < 2000000; i++)
	{
		StackPush(s, &i);
	}
	for (unsigned int i = 0; i < 2000000; i++)
	{
        StackPop(s, &out);
		//printf("%d ", out);
	}
    StackDispose(s, &data_free);

    LinkedList* ll = malloc(sizeof(LinkedList));
    LinkedListNew(ll, 4);
    for (unsigned int i = 0 ; i < 2000000; i++)
    {
        LinkedListInsert(ll, &i);
    }
	// Changing Values
	int val = 9999;
	for (unsigned int i = 0; i < 2000000; i+=10)
	{
		LinkedListReplace(ll, &i, &val, &data_compare);
	}
	// Printing Values
	for (unsigned int i = 0; i < 2000000; i++)
	{
		printf("%x",LinkedListAt(ll, i)->elem);
	}

}
