#include "../includes/c_vector.h"
#include <stdlib.h>

static void* getPointer(void* elems, unsigned int index, 
	unsigned nbytes)
{
	return (void*)((char*)elems + index * nbytes);
}

void VectorNew_(VectorBase*v, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elemsize > 0);
	v->elemsize = elemsize;
	v->logiclen = 0;
	v->alloclen = 4;
	v->DataCmp = DataCmp;
	v->FreeFunc = FreeFunc;
	v->elems = malloc(v->alloclen * v->elemsize);
	ASSERT(v->elems != NULL);
}

void VectorPush_(VectorBase* v, void* data)
{
	if (v->logiclen == v->alloclen)
	{// resize
		v->alloclen = v->alloclen * 2;
		v->elems = realloc(v->elems, v->alloclen * v->elemsize);
		ASSERT(v->elems != NULL);
	}
	void* target = getPointer(v->elems, v->logiclen, v->elemsize);
	MemoryCopy(target, data, v->elemsize);
	v->logiclen++;
}

void* VectorAt_(VectorBase* v, unsigned int index)
{
	ASSERT(index >= 0 && index < v->logiclen);
	void* target = getPointer(v->elems, index, v->elemsize);
	return target;
}

void* VectorGet_(VectorBase* v, void* data)
{
	ASSERT(v && data);
	for (unsigned int i = 0; i < v->logiclen; i++){
		if (v->DataCmp(getPointer(v->elems, i, v->elemsize),
			data, v->elemsize) == 0)
			return getPointer(v->elems, i, v->elemsize);
	}
	return NULL;
}

void VectorClear_(VectorBase* v)
{
	v->logiclen = 0;
}

void VectorDelete_(VectorBase* v)
{
	v->FreeFunc(v->elems);
	v->FreeFunc(v);
}

VectorIter* VectorIterator_(VectorBase* v)
{
	ASSERT(v);
	if (v->logiclen == 0) return NULL;
	void* n = malloc(sizeof(VectorIter));
	((VectorIter*)n)->data = malloc(v->elemsize);
	((VectorIter*)n)->index = -1;
	return ((VectorIter*)n);
}

VectorIter* VectorNext_(VectorBase* v, VectorIter* veciter)
{
	ASSERT(v && veciter);
	if (v->logiclen == 0 || veciter->index + 1 == v->logiclen){ v->FreeFunc(veciter->data); return NULL; };
	MemoryCopy(veciter->data, getPointer(v->elems, veciter->index + 1,
		v->elemsize), v->elemsize);
	veciter->index = veciter->index + 1;
	return veciter;
}

unsigned int VectorSize_(VectorBase* v)
{
	return v->logiclen;
}