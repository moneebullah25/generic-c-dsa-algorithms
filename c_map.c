#include "c_map.h"
#include <string.h>

size_t HashFunctionInt(void* key, size_t keysize)
{
	ASSERT(keysize > 0);
	size_t x = 0;
	for (size_t i = 0; i < keysize; i++)
		x += (int)(((char *)(key))[i]);

	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

size_t HashFunctionStr(void* key, size_t keysize)
{
	ASSERT(keysize > 0);
	size_t hash = 5381;
	int c;

	void* str = malloc(sizeof(keysize));
	memory_copy(str, key, keysize);

	while (c = *(*(char**)str)++)
		hash = ((hash << 5) + hash) + c; /* pstruct * 33 + c */

	free(str);

	return hash;
}

static void SetEmpty(void* key, size_t keysize)
{
	for (size_t j = 0; j < keysize; j++)
		((char*)key)[j] = EMPTY;
}

static void SetDeleted(void* key, size_t keysize)
{
	for (size_t j = 0; j < keysize; j++)
		((char*)key)[j] = DELETED;
}

static bool IsEmpty(void* key, size_t keysize)
{
	for (size_t j = 0; j < keysize; j++)
		if (((char*)key)[j] != (char)EMPTY) return false;
	return true;
}

void MapNew_(MapBase* m, size_t keysize, size_t valuesize, char* pstruct)
{
	ASSERT(keysize > 0 && valuesize > 0);
	m->alloclen = 4; m->logiclen = 0;
	m->elems = malloc(m->alloclen * sizeof(MapNode));
	ASSERT(m->elems != 0);
	m->keysize = keysize;
	m->valuesize = valuesize;
	m->hash = pstruct;
	for (size_t i = 0; i < m->alloclen; i++){
		m->elems[i].key = malloc(m->keysize);
		m->elems[i].value = malloc(m->valuesize);
		SetEmpty(m->elems[i].key, m->keysize);
		SetEmpty(m->elems[i].value, m->valuesize);
	}
}

void MapSet_(MapBase* m, void* key, void* value)
{
	ASSERT(key && value);
	if (m->logiclen == m->alloclen)
	{
		/* Done Shallow copy and only stores the address of key/value pairs only */
		MapNode* oldelemscpy = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(oldelemscpy);
		memory_copy(oldelemscpy, m->elems, m->alloclen * sizeof(MapNode));
		
		// Just free the shallow copy
		free(m->elems);
		m->alloclen *= 2;
		m->elems = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(m->elems);
		for (size_t i = 0; i < m->alloclen; i++) {
			m->elems[i].key = malloc(m->keysize);
			m->elems[i].value = malloc(m->valuesize);
			SetEmpty(m->elems[i].key, m->keysize);
			SetEmpty(m->elems[i].value, m->valuesize);
		}

		// Paste old elements to new space
		for (size_t i = 0; i < m->alloclen / 2; i++)
		{
			size_t hash_value;
			if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
			else hash_value = HashFunctionInt(key, m->keysize);
			hash_value = hash_value % m->alloclen;
			while (!IsEmpty(m->elems[hash_value].key, m->keysize))
			{
				hash_value++;
				if (hash_value == m->alloclen)
					hash_value = 0;
			}
			
			memory_copy(m->elems[hash_value].key, oldelemscpy[i].key, m->keysize); // Insertion
			memory_copy(m->elems[hash_value].value, oldelemscpy[i].value, m->valuesize);
		}
		// Just free the shallow copy
		free(oldelemscpy);
		
		MapSet_(m, key, value);
		return;
	}
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (!IsEmpty(m->elems[hash_value].key, m->keysize))
	{
		hash_value++;
		if (hash_value == m->alloclen)
			hash_value = 0;
	}
	
	memory_copy(m->elems[hash_value].key, key, m->keysize); // Insertion
	memory_copy(m->elems[hash_value].value, value, m->valuesize);
	m->logiclen++;
}

size_t MapSize_(MapBase* m)
{
	return m->logiclen;
}

void* MapGet_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	if (m->hash != "dh") {
		while (M_ABS(data_compare(m->elems[hash_value].key, key, m->keysize)))
		{
			hash_value++;
			if (hash_value == m->alloclen)
				hash_value = 0;
		}
	}
	else {
		while (M_ABS(strcmp(m->elems[hash_value].key, key)))
		{
			hash_value++;
			if (hash_value == m->alloclen)
				hash_value = 0;
		}
	}
	return m->elems[hash_value].value;
}

size_t MapRemove_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (M_ABS(data_compare(m->elems[hash_value].key, key, m->keysize)))
	{
		hash_value++;
		if (hash_value == m->logiclen)
			return 0; // Value Doesn't Exist
	}
	SetEmpty(m->elems[hash_value].key, m->keysize);
	SetEmpty(m->elems[hash_value].value, m->valuesize);
	m->logiclen--;
	return 1;
}

MapIter* MapIterator_(MapBase* m)
{
	ASSERT(m);
	if (m->logiclen == 0) return NULL;
	MapIter* n = malloc(sizeof(MapIter));
	n->node.key = malloc(m->keysize);
	n->node.value = malloc(m->valuesize);

	// Find very first element and return that
	for (size_t i = 0; i < m->alloclen; i++)
	{
		if (!IsEmpty(m->elems[i].key, m->keysize))
		{
			n->keyindex = i;
			memory_copy(n->node.key, m->elems[i].key, m->keysize);
			memory_copy(n->node.value, m->elems[i].value, m->valuesize);
			return n;
		}
	}
	return NULL;
}

MapIter* MapNext_(MapBase* m, const MapIter* mapiter)
{
	ASSERT(m && mapiter);
	if (m->logiclen == 0) return NULL;
	MapIter* n = malloc(sizeof(MapIter));
	n->node.key = malloc(m->keysize);
	n->node.value = malloc(m->valuesize);
	for (size_t i = mapiter->keyindex + 1; i < m->alloclen; i++)
	{
		if (!IsEmpty(m->elems[i].key, m->keysize))
		{
			n->keyindex = i;
			memory_copy(n->node.key, m->elems[i].key, m->keysize);
			memory_copy(n->node.value, m->elems[i].value, m->valuesize);
			return n;
		}
	}
	return NULL;
}

void MapClear_(MapBase* m)
{
	for (size_t i = 0; i < m->alloclen; i++){
		SetEmpty(m->elems[i].key, m->keysize);
		SetEmpty(m->elems[i].value, m->valuesize);
	}
	m->logiclen = 0;
}

void MapDelete_(MapBase* m)
{
	if (m->hash != "dh") {
		for (size_t i = 0; i < m->alloclen; i++) {
			free(m->elems[i].key);
			free(m->elems[i].value);
		}
	}

	free(m->elems);

}

