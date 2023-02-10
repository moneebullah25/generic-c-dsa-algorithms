#ifndef _C_HELPER_HEADER_
#define _C_HELPER_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif

#define bool  _Bool
#define false 0
#define true  1


	/**
	* Macro for debugging assertion.
	* Time complexity:
	*		-   O(1)
	* If the macroDEBUG is defined, the macro will check if the given expression "x" is true, if not it will call the assert_handler function with the expression, file name and line number as arguments and halt the program execution.
	* If the macroDEBUG is not defined, the macro will not check the expression and will not perform any action.
	* @param x Expression to be checked for assertion
	*/
#ifdef DEBUG
#define ASSERT(x) ((void)(!(x) && assert_handler(#x, __FILE__, __LINE__) && (HALT(), 1)))
#else
#define ASSERT(x) ((void)sizeof(x))
#endif

	/**
	* Macro for finding the maximum of two given values.
	* Time complexity:
	* -   O(1)
	* @param X First value
	* @param Y Second value
	* @return The maximum of the two given values
	*/
#define M_MAX(X, Y) ((X) >= (Y) ? (X) : (Y))

	/**
	* Macro for finding the minimum of two given values.
	* Time complexity:
	* -   O(1)
	* @param X First value
	* @param Y Second value
	* @return The minimum of the two given values
	*/
#define M_MIN(X, Y) ((X) <= (Y) ? (X) : (Y))

	/**
	* Macro for finding the absolute value of a given value.
	* Time complexity:
	* -   O(1)
	* @param X The value of which absolute value is to be calculated
	* @return The absolute value of the given value
	*/
#define M_ABS(X) ((X < 0) ? (-X) : (X))

	/**
	* Frees the memory allocated for a string.
	* Requirements:
	*		-   elems != NULL
	* Time complexity:
	*		-   O(1)
	* @param elems The pointer to the string to be freed.
	*/
	void FreeString(void *elems);

	/**
	* Frees the memory allocated for a pointer.
	* Requirements:
	*		-   elems != NULL
	* Time complexity:
	*		-   O(1)
	* @param elems The pointer to the pointed data to be freed.
	*/
	void FreeData(void *elems);

	/**
	* Swaps the memory contents of two given pointers.
	* Requirements:
	*		-   vp1 and vp2 != NULL
	* Time complexity:
	*		-   O(nbytes)
	* @param vp1 Pointer to the first memory location to be swapped
	* @param vp2 Pointer to the second memory location to be swapped
	* @param nbytes Number of bytes to be swapped
	*/
	void MemorySwap(void *vp1, void *vp2, unsigned int nbytes);

	/**
	* Swaps the string contents of two given pointers.
	* Requirements:
	*		-   vp1 and vp2 != NULL
	* Time complexity:
	*		-   O(1)
	* @param vp1 Pointer to the first string to be swapped
	* @param vp2 Pointer to the second string to be swapped
	* @param nbytes Number of bytes to be swapped (Remains unused to avoid warnings)
	*/
	void StringSwap(void *vp1, void *vp2, unsigned int nbytes);

	/**
	* Compare the contents of two given pointers.
	* Requirements:
	*		-   vp1 and vp2 != NULL
	* Time complexity:
	*		-   O(nbytes)
	* @param vp1 Pointer to the first memory location to be compared
	* @param vp2 Pointer to the second memory location to be compared
	* @param nbytes Number of bytes to be compared
	* @return returns an integer less than, equal to, or greater than zero if the first n bytes of vp1 is found, respectively, to be less than, to match, or be greater than the first n bytes of vp2
	*/
	int DataCompare(const void *vp1, const void *vp2, unsigned int nbytes);

int DoubleDataCompare(const void *vp1, const void *vp2, unsigned int nbytes);
int IntDataCompare(const void *vp1, const void *vp2, unsigned int nbytes);
	/**
	* Compare two given strings.
	* Requirements:
	*		-   vp1 and vp2 != NULL
	* Time complexity:
	* -   O(min(length of vp1, length of vp2))
	* @param vp1 Pointer to the first string to be compared
	* @param vp2 Pointer to the second string to be compared
	* @return returns an integer less than, equal to, or greater than zero if the vp1 is found, respectively, to be less than, to match, or be greater than the vp2
	*/
	int StringCompare(const void *vp1, const void *vp2, unsigned int nbytes);

	/**
	* Copies the contents of memory from one location to another.
	* Requirements:
	*		-   dest and src should not overlap
	*		-	dest and src != NULL
	* Time complexity:
	*		-   O(nbytes)
	* @param dest Pointer to the destination memory location
	* @param src Pointer to the source memory location
	* @param nbytes Number of bytes to be copied
	* @return A pointer to the destination memory location
	*/
	void *MemoryCopy(void *dest, const void *src, unsigned int nbytes);

	/**
	* Copies the contents of a string from one location to another.
	* Requirements:
	*		-   dest and src should not overlap
	*		-	dest and src != NULL
	* Time complexity:
	*		-   O(min(length of src, nbytes))
	* @param dest Pointer to the destination string location
	* @param src Pointer to the source string location
	* @param nbytes Number of bytes to be copied
	*/
	void StringCopy(void *dest, const void *src, unsigned int nbytes);

	/**
	* Move contents of memory from one location to another.
	* Requirements:
	*		-   dest and src may overlap
	*		-	dest and src != NULL
	* Time complexity:
	*		-   O(nbytes)
	* @param dest Pointer to the destination memory location
	* @param src Pointer to the source memory location
	* @param nbytes Number of bytes to be moved
	* @return A pointer to the destination memory location
	*/
	void *MemoryMove(void *dest, void *src, unsigned int nbytes);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_HELPER_HEADER_ */