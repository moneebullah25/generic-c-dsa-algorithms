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

	void* str = malloc(sizeof(keysize));
	memory_copy(str, key, keysize);

	while (c = *(*(char**)str)++)
		hash = ((hash << 5) + hash) + c; /* pstruct * 33 + c */

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
	m->elems = malloc(m->alloclen * (keysize + valuesize));
	ASSERT(m->elems != 0);
	m->keysize = keysize;
	m->valuesize = valuesize;
	m->hash = pstruct;
	// set *key to all 1's with respect to keysize
	for (size_t i = 0; i < m->alloclen; i++){
		SetEmpty(&m->elems[i].key, m->keysize);
		SetEmpty(&m->elems[i].value, m->valuesize);
	}
}

void MapSet_(MapBase* m, void* key, void* value)
{
	ASSERT(key && value);
	if (m->logiclen == m->alloclen)
	{
		MapNode* oldelemscpy = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(oldelemscpy);
		memory_copy(oldelemscpy, m->elems, m->alloclen * sizeof(MapNode));
		m->alloclen *= 2;
		free(m->elems);
		m->elems = malloc(m->alloclen * sizeof(MapNode));
		ASSERT(m->elems);
		// Set empty newly allocated space
		SetEmpty(m->elems, m->alloclen * sizeof(MapNode));
		m->logiclen = 0;
		// Paste old elements to new space
		for (size_t i = 0; i < m->alloclen / 2; i++)
			MapSet_(m, &oldelemscpy[i].key, &oldelemscpy[i].value);
		free(oldelemscpy);
	}
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
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

void* MapGet_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
	else hash_value = HashFunctionInt(key, m->keysize);
	hash_value = hash_value % m->alloclen;
	if (m->hash != "dh") {
		while (M_ABS(data_compare(&m->elems[hash_value].key, key, m->keysize)))
		{
			hash_value++;
			if (hash_value == m->logiclen)
				return NULL;
		}
	}
	else {
		while (M_ABS(string_compare(&m->elems[hash_value].key, key, m->keysize)))
		{
			hash_value++;
			if (hash_value == m->logiclen)
				return NULL;
		}
	}
	return &m->elems[hash_value].value;
}

size_t MapRemove_(MapBase* m, void* key)
{
	ASSERT(key);
	size_t hash_value;
	if (m->hash == "dh") hash_value = HashFunctionStr(key, m->keysize);
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
	void* n = malloc(sizeof(MapIter));
	// Find very first element and return that
	for (size_t i = 0; i < m->alloclen; i++)
	{
		if (!IsEmpty(&m->elems[i].key, m->keysize))
		{
			((MapIter*)n)->keyindex = i;
			((MapIter*)n)->node.key = m->elems[i].key;
			((MapIter*)n)->node.value = m->elems[i].value;
			return ((MapIter*)n);
		}
	}
	return NULL;
}

MapIter* MapNext_(MapBase* m, const MapIter* mapiter)
{
	ASSERT(m && mapiter);
	if (m->logiclen == 0) return NULL;
	void* n = malloc(sizeof(MapIter));
	for (size_t i = mapiter->keyindex + 1; i < m->alloclen; i++)
	{
		if (!IsEmpty(&m->elems[i].key, m->keysize))
		{
			((MapIter*)n)->keyindex = i;
			((MapIter*)n)->node.key = m->elems[i].key;
			((MapIter*)n)->node.value = m->elems[i].value;
			return ((MapIter*)n);
		}
	}
	return NULL;
}

void MapClear_(MapBase* m)
{
	for (size_t i = 0; i < m->alloclen; i++){
		SetEmpty(&m->elems[i].key, m->keysize);
		SetEmpty(&m->elems[i].value, m->valuesize);
	}
	m->logiclen = 0;
}

void MapDelete_(MapBase* m)
{
	MapClear_(m);
	free(m->elems);
	free(m);
}

