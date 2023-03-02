#ifndef _C_CLIST_HEADER_
#define _C_CLIST_HEADER_

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
 * @param back A pointer to a previous list node
**/
typedef struct ListNode {
	void* elem;
	unsigned int elemsize;
	struct ListNode* next;
	struct ListNode* back;
} ListNode;

/**
 * A structure that represents an iterator for a doubly linked list.
 * @param data A pointer to the data of the current element
 * @param index The index of the current element
**/
typedef struct DoublyLinkedListIter{
	void * data;
	int index;
}DoublyLinkedListIter;

/**
 * A structure that represents the basic functionality of a doubly linked list.
 * @param head A pointer to the first element of the doubly linked list
 * @param tail A pointer to the last element of the doubly linked list
 * @param listsize The number of elements in the doubly linked list 
 * @param elemsize The size of an elem in list node
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
typedef struct DoublyLinkedListBase {
	ListNode* head; ListNode* tail;
	unsigned int listsize; unsigned int elemsize;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} DoublyLinkedListBase;


/**
 * A macro that creates a doubly linked list template for a given data type T.
 * The macro creates a struct with a DoublyLinkedListBase as a member and an additional member with the name data_ of the type T and value_ of the type T.
 * @param T The type of the data the doubly linked list will hold
**/
#define DoublyLinkedListT(T) \
struct { DoublyLinkedListBase base; T data_; T value_; }

/**
 * A macro that creates a new doubly linked list with a given comparison function and a function to free memory.
 * The macro calls the DoublyLinkedListNew_ function with the address of the base member of the DoublyLinkedListBase struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param dll Pointer to the doubly linked list struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define DoublyLinkedListNew(dll, DataCmp, FreeFunc) \
	DoublyLinkedListNew_(&(dll)->base, sizeof((dll)->data_), DataCmp, FreeFunc)

/**
 * A macro that inserts data at tail in the doubly linked list pointer passed as argument.
 * The macro calls the DoublyLinkedListInsertAtTail_ function with the address of the base member of the DoublyLinkedListBase struct and the address of the data_ member of the doubly linked list struct as arguments.
 * @param dll Pointer to the doubly linked list struct
 * @param data Data to be stored in doubly linked list
**/
#define DoublyLinkedListInsertAtTail(dll, data) \
	((dll)->data_ = data, \
	DoublyLinkedListInsertAtTail_(&(dll)->base, &(dll)->data_))

/**
 * A macro that inserts data at head in the doubly linked list pointer passed as argument.
 * The macro calls the DoublyLinkedListInsertAtHead_ function with the address of the base member of the DoublyLinkedListBase struct and the address of the data_ member of the doubly linked list struct as arguments.
 * @param dll Pointer to the doubly linked list struct
 * @param data Data to be stored in doubly linked list
**/
#define DoublyLinkedListInsertAtHead(dll, data) \
	((dll)->data_ = data, \
	DoublyLinkedListInsertAtHead_(&(dll)->base, &(dll)->data_))

/**
 * Macro that replaces the element with the specified data with the specified value in the doubly linked list.
 * The macro DoublyLinkedListReplace calls the function DoublyLinkedListReplace_ with the address of the base member of the DoublyLinkedListBase struct and the address of the data_ member of the doubly linked list struct as arguments.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data of the element to be replaced
 * @param value pointer to the new value to be set
**/
#define DoublyLinkedListReplace(dll, data, value) \
	((dll)->data_ = data, \
	(dll)->value_ = value, \
	DoublyLinkedListReplace_(&(dll)->base, &(dll)->data_, &(dll)->value_))

/**
 * Macro that replaces all the elements with the specified data with the specified value in the doubly linked list.
 * The macro DoublyLinkedListReplaceAll calls the function DoublyLinkedListReplaceAll_ with the address of the base member of the DoublyLinkedListBase struct and the address of the data_ member of the doubly linked list struct as arguments.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data of the elements to be replaced
 * @param value pointer to the new value to be set
**/
#define DoublyLinkedListReplaceAll(dll, data, value) \
	((dll)->data_ = data, \
	(dll)->value_ = value, \
	DoublyLinkedListReplaceAll_(&(dll)->base, &(dll)->data_, &(dll)->value_))

/**
 * Macro that gets the index of the first element with the specified data in the doubly linked list.
 * The macro DoublyLinkedListGetIndex calls the function DoublyLinkedListGetIndex_ with the address of the base member of the DoublyLinkedListBase struct and the address of the data_ member of the doubly linked list struct as arguments.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data of the element for which the index needs to be found
 * @return returns the index of the first element with the specified data, if not found returns -1
**/
#define DoublyLinkedListGetIndex(dll, data) \
	((dll)->data_ = data, \
	DoublyLinkedListGetIndex_(&(dll)->base, &(dll)->data_))

