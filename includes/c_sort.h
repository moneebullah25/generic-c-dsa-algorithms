#ifndef _C_SORT_HEADER_
#define _C_SORT_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "c_helper.h"

/**
 * Function that performs a linear search on an array of elements for a specific key.
 * The function compares the key with each element in the array using the provided memory comparison function and returns the address of the first element that matches the key.
 * If no match is found, the function returns a null pointer.
 * The function asserts that the key, base, and memory comparison function pointers passed are not null.
 * @param key pointer to the key to be searched for
 * @param base pointer to the base of the array
 * @param nelems number of elements in the array
 * @param elemsize size of each element in the array
 * @param MemCmp pointer to the memory comparison function
 * Requirements:
 * - key pointer, base pointer, and MemCmp pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void* LinearSearch(void* key, void* base, unsigned int nelems, unsigned int elemsize, int(*MemCmp)(const void*, const void*, unsigned int));

/**
 * Function that performs a binary search on a sorted array of elements for a specified key.
 * The function asserts that the base pointer, key, and comparison function passed are not null.
 * The function recursively divides the array in half and compares the middle element to the key.
 * If the key is found, the function returns a pointer to the element.
 * If the key is not found, the function returns null.
 * @param key pointer to the key to be searched for
 * @param base pointer to the base of the array
 * @param s starting index of the array
 * @param n ending index of the array
 * @param elemsize size of each element in the array
 * @param MemCmp pointer to the comparison function
 * Requirements:
 * - key, base, and MemCmp pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(log n)
**/
void* BinarySearch(void* key, void* base, unsigned int s, unsigned int n, unsigned int elemsize, int(*MemCmp)(const void*, const void*, unsigned int));

/**
 * Function that sorts an array of elements using the bubble sort algorithm.
 * The function takes a pointer to the base of the array, the size of each element, the number of elements, a pointer to a memory comparison function, and a pointer to a memory swap function as arguments.
 * The function repeatedly iterates through the array comparing adjacent elements and swapping them if they are in the wrong order.
 * @param base pointer to the base of the array
 * @param elemsize size of each element in the array
 * @param n number of elements in the array
 * @param MemCmp pointer to a memory comparison function that compares two elements
 * @param MemSwap pointer to a memory swap function that swaps two elements
 * Requirements:
 * - key, base, MemSwap and MemCmp pointer should not be nullptr
 * Time complexity: O(n^2)
 * Space complexity: O(1)
**/
void BubbleSort(void* base, unsigned int elemsize, unsigned int n, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));
	
/**
 * Function that sorts an array of elements using the QuickSort algorithm.
 * The function takes as input a base pointer to the array, the size of the elements in the array, the low and high indices of the array, a pointer to a comparison function and a pointer to a swap function.
 * The function asserts that the base pointer, comparison function and swap function passed are not null.
 * @param base pointer to the base of the array
 * @param elemsize size of the elements in the array
 * @param low the low index of the array
 * @param high the high index of the array
 * @param MemCmp pointer to a comparison function
 * @param MemSwap pointer to a swap function
 * Requirements:
 * - base pointer, MemCmp and MemSwap should not be nullptr
 * Time complexity: O(n^2) in worst case, O(n*log n) on average case
 * Space complexity: O(log n)
**/
void QuickSort(void* base, int elemsize, int low, int high, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));
	
/**
 * Sorts an array of elements using the merge sort algorithm.
 * The function takes in a pointer to the base of the array, the size of each element, the left and right bounds of the array,
 * a comparison function to compare elements, and a function to swap elements.
 * The function asserts that the base pointer and the element size are not null.
 * @param base pointer to the base of the array
 * @param elemsize size of each element in the array
 * @param l left bound of the array
 * @param r right bound of the array
 * @param MemCmp pointer to a function that compares elements
 * @param MemSwap pointer to a function that swaps elements
 * Requirements:
 * - base pointer and elemsize should not be nullptr
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
**/
void MergeSort(void* base, unsigned int elemsize, unsigned int l, unsigned int r, 
    int(*MemCmp)(const void*, const void*, unsigned int),
    void(*MemSwap)(void *vp1, void *vp2, unsigned int nbytes));


#ifdef __cplusplus
}
#endif /* __cplusplus */
	
#endif /* _C_SORT_HEADER_ */
