#ifndef _C_SORT_HEADER_
#define _C_SORT_HEADER_

#include "c_helper.h"

void* LinearSearch(void* key, void* base, size_t nelems, size_t elemsize, int(*MemCmp)(const void*, const void*, size_t));
void* BinarySearch(void* key, void* base, size_t s, size_t n, size_t elemsize, int(*MemCmp)(const void*, const void*, size_t));
void BubbleSort(void* base, size_t elemsize, size_t n, 
    int(*MemCmp)(const void*, const void*, size_t),
    void(*MemSwap)(void *vp1, void *vp2, size_t nbytes));
void QuickSort(void* base, int elemsize, int low, int high, 
    int(*MemCmp)(const void*, const void*, size_t),
    void(*MemSwap)(void *vp1, void *vp2, size_t nbytes));
void MergeSort(void* base, size_t elemsize, size_t l, size_t r, 
    int(*MemCmp)(const void*, const void*, size_t),
    void(*MemSwap)(void *vp1, void *vp2, size_t nbytes));

#endif 
