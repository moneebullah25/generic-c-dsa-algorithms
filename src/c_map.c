#include "../includes/c_map.h"
#include <stdlib.h>

unsigned int HashFunctionInt(const void* key, unsigned int keysize)
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
unsigned int HashFunctionStr(const void* key, unsigned int keysize)
{
	unsigned int hash = 5381;
	int c;
	int i = 0;

	while ((c = *(*(char**)key + i++)))
		hash = ((hash << 5) + hash) + c; /* pstruct * 33 + c */


	return hash;
}
unsigned int LinearProbing(unsigned int hash, unsigned int i)
{
	return hash+1;
}
unsigned int QuadraticProbing(unsigned int hash, unsigned int i)
{
	return hash + (i * i);
}
unsigned int DoubleHashing(unsigned int hash, unsigned int i)
{
	return hash + (i * hash);
}
static void SetEmpty(void* key, unsigned int keysize)
{
	for (unsigned int j = 0; j < keysize; j++)
		((char*)key)[j] = EMPTY;
}
static bool IsEmpty(void* key, unsigned int keysize)
{
	for (unsigned int j = 0; j < keysize; j++)
		if (((char*)key)[j] != (char)EMPTY) return false;
	return true;
}
static void InitMapNpde(MapNode* mn, unsigned int keyize, unsigned int valuesize)
{
	mn->key = malloc(keyize);
	mn->value = malloc(valuesize);
	SetEmpty(mn->key, keyize);
	SetEmpty(mn->value, valuesize);
}


void MapNew_(MapBase* m, unsigned int keysize, unsigned int valuesize,
	unsigned int(*HashFunc)(const void* key, unsigned int keysize),
	unsigned int(*CollRes)(unsigned int hash, unsigned int i),
	int(*DataCmp)(const void* key1, const void* key2, unsigned int keysize),
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
	for (unsigned int i = 0; i < m->alloclen; i++)
		InitMapNpde(&m->elems[i], m->keysize, m->valuesize);
}

void MapSet_(MapBase* m, void* key, void* value)
{
	ASSERT(key && value);
	if (m->logiclen == m->alloclen) MapResize_(m);
	
	unsigned int hash_value;
	hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	unsigned int i = 1;
	while (!IsEmpty(m->elems[hash_value].key, m->keysize))
	{
		if (m->DataCmp(m->elems[hash_value].key, key, m->keysize) == 0) break;
		hash_value = m->CollRes(hash_value, i) % m->alloclen;
	}
	
	MemoryCopy(m->elems[hash_value].key, key, m->keysize); // Insertion
	MemoryCopy(m->elems[hash_value].value, value, m->valuesize);
	m->logiclen++;
}

void MapResize_(MapBase* m)
{
	/* Done Shallow copy and only stores the address of key/value pairs only */
		MapNode* oldelemscpy = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(oldelemscpy);
		MemoryCopy(oldelemscpy, m->elems, m->alloclen * sizeof(MapNode));
		
		// Just free the shallow copy
		free(m->elems);
		m->alloclen *= 2;
		m->elems = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(m->elems);
		for (unsigned int i = 0; i < m->alloclen; i++)
			InitMapNpde(&m->elems[i], m->keysize, m->valuesize);

		// Paste old elements to new space
		for (unsigned int i = 0; i < m->alloclen / 2; i++)
		{
			unsigned int hash_value = m->HashFunc(oldelemscpy[i].key, m->keysize) % m->alloclen;
			while (!IsEmpty(m->elems[hash_value].key, m->keysize))
				hash_value = m->CollRes(hash_value, i) % m->alloclen;
			
			MemoryCopy(m->elems[hash_value].key, oldelemscpy[i].key, m->keysize); // Insertion
			MemoryCopy(m->elems[hash_value].value, oldelemscpy[i].value, m->valuesize);
		}
		// Just free the shallow copy
		free(oldelemscpy);
}

unsigned int MapSize_(MapBase* m)
{
	return m->logiclen;
}

void* MapGet_(MapBase* m, void* key)
{
	ASSERT(key);
	unsigned int hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	unsigned int i = 0;
	unsigned int last_hash;
	while (M_ABS(m->DataCmp(m->elems[hash_value].key, key, m->keysize)))
	{
		last_hash = hash_value;
		hash_value = m->CollRes(hash_value, i) % m->alloclen;
		if (hash_value < last_hash) i++;
		if (i == TRAVERSE_COUNT) return NULL;
	}
	return m->elems[hash_value].value;
}

unsigned int MapRemove_(MapBase* m, void* key)
{
	ASSERT(key);
	unsigned int hash_value = m->HashFunc(key, m->keysize) % m->alloclen;
	unsigned int i = 0;
	unsigned int last_hash;
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

MapIter* MapNext_(MapBase* m, MapIter* mapiter)
{
	ASSERT(m && mapiter);
	if (m->logiclen == 0 || mapiter->keyindex == m->alloclen) return NULL;
	for (unsigned int i = mapiter->keyindex + 1; i < m->alloclen; i++)
	{
		if (!IsEmpty(m->elems[i].key, m->keysize))
		{
			mapiter->keyindex = i;
			MemoryCopy(mapiter->node.key, m->elems[i].key, m->keysize);
			MemoryCopy(mapiter->node.value, m->elems[i].value, m->valuesize);
			return mapiter;
		}
	}
	mapiter = NULL;
	return mapiter;
}

void MapClear_(MapBase* m)
{
	for (unsigned int i = 0; i < m->alloclen; i++){
		SetEmpty(m->elems[i].key, m->keysize);
		SetEmpty(m->elems[i].value, m->valuesize);
	}
	m->logiclen = 0;
}

void MapDelete_(MapBase* m)
{
	for (unsigned int i = 0; i < m->alloclen; i++) {
		m->FreeFuncKey(m->elems[i].key);
		m->FreeFuncVal(m->elems[i].value);
	}
	
	free(m->elems);
}

