#ifndef _C_SORT_HEADER_
#define _C_SORT_HEADER_

#include "c_helper.h"

#define LinearSearch(key, base, nelems, MemCmp) \
	LinearSearch_(key, base, nelems, sizeof(key), MemCmp)

#define BinarySearch(key, base, nelems, MemCmp) \
	BinarySearch_(key, base, 0, nelems, sizeof(key), MemCmp)

#define QuickSort(base, elemsize, nelems, MemCmp) \
	QuickSort_(base, elemsize, 0, nelems, MemCmp)

#define MergeSort(base, elemsize, nelems, MemCmp) \
	MergeSort_(base, elemsize, 0, nelems, MemCmp)

void* LinearSearch_(void* key, void* base, unsigned int nelems, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void* BinarySearch_(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void BubbleSort(void* base, unsigned int elemsize, unsigned int n, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void QuickSort_(void* base, int elemsize, int low, int high, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
void MergeSort_(void* base, unsigned int elemsize, unsigned int l, unsigned int r, int(*MemCmp)(void * a, void * b, unsigned int elembytes));


#endif 
