#include "c_map.h"
#include <stdio.h>

void MapNew(Map* m, unsigned int keysize, unsigned int valuesize)
{
	ASSERT(keysize > 0 && valuesize > 0);
	m->alloclen = 4; m->logiclen = 0;
	m->elems = malloc(m->alloclen * sizeof(MapNode));
	ASSERT(m->elems != 0);
	m->keysize = keysize;
	m->valuesize = valuesize;
	// set *key to all 1's with respect to keysize
	for (unsigned int i = 0; i < m->alloclen; i++){
		SetEmpty(m->elems[i]->key, m->keysize);
		SetEmpty(m->elems[i]->value, m->valuesize);
	}
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

void SetEmpty(void* key, unsigned int keysize)
{
	for (unsigned int j = 0; j < m->keysize; j++)	
		((char*)key)[j] = EMPTY;
}

void SetDeleted(void* key, unsigned int keysize)
{
	for (unsigned int j = 0; j < m->keysize; j++)	
		((char*)key)[j] = DELETED;
}

bool IsEmpty(void* key, unsigned int keysize)
{
	for (unsigned int j = 0; j < m->keysize; j++)	
		if (((char*)key)[j] != EMPTY) return false;
	return true;
}

void* MapSet(Map* m, void* key, void* value, char* hash)
{
	if (m->logiclen == m->alloclen)
	{
		// Resize
		m->alloclen *= 2;
		m->elems = realloc(m->alloclen * sizeof(MapNode));
	}
	ASSERT(key && value);
	unsigned int hash_value
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while !(IsEmpty(m->elems[hash_value]->key, m->keysize))
		hash_value++; // Linear Probing
	
	memory_copy(m->elems[hash_value]->key, key, m->keysize); // Insertion
	memory_copy(m->elems[hash_value]->value, value, m->valuesize);
	m->logiclen++;
}

unsigned int MapSize(Map* m)
{
	return m->logiclen;
}

void* MapGet(Map* m, void* key, char* hash)
{
	ASSERT(key);
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (M_ABS(data_compare(m->elems[hash_value]->key, key, m->keysize)))
	{
		hash_value++;
		if (hash_value == m->logiclen)
			return NULL;
	}
	return m->elems[hash_value]->value;
}

unsigned int MapRemove(Map* m, void* key)
{
	ASSERT(key);
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (M_ABS(data_compare(m->elems[hash_value]->key, key, m->keysize)))
	{
		hash_value++;
		if (hash_value == m->logiclen)
			return 0; // Value Doesn't Exist
	}
	SetEmpty(m->elems[hash_value]->key, m->keysize);
	SetEmpty(m->elems[hash_value]->value, m->valuesize);
	m->logiclen--;
	return 1;
}


int main(void)
{
	std::map<std::string, int> map;
	// Insert some values into the map
	map["one"] = 1;
	map["two"] = 2;
	map["three"] = 3;

	Map* m = malloc(sizeof(Map));
	MapNew(m, sizeof(char*), sizeof(int));
	MapInsert(m, "Muneeb", 21);
	MapInsert(m, "Moiz", 15);
	void* age = MapAt("Moiz");
	*(int*)age = 16;
	
	
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
