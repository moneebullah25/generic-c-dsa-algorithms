#ifndef _C_LIST_HEADER_
#define _C_LIST_HEADER_

#include "c_helper.h"

#define MAX_UNSIGNED 4294967295

typedef struct {
	void* elem;
	unsigned int elemsize;
	struct ListNode* next;
} ListNode;

void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data);

typedef struct {
	ListNode* head; ListNode* tail;
	unsigned int listsize; unsigned int elemsize;
} LinkedList;

void LinkedListNew(LinkedList* ll, unsigned int elemsize);
void LinkedListInsert(LinkedList* ll, void* data);
void LinkedListInsertAtHead(LinkedList* ll, void* data);
/*Replace Data with Value once*/
void LinkedListReplace(LinkedList* ll, void* data, void* value, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
/*Replace Data with Value unless doesn't find any*/
void LinkedListReplaceAll(LinkedList* ll, void* data, void* value, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
unsigned int LinkedListGetIndex(LinkedList* ll, void* data, int(*MemCmp)(void* a, void* b, unsigned int elembytes));
ListNode* LinkedListAt(LinkedList* ll, unsigned int index);

#endif