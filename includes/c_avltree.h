#ifndef _C_AvlTree_HEADER_
#define _C_AvlTree_HEADER_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif

#define bool _Bool
#define false 0
#define true 1

typedef struct AvlTreeBase AvlTreeBase;

struct AvlTreeBase {
    void* data; unsigned int elemsize, logiclen, height;
    AvlTreeBase* left, *right;
    int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
};

#define AvlTreeT(T) \
    struct { AvlTreeBase base; T data_; } 

#define AvlTreeNew(t, DataCmp, FreeFunc) \
    AvlTreeNew_(&(t)->base, sizeof((t)->data_), DataCmp, FreeFunc)

#define AvlTreeHeight(t) \
    AvlTreeHeight_(&(t)->base)

#define AvlTreeBalance(t) \
    AvlTreeBalance_(&(t)->base)

#define AvlTreeLeftRotate(t) \
	AvlTreeLeftRotate_(&(t)->base)

#define AvlTreeRightRotate(t) \
	AvlTreeRightRotate_(&(t)->base)

#define AvlTreeInsert(t, data) \
    AvlTreeInsert_(&(t)->base, &(t)->data_)

#define AvlTreeContains(t, data) \
    AvlTreeContains_(&(t)->base, &(t)->data_)

#define AvlTreeRemove(t, data) \
    AvlTreeRemove_(&(t)->base, &(t)->data_)

#define AvlTreeClear(t) \
    AvlTreeClear_(&(t)->base)

#define AvlTreeDelete(t) \
    AvlTreeDelete_(&(t)->base)

#define AvlTreeSize(t) \
    AvlTreeSize_(&(t)->base)

#define AvlTreeEmpty(t) \
    AvlTreeEmpty_(&(t)->base)

#define AvlTreeInOrder(t, data_format) \
    AvlTreeInOrder_(&(t)->base, data_format)

#define AvlTreePreOrder(t, data_format) \
    AvlTreePreOrder_(&(t)->base, data_format)

#define AvlTreePostOrder(t, data_format) \
    AvlTreePostOrder_(&(t)->base, data_format)



void AvlTreeNew_(AvlTreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

int AvlTreeHeight_(AvlTreeBase* t);

int AvlTreeBalance_(AvlTreeBase* t);

AvlTreeBase* AvlTreeLeftRotate_(AvlTreeBase* t);

AvlTreeBase* AvlTreeRightRotate_(AvlTreeBase* t);

AvlTreeBase* AvlTreeInsert_(AvlTreeBase* t, void* data);

bool AvlTreeContains_(AvlTreeBase* t, void* data);

AvlTreeBase* AvlTreeRemove_(AvlTreeBase* t, void* data);

void AvlTreeClear_(AvlTreeBase* t);

void AvlTreeDelete_(AvlTreeBase* t);

unsigned int AvlTreeSize_(AvlTreeBase* t);

bool AvlTreeEmpty_(AvlTreeBase* t);

AvlTreeBase* AvlTreeMin(AvlTreeBase* t);

AvlTreeBase* AvlTreeMax(AvlTreeBase* t);

void AvlTreeInOrder_(AvlTreeBase* t, const char *data_format);

void AvlTreePreOrder_(AvlTreeBase* t, const char *data_format);

void AvlTreePostOrder_(AvlTreeBase* t, const char *data_format);

typedef AvlTreeT(void*) AvlTree;
typedef AvlTreeT(int) AvlTreeInt;
typedef AvlTreeT(float) AvlTreeFloat;
typedef AvlTreeT(double) AvlTreeDouble;
typedef AvlTreeT(char) AvlTreeChar;
typedef AvlTreeT(char*) AvlTreeString;



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_AvlTree_HEADER_ */