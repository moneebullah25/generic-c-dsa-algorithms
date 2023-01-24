# **C HELPER**

This is a C header file that defines several macros and functions that can be used in C programs.

## Macros:

- **ASSERT(x)**: a macro for debugging assertions that checks if the given expression "x" is true and halts the program execution if it is not. It also calls the assert\_handler function with the expression, file name and line number as arguments.
- **M\_MAX(X, Y)**: a macro that returns the maximum of two given values.
- **M\_MIN(X, Y)**: a macro that returns the minimum of two given values.
- **M\_ABS(X)**: a macro that returns the absolute value of a given value.

## Functions:

Memory Management

- **FreeString(void \*elems)**: a function that frees the memory allocated for a string.
- **FreeData(void \*elems)**: a function that frees the memory allocated for a pointer.

Memory Manipulation

- **MemorySwap(void \*vp1, void \*vp2, unsigned int nbytes)**: a function that swaps the memory contents of two given pointers.
- **StringSwap(void \*vp1, void \*vp2, unsigned int nbytes)**: a function that swaps the string contents of two given pointers.
- **StringCompare(const void \*vp1, const void \*vp2)**: a function that compares the contents of two given strings and returns an integer less than, equal to, or greater than zero if the vp1 is found, respectively, to be less than, to match, or be greater than the vp2.
- **MemoryCopy(void \*dest, const void \*src, unsigned int nbytes)**: a function that copies the contents of memory from one location to another. The two pointers should not overlap.
- **StringCopy(void \*dest, const void \*src, unsigned int nbytes)**: a function that copies the contents of a string from one location to another. The two pointers should not overlap.
- **MemoryMove(void \*dest, void \*src, unsigned int nbytes)**: a function that move contents of memory from one location to another. The two pointers may overlap.

## Note:

These functions and macros are provided as a convenience and can be used in various situations depending on the use case. It is important to read the comments above each function to understand the requirements and time complexities.

# **C SORT**

This is a C header file that defines several sorting functions that can be used in C programs.

- **LinearSearch(void\* key, void\* base, unsigned int nelems, unsigned int elemsize, int(\*MemCmp)(const void\*, const void\*, unsigned int))**: a function that performs a linear search on an array of elements for a specific key. It compares the key with each element in the array using the provided memory comparison function and returns the address of the first element that matches the key. If no match is found, the function returns a null pointer.
- **BinarySearch(void\* key, void\* base, unsigned int s, unsigned int n, unsigned int elemsize, int(\*MemCmp)(const void\*, const void\*, unsigned int))**: a function that performs a binary search on a sorted array of elements for a specified key. The function recursively divides the array in half and compares the middle element to the key. If the key is found, the function returns a pointer to the element. If the key is not found, the function returns null.
- **BubbleSort(void\* base, unsigned int elemsize, unsigned int n, int(\*MemCmp)(const void\*, const void\*, unsigned int), void(\*MemSwap)(void \*vp1, void \*vp2, unsigned int nbytes))**: function that sorts an array of elements using the bubble sort algorithm. It takes a pointer to the base of the array, the size of each element, the number of elements, a pointer to a memory comparison function, and a pointer to a memory swap function as arguments. The function repeatedly iterates through the array comparing adjacent elements and swapping them if they are in the wrong order.
- **MergeSort(void\* base, unsigned int elemsize, unsigned int low, unsigned int high, int(\*MemCmp)(const void\*, const void\*, unsigned int), void(\*MemSwap)(void \*vp1, void \*vp2, unsigned int nbytes))** : a function that sorts an array of elements using the MergeSort algorithm. It takes as input a base pointer to the array, the size of the elements in the array, the low and high indices of the array, a pointer to a comparison function and a pointer to a swap function. The function sorts the array by dividing it into two sub-arrays, sorting them recursively, and then merging the sorted sub-arrays back into the original array. It asserts that the pointers passed as arguments are not null and have time complexity O(n log n) and space complexity O(n)
- **QuickSort(void\* base, unsigned int elemsize, unsigned int low, unsigned int high, int(\*MemCmp)(const void\*, const void\*, unsigned int), void(\*MemSwap)(void \*vp1, void \*vp2, unsigned int nbytes))**: function that sorts an array of elements using the QuickSort algorithm. It takes as input a base pointer to the array, the size of the elements in the array, the low and high indices of the array, a pointer to a comparison function and a pointer to a swap function.

