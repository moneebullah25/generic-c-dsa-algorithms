#ifndef _C_HELPER_HEADER_
#define _C_HELPER_HEADER_

#include <stdlib.h>

#ifndef NULL 
#define NULL 0
#endif

#ifdef DEBUG
#define ASSERT(x) ((void)(!(x) && assert_handler(#x, __FILE__, __LINE__) && (HALT(), 1)))
#else
#define ASSERT(x) ((void)sizeof(x))
#endif

#define M_MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define M_MIN(X, Y) ((X) <= (Y) ? (X) : (Y))
#define M_ABS(X) ((X < 0) ? (-X) : (X))

typedef enum { false = 0, true = 1 } bool;

void string_free(void* elems);
void data_free(void* elems);
void memory_swap(void * vp1, void * vp2, unsigned int size);
int data_compare(void* vp1, void* vp2, unsigned int n);
int string_compare(void* vp1, void* vp2, unsigned int n);
void* memory_copy(void* dest, void* src, unsigned int n);
void* memory_move(void* dest, void* src, unsigned int n);

#endif 