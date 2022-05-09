#include "c_vector.h"


void VectorNew(Vector*v, unsigned int elem_size)
{
	ASSERT(elem_size > 0);
	v->elemsize = elem_size;
	v->logicallen = 0;
	v->alloclen = 4;
	v->elems = malloc(v->alloclen * v->elemsize);
	ASSERT(v->elems != NULL);
}

void VectorPushBack(Vector* v, void* elem)
{
	if (v->logicallen == v->alloclen)
	{// resize
		v->alloclen = v->alloclen * 2;
		v->elems = realloc(v->elems, v->alloclen * v->elemsize);
		ASSERT(v->elems != NULL);
	}
	void* target = (void*)((char*)v->elems + v->logicallen * v->elemsize);
	memory_copy(target, elem, v->elemsize);
	v->logicallen++;
}

void VectorAt(Vector* v, unsigned int index, void* output)
{
	ASSERT(index >= 0 && index < v->logicallen);
	void* target = (void*)((char*)v->elems + index * v->elemsize);
	memory_copy(output, target, v->elemsize);
}

void VectorDispose(Vector* v, void(*freefunc)(void* elems))
{
	ASSERT(v->elems != NULL);
	freefunc(v->elems);
	v->logicallen = 0;
	v->alloclen = 0;
	v->elemsize = 0;
	v->elems = NULL;
}

unsigned int VectorSize(Vector* v)
{
	return v->logicallen;
}