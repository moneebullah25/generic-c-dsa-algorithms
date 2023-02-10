#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../includes/c_helper.h"

void FreeString(void *elems) {
	free(*(char **)&elems);
}

void FreeData(void *elems) {
	free(elems);
}

void MemorySwap(void *vp1, void *vp2, unsigned int nbytes) {
	char* buffer = malloc(nbytes);
	memcpy(buffer, vp1, nbytes);
	memcpy(vp1, vp2, nbytes);
	memcpy(vp2, buffer, nbytes);
}

void StringSwap(void *vp1, void *vp2, unsigned int nbytes) {
	char *temp = *(char **)vp1;
	*(char **)vp1 = *(char **)vp2;
	*(char **)vp2 = temp;
}

int DataCompare(const void *vp1, const void *vp2, unsigned int nbytes) {
	return memcmp(vp1, vp2, nbytes);
}

int DoubleDataCompare(const void *vp1, const void *vp2, unsigned int nbytes)
{
	if (*(double*)vp1 < *(double*)vp2) return -1;
	else if (*(double*)vp1 == *(double*)vp2) return 0;
	else return 1;
}

int IntDataCompare(const void *vp1, const void *vp2, unsigned int nbytes)
{
	if (*(int*)vp1 < *(int*)vp2) return -1;
	else if (*(int*)vp1 == *(int*)vp2) return 0;
	else return 1;
}

int StringCompare(const void *vp1, const void *vp2, unsigned int nbytes) {
	return strcmp(*(char **)vp1, *(char **)vp2);
}

void *MemoryCopy(void *dest, const void *src, unsigned int nbytes) {
	return memcpy(dest, src, nbytes);
}

void StringCopy(void *dest, const void *src, unsigned int nbytes) {
	*(char **)dest = strdup(*(char **)src);
}

void *MemoryMove(void *dest, void *src, unsigned int nbytes) {
	return memmove(dest, src, nbytes);
}