Note that all the functions assert that the pointers passed as arguments are not null and have time and space complexities depending on the sorting algorithm.

# **C STACK**

This is a header file for a stack implementation in C. It defines a structure called StackBase, which contains basic information about the stack such as the element pointer, element size, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing. Another structure called StackIter is also defined, which represents an iterator for the stack and contains the data pointer and index of the current element.

Additionally, there are a number of macros defined to make using the stack more convenient. StackT creates a stack template for a given data type, StackNew creates a new stack with a given comparison function and memory freeing function, StackPush and StackPop push and pop elements from the stack, StackTop returns the top element of the stack, StackClear clears the stack, and StackDelete deletes the stack.

## Macros:

The given macros are for creating and manipulating a stack template for a specific data type T. 
- **StackT(T)** macro creates a struct with a StackBase as a member and an additional member with the name data_ of the type T. 
- **StackNew(s, DataCmp, FreeFunc)** macro creates a new stack with a given comparison function and a function to free memory. 
- **StackPush(s, data)** macro pushes an element to the stack.
- **StackPop(s)** macro pops an element from the stack.
- **StackTop(s)** macro returns the top element of the stack.
- **StackClear(s)** macro clears the stack.
- **StackDelete(s)** macro deletes the stack.
- **StackIterator(s)** macro returns an iterator for the stack. 
- **StackNext(s, iter)** macro returns the next element of the stack using an iterator.
- **StackSize(s)** macro returns the logical length of the stack

## Functions:

- **StackNew_(StackBase\* s, unsigned int elem_size, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void\* elems))**: This function creates a new stack with a given comparison function and memory freeing function. It sets up the StackBase structure with the appropriate values and initializes the stack. The function takes in a pointer to the StackBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **StackPush_(StackBase\* s, void\* elem)**: This function pushes an element to the stack. It takes in a pointer to the StackBase structure and a pointer to the element to be pushed as arguments. It adds the element to the top of the stack, increases the logical length of the stack, and possibly reallocates memory if needed.
- **StackPop_(StackBase\* s)**: This function pops an element from the stack. It takes in a pointer to the StackBase structure as an argument. It removes the top element from the stack, decreases the logical length of the stack, and possibly reallocates memory if needed.
- **StackTop_(StackBase\* s)**: This function returns the top element of the stack. It takes in a pointer to the StackBase structure as an argument. It returns a pointer to the top element of the stack without removing it from the stack.
- **StackClear_(StackBase\* s)**: This function clears the stack. It takes in a pointer to the StackBase structure as an argument. It removes all elements from the stack, decreases the logical length of the stack to 0, and possibly reallocates memory if needed.
- **StackDelete_(StackBase\* s)**: This function deletes the stack. It takes in a pointer to the StackBase structure as an argument. It calls the memory freeing function for each element in the stack, deallocates memory and set the stack pointer to NULL.
- **StackIterator_(StackBase\* s)**: This function returns an iterator for the stack. It takes in a pointer to the StackBase structure as an argument. It returns an iterator for the stack which allows you to iterate through the elements of the stack.
- **StackNext_(StackBase\* s, StackIter\* stackiter)**: This function returns the next element in the stack iterator. It takes in a pointer to the StackBase structure and a pointer to the StackIter structure as arguments. It returns a pointer to the next element in the stack iterator, and if the end of the stack has been reached it returns NULL.
- **StackSize_(StackBase\* s)**: This function returns the number of elements in the stack. It takes in a pointer to the StackBase structure as an argument. It returns an unsigned int representing the number of elements in the stack.

