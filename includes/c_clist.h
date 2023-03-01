#ifndef _C_DLIST_HEADER_
#define _C_DLIST_HEADER_

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
} ListNode;

/**
 * A structure that represents an iterator for a circular linked list.
 * @param data A pointer to the data of the current element
 * @param index The index of the current element
**/
typedef struct CircularLinkedListIter{
	void * data;
	unsigned int index;
}CircularLinkedListIter;

/**
 * A structure that represents the basic functionality of a circular linked list.
 * @param head A pointer to the first element of the circular linked list
 * @param tail A pointer to the last element of the circular linked list
 * @param listsize The number of elements in the circular linked list 
 * @param elemsize The size of an elem in list node
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
typedef struct CircularLinkedListBase {
	ListNode* head; 
	unsigned int listsize; unsigned int elemsize;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} CircularLinkedListBase;


/**
 * A macro that creates a circular linked list template for a given data type T.
 * The macro creates a struct with a CircularLinkedListBase as a member and an additional member with the name data_ of the type T and value_ of the type T.
 * @param T The type of the data the circular linked list will hold
**/
#define CircularLinkedListT(T) \
struct { CircularLinkedListBase base; T data_; T value_; }

/**
 * A macro that creates a new circular linked list with a given comparison function and a function to free memory.
 * The macro calls the CircularLinkedListNew_ function with the address of the base member of the CircularLinkedListBase struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param cll Pointer to the circular linked list struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define CircularLinkedListNew(cll, DataCmp, FreeFunc) \
	CircularLinkedListNew_(&(cll)->base, sizeof((cll)->data_), DataCmp, FreeFunc)

/**
 * A macro that inserts data at head in the circular linked list pointer passed as argument.
 * The macro calls the CircularLinkedListInsertAtHead_ function with the address of the base member of the CircularLinkedListBase struct and the address of the data_ member of the circular linked list struct as arguments.
 * @param cll Pointer to the circular linked list struct
 * @param data Data to be stored in circular linked list
**/
#define CircularLinkedListInsert(cll, data) \
	((cll)->data_ = data, \
	CircularLinkedListInsert_(&(cll)->base, &(cll)->data_))

/**
 * Macro that replaces the element with the specified data with the specified value in the circular linked list.
 * The macro CircularLinkedListReplace calls the function CircularLinkedListReplace_ with the address of the base member of the CircularLinkedListBase struct and the address of the data_ member of the circular linked list struct as arguments.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data of the element to be replaced
 * @param value pointer to the new value to be set
**/
#define CircularLinkedListReplace(cll, data, value) \
	((cll)->data_ = data, \
	(cll)->value_ = value, \
	CircularLinkedListReplace_(&(cll)->base, &(cll)->data_, &(cll)->value_))

/**
 * Macro that replaces all the elements with the specified data with the specified value in the circular linked list.
 * The macro CircularLinkedListReplaceAll calls the function CircularLinkedListReplaceAll_ with the address of the base member of the CircularLinkedListBase struct and the address of the data_ member of the circular linked list struct as arguments.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data of the elements to be replaced
 * @param value pointer to the new value to be set
**/
#define CircularLinkedListReplaceAll(cll, data, value) \
	((cll)->data_ = data, \
	(cll)->value_ = value, \
	CircularLinkedListReplaceAll_(&(cll)->base, &(cll)->data_, &(cll)->value_))

/**
 * Macro that gets the index of the first element with the specified data in the circular linked list.
 * The macro CircularLinkedListGetIndex calls the function CircularLinkedListGetIndex_ with the address of the base member of the CircularLinkedListBase struct and the address of the data_ member of the circular linked list struct as arguments.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data of the element for which the index needs to be found
 * @return returns the index of the first element with the specified data, if not found returns -1
**/
#define CircularLinkedListGetIndex(cll, data) \
	((cll)->data_ = data, \
	CircularLinkedListGetIndex_(&(cll)->base, &(cll)->data_))

