#ifndef _C_STACK_HEADER_
#define _C_STACK_HEADER_

#include "c_helper.h"

typedef struct StackBase{
	void* elems; unsigned int elemsize; unsigned int logiclen; unsigned int alloclen;

	int(*DataCmp)(void *key1, void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} StackBase;

typedef struct StackIter{
	void* data;
	unsigned int index;
}StackIter;

#define StackT(T) \
struct { StackBase base; T* ref; T data_; }

#define StackNew(s, DataCmp, FreeFunc) \
	StackNew_(&(s)->base, sizeof((s)->data_), DataCmp, FreeFunc)

#define StackPush(s, data) \
	((s)->data_ = (data), \
	StackPush_(&(s)->base, &(s)->data_))

#define StackPop(s) \
	(s)->ref = StackGet_(&(s)->base, &(s)->data_)

#define StackTop(s) \
	(s)->ref = StackGet_(&(s)->base, &(s)->data_)

#define StackClear(s) \
	StackClear_(&(s)->base)

#define StackDelete(s) \
	StackDelete_(&(s)->base)

#define StackIterator(s) \
	StackIterator_(&(s)->base)

#define StackNext(s, iter) \
	StackNext_(&(s)->base, iter)

#define StackSize(s) \
	StackSize_(&(s)->base)

void StackNew_(StackBase* s, unsigned int elem_size,
	int(*DataCmp)(void *key1, void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
void StackPush_(StackBase* s, void* elem);
void* StackPop_(StackBase* s);
void* StackTop_(StackBase* s);
void StackClear_(StackBase* s);
void StackDelete_(StackBase* s);
StackIter* StackIterator_(StackBase* s);
void* StackNext_(StackBase* s, StackIter* stackiter);
unsigned int StackSize_(StackBase* s);

typedef StackT(void*) Stack;
typedef StackT(double) StackDouble;
typedef StackT(float) StackFloat;
typedef StackT(int) StackInt;
typedef StackT(char*) StackString;
typedef StackT(char) StackChar;
typedef StackT(bool) StackBool;

#endif