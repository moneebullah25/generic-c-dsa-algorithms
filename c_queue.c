#include "c_queue.h"

void QueueNew(Queue* q, unsigned int elem_size)
{
	ASSERT(elem_size > 0);
	q->elemsize = elem_size;
	q->logicallen = 0;
	q->alloclen = 4;
	q->elems = malloc(q->alloclen * q->elemsize);
	q->front = q->elems;
	q->rear = q->elems;
	ASSERT(q->elems != NULL);
}

void QueueDispose(Queue* q, void(*freefunc)(void* elems))
{
	ASSERT(q->elems != NULL);
	freefunc(q->elems);
	q->logicallen = 0;
	q->alloclen = 0;
	q->elemsize = 0;
	q->front = q->rear = q->elems = NULL;
}

void QueuePush(Queue* q, void* elem)
{
	if (q->logicallen == q->alloclen || 
		q->rear == (void *)((char *)q->elems + q->alloclen * q->elemsize)){
		// resize
		q->alloclen *= 2;
		unsigned int frontOffset = (unsigned int)((char *)q->front - (char *)q->elems);
		unsigned int rearOffset = (unsigned int)((char *)q->rear - (char *)q->elems);
		q->elems = realloc(q->elems, q->alloclen * q->elemsize);
		ASSERT(q->elems != NULL);
		// modifying pointer in case new address
		q->front = (void *)((char *)q->elems + frontOffset);
		q->rear = (void *)((char *)q->elems + rearOffset);
	}
	MemoryCopy(q->rear, elem, q->elemsize);
	q->logicallen++;
	q->rear = (void*)((char*)(q->rear) + q->elemsize);
}

void QueuePop(Queue* q, void* output)
{
	ASSERT(q->logicallen > 0); // empty Queue check
	if (q->logicallen == (q->alloclen / 2))
	{
		// shrink size by half
		q->alloclen = q->alloclen / 2;
		unsigned int frontOffset = (unsigned int)((char *)q->front - (char *)q->elems);
		unsigned int rearOffset = (unsigned int)((char *)q->rear - (char *)q->elems);
		for (unsigned int i = 0; i < q->logicallen; i++)
		{
			MemoryCopy((char *)q->elems + i * q->elemsize,
				(char *)q->front + i * q->elemsize, q->elemsize);
		}
		q->elems = realloc(q->elems, q->alloclen * q->elemsize);
		ASSERT(q->elems != NULL);
		// modifying pointer same address always shrinking only
		q->front = q->elems;
		q->rear = (void *)((char *)q->elems + q->alloclen * q->elemsize);
	}
	q->logicallen--;
	MemoryCopy(output, q->front, q->elemsize);
	q->front = (void*)((char*)(q->front) + q->elemsize);
	if (q->front == (void*)((char*)q->elems + q->alloclen * q->elemsize))
	{
		// set the q->front to start of array
		q->front = q->elems;
	}
}

void QueueTop(Queue* q, void* output)
{
	ASSERT(q->logicallen > 0); // empty Queue check
	MemoryCopy(output, q->front, q->elemsize);
}

unsigned int QueueSize(Queue* q)
{
	return q->logicallen;
}