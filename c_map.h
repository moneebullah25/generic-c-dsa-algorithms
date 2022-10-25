#ifndef _C_MAP_HEADER_
#define _C_MAP_HEADER_

#include "c_helper.h"

typedef struct {
	void* key;
	void* value;
	unsigned int keysize;
	unsigned int valuesize;
} MapNode;

typedef struct {
	MapNode* elems;
	unsigned int logiclen;
	unsigned int alloclen;
} Map;

void MapNew(Map* m, unsigned int keysize, unsigned int valuesize);
unsigned int HashFunctionInt(void* key, unsigned int keysize);
unsigned int HashFunctionStr(void* key, unsigned int keysize);


#endif