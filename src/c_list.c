#include "../includes/c_list.h"


static void ListNodeNew(ListNode* ln, unsigned int elemsize, void* data)
{
	ASSERT(elemsize > 0);
	ln->elemsize = elemsize;
	ln->elem = malloc(ln->elemsize);
	ln->next = NULL;
	ASSERT(ln->elem != NULL);
	MemoryCopy(ln->elem, data, elemsize);
}

static void ListDelete(ListNode* node) {
	if (node == NULL) {
		return;
	}
	ListDelete(node->next);
	free(node->elem);
	free(node);
}

void LinkedListNew_(LinkedListBase* ll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
	ASSERT(elemsize > 0);
	ll->elemsize = elemsize;
	ll->listsize = 0;
	ll->head = (ListNode*)malloc(sizeof(ListNode));
	ll->tail = (ListNode*)malloc(sizeof(ListNode));
	ASSERT(ll->head != NULL && ll->tail != NULL);
	ll->head = NULL;
	ll->tail = NULL;
	ll->DataCmp = DataCmp;
	ll->FreeFunc = FreeFunc;
}

void LinkedListInsertAtTail_(LinkedListBase* ll, void* data)
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

void LinkedListInsertAtHead_(LinkedListBase* ll, void* data)
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

void LinkedListReplace_(LinkedListBase* ll, void* data, void* value)
{
	ASSERT(ll);
	if (!ll->head) return;
	ListNode* temp = ll->head;
	while (temp->next != NULL)
	{
		if (ll->DataCmp(temp->elem, data, temp->elemsize) == 0)
		{
			MemoryCopy(temp->elem, value, temp->elemsize);
			break;
		}
		temp = temp->next;
	}
}

void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value)
{
	ASSERT(ll);
	if (!ll->head) return;
	ListNode* temp = ll->head;
	while (temp->next != NULL)
	{
		if (ll->DataCmp(temp->elem, data, temp->elemsize) == 0)
		{
			MemoryCopy(temp->elem, value, temp->elemsize);
		}
		temp = temp->next;
	}
}

int LinkedListGetIndex_(LinkedListBase* ll, void* data)
{
	ASSERT(ll);
	if (!ll->head) return -1;
	ListNode* temp = ll->head;
	unsigned int retindex = 0;
	while (temp->next != NULL)
	{
		if (ll->DataCmp(temp->elem, data, temp->elemsize) == 0)
		{
			return retindex;
		}
		temp = temp->next;
		retindex++;
	}
	return -1;
}

void* LinkedListAt_(LinkedListBase* ll, unsigned int index)
{
	ASSERT(ll);
	if (!ll->head) return NULL;
	ListNode* temp = ll->head;
	unsigned int retindex = 0;
	while (temp != NULL)
	{
		if (index == retindex)
		{
			return temp->elem;
		}
		temp = temp->next;
		retindex++;
	}
	return NULL;
}
void LinkedListClear_(LinkedListBase* ll)
{
	ASSERT(ll != NULL);
	ListDelete(ll->head);
	ll->head = ll->tail = NULL;
	ll->listsize = 0; 
}

void LinkedListDelete_(LinkedListBase* ll)
{
	ASSERT(ll != NULL);
	ListDelete(ll->head);
	ll->FreeFunc(ll);
}


unsigned int LinkedListSize_(LinkedListBase* ll)
{
	return ll->listsize;
}