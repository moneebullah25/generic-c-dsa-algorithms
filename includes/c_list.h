#ifndef _C_LIST_HEADER_
#define _C_LIST_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif

#define bool _Bool
#define false 0
#define true 1

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
**/
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
**/
#define LinkedListT(T) \
struct { LinkedListBase base; T data_; T value_; }

/**
 * A macro that creates a new linked list with a given comparison function and a function to free memory.
 * The macro calls the LinkedListNew_ function with the address of the base member of the LinkedListBase struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param ll Pointer to the linked list struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define LinkedListNew(ll, DataCmp, FreeFunc) \
	LinkedListNew_(&(ll)->base, sizeof((ll)->data_), DataCmp, FreeFunc)

/**
 * A macro that inserts data at tail in the linked list pointer passed as argument.
 * The macro calls the LinkedListInsertAtTail_ function with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll Pointer to the linked list struct
 * @param data Data to be stored in linked list
**/
#define LinkedListInsertAtTail(ll, data) \
	((ll)->data_ = data, \
	LinkedListInsertAtTail_(&(ll)->base, &(ll)->data_))

/**
 * A macro that inserts data at head in the linked list pointer passed as argument.
 * The macro calls the LinkedListInsertAtHead_ function with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll Pointer to the linked list struct
 * @param data Data to be stored in linked list
**/
#define LinkedListInsertAtHead(ll, data) \
	((ll)->data_ = data, \
	LinkedListInsertAtHead_(&(ll)->base, &(ll)->data_))

/**
 * Macro that replaces the element with the specified data with the specified value in the linked list.
 * The macro LinkedListReplace calls the function LinkedListReplace_ with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll pointer to the linked list
 * @param data pointer to the data of the element to be replaced
 * @param value pointer to the new value to be set
**/
#define LinkedListReplace(ll, data, value) \
	((ll)->data_ = data, \
	(ll)->value_ = value, \
	LinkedListReplace_(&(ll)->base, &(ll)->data_, &(ll)->value_))

/**
 * Macro that replaces all the elements with the specified data with the specified value in the linked list.
 * The macro LinkedListReplaceAll calls the function LinkedListReplaceAll_ with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll pointer to the linked list
 * @param data pointer to the data of the elements to be replaced
 * @param value pointer to the new value to be set
**/
#define LinkedListReplaceAll(ll, data, value) \
	((ll)->data_ = data, \
	(ll)->value_ = value, \
	LinkedListReplaceAll_(&(ll)->base, &(ll)->data_, &(ll)->value_))

/**
 * Macro that gets the index of the first element with the specified data in the linked list.
 * The macro LinkedListGetIndex calls the function LinkedListGetIndex_ with the address of the base member of the LinkedListBase struct and the address of the data_ member of the linked list struct as arguments.
 * @param ll pointer to the linked list
 * @param data pointer to the data of the element for which the index needs to be found
 * @return returns the index of the first element with the specified data, if not found returns -1
**/
#define LinkedListGetIndex(ll, data) \
	((ll)->data_ = data, \
	LinkedListGetIndex_(&(ll)->base, &(ll)->data_))

/**
 * Macro that gets the element at the specified index in the linked list.
 * The macro LinkedListAt calls the function LinkedListAt_ with the address of the base member of the LinkedListBase struct and the index as arguments.
 * @param ll pointer to the linked list
 * @param index index of the element which needs to be found
 * @return returns the element at the specified index
**/
#define LinkedListAt(ll, index) \
	LinkedListAt_(&(ll)->base, index)

/**
 * Macro that clears all the elements in the linked list.
 * The macro LinkedListClear calls the function LinkedListClear_ with the address of the base member of the LinkedListBase struct as an argument.
 * @param ll pointer to the linked list
**/
#define LinkedListClear(ll) \
	LinkedListClear_(&(ll)->base)

/**
 * Macro that deletes the linked list.
 * The macro LinkedListDelete calls the function LinkedListDelete_ with the address of the base member of the LinkedListBase struct as an argument.
 * @param ll pointer to the linked list
**/
#define LinkedListDelete(ll) \
	LinkedListDelete_(&(ll)->base)

/**
 * Macro that gets the number of elements in the linked list.
 * The macro LinkedListSize calls the function LinkedListSize_ with the address of the base member of the LinkedListBase struct
 * @param ll pointer to the linked list
**/
#define LinkedListSize(ll) \
	LinkedListSize_(&(ll)->base)

