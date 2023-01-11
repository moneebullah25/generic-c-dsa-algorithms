#include "c_list.h"


void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data)
{
	ASSERT(elemsize > 0);
	ln->elemsize = elemsize;
	ln->elem = malloc(ln->elemsize);
	ln->next = NULL;
	ASSERT(ln->elem != NULL);
	MemoryCopy(ln->elem, data, elemsize);
}

void LinkedListNew(LinkedList* ll, unsigned int elemsize)
{
	ASSERT(elemsize > 0);
	ll->elemsize = elemsize;
	ll->listsize = 0;
	ll->head = (ListNode*)malloc(sizeof(ListNode));
	ll->tail = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(ll->head != NULL && ll->tail != NULL);
	ll->head = NULL;
	ll->tail = NULL;
}

void LinkedListInsertAtTail(LinkedList* ll, void* data)
{
	ASSERT(ll != NULL);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node != NULL);
	ListNodeNew(node, ll->elemsize, data);
	if (ll->head == NULL)
	{
		ll->head = ll->tail = node;
	}
	else
	{
		ll->tail->next = node;
		ll->tail = node;
	}
	ll->listsize++;
}

void LinkedListInsertAtHead(LinkedList* ll, void* data)
{
	ASSERT(ll != NULL);
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(node != NULL);
	ListNodeNew(node, ll->elemsize, data);
	if (ll->head == NULL)
	{
		ll->head = ll->tail = node;
	}
	else
	{
		node->next = ll->head;
		ll->head = node;
	}
	ll->listsize++;
}

void LinkedListReplace(LinkedList* ll, void* data, void* value, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	ASSERT(ll != NULL);
	ListNode* temp = ll->head;
	while (temp->next != NULL)
	{
		if (MemCmp(temp->elem, data, temp->elemsize) == 0)
		{
			MemoryCopy(temp->elem, value, temp->elemsize);
			break;
		}
		temp = temp->next;
	}
}

void LinkedListReplaceAll(LinkedList* ll, void* data, void* value, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	ASSERT(ll != NULL);
	ListNode* temp = ll->head;
	while (temp->next != NULL)
	{
		if (MemCmp(temp->elem, data, temp->elemsize) == 0)
		{
			MemoryCopy(temp->elem, value, temp->elemsize);
		}
		temp = temp->next;
	}
}

unsigned int LinkedListGetIndex(LinkedList* ll, void* data, int(*MemCmp)(void* a, void* b, unsigned int elembytes))
{
	ASSERT(ll != NULL);
	ListNode* temp = ll->head;
	unsigned int retindex = 0;
	while (temp->next != NULL)
	{
		if (MemCmp(temp->elem, data, temp->elemsize) == 0)
		{
			return retindex;
		}
		temp = temp->next;
		retindex++;
	}
	return MAX_UNSIGNED;
}

ListNode* LinkedListAt(LinkedList* ll, unsigned int index)
{
	ASSERT(ll != NULL);
	ListNode* temp = ll->head;
	unsigned int retindex = 0;
	while (temp->next != NULL)
	{
		if (index == retindex)
		{
			return temp;
		}
		temp = temp->next;
		retindex++;
	}
	return NULL;
}

static void ListDelete(ListNode* head)
{
	if (head == NULL)
		return;
	ListDelete(head->next);
	free(head);
}

void LinkedListDispose(LinkedList* ll)
{
	ASSERT(ll != NULL);
	ListDelete(ll->head);
	ll->listsize = 0;
	ll->head = ll->tail = NULL;
}
