#ifndef _C_SORT_HEADER_
#define _C_SORT_HEADER_

#include "c_helper.h"

void* LinearSearch(void* key, void* base, unsigned int nelems, unsigned int elemsize, int(*MemCmp)(const void*, const void*, unsigned int));
void* BinarySearch(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, int(*MemCmp)(const void*, const void*, unsigned int));
void BubbleSort(void* base, unsigned int elemsize, unsigned int n, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));
void QuickSort(void* base, int elemsize, int low, int high, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));
void MergeSort(void* base, unsigned int elemsize, unsigned int l, unsigned int r, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));

#endif 
