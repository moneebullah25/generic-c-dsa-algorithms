#include "../includes/c_stack.h"

void StackNew(Stack* s, unsigned int elem_size)
{
	ASSERT(elem_size > 0);
	s->elemsize = elem_size;
	s->logicallen = 0;
	s->alloclen = 4;
	s->elems = malloc(s->alloclen * s->elemsize);
	ASSERT(s->elems != NULL);
}

void StackDispose(Stack* s, void(*freefunc)(void* elems))
{
	ASSERT(s->elems != NULL);
	freefunc(s->elems);
	s->alloclen = 0;
	s->logicallen = 0;
	s->elemsize = 0;
	s->elems = NULL;
}

void StackPush(Stack* s, void* elem)
{
	if (s->logicallen == s->alloclen){
		// resize
		s->alloclen *= 2;
		s->elems = realloc(s->elems, s->alloclen * s->elemsize);
		ASSERT(s->elems != NULL);
	}

	void* target = (char*)s->elems + s->logicallen * s->elemsize;
	MemoryCopy(target, elem, s->elemsize);
	s->logicallen++;
}

void StackPop(Stack* s, void* output)
{
	ASSERT(s->logicallen > 0); // empty Stack check
	if (s->logicallen == (s->alloclen / 2))
	{
		// Shrink the size to halp
		s->alloclen = s->alloclen / 2;
		s->elems = realloc(s->elems, s->alloclen * s->elemsize);
		ASSERT(s->elems != NULL);
	}
	s->logicallen--;
	void* target = (char*)s->elems + s->logicallen * s->elemsize;
	MemoryCopy(output, target, s->elemsize);
}

void StackTop(Stack* s, void* output)
{
	ASSERT(s->logicallen > 0);
	void* target = (char*)s->elems + s->logicallen * s->elemsize;
	MemoryCopy(output, target, s->elemsize);
}

unsigned int StackSize(Stack* s)
{
	return s->logicallen;
}