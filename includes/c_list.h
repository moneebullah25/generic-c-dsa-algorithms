#ifndef _C_LIST_HEADER_
#define _C_LIST_HEADER_

#include "c_helper.h"

#define MAX_UNSIGNED 4294967295

typedef struct ListNode {
	void* elem;
	size_t elemsize;
	struct ListNode* next;
} ListNode;

typedef struct LinkedListBase {
	ListNode* head; ListNode* tail;
	size_t listsize; size_t elemsize;

	int(*DataCmp)(const void *key1, const void *key2, size_t keysize);
	void(*FreeFunc)(void* elems);
} LinkedListBase;

#define LinkedListT(T) \
struct { LinkedListBase base; T data_; T value_; }

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

#define LinkedListGetIndex(ll, data) \
	((ll)->data_ = data, \
	LinkedListGetIndex_(&(ll)->base, &(ll)->data_))

#define LinkedListAt(ll, index) \
	LinkedListAt_(&(ll)->base, index)

#define LinkedListClear(ll) \
	LinkedListClear_(&(ll)->base)

#define LinkedListDelete(ll) \
	LinkedListDelete_(&(ll)->base)

#define LinkedListSize(ll) \
	LinkedListSize_(&(ll)->base)

void LinkedListNew_(LinkedListBase* ll, size_t elemsize,
	int(*DataCmp)(const void *key1, const void *key2, size_t keysize),
	void(*FreeFunc)(void* elems));
void LinkedListInsertAtTail_(LinkedListBase* ll, void* data);
void LinkedListInsertAtHead_(LinkedListBase* ll, void* data);
/*Replace Data with Value once*/
void LinkedListReplace_(LinkedListBase* ll, void* data, void* value);
/*Replace Data with Value unless doesn't find any*/
void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value);
int LinkedListGetIndex_(LinkedListBase* ll, void* data);
void* LinkedListAt_(LinkedListBase* ll, size_t index);
void LinkedListClear_(LinkedListBase* ll);
void LinkedListDelete_(LinkedListBase* ll);
size_t LinkedListSize_(LinkedListBase* ll);

typedef LinkedListT(void*) LinkedList;
typedef LinkedListT(double) LinkedListDouble;
typedef LinkedListT(float) LinkedListFloat;
typedef LinkedListT(int) LinkedListInt;
typedef LinkedListT(char*) LinkedListString;
typedef LinkedListT(char) LinkedListChar;
typedef LinkedListT(bool) LinkedListBool;

#endif