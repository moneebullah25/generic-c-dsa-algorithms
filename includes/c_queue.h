#ifndef _C_QUEUE_HEADER_
#define _C_QUEUE_HEADER_

#include "c_helper.h"

typedef struct {
	void* elems; unsigned int elemsize; unsigned int logicallen; unsigned int alloclen;
	void* front; void* rear;
}Queue;

void QueueNew(Queue* q, unsigned int elem_size);
void QueueDispose(Queue* q, void(*freefunc)(void* elems));
void QueuePush(Queue* q, void* elem);
void QueuePop(Queue* q, void* output);
void QueueTop(Queue* q, void* output);
unsigned int QueueSize(Queue* q);

#endif