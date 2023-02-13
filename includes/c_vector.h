#ifndef _C_VECTOR_HEADER_
#define _C_VECTOR_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * A structure that represents the basic functionality of a Vector.
 * @param elems A pointer to the element of the Vector
 * @param elemsize The size of an element
 * @param logiclen The number of elements in the Vector
 * @param alloclen The number of elements for which memory has been allocated
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
typedef struct VectorBase{
	void * elems; unsigned int elemsize; unsigned int logiclen; unsigned int alloclen;

	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void * elems);
} VectorBase;

/**
 * A structure that represents an iterator for a Vector.
 * @param data A pointer to the data of the current element
 * @param index The index of the current element
**/
typedef struct VectorIter{
	void * data;
	unsigned int index;
}VectorIter;

/**
 * A macro that creates a Vector template for a given data type T.
 * The macro creates a struct with a VectorBase as a member and an additional member with the name data_ of the type T.
 * @param T The type of the data the Vector will hold
**/
#define VectorT(T) \
	struct { VectorBase base; T data_; }

/**
 * A macro that creates a new Vector with a given comparison function and a function to free memory.
 * The macro calls the VectorNew_ function with the address of the base member of the Vector struct, the size of the data_ member, the comparison function and the memory freeing function as arguments.
 * @param v Pointer to the Vector struct
 * @param DataCmp A pointer to a function that compares data
 * @param FreeFunc A pointer to a function that frees memory
**/
#define VectorNew(v, DataCmp, FreeFunc) \
	VectorNew_(&(v)->base, sizeof((v)->data_), DataCmp, FreeFunc)

/**
 * A macro that pushes an element to the Vector.
 * The macro assigns the data to the data_ member of the Vector struct and calls the VectorPush_ function with the address of the base member and the address of the data_ member of the Vector struct as arguments.
 * @param v Pointer to the Vector struct
 * @param data The element to be pushed to the Vector
**/
#define VectorPush(v, data) \
	((v)->data_ = (data), \
	VectorPush_(&(v)->base, &(v)->data_))

/**
 * Macro that returns the element at the specified index in the vector.
 * The macro calls the VectorAt_ function with the address of the base member of the Vector struct, and the index 
 * @param v pointer to the vector
 * @param index index of the element to be returned
**/
#define VectorAt(v, index) \
	VectorAt_(&(v)->base, index)

/**
 * A macro that gets an element from the Vector.
 * The macro assigns the data to the data_ member of the Vector struct and calls the VectorGet_ function with the address of the base member and the address of the data_ member of the Vector struct as arguments.
 * @param v Pointer to the Vector struct
 * @param data The element to be get from the Vector
**/
#define VectorGet(v, data) \
	((v)->data_ = (data), \
	VectorGet_(&(v)->base, &(v)->data_))

/**
 * A macro that clears the Vector.
 * The macro calls the VectorClear_ function with the address of the base member of the Vector struct as the argument.
 * @param v Pointer to the Vector struct
**/
#define VectorClear(v) \
	VectorClear_(&(v)->base)

/**
 * A macro that deletes the Vector.
 * The macro calls the VectorDelete_ function with the address of the base member of the Vector struct as the argument.
 * @param v Pointer to the Vector struct
**/
#define VectorDelete(v) \
	VectorDelete_(&(v)->base)

/**
 * A macro that returns an iterator for the Vector.
 * The macro calls the VectorIterator_ function with the address of the base member of the Vector struct as the argument.
 * @param v Pointer to the Vector struct
 * @return A VectorIter struct representing the iterator
**/
#define VectorIterator(v) \
	VectorIterator_(&(v)->base)

/**
 * A macro that returns the next element of the Vector using an iterator.
 * The macro calls the VectorNext_ function with the address of the base member of the Vector struct and the iterator as the arguments.
 * @param v Pointer to the Vector struct
 * @param iter Pointer to the iterator
 * @return A pointer to the next element of the Vector
**/
#define VectorNext(v, iter) \
	VectorNext_(&(v)->base, iter)

