#ifndef _C_LIST_HEADER_
#define _C_LIST_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "c_helper.h"

/**
 * A structure that represents the basic functionality of a list node.
 * @param elems A pointer to the element of the list node
 * @param elemsize The size of an element
 * @param next A pointer to a next list node
**/
typedef struct ListNode {
	void* elem;
	unsigned int elemsize;
	struct ListNode* next;
} ListNode;

/**
 * A structure that represents the basic functionality of a linked list.
 * @param head A pointer to the first element of the linked list
 * @param tail A pointer to the last element of the linked list
 * @param listsize The number of elements in the linked list 
 * @param elemsize The size of an elem in list node
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
*/
typedef struct LinkedListBase {
	ListNode* head; ListNode* tail;
	unsigned int listsize; unsigned int elemsize;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} LinkedListBase;

/**
 * A macro that creates a linked list template for a given data type T.
 * The macro creates a struct with a LinkedListBase as a member and an additional member with the name data_ of the type T and value_ of the type T.
 * @param T The type of the data the linked list will hold
*/
#define LinkedListT(T) \
struct { LinkedListBase base; T data_; T value_; }

/**
 * A macro that creates a new linked list with a given comparison function and a function to free memory.
 * The macro calls the LinkedListNew_ function with the address of the base member of the LinkedListBase struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param ll Pointer to the linked list struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
*/
#define LinkedListNew(ll, DataCmp, FreeFunc) \
	LinkedListNew_(&(ll)->base, sizeof((ll)->data_), DataCmp, FreeFunc)

/**
 * A macro that inserts data at tail in the linked list pointer passed as argument.
 * The macro calls the LinkedListInsertAtTail_ function with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll Pointer to the linked list struct
 * @param data Data to be stored in linked list
*/
#define LinkedListInsertAtTail(ll, data) \
	((ll)->data_ = data, \
	LinkedListInsertAtTail_(&(ll)->base, &(ll)->data_))

/**
 * A macro that inserts data at head in the linked list pointer passed as argument.
 * The macro calls the LinkedListInsertAtHead_ function with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll Pointer to the linked list struct
 * @param data Data to be stored in linked list
*/
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

void LinkedListNew_(LinkedListBase* ll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
void LinkedListInsertAtTail_(LinkedListBase* ll, void* data);
void LinkedListInsertAtHead_(LinkedListBase* ll, void* data);
/*Replace Data with Value once*/
void LinkedListReplace_(LinkedListBase* ll, void* data, void* value);
/*Replace Data with Value unless doesn't find any*/
void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value);
int LinkedListGetIndex_(LinkedListBase* ll, void* data);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_LIST_HEADER_ */