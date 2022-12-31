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
	unsigned int logiclen;
	unsigned int alloclen;
	unsigned int keysize;
	unsigned int valuesize;
} Map;

void MapNew(Map* m, unsigned int keysize, unsigned int valuesize);
void* MapSet(Map* m, void* key, void* value, char* hash);
unsigned int MapSize(Map* m);
void* MapGet(Map* m, void* key, char* hash);
unsigned int MapRemove(Map* m, void* key, char* hash);

#endif