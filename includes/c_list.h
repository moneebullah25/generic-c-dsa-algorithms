#ifndef _C_LIST_HEADER_
#define _C_LIST_HEADER_

#include "c_helper.h"

#define MAX_UNSIGNED 4294967295

typedef struct ListNode {
	void* elem;
	unsigned int elemsize;
	struct ListNode* next;
} ListNode;

typedef struct LinkedListBase {
	ListNode* head; ListNode* tail;
	unsigned int listsize; unsigned int elemsize;

	int(*DataCmp)(void *key1, void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} LinkedListBase;

#define LinkedListT(T) \
struct { LinkedListBase base; T* ref; T data_; T value_; }

#define LinkedListNew(ll, DataCmp, FreeFunc) \
	LinkedListNew_(&(ll)->base, sizeof((ll)->data_), DataCmp, FreeFunc)

#define LinkedListInsertAtTail(ll, data) \
	((ll)->data_ = data, \
	LinkedListInsertAtTail_(&(ll)->base, &(ll)->data_))

#define LinkedListInsertAtHead(ll, data) \
	((ll)->data_ = data, \
	LinkedListInsertAtHead_(&(ll)->base, &(ll)->data_))

#define LinkedListReplace(ll, data, value) \
	((ll)->data_ = data, \
	(ll)->value_ = value, \
	LinkedListReplace_(&(ll)->base, &(ll)->data_, &(ll)->value_))

#define LinkedListReplaceAll(ll, data, value) \
	((ll)->data_ = data, \
	(ll)->value_ = value, \
	LinkedListReplaceAll_(&(ll)->base, &(ll)->data_, &(ll)->value_))

#define LinedListGetIndex(ll, data) \
	((ll)->data_ = data, \
	LinkedListGetIndex_(&(ll)->base, &(ll)->data_))

#define LinkedListAt(ll, index) \
	(ll)->ref =  LinkedListAt_(&(ll)->base, index)

#define LinkedListClear(v) \
	LinkedListClear_(&(v)->base)

#define LinkedListDelete(v) \
	LinkedListDelete_(&(v)->base)

#define LinkedListSize(v) \
	LinkedListSize_(&(v)->base)

void LinkedListNew_(LinkedListBase* ll, unsigned int elemsize,
	int(*DataCmp)(void *key1, void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
void LinkedListInsertAtTail_(LinkedListBase* ll, void* data);
void LinkedListInsertAtHead_(LinkedListBase* ll, void* data);
/*Replace Data with Value once*/
void LinkedListReplace_(LinkedListBase* ll, void* data, void* value);
/*Replace Data with Value unless doesn't find any*/
void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value);
unsigned int LinkedListGetIndex_(LinkedListBase* ll, void* data);
void* LinkedListAt_(LinkedListBase* ll, unsigned int index);
void LinkedListClear_(LinkedListBase* ll);
void LinkedListDelete_(LinkedListBase* ll);
unsigned int LinkedListSize_(LinkedListBase* ll);

typedef LinkedListT(void*) LinkedList;
typedef LinkedListT(double) LinkedListDouble;
typedef LinkedListT(float) LinkedListFloat;
typedef LinkedListT(int) LinkedListInt;
typedef LinkedListT(char*) LinkedListString;
typedef LinkedListT(char) LinkedListChar;
typedef LinkedListT(bool) LinkedListBool;

#endif