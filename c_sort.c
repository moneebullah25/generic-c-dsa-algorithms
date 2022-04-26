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

void* BinarySearch(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	unsigned int middle = (s + n) / 2;
	void* elemaddr = (void*)((char*)(base) + (middle * elemsize));
	if (MemCmp(elemaddr, key, elemsize) == 0)
		return elemaddr;
	else if (MemCmp(elemaddr, key, elemsize) < 0)
        return BinarySearch(key, base, s, middle, elemsize, MemCmp);
	else if (MemCmp(elemaddr, key, elemsize) > 0)
        return BinarySearch(key, base, middle + 1, n, elemsize, MemCmp);
    else
        return (void*)((char*)(base) + (n * elemsize));
}

void BubbleSort(void* base, unsigned int elemsize, unsigned int n, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	bool is_sort;
	do
	{
		for (unsigned int j = 0; j < n - 1; j++)
		{
			is_sort = true;
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