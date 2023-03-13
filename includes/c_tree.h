#ifndef _C_TREE_HEADER_
#define _C_TREE_HEADER_

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

typedef struct TreeBase {
    void* data; unsigned int elemsize, logiclen;
    TreeBase* left, *right;
    int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} TreeBase;

#define TreeT(T) \
    struct { TreeBase base; T data_; } 

#define TreeNew(t, DataCmp, FreeFunc) \
    TreeNew_(&(t)->base, sizeof((t)->data_), DataCmp, FreeFunc)

#define TreeInsert(t, data) \
    TreeInsert_(&(t)->base, &(t)->data_)

#define TreeContains(t, data) \
    TreeContains_(&(t)->base, &(t)->data_)

#define TreeRemove(t, data) \
    TreeRemove_(&(t)->base, &(t)->data_)

#define TreeClear(t) \
    TreeClear_(&(t)->base)

#define TreeDelete(t) \
    TreeDelete_(&(t)->base)

#define TreeSize(t) \
    TreeSize_(&(t)->base)

#define TreeEmpty(t) \
    TreeEmpty_(&(t)->base)

#define TreeInOrder(t, data_format) \
    TreeInOrder_(&(t)->base, data_format)

#define TreePreOrder(t, data_format) \
    TreePreOrder_(&(t)->base, data_format)

#define TreePostOrder(t, data_format) \
    TreePostOrder_(&(t)->base, data_format)



void TreeNew_(TreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

TreeBase* TreeInsert_(TreeBase* t, void* data);

bool TreeContains_(TreeBase* t, void* data);

TreeBase* TreeRemove_(TreeBase* t, void* data);

void TreeClear_(TreeBase* t);

void TreeDelete_(TreeBase* t);

unsigned int TreeSize_(TreeBase* t);

bool TreeEmpty_(TreeBase* t);

TreeBase* TreeMin(TreeBase* t);

TreeBase* TreeMax(TreeBase* t);

void TreeInOrder_(TreeBase* t, const char *data_format);

void TreePreOrder_(TreeBase* t, const char *data_format);

void TreePostOrder_(TreeBase* t, const char *data_format);



typedef TreeT(void*) Tree;
typedef TreeT(int) TreeInt;
typedef TreeT(float) TreeFloat;
typedef TreeT(double) TreeDouble;
typedef TreeT(char) TreeChar;
typedef TreeT(char*) TreeString;



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_TREE_HEADER_ */