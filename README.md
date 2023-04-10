# **Table of Contents**
- [Introduction](#introduction)
- [Usage](#usage)
  - [Compiling the project](#compiling-the-project)
  - [Creating Libraries](#creating-libraries)
  - [Running tests](#running-tests)
  - [Cleaning up the directory](#cleaning-up-the-directory)
- [C HELPER](#c-helper)
  - [Macros](#macros)
  - [Functions](#functions)
  - [Note](#note)
- [C SORT](#c-sort)
- [C STACK](#c-stack)
  - [Macros](#macros-1)
  - [Functions](#functions-1)
  - [Templates](#templates)
- [C QUEUE](#c-queue)
  - [Macros](#macros-2)
  - [Functions](#functions-2)
  - [Templates](#templates-1)
- [C VECTOR](#c-vector)
  - [Macros](#macros-3)
  - [Functions](#functions-3)
  - [Templates](#templates-2)
- [C LIST](#c-list)
  - [Macros](#macros-4)
  - [Functions](#functions-4)
  - [Templates](#templates-3)
- [C DOUBLY LIST](#c-doubly-list)
  - [Macros](#macros-5)
  - [Functions](#functions-5)
  - [Templates](#templates-4)
- [C CIRCULAR LIST](#c-circular-list)
  - [Macros](#macros-6)
  - [Functions](#functions-6)
  - [Templates](#templates-5)
- [C MAP](#c-map)
  - [Macros](#macros-7)
  - [Functions](#functions-7)
  - [Templates](#templates-6)
- [C MATRIX](#c-matrix)
  - [Functions](#functions-8)
- [C TREE](#c-tree)
  - [Macros](#macros-8)
  - [Functions](#functions-9)
  - [Templates](#templates-7)
- [C AVL TREE](#c-avl-tree)
  - [Macros](#macros-9)
  - [Functions](#functions-10)
  - [Templates](#templates-8)

# **Introduction**

This project provides a collection of data structures and algorithms implemented in pure C language using void pointers. The implementations are generic in nature and can be used with any data type. The project provides support for primitive C data types such as int, double and char*, chat, float.

The project is designed to be flexible and user-friendly. It comes with a set of comparison and free functions for the supported data types which are declared and defined in the c_helper file. However, users are encouraged to use their own comparison and free functions if they wish to use the algorithms with other data types. If the user chooses to use the provided data types, they can simply use the built-in comparison and free functions and pass the pointer of their own comparison and free functions in the initialization of the data structure.

The data structures currently supported by the project include Stack, Queue, Vector, Hash Maps, Matrix, Linked List, Circular Linked List, Doubly Linked List, Tree, Avl Tree and some basic searching and sorting functions (see above links for complete data structures). Each data structure is implemented with a set of generic functions that perform standard operations such as insertion, deletion, traversal and searching.

The project also provides a set of efficient algorithms for sorting and searching. The sorting algorithms include Bubble Sort, Selection Sort, Insertion Sort, Quick Sort, Merge Sort and Heap Sort. The searching algorithms include Linear Search and Binary Search.

This project has been thoroughly tested with the supported data types to ensure that it is reliable and efficient.

# **Usuage**
## **Compiling the project**
To compile the project and create the executables, run the following command:
```
make all
```
This will compile all the source files, create object files and libraries, and link them to create the executables. 

## **Creating Libraries**
To just create the libraries, run the following command:
```
make lib
```
It will populate .a and .lib files in lib directory.

## **Running tests**
To run the tests, run the following command:
```
make run_tests
```
This will compile and run all the tests in the tests directory. 

## **Cleaning up the directory**
To clean up the directory and remove all the compiled files, run the following command:
```
make clean
```
This will remove all the object files, libraries, and executables. 

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
- **LinkedListIterator** returns the address of the newly created iterator for linked list.
- **LinkedListNext** sets the data and index in iterator to the value pointing in the linked list.

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
- **LinkedListIterator\_(LinkedListBase\* ll)**:  This function creates a new linked list iterator and returns a pointer to it. It takes in a pointer to the LinkedListBase structure as an argument. It allocates memory for the iterator and its data, sets the index to -1, and returns a pointer to the iterator.
- **LinkedListNext\_(LinkedListBase\* ll, LinkedListIter\* lliter)**: This function advances the iterator to the next element in the linked list and returns a pointer to it. It takes in a pointer to the LinkedListBase structure and a pointer to the current iterator as arguments. It checks if the linked list is empty or if the current index is already at the end of the list, in which case it frees the memory for the iterator's data and returns NULL. Otherwise, it increments the index, copies the data at the new index into the iterator's data, and returns the iterator.

## Templates:

- **LinkedList** is a linked list of void pointers.
- **LinkedListDouble** is a linked list of double values.
- **LinkedListFloat** is a linked list of float values.
- **LinkedListInt** is a linked list of integers.
- **LinkedListString** is a linked list of strings (represented by char pointers).
- **LinkedListChar** is a linked list of characters.
- **LinkedListBool** is a linked list of booleans.

# **C DOUBLY LIST**

This is a header file for a doubly linked list implementation in C. It defines two structures: ListNode, which contains basic information about a node in the list such as the element pointer, element size, and the next node pointer, and DoublyLinkedListBase, which contains basic information about the doubly linked list such as the head and tail pointer, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing.

Additionally, there are a number of macros defined to make using the doubly linked list more convenient. 

## Macros:

- **DoublyLinkedListT** creates a doubly linked list template for a given data type.
- **DoublyLinkedListNew** creates a new doubly linked list with a given comparison function and memory freeing function.
- **DoublyLinkedListInsertAtTail** insert elements at the tail of the doubly linked list.
- **DoublyLinkedListInsertAtHead** insert elements at the head of the doubly linked list.
- **DoublyLinkedListReplace** replace only first found element in the doubly linked list.
- **DoublyLinkedListReplaceAll** replace all found elements in the doubly linked list.
- **DoublyLinkedListGetIndex** returns the index of a given element in the doubly linked list.
- **DoublyLinkedListAt** returns the element at a given index in the doubly linked list.
- **DoublyLinkedListClear** clears the doubly linked list, and DoublyLinkedListDelete deletes the doubly linked list.
- **DoublyLinkedListIterator** returns the address of the newly created iterator for doubly linked list.
- **DoublyLinkedListNext** sets the data and index in iterator to the value pointing next in the doubly linked list.
- **DoublyLinkedListBack** sets the data and index in iterator to the value pointing previous in the doubly linked list.

## Functions:

- **DoublyLinkedListNew\_(DoublyLinkedListBase\* dll, unsigned int elemsize, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void \*elems))**: This function creates a new doubly linked list with a given comparison function and memory freeing function. It sets up the DoublyLinkedListBase structure with the appropriate values and initializes the doubly linked list. The function takes in a pointer to the DoublyLinkedListBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **DoublyLinkedListInsertAtTail\_(DoublyLinkedListBase\* dll, void\* data)**: This function inserts an element at the tail of the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the tail of the doubly linked list, increases the logical length of the doubly linked list.
- **DoublyLinkedListInsertAtHead\_(DoublyLinkedListBase\* dll, void\* data)**: This function inserts an element at the head of the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the head of the doubly linked list, increases the logical length of the doubly linked list.
- **DoublyLinkedListReplace\_(DoublyLinkedListBase\* dll, void\* data, void\* value)**: This function replaces the first element in the doubly linked list that matches a given data with a given value. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **DoublyLinkedListReplaceAll\_(DoublyLinkedListBase\* dll, void\* data, void\* value)**: This function replaces all elements in the doubly linked list that matches a given data with a given value. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **DoublyLinkedListGetIndex\_(DoublyLinkedListBase\* dll, void\* data)**: This function returns the index of the first element in the doubly linked list that matches a given data. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the data to be searched as arguments. It returns the index of the element if found, otherwise it returns -1.
- **DoublyLinkedListAt_(DoublyLinkedListBase\* dll, unsigned int index)**: This function returns the element at a given index in the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure and the index of the element as arguments. It returns a pointer to the element if found, otherwise it returns NULL.
- **DoublyLinkedListClear\_(DoublyLinkedListBase\* dll)**: This function clears the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure as an argument. It removes all elements from the doubly linked list, decreases the logical length of the doubly linked list to 0, and calls the memory freeing function for each element.
- **DoublyLinkedListDelete\_(DoublyLinkedListBase\* dll)**: This function deletes the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure as an argument. It calls the memory freeing function for each element in the doubly linked list, deallocates memory and set the doubly linked list pointer to NULL.
- **DoublyLinkedListSize\_(DoublyLinkedListBase\* dll)**: This function returns the logical length of the doubly linked list. It takes in a pointer to the DoublyLinkedListBase structure as an argument. It returns the logical length of the doubly linked list.
- **DoublyLinkedListIterator\_(DoublyLinkedListBase\* dll)**:  This function creates a new doubly linked list iterator and returns a pointer to it. It takes in a pointer to the DoublyLinkedListBase structure as an argument. It allocates memory for the iterator and its data, sets the index to -1, and returns a pointer to the iterator.
- **DoublyLinkedListNext\_(DoublyLinkedListBase\* dll, DoublyLinkedListIter\* dlliter)**: This function advances the iterator to the next element in the doubly linked list and returns a pointer to it. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the current iterator as arguments. It checks if the doubly linked list is empty or if the current index is already at the end of the list, in which case it frees the memory for the iterator's data and returns NULL. Otherwise, it increments the index, copies the data at the new index into the iterator's data, and returns the iterator.
- **DoublyLinkedListBack\_(DoublyLinkedListBase\* dll, DoublyLinkedListIter\* dlliter)**: This function advances the iterator to the previous element in the doubly linked list and returns a pointer to it. It takes in a pointer to the DoublyLinkedListBase structure and a pointer to the current iterator as arguments. It checks if the doubly linked list is empty or if the current index is already at the beginning of the list, in which case it frees the memory for the iterator's data and returns NULL. Otherwise, it increments the index, calculates the index of the previous element from the end of the list, copies the data at the new index into the iterator's data, and returns the iterator.

## Templates:

- **DoublyLinkedList** is a doubly linked list of void pointers.
- **DoublyLinkedListDouble** is a doubly linked list of double values.
- **DoublyLinkedListFloat** is a doubly linked list of float values.
- **DoublyLinkedListInt** is a doubly linked list of integers.
- **DoublyLinkedListString** is a doubly linked list of strings (represented by char pointers).
- **DoublyLinkedListChar** is a doubly linked list of characters.
- **DoublyLinkedListBool** is a doubly linked list of booleans.

# **C CIRCULAR LIST**

This is a header file for a circular linked list implementation in C. It defines two structures: ListNode, which contains basic information about a node in the list such as the element pointer, element size, and the next node pointer, and CircularLinkedListBase, which contains basic information about the circular linked list such as the head and tail pointer, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing.

Additionally, there are a number of macros defined to make using the circular linked list more convenient. 

## Macros:

- **CircularLinkedListT** creates a circular linked list template for a given data type.
- **CircularLinkedListNew** creates a new circular linked list with a given comparison function and memory freeing function.
- **CircularLinkedListInsertAtTail** insert elements at the tail of the circular linked list.
- **CircularLinkedListInsertAtHead** insert elements at the head of the circular linked list.
- **CircularLinkedListReplace** replace only first found element in the circular linked list.
- **CircularLinkedListReplaceAll** replace all found elements in the circular linked list.
- **CircularLinkedListGetIndex** returns the index of a given element in the circular linked list.
- **CircularLinkedListAt** returns the element at a given index in the circular linked list.
- **CircularLinkedListClear** clears the circular linked list, and CircularLinkedListDelete deletes the circular linked list.
- **CircularLinkedListIterator** returns the address of the newly created iterator for circular linked list.
- **CircularLinkedListNext** sets the data and index in iterator to the value pointing in the circular linked list.

## Functions:

- **CircularLinkedListNew\_(CircularLinkedListBase\* cll, unsigned int elemsize, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void \*elems))**: This function creates a new circular linked list with a given comparison function and memory freeing function. It sets up the CircularLinkedListBase structure with the appropriate values and initializes the circular linked list. The function takes in a pointer to the CircularLinkedListBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **CircularLinkedListInsertAtTail\_(CircularLinkedListBase\* cll, void\* data)**: This function inserts an element at the tail of the circular linked list. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the tail of the circular linked list, increases the logical length of the circular linked list.
- **CircularLinkedListInsertAtHead\_(CircularLinkedListBase\* cll, void\* data)**: This function inserts an element at the head of the circular linked list. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the element to be inserted as arguments. It adds the element to the head of the circular linked list, increases the logical length of the circular linked list.
- **CircularLinkedListReplace\_(CircularLinkedListBase\* cll, void\* data, void\* value)**: This function replaces the first element in the circular linked list that matches a given data with a given value. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **CircularLinkedListReplaceAll\_(CircularLinkedListBase\* cll, void\* data, void\* value)**: This function replaces all elements in the circular linked list that matches a given data with a given value. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the data and value to be replaced as arguments.
- **CircularLinkedListGetIndex\_(CircularLinkedListBase\* cll, void\* data)**: This function returns the index of the first element in the circular linked list that matches a given data. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the data to be searched as arguments. It returns the index of the element if found, otherwise it returns -1.
- **CircularLinkedListAt_(CircularLinkedListBase\* cll, unsigned int index)**: This function returns the element at a given index in the circular linked list. It takes in a pointer to the CircularLinkedListBase structure and the index of the element as arguments. It returns a pointer to the element if found, otherwise it returns NULL.
- **CircularLinkedListClear\_(CircularLinkedListBase\* cll)**: This function clears the circular linked list. It takes in a pointer to the CircularLinkedListBase structure as an argument. It removes all elements from the circular linked list, decreases the logical length of the circular linked list to 0, and calls the memory freeing function for each element.
- **CircularLinkedListDelete\_(CircularLinkedListBase\* cll)**: This function deletes the circular linked list. It takes in a pointer to the CircularLinkedListBase structure as an argument. It calls the memory freeing function for each element in the circular linked list, deallocates memory and set the circular linked list pointer to NULL.
- **CircularLinkedListSize\_(CircularLinkedListBase\* cll)**: This function returns the logical length of the circular linked list. It takes in a pointer to the CircularLinkedListBase structure as an argument. It returns the logical length of the circular linked list.
- **CircularLinkedListIterator\_(CircularLinkedListBase\* cll)**:  This function creates a new circular linked list iterator and returns a pointer to it. It takes in a pointer to the CircularLinkedListBase structure as an argument. It allocates memory for the iterator and its data, sets the index to -1, and returns a pointer to the iterator.
- **CircularLinkedListNext\_(CircularLinkedListBase\* cll, CircularLinkedListIter\* clliter)**: This function advances the iterator to the next element in the circular linked list and returns a pointer to it. It takes in a pointer to the CircularLinkedListBase structure and a pointer to the current iterator as arguments. It checks if the circular linked list is empty or if the current index is already at the end of the list, in which case it frees the memory for the iterator's data and returns NULL. Otherwise, it increments the index, copies the data at the new index into the iterator's data, and returns the iterator.

## Templates:

- **CircularLinkedList** is a circular linked list of void pointers.
- **CircularLinkedListDouble** is a circular linked list of double values.
- **CircularLinkedListFloat** is a circular linked list of float values.
- **CircularLinkedListInt** is a circular linked list of integers.
- **CircularLinkedListString** is a circular linked list of strings (represented by char pointers).
- **CircularLinkedListChar** is a circular linked list of characters.
- **CircularLinkedListBool** is a circular linked list of booleans.

# **C MAP**

This code defines a C-language implementation of a map data structure, which is a collection of key-value pairs. The structure, called MapBase, contains fields for the elements of the map (MapNode* elems), the number of elements in the map (unsigned int logiclen), the allocated size of the map (unsigned int alloclen), the size of the keys and values (unsigned int keysize and valuesize), a hash of the elements (char* hash), and several function pointers for hashing, collision resolution, data comparison, and freeing elements.

## Macros:

There are also several macros defined that simplify the use of the map, such as MapNew, MapSet, MapSize, MapGet, MapRemove, MapIterator, MapNext, MapClear, and MapDelete. The code also provides several example implementations of the function pointers for HashFunc, CollRes, and DataCmp, such as HashFunctionStr, HashFunctionInt, LinearProbing, QuadraticProbing, and DoubleHashing.

- **MapNew** is a macro that creates a new map object, and initializes it with the specified HashFunc, CollRes, DataCmp, FreeFuncKey, and FreeFuncVal function pointers.
- **MapSet** is a macro that sets a new key-value pair in the map.
- **MapSize** is a macro that returns the number of elements in the map.
- **MapGet** is a macro that gets the value associated with a specified key in the map.
- **MapRemove** is a macro that removes a key-value pair from the map.
- **MapIterator** is a macro that returns an iterator for the map, which can be used to iterate through the elements of the map.
- **MapNext** is a macro that moves the iterator to the next element of the map.
- **MapClear** is a macro that clears all elements from the map.
- **MapDelete** is a macro that deletes the map and frees all memory associated with it.

## Functions:

- **MapNew\_(MapBase\* m, unsigned int keysize, unsigned int valuesize, unsigned int(\*HashFunc)(const void\* key, unsigned int keysize), unsigned int(\*CollRes)(unsigned int hash, unsigned int i),  int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFuncKey)(void\* elems), void(\*FreeFuncVal)(void\* elems))** function creates a new map and initializes the base member of the MapBase struct. It also allocates memory for the array of map entries and initializes its elements with NULL. The function also assigns the passed key size, value size, hash function, collision resolution function, data comparison function, and free functions for key and value to the corresponding members of the base struct.
- **MapSet\_(MapBase\* m, void\* key, void\* value)** function sets the value for a given key in the map. This function uses the hash function and collision resolution function to find the index of the map entry corresponding to the given key. If the key is not found in the map, a new entry is created and the key and value are inserted into it. If the key is found in the map, the corresponding value is updated with the given value. If the number of elements in the map is equal to the number of allocated entries, the map is resized to accomodate more elements.
- **MapResize\_(MapBase\* m)** function resizes the map by creating a new array of map entries and copying the existing elements to the new array. This function doubles the size of the array and re-hashes the elements according to the new size.
- **MapSize\_(MapBase\* m)** function returns the number of elements stored in the map.
- **MapGet\_(MapBase\* m, void\* key)** function returns the value of the element with the specified key in the map.
- **MapRemove\_(MapBase\* m, void\* key)** function removes the element with the specified key from the map.
- **MapIterator\_(MapBase\* m)** function creates a new map iterator and initializes the keyindex member of the MapIter struct.
- **MapNext\_(MapBase\* m, MapIter\* mapiter)** function returns the next non-empty key-value pair in the map.
- **MapClear\_(MapBase\* m)** function clears all the elements from the map. And set all elements to NULL. Logical length become 0. However allocated length remains same.
- **MapDelete_(MapBase* m)** function that deletes the map and frees all the allocated memory. 

## Templates:

- **Map** is map of void pointer keys and void pointer values.
- **MapDouble** is map of double value keys and double value values.
- **MapFloat** is map of float value keys and float value values.
- **MapInt** is map of integer value keys and integer value values.
- **MapString** is map of string char pointer keys and string char pointer values.
- **MapStringDouble** is a map template that uses a string as the key and double as the value.
- **MapStringFloat** is a map template that uses a string as the key and float as the value.
- **MapStringInt** is a map template that uses a string as the key and integer as the value.
- **MapStringBool** is a map template that uses a string as the key and boolean as the value.
- **MapCharDouble** is a map template that uses a character as the key and double as the value.
- **MapCharFloat** is a map template that uses a character as the key and float as the value.
- **MapCharInteger** is a map template that uses a character as the key and integer as the value.
- **MapCharBool** is a map template that uses a character as the key and boolean as the value.
- **MapIntDouble** is a map template that uses a integer as the key and double as the value.
- **MapIntFloat** is a map template that uses a integer as the key and float as the value.
- **MapIntString** is a map template that uses a integer as the key and string as the value.
- **MapIntBool** is a map template that uses a integer as the key and boolean as the value.
- **MapFloatDouble** is a map template that uses a float as the key and double as the value.
- **MapFloatInt** is a map template that uses a float as the key and integer as the value.
- **MapFloatString** is a map template that uses a float as the key and string as the value.
- **MapFloatBool** is a map template that uses a float as the key and boolean as the value.
- **MapDoubleString** is a map template that uses a double as the key and string as the value.
- **MapDoubleInt** is a map template that uses a double as the key and integer as the value.
- **MapDoubleFloat** is a map template that uses a double as the key and float as the value.
- **MapDoubleBool** is a map template that uses a double as the key and boolean as the value.

# **C MATRIX**

The **Matrix** class is a data structure for representing and manipulating matrices in C. The class definition starts with a header guard, followed by an include for a "c\_helper.h" file. The definition of the **Matrix** structure starts with the definition of a struct, which consists of the following member variables:

- **unsigned int num\_rows** : Number of rows in the matrix.
- **unsigned int num\_cols** : Number of columns in the matrix.
- **double\*\* data** : A two-dimensional array of double-precision floating-point values representing the data in the matrix.
- **bool is\_square** : A boolean value indicating whether the matrix is square or not.

## Functions: 
- **Matrix\* MatrixEmpty(unsigned int num\_rows, unsigned int num\_cols)** creates and returns a new empty matrix with given number of rows and columns and all values are remains uninitialized.
- **Matrix\* MatrixEmptyLike(Matrix\* m)** creates and returns a new empty matrix with the same number of rows and columns as the given matrix and all values are remains uninitialized.
- **Matrix\* MatrixNew(unsigned int num\_rows, unsigned int num\_cols)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols.
- **Matrix\* MatrixNewLike(Matrix\* m)** creates and returns a new empty matrix with the same number of rows and columns as the given matrix and all values set to 0.
- **Matrix\* MatrixRandom(unsigned int num\_rows, unsigned int num\_cols, double min, double max)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols and fills it with random numbers in the range [min, max].
- **Matrix\* MatrixRandomLike(Matrix\* m, double min, double max)** creates and returns a new matrix with given number of rows and columns as given matrix and all values set randomly within a specified range.
- **Matrix\* MatrixSquare(unsigned int size)** Allocates memory for a new Matrix structure with the given size and size number of columns and rows.
- **Matrix\* MatrixSquareLike(Matrix\* m)** creates and returns a new square matrix with size as given matrix and all values set to 0.
- **Matrix\* MatrixSquareRandom(unsigned int size, double min, double max)** Allocates memory for a new square Matrix structure with the given size and fills it with random numbers in the range [min, max].
- **Matrix\* MatrixSquareRandomLike(Matrix\* m, double min, double max)** creates and returns a new square matrix with size as given matrix and all values set randomly within a specified range.
- **Matrix\* MatrixZero(unsigned int num\_rows, unsigned int num\_cols)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols and fills it with zeros.
- **Matrix\* MatrixZeroLike(Matrix\* m)** creates and returns a new matrix with rows and columns as given matrix and all values set to 0.
- **Matrix\* MatrixOne(unsigned int num\_rows, unsigned int num\_cols)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols and fills it with ones.
- **Matrix\* MatrixOneLike(Matrix\* m)** creates and returns a new matrix with rows and columns as given matrix and all values set to 1.
- **Matrix\* MatrixN(unsigned int num\_rows, unsigned int num\_cols, double value)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols and fills it with the given value.
- **Matrix\* MatrixNLike(Matrix\* m, double value)** creates and returns a new matrix with dimensions same to passed matrix and all elements set to a given value.
- **Matrix\* MatrixIdentity(unsigned int size)** Allocates memory for a new square Matrix structure with the given size and fills it with an identity matrix.
- **Matrix\* MatrixIdentityLike(Matrix\* m)** creates and returns a new identity matrix with dimensions same as given matrix.
- **Matrix\* MatrixEye(unsigned int size, int k)** inspired from numpy python; creates and returns a new matrix with ones on the diagonal and zeros elsewhere. The position of diagonal can be changed by specifying the value of k parameter. See header file comments for more information.
- **Matrix\* MatrixEyeLike(Matrix\* m, int k)** inspired from numpy python; creates and returns a new matrix with ones on the diagonal and zeros elsewhere of size nxn same as matrix passed. The position of diagonal can be changed by specifying the value of k parameter. See header file comments for more information.
- **Matrix\* MatrixARange(double start, double stop, double step)** inspired from numpy python; Returns a pointer to a Matrix containing evenly spaced values within a given interval, with a given step size. See header file comments for more information.
- **Matrix\* MatrixLinearSpace(double start, double stop, unsigned int n)** inspired from numpy python; Returns a pointer to a Matrix containing evenly spaced values within a given interval, with a given number of samples. See header file comments for more information.
- **Matrix\* MatrixLogSpace(double start, double stop, unsigned int n)** inspired from numpy python; Returns a pointer to a Matrix containing evenly spaced values within a given interval, with a given number of samples, in logarithmic space. See header file comments for more information.
- **Matrix\* MatrixGeometrySpace(double start, double stop, unsigned int n)** inspired from numpy python; Returns a pointer to a Matrix containing values within a given interval, with a geometric spacing. See header file comments for more information.
- **Matrix\* MatrixFrom(unsigned int num\_rows, unsigned int num\_cols, unsigned int n\_values, double \*values)** Allocates memory for a new Matrix structure with the given number of num_rows and num_cols and fills it with the first n_values from the given array of values.
- **Matrix\* MatrixFromFile(const char\* file)** Allocates memory for a new Matrix structure and fills it with the data from the file specified by file.
- **Matrix\* MatrixCopy(Matrix\* m)** Allocates memory for a new Matrix structure and copies the data from the given Matrix structure m.
- **bool IsMatrixEqualDim(Matrix\* m1, Matrix\* m2)** Returns true if the dimensions of Matrix structures m1 and m2 are equal, false otherwise.
- **void PrintMatrix(Matrix\* m, const char\* data_format)** Prints the contents of the matrix in the specified data format.
- **bool IsMatrixInvertible(Matrix\* m)** Returns true if the matrix is invertible, false otherwise.
- **Matrix\* MatrixGet(Matrix\* m, unsigned row, unsigned col)** Returns the value stored in the matrix at the specified row and column.
- **Matrix\* MatrixColumnGet(Matrix\* m, unsigned int col)** Returns a column vector containing the values in the specified column of the matrix.
- **Matrix\* MatrixRowGet(Matrix\* m, unsigned int row)** Returns a row vector containing the values in the specified row of the matrix.
- **void MatrixSet(Matrix\* m, unsigned int row, unsigned int col, double value)** Sets the value of the matrix at the specified row and column.
- **void MatrixAllSet(Matrix\* m, double value)** Sets the value of all elements in the matrix to the specified value.
- **void MatrixDiagonalSet(Matrix\* m, double value)** Sets the value of all elements along the main diagonal of the matrix to the specified value.
- **void MatrixRowMultiplyValue(Matrix\* m, unsigned int row, double value)** Multiplies all elements in the specified row of the matrix by the specified value.
- **void MatrixRowAddValue(Matrix\* m, unsigned int row, double value)** Adds the specified value to all elements in the specified row of the matrix.
- **void MatrixColumnMultiplyValue(Matrix\* m, unsigned int col, double value)** Multiplies all elements in the specified column of the matrix by the specified value.
- **void MatrixColumnAddValue(Matrix\* m, unsigned int col, double value)** Adds the specified value to all elements in the specified column of the matrix.
- **void MatrixRowMultiplyRow(Matrix\* m, unsigned int where, unsigned int row, double value)** Multiplies the elements in the specified row by the elements in another specified row.
- **void MatrixRowAddRow(Matrix\* m, unsigned int where, unsigned int row, double value)** Adds the elements in one specified row to another specified row.
- **void MatrixColumnMultiplyColumn(Matrix\* m, unsigned int where, unsigned int col, double value)** Multiplies the elements in the specified column by the elements in another specified column.
- **void MatrixColumnAddValueColumn(Matrix\* m, unsigned int where, unsigned int col, double value)** Adds the elements in one specified column to another specified column.
- **void MatrixWholeMultiply(Matrix\* m, double value)** Multiplies all elements in the matrix by the specified value.
- **void MatrixWholeAdd(Matrix\* m, double value)** Adds the specified value to all elements in the matrix.
- **Matrix\* MatrixRowRemove(Matrix\* m, unsigned int row)** Removes a specified row from the matrix and returns the new modified matrix.
- **Matrix\* MatrixColumnRemove(Matrix\* m, unsigned int row)** Removes a specified column from the matrix and returns the new modified matrix.
- **void MatrixRowSwap(Matrix\* m, unsigned int row1, unsigned int row2)** Swaps two specified rows in the matrix.
- **void MatrixColumnSwap(Matrix\* m, unsigned int col1, unsigned int col2)** Swaps two specified columns in the matrix.
- **Matrix\* MatrixBroadcastRows(Matrix\* m, unsigned int row)** Replicates a specified row of the matrix to create a new matrix with multiple instances of that row.
- **Matrix\* MatrixBroadcastColumns(Matrix\* m, unsigned int col)** Replicates a specified column of the matrix to create a new matrix with multiple instances of that column.
- **Matrix\* MatrixBroadcastRowsAndColumns(Matrix\* m, unsigned int row, unsigned int col)** Replicates a specified row and column of the matrix to create a new matrix with multiple instances of those elements.
- **Matrix\* MatrixRowStack(Matrix\* m1, Matrix\* m2)** Stack two matrices row-wise (vertically) and return a new matrix.
- **Matrix\* MatrixColumnStack(Matrix* m1, Matrix\* m2)** Stack two matrices column-wise (horizontally) and return a new matrix.
- **Matrix\* MatrixAdd(Matrix\* m1, Matrix\* m2)** Adds two matrices together element-wise and returns the result as a new matrix. The matrices must have the same dimensions.
- **Matrix\* MatrixSubtract(Matrix\* m1, Matrix\* m2)** Subtracts one matrix from another element-wise and returns the result as a new matrix. The matrices must have the same dimensions.
- **Matrix\* MatrixMultiply(Matrix\* m1, Matrix\* m2)** Performs matrix multiplication between two matrices and returns the result as a new matrix. The number of columns in **m1** must be equal to the number of rows in **m2**.
- **Matrix\* MatrixAddWithBroadcast(Matrix\* m1, Matrix\* m2)** Adds two matrices together element-wise, with broadcasting of the smaller matrix to match the dimensions of the larger matrix.
- **Matrix\* MatrixSubtractWithBroadcast(Matrix\* m1, Matrix\* m2)** Subtracts one matrix from another element-wise, with broadcasting of the smaller matrix to match the dimensions of the larger matrix.
- **Matrix\* MatrixMultiplyWithBroadcast(Matrix\* m1, Matrix\* m2)** Multiply two matrices m1 and m2 with Broadcast if required and return the result.
- **Matrix\* MatrixElementWiseMultiplyWithBroadcast(Matrix\* m1, Matrix\* m2)**  Mutiply two matrices element wise aka (Hadamard product) m1 and m2 with Broadcast if required and return and create the resultant matrix.
- **void MatrixTranspose(Matrix\* m)** Transposes the input matrix by swapping rows and columns, and modifies the input matrix in-place.
- **double MatrixTrace(Matrix\* m)** Computes the trace of the input matrix, which is the sum of the elements on the main diagonal.
- **double MatrixDeterminant(Matrix\* m)** Computes the determinant of the input matrix.
- **void MatrixRowEchelon(Matrix\* m)** Transforms the input matrix into row echelon form, a type of triangular form, by row operations. The function modifies the input matrix in-place.
- **void MatrixReducedRowEchelon(Matrix\* m)** Transforms the input matrix into reduced row echelon form, a type of triangular form, by row operations. The function modifies the input matrix in-place.
- **Matrix\* MatrixRowEchelonGet(Matrix\* m)** Returns a new matrix that is the row echelon form of the input matrix, without modifying the input matrix.
- **Matrix\* MatrixReducedRowEchelonGet(Matrix\* m)** Returns a new matrix that is the reduced row echelon form of the input matrix, without modifying the input matrix.
- **double MatrixColumnL2Norm(Matrix\* m, unsigned int col)** Computes the L2 norm, also known as the Euclidean norm, of a specified column of the input matrix.
- **Matrix\* MatrixL2Norm(Matrix\* m)** Computes the L2 norm, also known as the Euclidean norm, of each column of the input matrix and returns a new matrix with the results.
- **double MatrixCosineSimilarity(Matrix\* m1, Matrix\* m2)** Compute the cosine similarity between two column matrices.
- **double MatrixTSSSSimilarity(Matrix\* m1, Matrix\* m2)** Calculate the Time Series Similarity using TS-SS similarity metric between two row vectors.
- **double MatrixEuclideanDistance(Matrix\* m1, Matrix\* m2)** Compute the Euclidean distance between two column matrices.
- **double MatrixManhattanDistance(Matrix\* m1, Matrix\* m2)** Calculate Manhattan distance between two matrices.
- **double MatrixMinkowskiDistance(Matrix\* m1, Matrix\* m2, int p)** Calculate Minkowski distance between two matrices.
- **void MatrixFree(Matrix\* m)** Deallocates the memory associated with the input matrix, freeing it for use by other parts of the program.

# **C TREE**

This is a header file for a binary tree implementation in C. It defines a structure called TreeBase, which contains basic information about the tree such as the element pointer, element size, logical length, and allocated length. It also contains function pointers for data comparison and memory freeing. Additionally, there are a number of macros defined to make using the binary tree more convenient.

## Macros: 

The given macros are for creating and manipulating a binary tree template for a specific data type T.

- **TreeT(T)** macro creates a struct with a TreeBase as a member and an additional member with the name data\_ of the type T.
- **TreeNew(t, DataCmp, FreeFunc)** macro creates a new Tree object using the provided DataCmp function to compare elements and FreeFunc to free memory, then returns a pointer to the newly created Tree object.
- **TreeInsert(t, data)** macro inserts the provided data into the Tree object referenced by 't'.
- **TreeContains(t, data)** macro checks if the provided data exists in the Tree object referenced by 't', returning 1 if it is found, and 0 otherwise.
- **TreeRemove(t, data)** macro removes the provided data from the Tree object referenced by 't'.
- **TreeClear(t)** macro removes all elements from the Tree object referenced by 't'.
- **TreeDelete(t)** macro frees all memory associated with the Tree object referenced by 't'.
- **TreeSize(t)** macro returns the number of elements currently stored in the Tree object referenced by 't'.
- **TreeEmpty(t)** macro checks if the Tree object referenced by 't' is empty, returning 1 if it is empty and 0 otherwise.
- **TreeMin(t)** macro returns a pointer to the minimum element stored in the Tree object referenced by 't'.
- **TreeMax(t)** macro returns a pointer to the maximum element stored in the Tree object referenced by 't'.
- **TreeInOrder(t, data\_format)** macro traverses the Tree object referenced by 't' in in-order traversal and prints each element using the provided 'data\_format' format string.
- **TreePreOrder(t, data\_format)** macro traverses the Tree object referenced by 't' in pre-order traversal and prints each element using the provided 'data\_format' format string.
- **TreePostOrder(t, data\_format)** macro traverses the Tree object referenced by 't' in post-order traversal and prints each element using the provided 'data\_format' format string.

## Functions: 

- **void TreeNew\_(TreeBase\* t, unsigned int elemsize, int(\*DataCmp)(const void \*key1, const void \*key2, unsigned int keysize), void(\*FreeFunc)(void\* elems))**: This function creates a new binary tree with a given comparison function and memory freeing function. It sets up the TreeBase structure with the appropriate values and initializes the binary tree. The function takes in a pointer to the TreeBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **TreeNode\* TreeInsert\_(TreeBase\* t, void\* data)**: This function inserts an element into the binary tree. It takes in a pointer to the TreeBase structure and a pointer to the element to be inserted as arguments.
- **bool TreeContains\_(TreeBase\* t, void\* data)**: This function checks if an element is present in the binary tree. It takes in a pointer to the TreeBase structure and a pointer to the element to be checked as arguments.
- **void TreeRemove\_(TreeBase\* t, void\* data)**: This function removes an element from the binary tree. It takes in a pointer to the TreeBase structure and a pointer to the element to be removed as arguments.
- **void TreeClear\_(TreeBase\* t)**: This function clears all elements from the binary tree. It takes in a pointer to the TreeBase structure as an argument.
- **void TreeDelete\_(TreeBase\* t)**: This function deletes the binary tree and frees the memory associated with it. It takes in a pointer to the TreeBase structure as an argument.
- **unsigned int TreeSize\_(TreeBase\* t)**: This function returns the number of elements in the binary tree. It takes in a pointer to the TreeBase structure as an argument.
- **bool TreeEmpty\_(TreeBase\* t)**: This function checks if the binary tree is empty. It takes in a pointer to the TreeBase structure as an argument.
- **void\* TreeMin\_(TreeBase\* t)**: This function returns a pointer to the smallest element in the binary tree. It takes in a pointer to the TreeBase structure as an argument.
- **void\* TreeMax\_(TreeBase\* t)**: This function returns a pointer to the largest element in the binary tree. It takes in a pointer to the TreeBase structure as an argument.
- **void TreeInOrder\_(TreeBase\* t, const char\* data\_format)**: This function performs an in-order traversal of the binary tree and prints the data in the specified format. It takes in a pointer to the TreeBase structure and a string specifying the format of the data as arguments.
- **void TreePreOrder\_(TreeBase\* t, const char\* data\_format)**: This function performs a pre-order traversal of the tree and prints the data of each node in the specified format. The function takes in a pointer to the TreeBase structure and a pointer to a string specifying the format of the data to print as arguments.
- **void TreePostOrder\_(TreeBase\* t, const char\* data\_format)**: This function performs a post-order traversal of the tree and prints the data of each node in the specified format. The function takes in a pointer to the TreeBase structure and a pointer to a string specifying the format of the data to print as arguments.

## Templates: 

- **Tree** is a binary tree template for any data type.
- **TreeInt** is a binary tree template specifically for integers.
- **TreeFloat** is a binary tree template specifically for single-precision floating-point numbers.
- **TreeDouble** is a binary tree template specifically for double-precision floating-point numbers.
- **TreeChar** is a binary tree template specifically for characters.
- **TreeString** is a binary tree template specifically for null-terminated character strings.

# **C AVL TREE**

## Macros: 

The given macros are for creating and manipulating a avl binary tree template for a specific data type T.

- **AvlTreeT(T)** macro creates a struct with an AvlTreeBase as a member and an additional member with the name data\_ of the type T.
- **AvlTreeNew(t, DataCmp, FreeFunc)** macro initializes an Avl tree pointed to by 't' with a comparison function 'DataCmp' and a function 'FreeFunc' to free the tree elements.
- **AvlTreeHeight(t)** macro returns the height of the Avl tree pointed to by 't'.
- **AvlTreeBalance(t)** macro returns the balance factor of the Avl tree pointed to by 't'.
- **AvlTreeLeftRotate(t)** macro performs a left rotation on the Avl tree pointed to by 't'.
- **AvlTreeRightRotate(t)** macro performs a right rotation on the Avl tree pointed to by 't'.
- **AvlTreeInsert(t, data)** macro inserts the data pointed to by 'data' into the Avl tree pointed to by 't'.
- **AvlTreeContains(t, data)** macro returns true if the Avl tree pointed to by 't' contains the data pointed to by 'data'.
- **AvlTreeRemove(t, data)** macro removes the data pointed to by 'data' from the Avl tree pointed to by 't'.
- **AvlTreeClear(t)** macro clears all the elements of the Avl tree pointed to by 't'.
- **AvlTreeDelete(t)** macro clears and deletes the Avl tree pointed to by 't'.
- **AvlTreeSize(t)** macro returns the number of elements in the Avl tree pointed to by 't'.
- **AvlTreeEmpty(t)** macro returns true if the Avl tree pointed to by 't' is empty.
- **AvlTreeMin(t)** macro returns the minimum element of the Avl tree pointed to by 't'.
- **AvlTreeMax(t)** macro returns the maximum element of the Avl tree pointed to by 't'.
- **AvlTreeInOrder(t, data\_format)** macro performs an in-order traversal of the Avl tree pointed to by 't', printing each element using the specified 'data\_format'.
- **AvlTreePreOrder(t, data\_format)** macro performs a pre-order traversal of the Avl tree pointed to by 't', printing each element using the specified 'data\_format'.
- **AvlTreePostOrder(t, data\_format)** macro performs a post-order traversal of the Avl tree pointed to by 't', printing each element using the specified 'data\_format'.

## Functions: 

- **AvlTreeNew\_(AvlTreeBase**_ **t, unsigned int elemsize, int(\*DataCmp)(const void \*key1, const void** _**key2, unsigned int keysize), void(\*FreeFunc)(void**_ **elems)):** This function creates a new AVL tree with a given comparison function and memory freeing function. It sets up the AvlTreeBase structure with the appropriate values and initializes the AVL tree. The function takes in a pointer to the AvlTreeBase structure, the size of an element, a pointer to a function that compares data, and a pointer to a function that frees memory as arguments.
- **AvlTreeHeight\_(AvlTreeBase**_ **t):** This function returns the height of the AVL tree with the root node specified by the pointer t.
- **AvlTreeBalance\_(AvlTreeBase**_ **t):** This function returns the balance factor of the AVL tree with the root node specified by the pointer t.
- **AvlTreeLeftRotate\_(AvlTreeBase**_ **t):** This function performs a left rotation on the AVL tree with the root node specified by the pointer t and returns a pointer to the new root.
- **AvlTreeRightRotate\_(AvlTreeBase**_ **t):** This function performs a right rotation on the AVL tree with the root node specified by the pointer t and returns a pointer to the new root.
- **AvlTreeInsert\_(AvlTreeBase t, void**_ **data):** This function inserts a new node with the given data into the AVL tree with the root node specified by the pointer t and returns a pointer to the new root.
- **AvlTreeContains\_(AvlTreeBase t, void**_ **data):** This function checks if a node with the given data exists in the AVL tree with the root node specified by the pointer t and returns a boolean value.
- **AvlTreeRemove\_(AvlTreeBase t, void_** **data):** This function removes the node with the given data from the AVL tree with the root node specified by the pointer t and returns a pointer to the new root. If the node does not exist, it returns NULL.
- **AvlTreeClear\_(AvlTreeBase**_ **t):** This function removes all the nodes from the AVL tree and resets the AVL tree to an empty state. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeDelete\_(AvlTreeBase**_ **t):** This function removes all the nodes from the AVL tree and frees the memory allocated for the AVL tree. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeSize\_(AvlTreeBase**_ **t):** This function returns the number of elements in the AVL tree. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeEmpty\_(AvlTreeBase**_ **t):** This function returns a boolean value indicating whether the AVL tree is empty or not. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeMin\_(AvlTreeBase**_ **t):** This function returns a pointer to the node containing the smallest element in the AVL tree. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeMax\_(AvlTreeBase**_ **t):** This function returns a pointer to the node containing the largest element in the AVL tree. It takes a pointer to an AvlTreeBase structure as an argument.
- **AvlTreeInOrder\_(AvlTreeBase_** **t, const char \*data\_format):** This function traverses the AVL tree in-order and prints the data of each node using the provided format string. It takes a pointer to an AvlTreeBase structure and a format string as arguments.
- **AvlTreePreOrder\_(AvlTreeBase_** **t, const char \*data\_format):** This function traverses the AVL tree pre-order and prints the data of each node using the provided format string. It takes a pointer to an AvlTreeBase structure and a format string as arguments.
- **AvlTreePostOrder\_(AvlTreeBase**_ **t, const char \*data\_format):** This function traverses the AVL tree post-order and prints the data of each node using the provided format string. It takes a pointer to an AvlTreeBase structure and a format string as arguments.

## Templates: 

- **AvlTree** is a typedef of AvlTreeT(void), which creates an AvlTree struct with a void data\_ member.
- **AvlTreeInt** is a typedef of AvlTreeT(int), which creates an AvlTree struct with an int data\_ member.
- **AvlTreeFloat** is a typedef of AvlTreeT(float), which creates an AvlTree struct with a float data\_ member.
- **AvlTreeDouble** is a typedef of AvlTreeT(double), which creates an AvlTree struct with a double data\_ member.
- **AvlTreeChar** is a typedef of AvlTreeT(char), which creates an AvlTree struct with a char data\_ member.
- **AvlTreeString** is a typedef of AvlTreeT(char), which creates an AvlTree struct with a char data\_ member.
