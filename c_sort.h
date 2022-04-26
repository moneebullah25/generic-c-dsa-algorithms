#ifndef _C_SORT_HEADER_
#define _C_SORT_HEADER_

#include "c_helper.h"

void* LinearSearch(void* key, void* base, unsigned int n, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void* BinarySearch(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void BubbleSort(void* base, unsigned int elemsize, unsigned int n, int(*MemCmp)(void* a, void* b, unsigned int elembytes));

#endif 