/**
 * A macro that returns the number of elements in the Vector.
 * The macro calls the VectorSize_ function with the address of the base member of the Vector struct as the argument.
 * @param v Pointer to the Vector struct
 * @return The number of elements in the Vector
**/
#define VectorSize(v) \
	VectorSize_(&(v)->base)

/**
 * Function that creates a new Vector.
 * Requirements:
 * - elem_size should be greater than 0
 * - The Vector should not be empty
 * - DataCmp function pointer must be passed in accordance with the type of data used in Vector later
 * - FreeFunc function pointer must be passed in accordance with the type of data used in Vector later to free the allocated memory
 * Time complexity:
 * - O(1)
 * @param v pointer to the Vector
 * @param elem_size size of an element
 * @param DataCmp pointer to a function that compares data
 * @param FreeFunc pointer to a function that frees memory
**/
void VectorNew_(VectorBase * v, unsigned int elem_size,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void * elems));

/**
 * Function that pushes an element to the Vector.
 * Requirements:
 * - The Vector should not be empty
 * - void * elem should not be null
 * Time complexity:
 * - O(1) amortized
 * @param v pointer to the Vector
 * @param elem pointer to the element to be pushed
**/
void VectorPush_(VectorBase * v, void * elem);

/**
 * Function that returns the element at the specified index in the vector.
 * Requirements:
 * - The Vector should not be empty
 * - The index should be within the range of the vector's logiclen
 * Time complexity:
 * - O(1)
 * @param v pointer to the vector
 * @param index index of the element to be returned
 * @return element at the specified index in the vector
**/
void * VectorAt_(VectorBase * v, unsigned int index);

/**
 * Function that returns the element matching the specified data in the vector.
 * Requirements:
 * - The Vector should not be empty
 * - The data should not be null
 * Time complexity:
 * - O(n) where n is the number of elements in the vector
 * @param v pointer to the vector
 * @param data pointer to the element to be searched
 * @return element matching the specified data in the vector
 **/
void * VectorGet_(VectorBase * v, void * data);

/**
 * Function that clears the Vector.
 * This function frees the memory allocated for the elements in the Vector and resets the logiclen and alloclen members of the Vector.
 * Requirements:
 * - The Vector should not be empty
 * Time complexity:
 * - O(1) where n is the number of elements in the Vector
 * @param v pointer to the Vector
**/
void VectorClear_(VectorBase * v);

/**
 * Function that deletes the Vector.
 * This function calls the VectorClear_ function and then frees the memory allocated for the Vector.
 * Requirements:
 * - The Vector should not be empty
 * Time complexity:
 * - O(1)
 * @param v pointer to the Vector
**/
void VectorDelete_(VectorBase * v);

/**
 * Function that creates an iterator for the Vector.
 * Requirements:
 * - The Vector should not be empty
 * Time complexity:
 * - O(1)
 * @param v pointer to the Vector
 * @return pointer to the iterator of the Vector
**/
VectorIter * VectorIterator_(VectorBase * v);

/**
 * Function that returns the next element of the Vector through the iterator.
 * Requirements:
 * - The Vector should not be empty
 * - The iterator should not be at the end of the Vector
 * Time complexity:
 * - O(1)
 * @param v pointer to the Vector
 * @param Vectoriter pointer to the iterator
 * @return pointer to the next element of the Vector
**/
VectorIter * VectorNext_(VectorBase * v, VectorIter * Vectoriter);

/**
 * Function that returns the number of elements in the Vector.
 * Requirements:
 * - The Vector should not be empty
 * Time complexity:
 * - O(1)
 * @param v pointer to the Vector
 * @return number of elements in the Vector
**/
unsigned int VectorSize_(VectorBase * v);

/**
 * Define a Vector of void pointers.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(void*) Vector;

/**
 * Define a Vector of double values.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(double) VectorDouble;

/**
 * Define a Vector of float values.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(float) VectorFloat;

/**
 * Define a Vector of integers.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(int) VectorInt;

/**
 * Define a Vector of strings.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(char*) VectorString;

/**
 * Define a Vector of characters.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(char) VectorChar;

/**
 * Define a Vector of booleans.
 * Time complexity:
 * - Depends on the operations performed on the Vector.
**/
typedef VectorT(bool) VectorBool;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_VECTOR_HEADER_ */