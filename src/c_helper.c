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
	ASSERT(n > 0);
	if (n == 0) return 0;
	if (!vp1)
    {
        if (!vp2) return 0;
        else return -1;
    }
    else if (!vp2){
        return 1;
    }

	while (*(char*)vp1 && *(char*)vp1 == *(char*)vp2) { vp1 = (char*)vp1 + 1; vp2 = (char*)vp2 + 1; }
	return (int)(unsigned char)(*(char*)vp1) - (int)(unsigned char)(*(char*)vp2);

	return 0;
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