/**
 * Function that creates a new linked list and initializes the base member of the LinkedListBase struct.
 * The function allocates memory for the head node of the linked list and initializes its data and value members with NULL.
 * The function also assigns the passed element size, data comparison function and free function to the corresponding members of the base struct.
 * The function asserts that the element size passed is greater than 0.
 * @param ll pointer to the linked list
 * @param elemsize size of the element to be stored in the linked list
 * @param DataCmp pointer to the data comparison function
 * @param FreeFunc pointer to the free function
 * Requirements:
 * - ll pointer should not be nullptr
 * - elemsize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void LinkedListNew_(LinkedListBase* ll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
	
/**
 * Function that inserts the passed data at the tail of the linked list.
 * The function creates a new node, assigns the passed data to the node's data member and sets the node's next pointer to NULL.
 * The function then updates the tail pointer of the linked list to point to the new node.
 * The function asserts that the passed linked list pointer is not NULL.
 * @param ll pointer to the linked list
 * @param data pointer to the data to be inserted
 * Requirements:
 * - ll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void LinkedListInsertAtTail_(LinkedListBase* ll, void* data);

/**
 * Function that inserts the passed data at the head of the linked list.
 * The function creates a new node, assigns the passed data to the node's data member and sets the node's next pointer to the current head of the linked list.
 * The function then updates the head pointer of the linked list to point to the new node.
 * The function asserts that the passed linked list pointer is not NULL.
 * @param ll pointer to the linked list
 * @param data pointer to the data to be inserted
 * Requirements:
 * - ll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void LinkedListInsertAtHead_(LinkedListBase* ll, void* data);

/**
 * Function that replaces the first occurrence of the data in the linked list with the passed value.
 * The function asserts that the linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param ll pointer to the linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - ll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void LinkedListReplace_(LinkedListBase* ll, void* data, void* value);

/**
 * Function that replaces all occurrences of the data in the linked list with the passed value.
 * The function asserts that the linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param ll pointer to the linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - ll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void LinkedListReplaceAll_(LinkedListBase* ll, void* data, void* value);

/**
 * Function that returns the index of the first occurrence of the specified data in the linked list.
 * The function iterates through the linked list and compares the data of each node with the specified data using the DataCmp function of the base struct.
 * The function returns the index of the first occurrence of the specified data in the linked list.
 * If the specified data is not found in the linked list, the function returns -1.
 * @param ll pointer to the linked list
 * @param data pointer to the data to be searched in the linked list
 * Requirements:
 * - ll pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
int LinkedListGetIndex_(LinkedListBase* ll, void* data);

/**
 * Function that returns the data of the node at the specified index in the linked list.
 * The function asserts that the specified index is within the valid range of the linked list.
 * @param ll pointer to the linked list
 * @param index index of the node whose data is to be returned
 * Requirements:
 * - ll pointer should not be nullptr
 * - index should be greater than or equal to 0 and less than the size of the linked list
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void* LinkedListAt_(LinkedListBase* ll, unsigned int index);

/**
 * Function that clears all elements from the linked list and resets the list size to 0.
 * The function iterates through the list and calls the free function on each element to free their memory.
 * The function also sets the head and tail pointers to NULL.
 * @param ll pointer to the linked list
 * Requirements:
 * - ll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void LinkedListClear_(LinkedListBase* ll);

/**
 * Function that deletes the linked list by clearing all elements and freeing the memory allocated for the head node.
 * The function calls the LinkedListClear_ function to clear all elements and then frees the memory allocated for the head node.
 * @param ll pointer to the linked list
 * Requirements:
 * - ll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void LinkedListDelete_(LinkedListBase* ll);

/**
 * Function that returns the number of elements in the linked list.
 * @param ll pointer to the linked list
 * Requirements:
 * - ll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
unsigned int LinkedListSize_(LinkedListBase* ll);

/**
 * Define a linked list of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(void*) LinkedList;

/**
 * Define a linked list of double values.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(double) LinkedListDouble;

/**
 * Define a linked list of float values.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(float) LinkedListFloat;

/**
 * Define a linked list of signed integer values.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(int) LinkedListInt;

/**
 * Define a linked list of pointer to character(s).
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(char*) LinkedListString;

/**
 * Define a linked list of character.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(char) LinkedListChar;

/**
 * Define a linked list of boolean values.
 * Time complexity:
 * - Depends on the operations performed on the linked list.
**/
typedef LinkedListT(bool) LinkedListBool;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_LIST_HEADER_ */