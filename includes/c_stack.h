#ifndef _C_STACK_HEADER_
#define _C_STACK_HEADER_

#include "c_helper.h"

typedef struct {
	void* elems; unsigned int elemsize; unsigned int logicallen; unsigned int alloclen;
} Stack;

void StackNew(Stack* s, unsigned int elem_size);
void StackDispose(Stack* s, void(*freefunc)(void* elems));
void StackPush(Stack* s, void* elem);
void StackPop(Stack* s, void* output);
void StackTop(Stack* s, void* output);
unsigned int StackSize(Stack* s);

#endif