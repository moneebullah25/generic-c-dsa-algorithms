#include <stdlib.h>

#include "c_helper.h"


void string_free(void* elems)
{
    ASSERT(elems);
	free(*(char**)&elems);
}

void data_free(void* elems)
{
    ASSERT(elems);
	free(elems);
}

void memory_swap(void * vp1, void * vp2, unsigned int size)
{
	char* buffer = (char*)malloc(size);
	memory_copy(buffer, vp1, size);
	memory_copy(vp1, vp2, size);
	memory_copy(vp2, buffer, size);
	free(buffer);
}

int data_compare(void* vp1, void* vp2, unsigned int n)
{
    ASSERT(n > 0);
	for (unsigned int i = 0; i < n; i++)
	{
		if (*((char*)(vp1)+i) != *((char*)(vp2)+i))
			return (*((char*)(vp1)+i)) - (*((char*)(vp2)+i));
	}
	return 0;
}

int string_compare(void* vp1, void* vp2, unsigned int n)
{
	if (!vp1)
    {
        if (!vp2) return 0;
        else return -1;
    }
    else if (!vp2)
        return 1;

    while (*(char*)vp1 && *(char*)vp1 == *(char*)vp2) { ++a; ++b; }
    return (int)(unsigned char)(*(char*)vp1) - (int)(unsigned char)(*(char*)vp2);
	
	return 0;
}

void* memory_copy(void* dest, const void* src, unsigned int n)
{
    ASSERT(n > 0);
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (unsigned int i=0; i<n; i++)
        cdest[i] = csrc[i];
    return dest;
}

void* memory_move(void *dest, void *src, unsigned int n)
{
    ASSERT(dest != NULL && src != NULL && n > 0);
    char *csrc =(char *)src;
    char *cdest =(char *)dest;
    // overlap buffer
    if((csrc < cdest) && (cdest < csrc + n)){
        for (cdest += n, csrc += n; n--;)
            *--cdest = *--csrc;
    } else {
        memory_copy(dest, src, n);
    }
    return dest;
}

