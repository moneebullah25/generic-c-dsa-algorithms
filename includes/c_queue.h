#ifndef _C_QUEUE_HEADER_
#define _C_QUEUE_HEADER_

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
 * A structure that represents the basic functionality of a Queue.
 * @param elems A pointer to the element of the Queue
 * @param elemsize The size of an element
 * @param logiclen The number of elements in the Queue
 * @param alloclen The number of elements for which memory has been allocated
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
typedef struct QueueBase{
	void * elems; unsigned int elemsize; unsigned int logiclen; unsigned int alloclen;
	void * front; void * rear;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void * elems);
} QueueBase;

/**
 * A structure that represents an iterator for a Queue.
 * @param data A pointer to the data of the current element
 * @param index The index of the current element
**/
typedef struct QueueIter{
	void * data;
	void * prevfront;
	unsigned int index;
}QueueIter;

/**
 * A macro that creates a Queue template for a given data type T.
 * The macro creates a struct with a QueueBase as a member and an additional member with the name data_ of the type T.
 * @param T The type of the data the Queue will hold
**/
#define QueueT(T) \
	struct { QueueBase base; T data_; }

/**
 * A macro that creates a new Queue with a given comparison function and a function to free memory.
 * The macro calls the QueueNew_ function with the address of the base member of the Queue struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param q Pointer to the Queue struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define QueueNew(q, DataCmp, FreeFunc) \
	QueueNew_(&(q)->base, sizeof((q)->data_), DataCmp, FreeFunc)

/**
 * A macro that pushes an element to the Queue.
 * The macro assigns the data to the data_ member of the Queue struct and calls the QueuePush_ function with the address of the base member and the address of the data_ member of the Queue struct as arguments.
 * @param q Pointer to the Queue struct
 * @param data The element to be pushed to the Queue
**/
#define QueuePush(q, data) \
	((q)->data_ = (data), \
	QueuePush_(&(q)->base, &(q)->data_))

/**
 * A macro that pops an element from the Queue.
 * The macro calls the QueuePop_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
**/
#define QueuePop(q) \
	QueuePop_(&(q)->base)

/**
 * A macro that returns the top element of the Queue.
 * The macro calls the QueueTop_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
 * @return A pointer to the top element of the Queue
**/
#define QueueTop(q) \
	QueueTop_(&(q)->base)

/**
 * A macro that clears the Queue.
 * The macro calls the QueueClear_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
**/
#define QueueClear(q) \
	QueueClear_(&(q)->base)

/**
 * A macro that deletes the Queue.
 * The macro calls the QueueDelete_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
**/
#define QueueDelete(q) \
	QueueDelete_(&(q)->base)

/**
 * A macro that returns an iterator for the Queue.
 * The macro calls the QueueIterator_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
 * @return A QueueIter struct representing the iterator
**/
#define QueueIterator(q) \
	QueueIterator_(&(q)->base)

/**
 * A macro that returns the next element of the Queue using an iterator.
 * The macro calls the QueueNext_ function with the address of the base member of the Queue struct and the iterator as the arguments.
 * @param q Pointer to the Queue struct
 * @param iter Pointer to the iterator
 * @return A pointer to the next element of the Queue
**/
#define QueueNext(q, iter) \
	QueueNext_(&(q)->base, iter)

/**
 * A macro that returns the number of elements in the Queue.
 * The macro calls the QueueSize_ function with the address of the base member of the Queue struct as the argument.
 * @param q Pointer to the Queue struct
 * @return The number of elements in the Queue
**/
#define QueueSize(q) \
	QueueSize_(&(q)->base)

/**
 * Function that creates a new Queue.
 * Requirements:
 * - elem_size should be greater than 0
 * - The Queue should not be empty
 * - DataCmp function pointer must be passed in accordance with the type of data used in Queue later
 * - FreeFunc function pointer must be passed in accordance with the type of data used in Queue later to free the allocated memory
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
 * @param elem_size size of an element
 * @param DataCmp pointer to a function that compares data
 * @param FreeFunc pointer to a function that frees memory
**/
void QueueNew_(QueueBase * q, unsigned int elem_size,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void * elems));

/**
 * Function that pushes an element to the Queue.
 * Requirements:
 * - The Queue should not be empty
 * - void * elem should not be null
 * Time complexity:
 * - O(1) amortized
 * @param q pointer to the Queue
 * @param elem pointer to the element to be pushed
**/
void QueuePush_(QueueBase * q, void * elem);

/**
 * Function that pops an element from the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1) amortized
 * @param q pointer to the Queue
 * @return pointer to the element that was popped
**/
void * QueuePop_(QueueBase * q);

/**
 * Function that returns the top element of the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
 * @return pointer to the top element of the Queue
**/
void * QueueTop_(QueueBase * q);

/**
 * Function that clears the Queue.
 * This function frees the memory allocated for the elements in the Queue and resets the logiclen and alloclen members of the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1) where n is the number of elements in the Queue
 * @param q pointer to the Queue
**/
void QueueClear_(QueueBase * q);

/**
 * Function that deletes the Queue.
 * This function calls the QueueClear_ function and then frees the memory allocated for the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
**/
void QueueDelete_(QueueBase * q);

/**
 * Function that creates an iterator for the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
 * @return pointer to the iterator of the Queue
**/
QueueIter * QueueIterator_(QueueBase * q);

/**
 * Function that returns the next element of the Queue through the iterator.
 * Requirements:
 * - The Queue should not be empty
 * - The iterator should not be at the end of the Queue
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
 * @param Queueiter pointer to the iterator
 * @return pointer to the next element of the Queue
**/
QueueIter * QueueNext_(QueueBase * q, QueueIter * queueiter);

/**
 * Function that returns the number of elements in the Queue.
 * Requirements:
 * - The Queue should not be empty
 * Time complexity:
 * - O(1)
 * @param q pointer to the Queue
 * @return number of elements in the Queue
**/
unsigned int QueueSize_(QueueBase * q);

/**
 * Define a Queue of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(void*) Queue;

/**
 * Define a Queue of double values.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(double) QueueDouble;

/**
 * Define a Queue of float values.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(float) QueueFloat;

/**
 * Define a Queue of integers.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(int) QueueInt;

/**
 * Define a Queue of strings.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(char*) QueueString;

/**
 * Define a Queue of characters.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(char) QueueChar;

/**
 * Define a Queue of booleans.
 * Time complexity:
 * - Depends on the operations performed on the Queue.
**/
typedef QueueT(bool) QueueBool;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_QUEUE_HEADER_ */