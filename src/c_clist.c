#include "../includes/c_clist.h"
#include "../includes/c_helper.h"
#include <stdlib.h>

static void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data)
{
	ASSERT(elemsize > 0);
	ln->elemsize = elemsize;
	ln->elem = malloc(ln->elemsize);
	ln->next = NULL;
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

void CircularLinkedListNew_(CircularLinkedListBase* cll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elemsize > 0);
	cll->elemsize = elemsize;
	cll->listsize = 0;
	cll->head = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(cll->head != NULL);
	cll->head = NULL;
	cll->DataCmp = DataCmp;
	cll->FreeFunc = FreeFunc;
}

void CircularLinkedListInsert_(CircularLinkedListBase* cll, void* data)
{
	ASSERT(cll != NULL);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node != NULL);
	ListNodeNew(node, cll->elemsize, data);
	if (cll->head == NULL)
	{
		cll->head = node;
		node->next = cll->head;
	}
	else
	{
		ListNode* temp = (ListNode*)cll->head;
		while (temp->next != cll->head)
			temp = temp->next;
		temp->next = node;
		node->next = cll->head;
	}
	cll->listsize++;
}

void CircularLinkedListReplace_(CircularLinkedListBase* cll, void* data, void* value)
{
	ASSERT(cll);
	if (!cll->head) return;
	ListNode* temp = (ListNode*)cll->head;
	while (temp->next != cll->head)
	{
		if (cll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
			break;
		}
		temp = ((ListNode*)temp)->next;
	}
}

void CircularLinkedListReplaceAll_(CircularLinkedListBase* cll, void* data, void* value)
{
	ASSERT(cll);
	if (!cll->head) return;
	ListNode* temp = (ListNode*)cll->head;
	while (temp->next != cll->head)
	{
		if (cll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
		}
		temp = ((ListNode*)temp)->next;
	}
}

int CircularLinkedListGetIndex_(CircularLinkedListBase* cll, void* data)
{
	ASSERT(cll);
	if (!cll->head) return -1;
	unsigned int retindex = 0;
	ListNode* temp = (ListNode*)cll->head;
	while (temp->next != cll->head)
	{
		if (cll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			return retindex;
		}
		temp = ((ListNode*)temp)->next;
		retindex++;
	}
	return -1;
}

void* CircularLinkedListAt_(CircularLinkedListBase* cll, unsigned int index)
{
	ASSERT(cll);
	if (!cll->head) return NULL;
	unsigned int retindex = 0;
	ListNode* temp = (ListNode*)cll->head;
	while (temp->next != cll->head)
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

void CircularLinkedListClear_(CircularLinkedListBase* cll)
{
	ASSERT(cll != NULL);
	ListDelete(cll->head, cll->FreeFunc);
	cll->head = NULL;
	cll->listsize = 0;
}

void CircularLinkedListDelete_(CircularLinkedListBase* cll)
{
	ASSERT(cll != NULL);
	ListDelete(cll->head, cll->FreeFunc);
	cll->FreeFunc(cll);
}

unsigned int CircularLinkedListSize_(CircularLinkedListBase* cll)
{
	return cll->listsize;
}

CircularLinkedListIter * CircularLinkedListIterator_(CircularLinkedListBase * cll)
{
	ASSERT(cll);
	if (cll->listsize == 0) return NULL;
	void* n = malloc(sizeof(CircularLinkedListIter));
	((CircularLinkedListIter*)n)->data = malloc(cll->elemsize);
	((CircularLinkedListIter*)n)->index = -1;
	return ((CircularLinkedListIter*)n);
}

CircularLinkedListIter * CircularLinkedListNext_(CircularLinkedListBase * cll, CircularLinkedListIter * clliter)
{
	ASSERT(cll);
	if (cll->listsize == 0 || clliter->index + 1 == cll->listsize){ cll->FreeFunc(clliter->data); return NULL; };
	clliter->index = clliter->index + 1;
	MemoryCopy(clliter->data, CircularLinkedListAt_(cll, clliter->index), cll->elemsize);
	return clliter;
}