## Templates:

- **Stack** is a stack of void pointers.
- **StackDouble** is a stack of double values.
- **StackFloat** is a stack of float values.
- **StackInt** is a stack of integers.
- **StackString** is a stack of strings (represented by char pointers).
- **StackChar** is a stack of characters.
- **StackBool** is a stack of booleans.

# **C QUEUE**

This is a header file for a queue implementation in C. It defines a structure called QueueBase, which contains basic information about the queue such as the element pointer, element size, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing. Another structure called QueueIter is also defined, which represents an iterator for the queue and contains the data pointer and index of the current element.

Additionally, there are a number of macros defined to make using the queue more convenient. QueueT creates a queue template for a given data type, QueueNew creates a new queue with a given comparison function and memory freeing function, QueueEnqueue and QueueDequeue enqueue and dequeue elements from the queue, QueueFront returns the front element of the queue, QueueRear returns the rear element of the queue, QueueClear clears the queue, and QueueDelete deletes the queue.

## Macros:

The given macros are for creating and manipulating a queue template for a specific data type T.

- **QueueT(T)** macro creates a struct with a QueueBase as a member and an additional member with the name data\_ of the type T.
- **QueueNew(q, DataCmp, FreeFunc)** macro creates a new queue with a given comparison function and a function to free memory.
- **QueuePush(q, data)** macro enqueues an element to the queue.
- **QueuePop(q)** macro dequeues an element from the queue.
- **QueueTop(q)** macro returns the front element of the queue.
- **QueueClear(q)** macro clears the queue.
- **QueueDelete(q)** macro deletes the queue.
- **QueueIterator(q)** macro returns an iterator for the queue.
- **QueueNext(q, iter)** macro returns the next element of the queue using an iterator.
- **QueueSize(q)** macro returns the logical length of the queue

## Functions:

- **QueueNew\_(QueueBase\* q, unsigned int elem\_size, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void\* elems))**: This function creates a new queue with a given comparison function and memory freeing function. It sets up the QueueBase structure with the appropriate values and initializes the queue. The function takes in a pointer to the QueueBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **QueuePush\_(QueueBase\* q, void\* elem)**: This function enqueues an element to the queue. It takes in a pointer to the QueueBase structure and a pointer to the element to be enqueued as arguments. It adds the element to the rear of the queue, increases the logical length of the queue, and possibly reallocates memory if needed.
- **QueuePop\_(QueueBase\* q)**: This function dequeues an element from the queue. It takes in a pointer to the QueueBase structure as an argument. It removes the front element from the queue, decreases the logical length of the queue, and possibly reallocates memory if needed.
- **QueueTop\_(QueueBase\* q):** This function returns the front element of the queue. It takes in a pointer to the QueueBase structure as an argument. It returns a pointer to the front element of the queue without removing it from the queue.
- **QueueClear\_(QueueBase\* q)**: This function clears the queue. It takes in a pointer to the QueueBase structure as an argument. It removes all elements from the queue, decreases the logical length of the queue to 0, and possibly reallocates memory if needed.
- **QueueDelete\_(QueueBase\* q)**: This function deletes the queue. It takes in a pointer to the QueueBase structure as an argument. It calls the memory freeing function for each element in the queue, deallocates memory and set the queue pointer to NULL.
- **QueueIterator\_(QueueBase\* q)**: This function returns an iterator for the queue. It takes in a pointer to the QueueBase structure as an argument. It returns an iterator for the queue which allows you to iterate through the elements of the queue.
- **QueueNext\_(QueueBase\* q, QueueIter\* queueiter)**: This function returns the next element in the queue iterator. It takes in a pointer to the QueueBase structure and a pointer to the QueueIter struct as arguments. It returns a pointer to the next element in the queue.

Please note, for all the queue function, the time complexity would depend on the specific operation being performed, but it is generally O(1) that is constant time.

