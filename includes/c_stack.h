#ifndef _C_STACK_HEADER_
#define _C_STACK_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "c_helper.h"

/**
 * A structure that represents the basic functionality of a stack.
 * @param elems A pointer to the element of the stack
 * @param elemsize The size of an element
 * @param logiclen The number of elements in the stack
 * @param alloclen The number of elements for which memory has been allocated
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
typedef struct StackBase{
	void* elems; unsigned int elemsize; unsigned int logiclen; unsigned int alloclen;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
} StackBase;

/**
 * A structure that represents an iterator for a stack.
 * @param data A pointer to the data of the current element
 * @param index The index of the current element
**/
typedef struct StackIter{
	void* data;
	unsigned int index;
}StackIter;

/**
 * A macro that creates a stack template for a given data type T.
 * The macro creates a struct with a StackBase as a member and an additional member with the name data_ of the type T.
 * @param T The type of the data the stack will hold
**/
#define StackT(T) \
struct { StackBase base; T data_; }

/**
 * A macro that creates a new stack with a given comparison function and a function to free memory.
 * The macro calls the StackNew_ function with the address of the base member of the stack struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param s Pointer to the stack struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define StackNew(s, DataCmp, FreeFunc) \
	StackNew_(&(s)->base, sizeof((s)->data_), DataCmp, FreeFunc)

/**
 * A macro that pushes an element to the stack.
 * The macro assigns the data to the data_ member of the stack struct and calls the StackPush_ function with the address of the base member and the address of the data_ member of the stack struct as arguments.
 * @param s Pointer to the stack struct
 * @param data The element to be pushed to the stack
**/
#define StackPush(s, data) \
	((s)->data_ = (data), \
	StackPush_(&(s)->base, &(s)->data_))

/**
 * A macro that pops an element from the stack.
 * The macro calls the StackPop_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
**/
#define StackPop(s) \
	StackPop_(&(s)->base)

/**
 * A macro that returns the top element of the stack.
 * The macro calls the StackTop_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
 * @return A pointer to the top element of the stack
**/
#define StackTop(s) \
	StackTop_(&(s)->base)

/**
 * A macro that clears the stack.
 * The macro calls the StackClear_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
**/
#define StackClear(s) \
	StackClear_(&(s)->base)

/**
 * A macro that deletes the stack.
 * The macro calls the StackDelete_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
**/
#define StackDelete(s) \
	StackDelete_(&(s)->base)

/**
 * A macro that returns an iterator for the stack.
 * The macro calls the StackIterator_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
 * @return A StackIter struct representing the iterator
**/
#define StackIterator(s) \
	StackIterator_(&(s)->base)

/**
 * A macro that returns the next element of the stack using an iterator.
 * The macro calls the StackNext_ function with the address of the base member of the stack struct and the iterator as the arguments.
 * @param s Pointer to the stack struct
 * @param iter Pointer to the iterator
 * @return A pointer to the next element of the stack
**/
#define StackNext(s, iter) \
	StackNext_(&(s)->base, iter)

/**
 * A macro that returns the number of elements in the stack.
 * The macro calls the StackSize_ function with the address of the base member of the stack struct as the argument.
 * @param s Pointer to the stack struct
 * @return The number of elements in the stack
**/
#define StackSize(s) \
	StackSize_(&(s)->base)

/**
 * Function that creates a new stack.
 * Requirements:
 * - elem_size should be greater than 0
 * - The stack should not be empty
 * - DataCmp function pointer must be passed in accordance with the type of data used in stack later
 * - FreeFunc function pointer must be passed in accordance with the type of data used in stack later to free the allocated memory
 * Time complexity:
 * - O(1)
 * @param s pointer to the stack
 * @param elem_size size of an element
 * @param DataCmp pointer to a function that compares data
 * @param FreeFunc pointer to a function that frees memory
**/
void StackNew_(StackBase* s, unsigned int elem_size,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

/**
 * Function that pushes an element to the stack.
 * Requirements:
 * - The stack should not be empty
 * - void* elem should not be null
 * Time complexity:
 * - O(1) amortized
 * @param s pointer to the stack
 * @param elem pointer to the element to be pushed
**/
void StackPush_(StackBase* s, void* elem);

/**
 * Function that pops an element from the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1) amortized
 * @param s pointer to the stack
 * @return pointer to the element that was popped
**/
void* StackPop_(StackBase* s);

/**
 * Function that returns the top element of the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1)
 * @param s pointer to the stack
 * @return pointer to the top element of the stack
**/
void* StackTop_(StackBase* s);

/**
 * Function that clears the stack.
 * This function frees the memory allocated for the elements in the stack and resets the logiclen and alloclen members of the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1) where n is the number of elements in the stack
 * @param s pointer to the stack
**/
void StackClear_(StackBase* s);

/**
 * Function that deletes the stack.
 * This function calls the StackClear_ function and then frees the memory allocated for the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1) 
 * @param s pointer to the stack
**/
void StackDelete_(StackBase* s);

/**
 * Function that creates an iterator for the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1)
 * @param s pointer to the stack
 * @return pointer to the iterator of the stack
**/
StackIter* StackIterator_(StackBase* s);

/**
 * Function that returns the next element of the stack through the iterator.
 * Requirements:
 * - The stack should not be empty
 * - The iterator should not be at the end of the stack
 * Time complexity:
 * - O(1)
 * @param s pointer to the stack
 * @param stackiter pointer to the iterator
 * @return pointer to the next element of the stack
**/
StackIter* StackNext_(StackBase* s, StackIter* stackiter);

/**
 * Function that returns the number of elements in the stack.
 * Requirements:
 * - The stack should not be empty
 * Time complexity:
 * - O(1)
 * @param s pointer to the stack
 * @return number of elements in the stack
**/
unsigned int StackSize_(StackBase* s);

/**
 * Define a stack of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(void*) Stack;

/**
 * Define a stack of double values.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(double) StackDouble;

/**
 * Define a stack of float values.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(float) StackFloat;

/**
 * Define a stack of integers.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(int) StackInt;

/**
 * Define a stack of strings.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(char*) StackString;

/**
 * Define a stack of characters.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(char) StackChar;

/**
 * Define a stack of booleans.
 * Time complexity:
 * - Depends on the operations performed on the stack.
**/
typedef StackT(bool) StackBool;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_STACK_HEADER_ */