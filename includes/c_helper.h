#ifndef _C_HELPER_HEADER_
#define _C_HELPER_HEADER_

#ifndef NULL
#define NULL 0
#endif

#define __bool_true_false_are_defined 1

#ifndef __cplusplus

#define bool  _Bool
#define false 0
#define true  1

#endif /* __cplusplus */

#ifdef DEBUG
#define ASSERT(x) ((void)(!(x) && assert_handler(#x, __FILE__, __LINE__) && (HALT(), 1)))
#else
#define ASSERT(x) ((void)sizeof(x))
#endif

#define M_MAX(X, Y) ((X) >= (Y) ? (X) : (Y))
#define M_MIN(X, Y) ((X) <= (Y) ? (X) : (Y))
#define M_ABS(X) ((X < 0) ? (-X) : (X))

typedef unsigned long long size_t;

void FreeString(void *elems);
void FreeData(void *elems);
void MemorySwap(void *vp1, void *vp2, size_t nbytes);
void StringSwap(void *vp1, void *vp2, size_t nbytes);
int DataCompare(const void *vp1, const void *vp2, size_t nbytes);
int StringCompare(const void *vp1, const void *vp2, size_t nbytes);
void *MemoryCopy(void *dest, const void *src, size_t nbytes);
void StringCopy(void *dest, const void *src, size_t nbytes);
void *MemoryMove(void *dest, void *src, size_t nbytes);

#endif