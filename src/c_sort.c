﻿#include "../includes/c_sort.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

void *LinearSearch(void *key, void *base, unsigned int nelems, unsigned int elemsize, int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes))
{
	for (unsigned int i = 0; i < nelems; i++)
	{
		void *elemaddr = (char *)(base) + (i * elemsize);
		if (MemCmp(elemaddr, key, elemsize) == 0)
			return elemaddr;
	}
	return NULL;
}

void *BinarySearch(void *key, void *base, unsigned int s, unsigned int n, unsigned int elemsize,
				   int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes))
{
	if (s < n)
	{
		unsigned int middle = (s + n) / 2;
		void *elemaddr = (void *)((char *)(base) + (middle * elemsize));
		if (MemCmp(elemaddr, key, elemsize) == 0)
			return elemaddr;
		else if (MemCmp(elemaddr, key, elemsize) < 0)
			return BinarySearch(key, base, middle + 1, n, elemsize, MemCmp);
		else
			return BinarySearch(key, base, s, middle, elemsize, MemCmp);
	}
	return NULL;
}

void BubbleSort(void *base, unsigned int elemsize, unsigned int n, 
	int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes),
	void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes))
{
	bool is_sort;
	do
	{
		is_sort = true;
		for (unsigned int j = 0; j < n - 1; j++)
		{
			void *elemaddr = (char *)(base) + (j * elemsize);
			void *elemaddr1 = (char *)(base) + ((j + 1) * elemsize);
			if (MemCmp(elemaddr, elemaddr1, elemsize) > 0)
			{
				is_sort = false;
				MemSwap(elemaddr, elemaddr1, elemsize);
			}
		}
	} while (!is_sort);
}

int partition(void *base, int elemsize, int low, int high, 
	int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes),
	void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes))
{

	void *pivot = (void *)((char *)base + elemsize * high);
	int i = (low - 1);

	for (long int j = low; j < high; j++)
	{
		if (MemCmp((void *)((char *)base + elemsize * j), pivot, elemsize) <= 0)
		{
			i++;
			MemSwap((void *)((char *)base + elemsize * i), (void *)((char *)base + elemsize * j), elemsize);
		}
	}

	MemSwap((void *)((char *)base + elemsize * (i + 1)), (void *)((char *)base + elemsize * (high)), elemsize);

	return (i + 1);
}

void QuickSort(void *base, int elemsize, int low, int high, 
	int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes),
	void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes))
{
	if (low < high)
	{

		// find the pivot element such that
		// elements smaller than pivot are on left of pivot
		// elements greater than pivot are on right of pivot
		int pi = partition(base, elemsize, low, high, MemCmp, MemSwap);

		// recursive call on the left of pivot
		QuickSort(base, elemsize, low, pi - 1, MemCmp, MemSwap);

		// recursive call on the right of pivot
		QuickSort(base, elemsize, pi + 1, high, MemCmp, MemSwap);
	}
}

void merge(void *base, unsigned int elemsize, unsigned int p, unsigned int q, unsigned int r, int(*MemCmp)(const void* vp1, const void* vp2, unsigned int nbytes))
{

	// Create L ← A[p..q] and M ← A[q+1..r]
	unsigned int n1 = q - p + 1;
	unsigned int n2 = r - q;

	void *L = malloc(elemsize * n1);
	void *M = malloc(elemsize * n2);

	for (unsigned int i = 0; i < n1; i++)
		MemoryCopy((char *)L + i * elemsize, (char *)base + (p + i) * elemsize, elemsize);
	for (unsigned int j = 0; j < n2; j++)
		MemoryCopy((char *)M + j * elemsize, (char *)base + (q + 1 + j) * elemsize, elemsize);

	// Maintain current index of sub-baseays and main baseay
	unsigned int i, j, k;
	i = 0;
	j = 0;
	k = p;

	// Until we reach either end of either L or M, pick larger among
	// elements L and M and place them in the correct position at A[p..r]
	while (i < n1 && j < n2)
	{
		if (MemCmp((char *)L + i * elemsize, (char *)M + j * elemsize, elemsize) <= 0)
		{
			MemoryCopy((char *)base + k * elemsize, (char *)L + i * elemsize, elemsize);
			i++;
		}
		else
		{
			MemoryCopy((char *)base + k * elemsize, (char *)M + j * elemsize, elemsize);
			j++;
		}
		k++;
	}

	// When we run out of elements in either L or M,
	// pick up the remaining elements and put in A[p..r]
	while (i < n1)
	{
		MemoryCopy((char *)base + k * elemsize, (char *)L + i * elemsize, elemsize);
		i++;
		k++;
	}

	while (j < n2)
	{
		MemoryCopy((char *)base + k * elemsize, (char *)M + j * elemsize, elemsize);
		j++;
		k++;
	}
}

// Divide the baseay into two subbaseays, sort them and merge them
void MergeSort(void* base, unsigned int elemsize, unsigned int l, unsigned int r, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes))
{
	ASSERT(base != NULL && elemsize > 0);
	if (l < r)
	{

		// m is the point where the baseay is divided into two subbaseays
		unsigned int m = l + (r - l) / 2;

		MergeSort(base, elemsize, l, m, MemCmp, MemSwap);
		MergeSort(base, elemsize, m + 1, r, MemCmp, MemSwap);

		// Merge the sorted subbaseays
		merge(base, elemsize, l, m, r, MemCmp);
	}
}