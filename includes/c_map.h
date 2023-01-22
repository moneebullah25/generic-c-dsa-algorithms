#ifndef _C_MAP_HEADER_
#define _C_MAP_HEADER_

#include "c_helper.h"

#define EMPTY 0xfe
#define TRAVERSE_COUNT 5
#define SHOPPTR "sh"
#define DHOPPTR "dh"

typedef struct {
	void* key;
	void* value;
} MapNode;


typedef struct {
	MapNode* elems;
	size_t logiclen, alloclen, keysize, valuesize;
	char* hash;
	
	size_t(*HashFunc)(void* key, size_t keysize);
	size_t(*CollRes)(size_t hash, size_t i);
	int(*DataCmp)(const void *key1, const void *key2, size_t keysize);
	void(*FreeFuncKey)(void* elems);
	void(*FreeFuncVal)(void* elems);
} MapBase;


typedef struct {
	MapNode node;
	size_t keyindex;
} MapIter;


#define MapT(T,  U) \
	struct { MapBase base; T key_; U value_; }

#define MapNew(m, HashFunc, CollRes, DataCmp, FreeFuncKey, FreeFuncVal) \
	MapNew_(&(m)->base, sizeof((m)->key_), sizeof((m)->value_), HashFunc, CollRes, DataCmp, FreeFuncKey, FreeFuncVal)

#define MapSet(m, key, value) \
	((m)->key_ = (key), \
	(m)->value_ = (value), \
	MapSet_(&(m)->base, &(m)->key_, &(m)->value_))

#define MapSize(m) \
	MapSize_(&(m)->base)

#define MapGet(m, key) \
	((m)->key_ = (key), \
	MapGet_(&(m)->base, &(m)->key_))

#define MapRemove(m, key) \
	((m)->key_ = (key), \
	MapRemove_(&(m)->base, &(m)->key_))

#define MapIterator(m) \
	MapIterator_(&(m)->base)

#define MapNext(m, iter) \
	MapNext_(&(m)->base, iter)

#define MapClear(m) \
	MapClear_(&(m)->base)

#define MapDelete(m) \
	MapDelete_(&(m)->base)

// Helpers Predefined with library
<<<<<<< HEAD
unsigned int HashFunctionStr(const void* key, unsigned int keysize);
unsigned int HashFunctionInt(const void* key, unsigned int keysize);
unsigned int LinearProbing(unsigned int hash, unsigned int i);
unsigned int QuadraticProbing(unsigned int hash, unsigned int i);
unsigned int DoubleHashing(unsigned int hash, unsigned int i);
=======
size_t HashFunctionStr(void* key, size_t keysize);
size_t HashFunctionInt(void* key, size_t keysize);
size_t LinearProbing(size_t hash, size_t i);
size_t QuadraticProbing(size_t hash, size_t i);
size_t DoubleHashing(size_t hash, size_t i);
>>>>>>> b6bd569769dc5b4784a0430d0dbc49e12d3cdb9a

void MapNew_(MapBase* m, size_t keysize, size_t valuesize,
	size_t(*HashFunc)(const void* key, size_t keysize),
	size_t(*CollRes)(size_t hash, size_t i), 
	int(*DataCmp)(const void *key1, const void *key2, size_t keysize),
	void(*FreeFuncKey)(void* elems), void(*FreeFuncVal)(void* elems));
void MapSet_(MapBase* m, void* key, void* value);
void MapResize_(MapBase* m);
size_t MapSize_(MapBase* m);
void* MapGet_(MapBase* m, void* key);
size_t MapRemove_(MapBase* m, void* key);
MapIter* MapIterator_(MapBase* m);
void* MapNext_(MapBase* m, MapIter* mapiter);
void MapClear_(MapBase* m);
void MapDelete_(MapBase* m);


typedef MapT(void*, void*) Map;
typedef MapT(double, double) MapDouble;
typedef MapT(float, float) MapFloat;
typedef MapT(int, int) MapInt;
typedef MapT(char*, char*) MapString;
typedef MapT(char, char) MapChar;

typedef MapT(char*, double) MapStringDouble;
typedef MapT(char*, float) MapStringFloat;
typedef MapT(char*, int) MapStringInt;
typedef MapT(char*, bool) MapStringBool;

typedef MapT(char, double) MapCharDouble;
typedef MapT(char, float) MapCharFloat;
typedef MapT(char, int) MapCharInt;
typedef MapT(char, bool) MapCharBook;

typedef MapT(int, double) MapIntDouble;
typedef MapT(int, float) MapIntFloat;
typedef MapT(int, char*) MapIntString;
typedef MapT(int, bool) MapIntBool;

typedef MapT(float, double) MapFloatDouble;
typedef MapT(float, char*) MapFloatString;
typedef MapT(float, int) MapFloatInt;
typedef MapT(float, bool) MapFloatBool;

typedef MapT(double, char*) MapDoubleString;
typedef MapT(double, int) MapDoubleInt;
typedef MapT(double, float) MapDoubleFloat;
typedef MapT(double, bool) MapDoubleBool;

#endif