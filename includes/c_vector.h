#ifndef _C_VECTOR_HEADER_
#define _C_VECTOR_HEADER_

#include "c_helper.h"

typedef struct VectorBase{
	void* elems;
	size_t elemsize, logiclen, alloclen;

	int(*DataCmp)(const void *key1, const void *key2, size_t keysize);
	void(*FreeFunc)(void* elems);
} VectorBase;

typedef struct VectorIter{
	void* data;
	size_t index;
}VectorIter;

#define VectorT(T) \
	struct { VectorBase base; T data_; }

#define VectorNew(v, DataCmp, FreeFunc) \
	VectorNew_(&(v)->base, sizeof((v)->data_), DataCmp, FreeFunc)

#define VectorPush(v, data) \
	((v)->data_ = (data), \
	VectorPush_(&(v)->base, &(v)->data_))

#define VectorAt(v, index) \
	VectorAt_(&(v)->base, index)

#define VectorGet(v, data) \
	((v)->data_ = (data), \
	VectorGet_(&(v)->base, &(v)->data_))

#define VectorClear(v) \
	VectorClear_(&(v)->base)

#define VectorDelete(v) \
	VectorDelete_(&(v)->base)

#define VectorIterator(v) \
	VectorIterator_(&(v)->base)

#define VectorNext(v, iter) \
	VectorNext_(&(v)->base, iter)

#define VectorSize(v) \
	VectorSize_(&(v)->base)


void VectorNew_(VectorBase*v, size_t elemsize, 
	int(*DataCmp)(const void *key1, const void *key2, size_t keysize),
	void(*FreeFunc)(void* elems));
void VectorPush_(VectorBase* v, void* data);
void* VectorAt_(VectorBase* v, size_t index);
void* VectorGet_(VectorBase* v, void* data);
void VectorClear_(VectorBase* v);
void VectorDelete_(VectorBase* v);
VectorIter* VectorIterator_(VectorBase* v);
void* VectorNext_(VectorBase* v, VectorIter* veciter);
size_t VectorSize_(VectorBase* v);

typedef VectorT(void*) Vector;
typedef VectorT(double) VectorDouble;
typedef VectorT(float) VectorFloat;
typedef VectorT(int) VectorInt;
typedef VectorT(char*) VectorString;
typedef VectorT(char) VectorChar;
typedef VectorT(bool) VectorBool;

#endif