#ifndef _C_MAP_HEADER_
#define _C_MAP_HEADER_

#include "c_helper.h"
#include "c_list.h"

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
unsigned int HashFunctionInt(void* key, unsigned int keysize);
unsigned int HashFunctionStr(void* key, unsigned int keysize);
void* HashAt(void* key, unsigned 

#endif