/**
 * Macro that gets the element at the specified index in the circular linked list.
 * The macro CircularLinkedListAt calls the function CircularLinkedListAt_ with the address of the base member of the CircularLinkedListBase struct and the index as arguments.
 * @param cll pointer to the circular linked list
 * @param index index of the element which needs to be found
 * @return returns the element at the specified index
**/
#define CircularLinkedListAt(cll, index) \
	CircularLinkedListAt_(&(cll)->base, index)

/**
 * Macro that clears all the elements in the circular linked list.
 * The macro CircularLinkedListClear calls the function CircularLinkedListClear_ with the address of the base member of the CircularLinkedListBase struct as an argument.
 * @param cll pointer to the circular linked list
**/
#define CircularLinkedListClear(cll) \
	CircularLinkedListClear_(&(cll)->base)

/**
 * Macro that deletes the circular linked list.
 * The macro CircularLinkedListDelete calls the function CircularLinkedListDelete_ with the address of the base member of the CircularLinkedListBase struct as an argument.
 * @param cll pointer to the circular linked list
**/
#define CircularLinkedListDelete(cll) \
	CircularLinkedListDelete_(&(cll)->base)

/**
 * Macro that gets the number of elements in the circular linked list.
 * The macro CircularLinkedListSize calls the function CircularLinkedListSize_ with the address of the base member of the CircularLinkedListBase struct
 * @param cll pointer to the circular linked list
**/
#define CircularLinkedListSize(cll) \
	CircularLinkedListSize_(&(cll)->base)

/**
 * A macro that returns an iterator for the circular linked list.
 * The macro calls the CircularLinkedListIterator_ function with the address of the base member of the Vector struct as the argument.
 * @param cll Pointer to the circular linked list struct
 * @return A VectorIter struct representing the iterator
**/
#define CircularLinkedListIterator(cll) \
	CircularLinkedListIterator_(&(cll)->base)

/**
 * A macro that returns the next element of the circular linked list using an iterator.
 * The macro calls the CircularLinkedListNext_ function with the address of the base member of the circular linked list struct and the iterator as the arguments.
 * @param cll Pointer to the circular linked list struct
 * @param iter Pointer to the iterator
 * @return A pointer to the next element of the circular linked list
**/
#define CircularLinkedListNext(cll, iter) \
	CircularLinkedListNext_(&(cll)->base, iter)

	