## Templates:

- **Queue** is a queue of void pointers.
- **QueueDouble** is a queue of double values.
- **QueueFloat** is a queue of float values.
- **QueueInt** is a queue of integers.
- **QueueString** is a queue of strings (represented by char pointers).
- **QueueChar** is a queue of characters.
- **QueueBool** is a queue of booleans.

# **C VECTOR**

This is a header file for a vector implementation in C. It defines a structure called VectorBase, which contains information about the vector such as a pointer to the data, the current size, and the allocated capacity. Additionally, the structure contains function pointers for data comparison and memory freeing. Another structure called VectorIter is also defined, which represents an iterator for the vector and contains the data pointer and index of the current element.

There are a number of macros defined to make using the vector more convenient. VectorT creates a vector template for a given data type, VectorNew creates a new vector with a given comparison function and memory freeing function, VectorPush adds an element to the end of the vector, VectorAt returns the element at a specific index, VectorGet returns the element at a specific index, VectorClear clears the vector, and VectorDelete deletes the vector. Additionally, there are macros for working with an iterator for the vector such as VectorIterator, VectorNext and VectorSize.

## Macros:

- **VectorT(T)** macro creates a struct with a VectorBase as a member and an additional member with the name data\_ of the type T.
- **VectorNew(v, DataCmp, FreeFunc)** macro creates a new vector with a given comparison function and a function to free memory.
- **VectorPush(v, data)** macro adds an element to the end of the vector.
- **VectorAt(v, index)** macro returns the element at a specific index in the vector.
- **VectorGet(v, data)** macro returns the element at a specific index in the vector.
- **VectorClear(v)** macro clears the vector.
- **VectorDelete(v)** macro deletes the vector.
- **VectorIterator(v)** macro returns an iterator for the vector.
- **VectorNext(v, iter)** macro returns the next element of the vector using an iterator.
- **VectorSize(v)** macro returns the current size of the vector.

## Functions:

- **VectorNew\_(VectorBase\* v, unsigned int elem\_size, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void\* elems))**: This function creates a new vector with a given comparison function and memory freeing function. It sets up the VectorBase structure with the appropriate values and initializes the vector. The function takes in a pointer to the VectorBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **VectorPush\_(VectorBase\* v, void\* elem)**: This function adds an element to the end of the vector. It takes in a pointer to the VectorBase structure and a pointer to the element to be added as arguments.
- **VectorAt\_(VectorBase\* v, unsigned int index)**: This function returns the element at a specific index in the vector. It takes in a pointer to the VectorBase structure and the index as arguments.
- **VectorGet\_(VectorBase\* v, void\* data)**: This function returns the element at a specific index in the vector. It takes in a pointer to the VectorBase structure and a pointer to the element to be returned as arguments
- **VectorClear\_(VectorBase\* v)**: This function clears the vector. It takes in a pointer to the VectorBase structure as an argument. It removes all elements from the vector, decreases the logical length of the vector to 0.
- **VectorDelete\_(VectorBase\* v)**: This function deletes the vector. It takes in a pointer to the VectorBase structure as an argument. It calls the memory freeing function for each element in the vector, deallocates memory and set the vector pointer to NULL.
- **VectorIterator\_(VectorBase\* v):** This function returns an iterator for the vector. It takes in a pointer to the VectorBase structure as an argument. It returns a pointer to the iterator of the vector.
- **VectorNext\_(VectorBase\* v, VectorIter\* Vectoriter):** This function returns the next element of the vector using an iterator. It takes in a pointer to the VectorBase structure and a pointer to the VectorIter structure as arguments.
- **VectorSize\_(VectorBase\* v)**: This function returns the current size of the vector. It takes in a pointer to the VectorBase structure as an argument.

## Templates:

