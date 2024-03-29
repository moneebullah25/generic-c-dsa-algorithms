#include "../includes/c_dlist.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

static void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data)
{
	ASSERT(elemsize);
	ln->elemsize = elemsize;
	ln->elem = malloc(ln->elemsize);
	ln->next = NULL;
	ln->back = NULL;
	ASSERT(ln->elem);
	MemoryCopy(ln->elem, data, elemsize);
}

static void ListDelete(ListNode* node, void(*FreeFunc)(void* elems)) {
	if (node == NULL) {
		return;
	}
	ListDelete(node->next, FreeFunc);
	FreeFunc(node->elem);
	FreeFunc(node);
}

void DoublyLinkedListNew_(DoublyLinkedListBase* dll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elemsize);
	dll->elemsize = elemsize;
	dll->listsize = 0;
	dll->head = NULL;
	dll->tail = NULL;
	dll->DataCmp = DataCmp;
	dll->FreeFunc = FreeFunc;
}

void DoublyLinkedListInsertAtTail_(DoublyLinkedListBase* dll, void* data)
{
	ASSERT(dll);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node);
	ListNodeNew(node, dll->elemsize, data);
	if (dll->head == NULL)
	{
		dll->head = dll->tail = node;
	}
	else
	{
		node->back = dll->tail;
		dll->tail->next = node;
		dll->tail = node;
	}
	dll->listsize++;
}

void DoublyLinkedListInsertAtHead_(DoublyLinkedListBase* dll, void* data)
{
	ASSERT(dll);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node);
	ListNodeNew(node, dll->elemsize, data);
	if (dll->head == NULL)
	{
		dll->head = dll->tail = node;
	}
	else
	{
		dll->head->back = node;
		node->next = dll->head;
		dll->head = node;
	}
	dll->listsize++;
}

void DoublyLinkedListReplace_(DoublyLinkedListBase* dll, void* data, void* value)
{
	ASSERT(dll);
	if (!dll->head) return;
	void* temp = (ListNode*)dll->head;
	while (temp)
	{
		if (dll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
			break;
		}
		temp = ((ListNode*)temp)->next;
	}
}

void DoublyLinkedListReplaceAll_(DoublyLinkedListBase* dll, void* data, void* value)
{
	ASSERT(dll);
	if (!dll->head) return;
	void* temp = (ListNode*)dll->head;
	while (temp)
	{
		if (dll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
		}
		temp = ((ListNode*)temp)->next;
	}
}

int DoublyLinkedListGetIndex_(DoublyLinkedListBase* dll, void* data)
{
	ASSERT(dll);
	if (!dll->head) return -1;
	void* temp = (ListNode*)dll->head;
	unsigned int retindex = 0;
	while (temp)
	{
		if (dll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			return retindex;
		}
		temp = ((ListNode*)temp)->next;
		retindex++;
	}
	return -1;
}

void* DoublyLinkedListAt_(DoublyLinkedListBase* dll, unsigned int index)
{
	ASSERT(dll);
	if (!dll->head) return NULL;
	void* temp = (ListNode*)dll->head;
	unsigned int retindex = 0;
	while (temp)
	{
		if (index == retindex)
		{
			return ((ListNode*)temp)->elem;
		}
		temp = ((ListNode*)temp)->next;
		retindex++;
	}
	return NULL;
}

void DoublyLinkedListClear_(DoublyLinkedListBase* dll)
{
	ASSERT(dll);
	ListDelete(dll->head, dll->FreeFunc);
	dll->head = dll->tail = NULL;
	dll->listsize = 0;
}

void DoublyLinkedListDelete_(DoublyLinkedListBase* dll)
{
	ASSERT(dll);
	ListDelete(dll->head, dll->FreeFunc);
	dll->FreeFunc(dll);
}

unsigned int DoublyLinkedListSize_(DoublyLinkedListBase* dll)
{
	return dll->listsize;
}

DoublyLinkedListIter * DoublyLinkedListIterator_(DoublyLinkedListBase * dll)
{
	ASSERT(dll);
	if (dll->listsize == 0) return NULL;
	void* n = malloc(sizeof(DoublyLinkedListIter));
	((DoublyLinkedListIter*)n)->data = malloc(dll->elemsize);
	((DoublyLinkedListIter*)n)->index = -1;
	return ((DoublyLinkedListIter*)n);
}

DoublyLinkedListIter * DoublyLinkedListNext_(DoublyLinkedListBase * dll, DoublyLinkedListIter * dlliter)
{
	ASSERT(dll);
	if (dll->listsize == 0 || dlliter->index + 1 == dll->listsize){ dll->FreeFunc(dlliter->data); return NULL; };
	dlliter->index = dlliter->index + 1;
	MemoryCopy(dlliter->data, DoublyLinkedListAt_(dll, dlliter->index), dll->elemsize);
	return dlliter;
}

DoublyLinkedListIter * DoublyLinkedListBack_(DoublyLinkedListBase * dll, DoublyLinkedListIter * dlliter)
{
	ASSERT(dll);
	if (dll->listsize == 0 || dlliter->index + 1 == dll->listsize) { dll->FreeFunc(dlliter->data); return NULL; };
	dlliter->index = dlliter->index + 1;
	MemoryCopy(dlliter->data, DoublyLinkedListAt_(dll, dll->listsize - dlliter->index - 1), dll->elemsize);
	return dlliter;
}