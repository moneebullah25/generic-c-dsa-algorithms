#include <stdlib.h>
#include <string.h>

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

void MemorySwap(void * vp1, void * vp2, unsigned int nbytes)
{
	char* buffer = (char*)malloc(nbytes);
	MemoryCopy(buffer, vp1, nbytes);
	MemoryCopy(vp1, vp2, nbytes);
	MemoryCopy(vp2, buffer, nbytes);
	free(buffer);
}

int DataCompare(const void* vp1, const void* vp2, unsigned int nbytes)
{
    ASSERT(nbytes > 0);
	for (unsigned int i = 0; i < nbytes; i++)
	{
		if (*((char*)(vp1)+i) != *((char*)(vp2)+i))
			return (*((char*)(vp1)+i)) - (*((char*)(vp2)+i));
	}
	return 0;
}

void StringSwap(void* vp1, void* vp2, unsigned int nbytes)
{

}

int StringCompare(const void* vp1, const void* vp2, unsigned int nbytes)
{
	int flag = 0;
	char* a = malloc(nbytes), *b = malloc(nbytes);
	a = MemoryCopy(a, vp1, nbytes), b = MemoryCopy(b, vp2, nbytes);
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

void* MemoryCopy(void* dest, const void* src, unsigned int nbytes)
{
    ASSERT(nbytes > 0);
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (unsigned int i=0; i<nbytes; i++)
        cdest[i] = csrc[i];
    return dest;
}

void* MemoryMove(void *dest, void *src, unsigned int nbytes)
{
    ASSERT(dest != NULL && src != NULL && nbytes > 0);
    char *csrc =(char *)src;
    char *cdest =(char *)dest;
    // overlap buffer
    if((csrc < cdest) && (cdest < csrc + nbytes)){
        for (cdest += nbytes, csrc += nbytes; nbytes--;)
            *--cdest = *--csrc;
    } else {
        MemoryCopy(dest, src, nbytes);
    }
    return dest;
}

