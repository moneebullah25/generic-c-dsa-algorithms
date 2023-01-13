#ifndef _C_VECTOR_HEADER_
#define _C_VECTOR_HEADER_

#include "c_helper.h"

typedef struct VectorBase{
	void* elems;
	unsigned int elemsize, logiclen, alloclen;

	int(*DataCmp)(void *key1, void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} VectorBase;

typedef struct VectorIter{
	void* data;
	unsigned int index;
}VectorIter;

#define VectorT(T) \
	struct { VectorBase base; T* ref; T data_; }

#define VectorNew(v, DataCmp, FreeFunc) \
	VectorNew_(&(v)->base, sizeof((v)->data_), DataCmp, FreeFunc)

#define VectorPush(v, data) \
	((v)->data_ = (data), \
	VectorPush_(&(v)->base, &(v)->data_))

#define VectorAt(v, index) \
	(v)->ref = VectorAt_(&(v)->base, index)

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


void VectorNew_(VectorBase*v, unsigned int elemsize, 
	int(*DataCmp)(void *key1, void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
void VectorPush_(VectorBase* v, void* data);
void* VectorAt_(VectorBase* v, unsigned int index);
void* VectorGet_(VectorBase* v, void* data);
void VectorClear_(VectorBase* v);
void VectorDelete_(VectorBase* v);
VectorIter* VectorIterator_(VectorBase* v);
VectorIter* VectorNext_(VectorBase* v, const VectorIter* mapiter);
unsigned int VectorSize_(VectorBase* v);

typedef VectorT(void*) Vector;
typedef VectorT(double) VectorDouble;
typedef VectorT(float) VectorFloat;
typedef VectorT(int) VectorInt;
typedef VectorT(char*) VectorString;
typedef VectorT(char) VectorChar;
typedef VectorT(bool) VectorBool;

#endif