/**
 * Macro that gets the element at the specified index in the doubly linked list.
 * The macro DoublyLinkedListAt calls the function DoublyLinkedListAt_ with the address of the base member of the DoublyLinkedListBase struct and the index as arguments.
 * @param dll pointer to the doubly linked list
 * @param index index of the element which needs to be found
 * @return returns the element at the specified index
**/
#define DoublyLinkedListAt(dll, index) \
	DoublyLinkedListAt_(&(dll)->base, index)

/**
 * Macro that clears all the elements in the doubly linked list.
 * The macro DoublyLinkedListClear calls the function DoublyLinkedListClear_ with the address of the base member of the DoublyLinkedListBase struct as an argument.
 * @param dll pointer to the doubly linked list
**/
#define DoublyLinkedListClear(dll) \
	DoublyLinkedListClear_(&(dll)->base)

/**
 * Macro that deletes the doubly linked list.
 * The macro DoublyLinkedListDelete calls the function DoublyLinkedListDelete_ with the address of the base member of the DoublyLinkedListBase struct as an argument.
 * @param dll pointer to the doubly linked list
**/
#define DoublyLinkedListDelete(dll) \
	DoublyLinkedListDelete_(&(dll)->base)

/**
 * Macro that gets the number of elements in the doubly linked list.
 * The macro DoublyLinkedListSize calls the function DoublyLinkedListSize_ with the address of the base member of the DoublyLinkedListBase struct
 * @param dll pointer to the doubly linked list
**/
#define DoublyLinkedListSize(dll) \
	DoublyLinkedListSize_(&(dll)->base)

/**
 * A macro that returns an iterator for the doubly linked list.
 * The macro calls the DoublyLinkedListIterator_ function with the address of the base member of the Vector struct as the argument.
 * @param dll Pointer to the doubly linked list struct
 * @return A VectorIter struct representing the iterator
**/
#define DoublyLinkedListIterator(dll) \
	DoublyLinkedListIterator_(&(dll)->base)

/**
 * A macro that returns the next element of the doubly linked list using an iterator.
 * The macro calls the DoublyLinkedListNext_ function with the address of the base member of the doubly linked list struct and the iterator as the arguments.
 * @param dll Pointer to the doubly linked list struct
 * @param dlliter Pointer to the iterator
 * @return A pointer to the next element of the doubly linked list
**/
#define DoublyLinkedListNext(dll, dlliter) \
	DoublyLinkedListNext_(&(dll)->base, dlliter)
	
/**
 * A macro that returns the previous element of the doubly linked list using an iterator.
 * The macro calls the DoublyLinkedListBack_ function with the address of the base member of the doubly linked list struct and the iterator as the arguments.
 * @param dll Pointer to the doubly linked list struct
 * @param dlliter Pointer to the iterator
 * @return A pointer to the next element of the doubly linked list
**/
#define DoublyLinkedListBack(dll, dlliter) \
	DoublyLinkedListBack_(&(dll)->base, dlliter)	
	
