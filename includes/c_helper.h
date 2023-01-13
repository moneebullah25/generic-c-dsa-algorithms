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

void FreeString(void* elems);
void FreeData(void* elems);
void MemorySwap(void * vp1, void * vp2, unsigned int size);
int DataCompare(const void* vp1, const void* vp2, unsigned int n);
int StringCompare(const void* vp1, const void* vp2, unsigned int n);
void* MemoryCopy(void* dest, void* src, unsigned int n);
void* MemoryMove(void* dest, void* src, unsigned int n);

#endif 