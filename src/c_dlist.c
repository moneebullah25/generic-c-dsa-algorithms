#include "../includes/c_dlist.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

static void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data)
{
	ASSERT(elemsize > 0);
	ln->elemsize = elemsize;
	ln->elem = malloc(ln->elemsize);
	ln->next = NULL;
	ln->back = NULL;
	ASSERT(ln->elem != NULL);
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
	ASSERT(elemsize > 0);
	dll->elemsize = elemsize;
	dll->listsize = 0;
	dll->head = (ListNode*)malloc(sizeof(ListNode));
	dll->tail = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(dll->head != NULL && dll->tail != NULL);
	dll->head = NULL;
	dll->tail = NULL;
	dll->DataCmp = DataCmp;
	dll->FreeFunc = FreeFunc;
}

void DoublyLinkedListInsertAtTail_(DoublyLinkedListBase* dll, void* data)
{
	ASSERT(dll != NULL);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node != NULL);
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
	ASSERT(dll != NULL);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node != NULL);
	ListNodeNew(node, dll->elemsize, data);
	if (dll->head == NULL)
	{
		dll->head = dll->tail = node;
	}
	else
	{
		dll->head->prev = node;
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
	while (temp != NULL)
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
	while (temp != NULL)
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
	while (temp != NULL)
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
	while (temp != NULL)
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
	ASSERT(dll != NULL);
	ListDelete(dll->head, dll->FreeFunc);
	dll->head = dll->tail = NULL;
	dll->listsize = 0;
}

void DoublyLinkedListDelete_(DoublyLinkedListBase* dll)
{
	ASSERT(dll != NULL);
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

DoublyLinkedListIter * DoublyLinkedListNext_(DoublyLinkedListBase * dll, DoublyLinkedListIter * lliter)
{
	ASSERT(dll);
	if (dll->listsize == 0 || lliter->index + 1 == v->logiclen){ v->FreeFunc(lliter->data); return NULL; };
	lliter->index = lliter->index + 1;
	lliter->data = DoublyLinkedListAt_(dll, dll->index);
	return lliter;
}

DoublyLinkedListIter * DoublyLinkedListBack_(DoublyLinkedListBase * dll, DoublyLinkedListIter * lliter)
{
	ASSERT(dll);
	if (dll->listsize == 0 || lliter->index + 1 == v->logiclen){ v->FreeFunc(lliter->data); return NULL; };
	if (lliter->index == -1) {lliter->data = dll->tail->data; lliter->index = dll->listsize - 1; return lliter;}
	lliter->index = lliter->index - 1;
	lliter->data = DoublyLinkedListAt_(dll, dll->index);
	return lliter;
}