/**
 * Function that creates a new doubly linked list and initializes the base member of the DoublyLinkedListBase struct.
 * The function allocates memory for the head node of the doubly linked list and initializes its data and value members with NULL.
 * The function also assigns the passed element size, data comparison function and free function to the corresponding members of the base struct.
 * The function asserts that the element size passed is greater than 0.
 * @param dll pointer to the doubly linked list
 * @param elemsize size of the element to be stored in the doubly linked list
 * @param DataCmp pointer to the data comparison function
 * @param FreeFunc pointer to the free function
 * Requirements:
 * - dll pointer should not be nullptr
 * - elemsize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void DoublyLinkedListNew_(DoublyLinkedListBase* dll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));
	
/**
 * Function that inserts the passed data at the tail of the doubly linked list.
 * The function creates a new node, assigns the passed data to the node's data member and sets the node's next pointer to NULL.
 * The function then updates the tail pointer of the doubly linked list to point to the new node.
 * The function asserts that the passed doubly linked list pointer is not NULL.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data to be inserted
 * Requirements:
 * - dll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void DoublyLinkedListInsertAtTail_(DoublyLinkedListBase* dll, void* data);

/**
 * Function that inserts the passed data at the head of the doubly linked list.
 * The function creates a new node, assigns the passed data to the node's data member and sets the node's next pointer to the current head of the doubly linked list.
 * The function then updates the head pointer of the doubly linked list to point to the new node.
 * The function asserts that the passed doubly linked list pointer is not NULL.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data to be inserted
 * Requirements:
 * - dll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void DoublyLinkedListInsertAtHead_(DoublyLinkedListBase* dll, void* data);

/**
 * Function that replaces the first occurrence of the data in the doubly linked list with the passed value.
 * The function asserts that the doubly linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - dll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void DoublyLinkedListReplace_(DoublyLinkedListBase* dll, void* data, void* value);

/**
 * Function that replaces all occurrences of the data in the doubly linked list with the passed value.
 * The function asserts that the doubly linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - dll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void DoublyLinkedListReplaceAll_(DoublyLinkedListBase* dll, void* data, void* value);

/**
 * Function that returns the index of the first occurrence of the specified data in the doubly linked list.
 * The function iterates through the doubly linked list and compares the data of each node with the specified data using the DataCmp function of the base struct.
 * The function returns the index of the first occurrence of the specified data in the doubly linked list.
 * If the specified data is not found in the doubly linked list, the function returns -1.
 * @param dll pointer to the doubly linked list
 * @param data pointer to the data to be searched in the doubly linked list
 * Requirements:
 * - dll pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
int DoublyLinkedListGetIndex_(DoublyLinkedListBase* dll, void* data);

/**
 * Function that returns the data of the node at the specified index in the doubly linked list.
 * The function asserts that the specified index is within the valid range of the doubly linked list.
 * @param dll pointer to the doubly linked list
 * @param index index of the node whose data is to be returned
 * Requirements:
 * - dll pointer should not be nullptr
 * - index should be greater than or equal to 0 and less than the size of the doubly linked list
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void* DoublyLinkedListAt_(DoublyLinkedListBase* dll, unsigned int index);

/**
 * Function that clears all elements from the doubly linked list and resets the list size to 0.
 * The function iterates through the list and calls the free function on each element to free their memory.
 * The function also sets the head and tail pointers to NULL.
 * @param dll pointer to the doubly linked list
 * Requirements:
 * - dll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void DoublyLinkedListClear_(DoublyLinkedListBase* dll);

/**
 * Function that deletes the doubly linked list by clearing all elements and freeing the memory allocated for the head node.
 * The function calls the DoublyLinkedListClear_ function to clear all elements and then frees the memory allocated for the head node.
 * @param dll pointer to the doubly linked list
 * Requirements:
 * - dll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void DoublyLinkedListDelete_(DoublyLinkedListBase* dll);

/**
 * Function that returns the number of elements in the doubly linked list.
 * @param dll pointer to the doubly linked list
 * Requirements:
 * - dll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
unsigned int DoublyLinkedListSize_(DoublyLinkedListBase* dll);


/**
 * Function that creates an iterator for the doubly linked list.
 * Requirements:
 * - The doubly linked list should not be empty
 * Time complexity:
 * - O(1)
 * @param dll pointer to the doubly linked list
 * @return pointer to the iterator of the doubly linked list
**/
DoublyLinkedListIter * DoublyLinkedListIterator_(DoublyLinkedListBase * dll);

/**
 * Function that returns the next element of the doubly linked list through the iterator.
 * Requirements:
 * - The doubly linked list should not be empty
 * - The iterator should not be at the end of the doubly linked list
 * Time complexity:
 * - O(1)
 * @param dll pointer to the doubly linked list
 * @param dlliter pointer to the iterator
 * @return pointer to the next element of the doubly linked list
**/
DoublyLinkedListIter * DoublyLinkedListNext_(DoublyLinkedListBase * dll, DoublyLinkedListIter * dlliter);

/**
 * Function that returns the previous element of the doubly linked list through the iterator.
 * Requirements:
 * - The doubly linked list should not be empty
 * - The iterator should not be at the end of the doubly linked list
 * Time complexity:
 * - O(1)
 * @param dll pointer to the doubly linked list
 * @param dlliter pointer to the iterator
 * @return pointer to the previous element of the doubly linked list
**/
DoublyLinkedListIter * DoublyLinkedListBack_(DoublyLinkedListBase * dll, DoublyLinkedListIter * dlliter);

/**
 * Define a doubly linked list of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(void*) DoublyLinkedList;

/**
 * Define a doubly linked list of double values.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(double) DoublyLinkedListDouble;

/**
 * Define a doubly linked list of float values.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(float) DoublyLinkedListFloat;

/**
 * Define a doubly linked list of signed integer values.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(int) DoublyLinkedListInt;

/**
 * Define a doubly linked list of pointer to character(s).
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(char*) DoublyLinkedListString;

/**
 * Define a doubly linked list of character.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(char) DoublyLinkedListChar;

/**
 * Define a doubly linked list of boolean values.
 * Time complexity:
 * - Depends on the operations performed on the doubly linked list.
**/
typedef DoublyLinkedListT(bool) DoublyLinkedListBool;
	

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_CLIST_HEADER_ */