- **Vector** is a vector of void pointers.
- **VectorDouble** is a vector of double values.
- **VectorFloat** is a vector of float values.
- **VectorInt** is a vector of integers.
- **VectorString** is a vector of strings (represented by char pointers).
- **VectorChar** is a vector of characters.
- **VectorBool** is a vector of booleans.

# **C LIST**

This is a header file for a linked list implementation in C. It defines two structures: ListNode, which contains basic information about a node in the list such as the element pointer, element size, and the next node pointer, and LinkedListBase, which contains basic information about the linked list such as the head and tail pointer, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing.

Additionally, there are a number of macros defined to make using the linked list more convenient. 

## Macros:

- **LinkedListT** creates a linked list template for a given data type.
- **LinkedListNew** creates a new linked list with a given comparison function and memory freeing function.
- **LinkedListInsertAtTail** insert elements at the tail of the linked list.
- **LinkedListInsertAtHead** insert elements at the head of the linked list.
- **LinkedListReplace** replace only first found element in the linked list.
- **LinkedListReplaceAll** replace all found elements in the linked list.
- **LinkedListGetIndex** returns the index of a given element in the linked list.
- **LinkedListAt** returns the element at a given index in the linked list.
- **LinkedListClear** clears the linked list, and LinkedListDelete deletes the linked list.

## Functions:

- **LinkedListNew\_(LinkedListBase\* ll, unsigned int elemsize, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void \*elems))**: This function creates a new linked list with a given comparison function and memory freeing function. It sets up the LinkedListBase structure with the appropriate values and initializes the linked list. The function takes in a pointer to the LinkedListBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **LinkedListInsertAtTail\_(LinkedListBase\* ll, void\* data)**: This function inserts an element at the tail of the linked list. It takes in a pointer to the LinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the tail of the linked list, increases the logical length of the linked list.
- **LinkedListInsertAtHead\_(LinkedListBase\* ll, void\* data)**: This function inserts an element at the head of the linked list. It takes in a pointer to the LinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the head of the linked list, increases the logical length of the linked list.
- **LinkedListReplace\_(LinkedListBase\* ll, void\* data, void\* value)**: This function replaces the first element in the linked list that matches a given data with a given value. It takes in a pointer to the LinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **LinkedListReplaceAll\_(LinkedListBase\* ll, void\* data, void\* value)**: This function replaces all elements in the linked list that matches a given data with a given value. It takes in a pointer to the LinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **LinkedListGetIndex\_(LinkedListBase\* ll, void\* data)**: This function returns the index of the first element in the linked list that matches a given data. It takes in a pointer to the LinkedListBase structure and a pointer to the data to be searched as arguments. It returns the index of the element if found, otherwise it returns -1.
- **LinkedListAt_(LinkedListBase\* ll, unsigned int index)**: This function returns the element at a given index in the linked list. It takes in a pointer to the LinkedListBase structure and the index of the element as arguments. It returns a pointer to the element if found, otherwise it returns NULL.
- **LinkedListClear\_(LinkedListBase\* ll)**: This function clears the linked list. It takes in a pointer to the LinkedListBase structure as an argument. It removes all elements from the linked list, decreases the logical length of the linked list to 0, and calls the memory freeing function for each element.
- **LinkedListDelete\_(LinkedListBase\* ll)**: This function deletes the linked list. It takes in a pointer to the LinkedListBase structure as an argument. It calls the memory freeing function for each element in the linked list, deallocates memory and set the linked list pointer to NULL.
- **LinkedListSize\_(LinkedListBase\* ll)**: This function returns the logical length of the linked list. It takes in a pointer to the LinkedListBase structure as an argument. It returns the logical length of the linked list.

## Templates:

- **LinkedList** is a linked list of void pointers.
- **LinkedListDouble** is a linked list of double values.
- **LinkedListFloat** is a linked list of float values.
- **LinkedListInt** is a linked list of integers.
- **LinkedListString** is a linked list of strings (represented by char pointers).
- **LinkedListChar** is a linked list of characters.
- **LinkedListBool** is a linked list of booleans.

