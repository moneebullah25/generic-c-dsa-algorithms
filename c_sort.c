#include "c_sort.h"

void* LinearSearch(void* key, void* base, unsigned int n, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	for (unsigned int i = 0; i < n; i++)
	{
		void* elemaddr = (char*)(base)+(i * elemsize);
		if (MemCmp(elemaddr, key, elemsize) == 0)
			return elemaddr;
	}
	return NULL;
}

void* BinarySearch(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, 
	int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	if (s < n){
		unsigned int middle = (s + n) / 2;
		void* elemaddr = (void*)((char*)(base)+(middle * elemsize));
		if (MemCmp(elemaddr, key, elemsize) == 0)
			return elemaddr;
		else if (MemCmp(elemaddr, key, elemsize) < 0)
			return BinarySearch(key, base, middle + 1, n, elemsize, MemCmp);
		else 
			return BinarySearch(key, base, s, middle, elemsize, MemCmp);
	}
	return NULL;
}

void BubbleSort(void* base, unsigned int elemsize, unsigned int n, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	bool is_sort;
	do
	{
		is_sort = true;
		for (unsigned int j = 0; j < n - 1; j++)
		{
			void* elemaddr = (char*)(base)+(j * elemsize);
			void* elemaddr1 = (char*)(base)+((j + 1) * elemsize);
			if (MemCmp(elemaddr, elemaddr1, elemsize) > 0)
			{
				is_sort = false;
				memory_swap(elemaddr, elemaddr1, elemsize);
			}
		}
	} while (!is_sort);

}

static long int partition(void* elems, unsigned int elemsize, unsigned int low, unsigned int high, int(*MemCmp)(void* a, void* b, unsigned int elembytes)) {

	void* pivot = (void*)((char*)elems + elemsize * high);
	unsigned int i = (low);

	for (long int j = low; j < high; j++) {
		if (MemCmp((void*)((char*)elems + elemsize * j), pivot, elemsize) <= 0) {
			memory_swap((void*)((char*)elems + elemsize*i), (void*)((char*)elems + elemsize * j), elemsize);
			i++;
		}
	}

	memory_swap((void*)((char*)elems + elemsize*(i)), (void*)((char*)elems + elemsize*(high)), elemsize);

	return (i);
}

void QuickSort(void* elems, unsigned int elemsize, unsigned int low, unsigned int high, int(*MemCmp)(void* a, void* b, unsigned int elembytes)) {
	ASSERT(elems != NULL && elemsize > 0);
	if (low < high - 1) {
		unsigned int pi = partition(elems, elemsize, low, high - 1, MemCmp);
		QuickSort(elems, elemsize, low, pi - 1, MemCmp);
		QuickSort(elems, elemsize, pi + 1, high - 1, MemCmp);
	}
}


void quicksort(void* elems, unsigned int elembytes, unsigned int first, unsigned int last, int(*MemCmp)(void* a, void* b, unsigned int elembytes)){
	void* i; void* j; void* pivot;

	if (first<last){
		pivot = first;
		i = first;
		j = last;

		while (MemCmp(i, j, elembytes) < 0){
			while (MemCmp((char*)elems + elembytes * *(unsigned int*)i, (char*)elems + elembytes * *(unsigned int*)pivot, elembytes) < 0 
				&& *(unsigned int*)i<*(unsigned int*)last)
				(*(unsigned int*)i)++;
			while (MemCmp((char*)elems + elembytes * *(unsigned int*)j, (char*)elems + elembytes * *(unsigned int*)pivot, elembytes) > 0)
				(*(unsigned int*)j)--;
			if (MemCmp((char*)elems + elembytes * *(unsigned int*)j, (char*)elems + elembytes * *(unsigned int*)j, elembytes) < 0){
				memory_swap(i, j, elembytes);
			}
		}

		memory_swap(pivot, j, elembytes);

		quicksort(elems, elembytes, first, *(unsigned int*)j - 1, MemCmp);
		quicksort(elems, elembytes, *(unsigned int*)j + 1, *(unsigned int*)last, MemCmp);

	}
}