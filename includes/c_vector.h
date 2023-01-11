#ifndef _C_VECTOR_HEADER_
#define _C_VECTOR_HEADER_

#include "c_helper.h"

typedef struct{
	void* elems;
	unsigned int elemsize, logicallen, alloclen;
} Vector;

void VectorNew(Vector*v, unsigned int elem_size);
void VectorPushBack(Vector* v, void* elem);
void VectorAt(Vector* v, unsigned int index, void* output);
void VectorDispose(Vector* v, void(*freefunc)(void* elems));
unsigned int VectorSize(Vector* v);

#endif