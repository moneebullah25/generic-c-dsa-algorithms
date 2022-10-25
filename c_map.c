#include "c_map.h"
#include <stdio.h>

void MapNew(Map* m, unsigned int keysize, unsigned int valuesize)
{
	ASSERT(keysize > 0 && valuesize > 0);
	m->alloclen = 4; m->logiclen = 0;
	m->elems = malloc(m->alloclen * sizeof(MapNode));
	ASSERT(m->elems != 0);
	m->elems->keysize = keysize; 
	m->elems->valuesize = valuesize;
	m->elems->key = malloc(keysize); 
	m->elems->value = malloc(valuesize);
	ASSERT(m->elems->key != 0 && m->elems->value != 0);
}


unsigned int HashFunctionInt(void* key, unsigned int keysize)
{
	ASSERT(keysize > 0);
	unsigned int x = 0;
	for (unsigned int i = 0; i < keysize; i++)
		x += (int)(((char *)(key))[i]);

	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}


unsigned int HashFunctionStr(void* key, unsigned int keysize)
{
	ASSERT(keysize > 0);
    unsigned int hash = 5381;
    int c;

    while (c = *((char *)key)++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(void)
{
	for (unsigned int i = 1; i < 10000; i += 9)
	{
		unsigned int sh, dh;
		sh = HashFunctionInt(&i, sizeof(unsigned int));
		dh = HashFunctionInt(&sh, sizeof(unsigned int));
		printf("Value : %u, Hash : %u, Double Hash : %u\n", i, sh, dh);
	}

	scanf_s("%d");
	return 0;
}
