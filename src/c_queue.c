#include "../includes/c_queue.h"
#include <stdlib.h>

void QueueNew_(QueueBase* q, unsigned int elem_size,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elem_size > 0);
	q->elemsize = elem_size;
	q->logiclen = 0;
	q->alloclen = 4;
	q->elems = malloc(q->alloclen * q->elemsize);
	q->front = q->elems;
	q->rear = q->elems;
	q->DataCmp = DataCmp;
	q->FreeFunc = FreeFunc;
	ASSERT(q->elems != NULL);
}

void QueuePush_(QueueBase* q, void* elem)
{
	if (q->logiclen == q->alloclen || 
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
	q->logiclen++;
	q->rear = (void*)((char*)(q->rear) + q->elemsize);
}

void* QueuePop_(QueueBase* q)
{
	ASSERT(q->logiclen > 0); // empty QueueBase check
	if (q->logiclen == (q->alloclen / 2))
	{
		// shrink size by half
		q->alloclen = q->alloclen / 2;
		for (unsigned int i = 0; i < q->logiclen; i++)
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
	q->logiclen--;
	void* output = malloc(q->elemsize);
	MemoryCopy(output, q->front, q->elemsize);
	q->front = (void*)((char*)(q->front) + q->elemsize);
	if (q->front == (void*)((char*)q->elems + q->alloclen * q->elemsize))
	{
		// set the q->front to start of array
		q->front = q->elems;
	}
	return output;
}

void* QueueTop_(QueueBase* q)
{
	ASSERT(q->logiclen > 0); // empty QueueBase check
	return q->front;
}

void QueueClear_(QueueBase* q)
{
	q->front = q->elems;
	q->rear = q->elems;
	q->logiclen = 0;
}

void QueueDelete_(QueueBase* q)
{
	ASSERT(q->elems != NULL);
	q->FreeFunc(q->elems);
	q->logiclen = 0;
	q->alloclen = 0;
	q->elemsize = 0;
	q->front = q->rear = q->elems = NULL;
}

QueueIter* QueueIterator_(QueueBase* q)
{
	ASSERT(q);
	if (q->logiclen == 0) return NULL;
	void* n = malloc(sizeof(QueueIter));
	((QueueIter*)n)->data = malloc(q->elemsize);
	((QueueIter*)n)->prevfront = q->front;
	((QueueIter*)n)->index = 0;
	return ((QueueIter*)n);
}

QueueIter* QueueNext_(QueueBase* q, QueueIter* queueiter)
{
	ASSERT(q);
	if (q->logiclen == 0 || queueiter->index == q->logiclen) { q->FreeFunc(queueiter); return NULL; };
	MemoryCopy(queueiter->data, queueiter->prevfront, q->elemsize);
	queueiter->index++;
	queueiter->prevfront = (void*)((char*)queueiter->prevfront + q->elemsize);
	if (queueiter->prevfront == (void*)((char*)q->elems + q->alloclen * q->elemsize))
		queueiter->prevfront = q->elems;
	return queueiter;
}

unsigned int QueueSize_(QueueBase* q)
{
	return q->logiclen;
}