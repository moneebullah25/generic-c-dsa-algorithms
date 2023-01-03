#include "c_map.h"

static size_t HashFunctionInt(void* key, size_t keysize)
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

static size_t HashFunctionStr(void* key, size_t keysize)
{
	ASSERT(keysize > 0);
	size_t hash = 5381;
	int c;

	while (c = *(*(char**)key)++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

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

void MapNew_(MapBase* m, size_t keysize, size_t valuesize)
{
	ASSERT(keysize > 0 && valuesize > 0);
	m->alloclen = 4; m->logiclen = 0;
	m->elems = malloc(m->alloclen * sizeof(MapNode));
	ASSERT(m->elems != 0);
	m->keysize = keysize;
	m->valuesize = valuesize;
	// set *key to all 1's with respect to keysize
	for (size_t i = 0; i < m->alloclen; i++)
		SetEmpty(&m->elems[i], m->keysize + m->valuesize);
}

void MapSet_(MapBase* m, void* key, void* value, char* hash)
{
	if (m->logiclen == m->alloclen)
	{
		m->alloclen *= 2;
		m->elems = realloc(m->elems, m->alloclen * sizeof(MapNode));
		ASSERT(m->elems);
		MapIter* iter = MapIterator_(m);
		while (iter != NULL){
			MapSet_(m, &iter->node.key, &iter->node.value, hash);
			SetEmpty(&m->elems[iter->keyindex], m->keysize + m->valuesize);
			iter = MapNext_(m, iter);
		}
	}
	ASSERT(key && value);
	size_t hash_value;
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (!IsEmpty(&m->elems[hash_value].key, m->keysize))
		hash_value++; // Linear Probing
	
	memory_copy(&m->elems[hash_value].key, key, m->keysize); // Insertion
	memory_copy(&m->elems[hash_value].value, value, m->valuesize);
	m->logiclen++;
}

size_t MapSize_(MapBase* m)
{
	return m->logiclen;
}

void* MapGet_(MapBase* m, void* key, char* hash)
{
	ASSERT(key);
	size_t hash_value;
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (M_ABS(data_compare(&m->elems[hash_value].key, key, m->keysize)))
	{
		hash_value++;
		if (hash_value == m->logiclen)
			return NULL;
	}
	return m->elems[hash_value].value;
}

size_t MapRemove_(MapBase* m, void* key, char* hash)
{
	ASSERT(key);
	size_t hash_value;
	if (hash == "string") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	while (M_ABS(data_compare(&m->elems[hash_value].key, key, m->keysize)))
	{
		hash_value++;
		if (hash_value == m->logiclen)
			return 0; // Value Doesn't Exist
	}
	SetEmpty(&m->elems[hash_value].key, m->keysize);
	SetEmpty(&m->elems[hash_value].value, m->valuesize);
	m->logiclen--;
	return 1;
}

MapIter* MapIterator_(MapBase* m)
{
	ASSERT(m);
	if (m->logiclen == 0) return NULL;
	MapIter* n = malloc(sizeof(MapIter));
	// Find very first element and return that
	for (size_t i = 0; i < m->logiclen; i++)
	{
		if (!IsEmpty(&m->elems[i].key, m->keysize))
		{
			n->keyindex = i;
			n->node.key = m->elems[i].key;
			n->node.value = m->elems[i].value;
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
	for (size_t i = mapiter->keyindex + 1; i < m->logiclen; i++)
	{
		if (!IsEmpty(&m->elems[i].key, m->keysize))
		{
			n->keyindex = i;
			n->node.key = m->elems[i].key;
			n->node.value = m->elems[i].value;
			return ((MapIter*)n);
		}
	}
	return NULL;
}

void MapClear_(MapBase* m)
{
	MapIter* iter = MapIterator_(m);
	while (iter != NULL){
		free(&iter->node.key);
		free(&iter->node.value);
		iter = MapNext_(m, iter);
	}
	free(m->elems);
	m->logiclen = 0;
	m->alloclen = 0;
	m->keysize = 0;
	m->valuesize = 0;
}

void MapDelete_(MapBase* m)
{
	MapClear_(m);
	free(m);
}