/**
 * Function that creates a new circular linked list and initializes the base member of the CircularLinkedListBase struct.
 * The function allocates memory for the head node of the circular linked list and initializes its data and value members with NULL.
 * The function also assigns the passed element size, data comparison function and free function to the corresponding members of the base struct.
 * The function asserts that the element size passed is greater than 0.
 * @param cll pointer to the circular linked list
 * @param elemsize size of the element to be stored in the circular linked list
 * @param DataCmp pointer to the data comparison function
 * @param FreeFunc pointer to the free function
 * Requirements:
 * - cll pointer should not be nullptr
 * - elemsize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void CircularLinkedListNew_(CircularLinkedListBase* cll, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

/**
 * Function that inserts the passed data at the head of the circular linked list.
 * The function creates a new node, assigns the passed data to the node's data member and sets the node's next pointer to the current head of the circular linked list.
 * The function then updates the head pointer of the circular linked list to point to the new node.
 * The function asserts that the passed circular linked list pointer is not NULL.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data to be inserted
 * Requirements:
 * - cll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void CircularLinkedListInsert_(CircularLinkedListBase* cll, void* data);

/**
 * Function that replaces the first occurrence of the data in the circular linked list with the passed value.
 * The function asserts that the circular linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - cll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void CircularLinkedListReplace_(CircularLinkedListBase* cll, void* data, void* value);

/**
 * Function that replaces all occurrences of the data in the circular linked list with the passed value.
 * The function asserts that the circular linked list pointer passed is not NULL.
 * The function also asserts that the data and value pointers passed are not NULL.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data that needs to be replaced
 * @param value pointer to the new value
 * Requirements:
 * - cll pointer should not be nullptr
 * - data and value pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void CircularLinkedListReplaceAll_(CircularLinkedListBase* cll, void* data, void* value);

/**
 * Function that returns the index of the first occurrence of the specified data in the circular linked list.
 * The function iterates through the circular linked list and compares the data of each node with the specified data using the DataCmp function of the base struct.
 * The function returns the index of the first occurrence of the specified data in the circular linked list.
 * If the specified data is not found in the circular linked list, the function returns -1.
 * @param cll pointer to the circular linked list
 * @param data pointer to the data to be searched in the circular linked list
 * Requirements:
 * - cll pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
int CircularLinkedListGetIndex_(CircularLinkedListBase* cll, void* data);

/**
 * Function that returns the data of the node at the specified index in the circular linked list.
 * The function asserts that the specified index is within the valid range of the circular linked list.
 * @param cll pointer to the circular linked list
 * @param index index of the node whose data is to be returned
 * Requirements:
 * - cll pointer should not be nullptr
 * - index should be greater than or equal to 0 and less than the size of the circular linked list
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void* CircularLinkedListAt_(CircularLinkedListBase* cll, unsigned int index);

/**
 * Function that clears all elements from the circular linked list and resets the list size to 0.
 * The function iterates through the list and calls the free function on each element to free their memory.
 * The function also sets the head and tail pointers to NULL.
 * @param cll pointer to the circular linked list
 * Requirements:
 * - cll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void CircularLinkedListClear_(CircularLinkedListBase* cll);

/**
 * Function that deletes the circular linked list by clearing all elements and freeing the memory allocated for the head node.
 * The function calls the CircularLinkedListClear_ function to clear all elements and then frees the memory allocated for the head node.
 * @param cll pointer to the circular linked list
 * Requirements:
 * - cll pointer should not be nullptr
 * Time complexity: O(n) where n is the number of elements in the list
 * Space complexity: O(1)
**/
void CircularLinkedListDelete_(CircularLinkedListBase* cll);

/**
 * Function that returns the number of elements in the circular linked list.
 * @param cll pointer to the circular linked list
 * Requirements:
 * - cll pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
unsigned int CircularLinkedListSize_(CircularLinkedListBase* cll);


/**
 * Function that creates an iterator for the circular linked list.
 * Requirements:
 * - The circular linked list should not be empty
 * Time complexity:
 * - O(1)
 * @param cll pointer to the circular linked list
 * @return pointer to the iterator of the circular linked list
**/
CircularLinkedListIter * CircularLinkedListIterator_(CircularLinkedListBase * cll);

/**
 * Function that returns the next element of the circular linked list through the iterator.
 * Requirements:
 * - The circular linked list should not be empty
 * - The iterator should not be at the end of the circular linked list
 * Time complexity:
 * - O(1)
 * @param cll pointer to the circular linked list
 * @param lliter pointer to the iterator
 * @return pointer to the next element of the circular linked list
**/
CircularLinkedListIter * CircularLinkedListNext_(CircularLinkedListBase * cll, CircularLinkedListIter * lliter);


/**
 * Define a circular linked list of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(void*) CircularLinkedList;

/**
 * Define a circular linked list of double values.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(double) CircularLinkedListDouble;

/**
 * Define a circular linked list of float values.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(float) CircularLinkedListFloat;

/**
 * Define a circular linked list of signed integer values.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(int) CircularLinkedListInt;

/**
 * Define a circular linked list of pointer to character(s).
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(char*) CircularLinkedListString;

/**
 * Define a circular linked list of character.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(char) CircularLinkedListChar;

/**
 * Define a circular linked list of boolean values.
 * Time complexity:
 * - Depends on the operations performed on the circular linked list.
**/
typedef CircularLinkedListT(bool) CircularLinkedListBool;
	

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_DLIST_HEADER_ */