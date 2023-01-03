#ifndef _C_MAP_HEADER_
#define _C_MAP_HEADER_

#include "c_helper.h"

#define EMPTY 0xff
#define DELETED 0xfe


typedef struct {
	void* key;
	void* value;
} MapNode;


typedef struct {
	MapNode* elems;
	size_t logiclen;
	size_t alloclen;
	size_t keysize;
	size_t valuesize;
} MapBase;


typedef struct {
	MapNode* node;
	size_t keyindex;
} MapIter;


#define MapT(T) \
	struct { MapBase base; T* ref; T key_; T value_; }


#define MapNew(m, keysize, valuesize) \
	MapNew_(&(m)->base, keysize, valuesize)


#define MapSet(m, key, value, hash) \
	((m)->key_ = (key), \
	(m)->value_ = (value), \
	MapSet_(&(m)->base, &(m)->key_, &(m)->value_, hash))


#define MapSize(m) \
	MapSize_(&(m)->base)


#define MapGet(m, key, hash) \
	((m)->key_ = (key), \
	(m)->ref = MapGet_(&(m)->base, &(m)->key_, hash))


#define MapRemove(m, key, hash) \
	((m)->key_ = (key), \
	MapRemove_(&(m)->base, &(m)->key_, hash))


#define MapIterator(m) \
	MapIterator_(&(m)->base)


#define MapNext(m, iter) \
	MapNext_(&(m)->base, iter)


#define MapClear(m) \
	MapClear_(&(m)->base)


#define MapDelete(m) \
	MapDelete_(&(m)->base)



void MapNew_(MapBase* m, size_t keysize, size_t valuesize);
void* MapSet_(MapBase* m, void* key, void* value, char* hash);
size_t MapSize_(MapBase* m);
void* MapGet_(MapBase* m, void* key, char* hash);
size_t MapRemove_(MapBase* m, void* key, char* hash);
MapIter* MapIterator_(MapBase* m);
MapIter* MapNext_(MapBase* m, const MapIter* mapiter);
void MapClear_(MapBase* m);
void MapDelete_(MapBase* m);


typedef MapT(void*) Map;

#endif