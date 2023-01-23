#include "../includes/c_stack.h"
#include <stdlib.h>

static void* getPointer(void* elems, unsigned int index,
	unsigned nbytes)
{
	return (void*)((char*)elems + index * nbytes);
}

void StackNew_(StackBase* s, unsigned int elem_size,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elem_size > 0);
	s->elemsize = elem_size;
	s->logiclen = 0;
	s->alloclen = 4;
	s->elems = malloc(s->alloclen * s->elemsize);
	s->DataCmp = DataCmp;
	s->FreeFunc = FreeFunc;
	ASSERT(s->elems != NULL);
}

void StackPush_(StackBase* s, void* elem)
{
	if (s->logiclen == s->alloclen){
		// resize
		s->alloclen *= 2;
		s->elems = realloc(s->elems, s->alloclen * s->elemsize);
		ASSERT(s->elems != NULL);
	}

	void* target = getPointer(s->elems, s->logiclen, s->elemsize);
	MemoryCopy(target, elem, s->elemsize);
	s->logiclen++;
}

void* StackPop_(StackBase* s)
{
	ASSERT(s->logiclen > 0); 
	if (s->logiclen == (s->alloclen / 2))
	{
		s->alloclen = s->alloclen / 2;
		s->elems = realloc(s->elems, s->alloclen * s->elemsize);
		ASSERT(s->elems != NULL);
	}
	void* target = getPointer(s->elems, s->logiclen--, s->elemsize);
	return target;
}

void* StackTop_(StackBase* s)
{
	ASSERT(s->logiclen > 0);
	void* target = getPointer(s->elems, s->logiclen-1, s->elemsize);
	return target;
}

void StackClear_(StackBase* s)
{
	s->logiclen = 0;
}

void StackDelete_(StackBase* s)
{
	ASSERT(s->elems != NULL);
	s->FreeFunc(s->elems);
	s->alloclen = 0;
	s->logiclen = 0;
	s->elemsize = 0;
}

StackIter* StackIterator_(StackBase* s)
{
	ASSERT(s);
	if (s->logiclen == 0) return NULL;
	void* n = malloc(sizeof(StackIter));
	((StackIter*)n)->data = malloc(s->elemsize);
	((StackIter*)n)->index = s->logiclen;
	return ((StackIter*)n);
}

StackIter* StackNext_(StackBase* s, StackIter* stackiter)
{
	ASSERT(s);
	if (s->logiclen == 0 || stackiter->index == 0) { s->FreeFunc(stackiter); return NULL; };
	MemoryCopy(stackiter->data, getPointer(s->elems, stackiter->index - 1,
		s->elemsize), s->elemsize);
	stackiter->index = stackiter->index - 1;
	return stackiter;
}

unsigned int StackSize_(StackBase* s)
{
	return s->logiclen;
}