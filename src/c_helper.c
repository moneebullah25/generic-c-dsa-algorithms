#include <stdlib.h>
#include <string.h>

#include "../includes/c_helper.h"

void FreeString(void *elems)
{
	ASSERT(elems);
	free(*(char **)&elems);
}

void FreeData(void *elems)
{
	ASSERT(elems);
	free(elems);
}

void MemorySwap(void *vp1, void *vp2, unsigned int nbytes)
{
	char *buffer = (char *)malloc(nbytes);
	MemoryCopy(buffer, vp1, nbytes);
	MemoryCopy(vp1, vp2, nbytes);
	MemoryCopy(vp2, buffer, nbytes);
	free(buffer);
}

void StringSwap(void *str1, void *str2, unsigned int nbytes)
{
	if (str1 == NULL || str2 == NULL) {
		return;
	}
	char *s1 = *(char **)str1;
	char *s2 = *(char **)str2;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int max_len = (len1 > len2) ? len1 : len2;
	char *temp = malloc(max_len + 1);
	StringCopy(&temp, &s1, nbytes);
	StringCopy(&s1, &s2, nbytes);
	StringCopy(&s2, &temp, nbytes);
	free(temp);
}

int DataCompare(const void *vp1, const void *vp2, unsigned int nbytes)
{
	ASSERT(nbytes > 0);
	for (unsigned int i = 0; i < nbytes; i++)
	{
		if (*((char *)(vp1) + i) != *((char *)(vp2) + i))
			return (*((char *)(vp1) + i)) - (*((char *)(vp2) + i));
	}
	return 0;
}

int StringCompare(const void *vp1, const void *vp2, unsigned int nbytes)
{
	if (vp1 == NULL || vp2 == NULL) {
		return 0;
	}
	const char *s1 = *(const char **)vp1;
	const char *s2 = *(const char **)vp2;
	int i = 0;
	while (i < nbytes)
	{
		if (s1[i] != s2[i])
		{
			return 1;
		}
		i++;
	}
	return 0;
}


void *MemoryCopy(void *dest, const void *src, unsigned int nbytes)
{
	ASSERT(nbytes > 0);
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (unsigned int i = 0; i < nbytes; i++)
		cdest[i] = csrc[i];
	return dest;
}

void StringCopy(void *dest, const void *src, unsigned int nbytes)
{
	const char *s = *(const char **)src;
	char *d = *(char **)dest;
	int i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

void *MemoryMove(void *dest, void *src, unsigned int nbytes)
{
	ASSERT(dest != NULL && src != NULL && nbytes > 0);
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	// overlap buffer
	if ((csrc < cdest) && (cdest < csrc + nbytes))
	{
		for (cdest += nbytes, csrc += nbytes; nbytes--;)
			*--cdest = *--csrc;
	}
	else
	{
		MemoryCopy(dest, src, nbytes);
	}
	return dest;
}
