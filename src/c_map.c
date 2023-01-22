#include "../includes/c_map.h"
#include <string.h>

size_t HashFunctionInt(const void* key, size_t keysize)
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
size_t HashFunctionStr(const void* key, size_t keysize)
{
	size_t hash = 5381;
	int c;

	char* str = malloc(strlen((char*)key));
	str = strdup((char*)key);

	while ((c = *(*(char**)str)++))
		hash = ((hash << 5) + hash) + c; /* pstruct * 33 + c */

	free(str);

	return hash;
}
size_t LinearProbing(size_t hash, size_t i)
{
	return hash+1;
}
size_t QuadraticProbing(size_t hash, size_t i)
{
	return hash + (i * i);
}
size_t DoubleHashing(size_t hash, size_t i)
{
	return hash + (i * hash);
}
static void SetEmpty(void* key, size_t keysize)
{
	for (size_t j = 0; j < keysize; j++)
		((char*)key)[j] = EMPTY;
}
static bool IsEmpty(void* key, size_t keysize)
{
	for (size_t j = 0; j < keysize; j++)
		if (((char*)key)[j] != (char)EMPTY) return false;
	return true;
}
static void InitMapNpde(MapNode* mn, size_t keyize, size_t valuesize)
{
	mn->key = malloc(keyize);
	mn->value = malloc(valuesize);
	SetEmpty(mn->key, keyize);
	SetEmpty(mn->value, valuesize);
}


void MapNew_(MapBase* m, size_t keysize, size_t valuesize,
	size_t(*HashFunc)(const void* key, size_t keysize),
	size_t(*CollRes)(size_t hash, size_t i),
	int(*DataCmp)(const void* key1, const void* key2, size_t keysize),
	void(*FreeFuncKey)(void* elems), void(*FreeFuncVal)(void* elems))
{
	ASSERT(keysize > 0 && valuesize > 0);
	m->alloclen = 4; m->logiclen = 0;
	m->elems = malloc(m->alloclen * sizeof(MapNode));
	ASSERT(m->elems != 0);
	m->keysize = keysize;
	m->valuesize = valuesize;
	m->HashFunc = HashFunc;
	m->CollRes = CollRes;
	m->DataCmp = DataCmp;
	m->FreeFuncKey = FreeFuncKey;
	m->FreeFuncVal = FreeFuncVal;
	for (size_t i = 0; i < m->alloclen; i++)
		InitMapNpde(&m->elems[i], m->keysize, m->valuesize);
}

void MapSet_(MapBase* m, void* key, void* value)
{
	ASSERT(key && value);
	if (m->logiclen == m->alloclen) MapResize_(m);
	
	size_t hash_value;
	hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	size_t i = 1;
	while (!IsEmpty(m->elems[hash_value].key, m->keysize))
	{
		if (m->DataCmp(m->elems[hash_value].key, key, m->keysize) == 0) break;
		hash_value = m->CollRes(hash_value, i) % m->alloclen;
	}
	
	memcpy(m->elems[hash_value].key, key, m->keysize); // Insertion
	memcpy(m->elems[hash_value].value, value, m->valuesize);
	m->logiclen++;
}

void MapResize_(MapBase* m)
{
	/* Done Shallow copy and only stores the address of key/value pairs only */
		MapNode* oldelemscpy = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(oldelemscpy);
		memcpy(oldelemscpy, m->elems, m->alloclen * sizeof(MapNode));
		
		// Just free the shallow copy
		free(m->elems);
		m->alloclen *= 2;
		m->elems = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(m->elems);
		for (size_t i = 0; i < m->alloclen; i++)
			InitMapNpde(&m->elems[i], m->keysize, m->valuesize);

		// Paste old elements to new space
		for (size_t i = 0; i < m->alloclen / 2; i++)
		{
			size_t hash_value = m->HashFunc(oldelemscpy[i].key, m->keysize) % m->alloclen;
			while (!IsEmpty(m->elems[hash_value].key, m->keysize))
				hash_value = m->CollRes(hash_value, i) % m->alloclen;
			
			memcpy(m->elems[hash_value].key, oldelemscpy[i].key, m->keysize); // Insertion
			memcpy(m->elems[hash_value].value, oldelemscpy[i].value, m->valuesize);
		}
		// Just free the shallow copy
		free(oldelemscpy);
}

size_t MapSize_(MapBase* m)
{
	return m->logiclen;
}

void* MapGet_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	size_t i = 0;
	size_t last_hash;
	while (M_ABS(m->DataCmp(m->elems[hash_value].key, key, m->keysize)))
	{
		last_hash = hash_value;
		hash_value = m->CollRes(hash_value, i) % m->alloclen;
		if (hash_value < last_hash) i++;
		if (i == TRAVERSE_COUNT) return NULL;
	}
	return m->elems[hash_value].value;
}

size_t MapRemove_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	size_t i = 0;
	size_t last_hash;
	while (M_ABS(m->DataCmp(m->elems[hash_value].key, key, m->keysize)))
	{
		last_hash = hash_value;
		hash_value = m->CollRes(hash_value, i) % m->alloclen;
		if (hash_value < last_hash) i++;
		if (i == TRAVERSE_COUNT) return 0;
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
	void* n = malloc(sizeof(MapIter));
	((MapIter*)n)->node.key = malloc(m->keysize);
	((MapIter*)n)->node.value = malloc(m->valuesize);
	((MapIter*)n)->keyindex = -1;
	return ((MapIter*)n);
}

void* MapNext_(MapBase* m, MapIter* mapiter)
{
	ASSERT(m && mapiter);
	if (m->logiclen == 0 || mapiter->keyindex == m->alloclen) return NULL;
	for (size_t i = mapiter->keyindex + 1; i < m->alloclen; i++)
	{
		if (!IsEmpty(m->elems[i].key, m->keysize))
		{
			mapiter->keyindex = i;
			memcpy(mapiter->node.key, m->elems[i].key, m->keysize);
			memcpy(mapiter->node.value, m->elems[i].value, m->valuesize);
			return mapiter;
		}
	}
	mapiter = NULL;
	return mapiter;
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
	for (size_t i = 0; i < m->alloclen; i++) {
		m->FreeFuncKey(m->elems[i].key);
		m->FreeFuncVal(m->elems[i].value);
	}
	
	free(m->elems);
}

