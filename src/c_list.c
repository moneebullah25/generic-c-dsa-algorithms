#include "../includes/c_list.h"


static void ListNodeNew(ListNode* ln, size_t elemsize, void* data)
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

void LinkedListNew_(LinkedListBase* ll, size_t elemsize,
	int(*DataCmp)(const void *key1, const void *key2, size_t keysize),
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
	void* temp = (ListNode*)ll->head;
	while (temp != NULL)
	{
		if (ll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
			break;
		}
		temp = ((ListNode*)temp)->next;
	}
}

void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value)
{
	ASSERT(ll);
	if (!ll->head) return;
	void* temp = (ListNode*)ll->head;
	while (temp != NULL)
	{
		if (ll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			MemoryCopy(((ListNode*)temp)->elem, value, ((ListNode*)temp)->elemsize);
		}
		temp = ((ListNode*)temp)->next;
	}
}

int LinkedListGetIndex_(LinkedListBase* ll, void* data)
{
	ASSERT(ll);
	if (!ll->head) return -1;
	void* temp = (ListNode*)ll->head;
	size_t retindex = 0;
	while (temp != NULL)
	{
		if (ll->DataCmp(((ListNode*)temp)->elem, data, ((ListNode*)temp)->elemsize) == 0)
		{
			return retindex;
		}
		temp = ((ListNode*)temp)->next;
		retindex++;
	}
	return -1;
}

void* LinkedListAt_(LinkedListBase* ll, size_t index)
{
	ASSERT(ll);
	if (!ll->head) return NULL;
	void* temp = (ListNode*)ll->head;
	size_t retindex = 0;
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
void LinkedListClear_(LinkedListBase* ll)
{
	ASSERT(ll != NULL);
	ListDelete(ll->head, ll->FreeFunc);
	ll->head = ll->tail = NULL;
	ll->listsize = 0;
}

void LinkedListDelete_(LinkedListBase* ll)
{
	ASSERT(ll != NULL);
	ListDelete(ll->head, ll->FreeFunc);
	ll->FreeFunc(ll);
}


size_t LinkedListSize_(LinkedListBase* ll)
{
	return ll->listsize;
}