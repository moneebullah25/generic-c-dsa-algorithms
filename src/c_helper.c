#include <stdlib.h>

#include "../includes/c_helper.h"


void FreeString(void* elems)
{
    ASSERT(elems);
	free(*(char**)&elems);
}

void FreeData(void* elems)
{
    ASSERT(elems);
	free(elems);
}

void MemorySwap(void * vp1, void * vp2, unsigned int size)
{
	char* buffer = (char*)malloc(size);
	MemoryCopy(buffer, vp1, size);
	MemoryCopy(vp1, vp2, size);
	MemoryCopy(vp2, buffer, size);
	free(buffer);
}

int DataCompare(const void* vp1, const void* vp2, unsigned int n)
{
    ASSERT(n > 0);
	for (unsigned int i = 0; i < n; i++)
	{
		if (*((char*)(vp1)+i) != *((char*)(vp2)+i))
			return (*((char*)(vp1)+i)) - (*((char*)(vp2)+i));
	}
	return 0;
}

int StringCompare(const void* vp1, const void* vp2, unsigned int n)
{
	int flag = 0;
	char* a = malloc(n), *b = malloc(n);
	a = MemoryCopy(a, vp1, n), b = MemoryCopy(b, vp2, n);
	while (*a != '\0' && *b != '\0')  // while loop  
	{
		if (*a != *b)
			flag = 1;
		a++;
		b++;
	}
	if (flag == 0) return 0;
	else return 1;
}

void* MemoryCopy(void* dest, void* src, unsigned int n)
{
    ASSERT(n > 0);
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (unsigned int i=0; i<n; i++)
        cdest[i] = csrc[i];
    return dest;
}

void* MemoryMove(void *dest, void *src, unsigned int n)
{
    ASSERT(dest != NULL && src != NULL && n > 0);
    char *csrc =(char *)src;
    char *cdest =(char *)dest;
    // overlap buffer
    if((csrc < cdest) && (cdest < csrc + n)){
        for (cdest += n, csrc += n; n--;)
            *--cdest = *--csrc;
    } else {
        MemoryCopy(dest, src, n);
    }
    return dest;
}

