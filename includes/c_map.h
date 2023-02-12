#ifndef _C_MAP_HEADER_
#define _C_MAP_HEADER_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "c_helper.h"

#define EMPTY 0xfe
#define TRAVERSE_COUNT 5
#define SHOPPTR "sh"
#define DHOPPTR "dh"


/**
 * MapNode struct represents a node in the map. It contains two void pointers, key and value, that can store any data type.
 * The key is used to identify the specific node in the map, while the value is the data that is associated with the key.
**/
typedef struct {
	void* key;
	void* value;
} MapNode;

/**
 * Structure for the base of a map.
 * The structure contains a pointer to an array of map entries, the logical and allocation lengths of the map, the key and value sizes, a pointer to the hash array, and pointers to the hash function, collision resolution function, data comparison function, and free functions for key and value.
 * @param elems pointer to an array of map entries
 * @param logiclen logical length of the map
 * @param alloclen allocation length of the map
 * @param keysize size of the key in the map
 * @param valuesize size of the value in the map
 * @param HashFunc pointer to the hash function
 * @param CollRes pointer to the collision resolution function
 * @param DataCmp pointer to the data comparison function
 * @param FreeFuncKey pointer to the free function for key
 * @param FreeFuncVal pointer to the free function for value
**/
typedef struct {
	MapNode* elems;
	unsigned int logiclen, alloclen, keysize, valuesize;
	char* hash;
	
	unsigned int(*HashFunc)(const void* key, unsigned int keysize);
	unsigned int(*CollRes)(unsigned int hash, unsigned int i);
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFuncKey)(void* elems);
	void(*FreeFuncVal)(void* elems);
} MapBase;

/**
 * Structure for an iterator for a map.
 * The structure contains a pointer to a map entry and an index for the key.
 * @param node pointer to a map entry
 * @param keyindex index of the key in the map
**/
typedef struct {
	MapNode node;
	unsigned int keyindex;
} MapIter;


/**
 * A macro that creates a map template for given key type T and value type U.
 * The macro creates a struct with a MapBase as a member and additional members with the name key_ of type T and value_ of type U.
 * @param T The type of the key the map will hold
 * @param U The type of the value the map will hold
**/
#define MapT(T, U) \
	struct { MapBase base; T key_; U value_; }

/**
 * A macro that creates a new map with a given hash function, collision resolution function, comparison function, and functions to free memory for the key and value.
 * The macro calls the MapNew_ function with the address of the base member of the map struct, the size of the key_ and value_ members, the hash function, collision resolution function, comparison function, and the memory freeing functions for the key and value as arguments.
 * @param m Pointer to the map struct
 * @param HashFunc A pointer to a function that hashes the key
 * @param CollRes A pointer to a function that handles collisions
 * @param DataCmp A pointer to a function that compares keys
 * @param FreeFuncKey A pointer to a function that frees memory for the key
 * @param FreeFuncVal A pointer to a function that frees memory for the value
**/
#define MapNew(m, HashFunc, CollRes, DataCmp, FreeFuncKey, FreeFuncVal) \
	MapNew_(&(m)->base, sizeof((m)->key_), sizeof((m)->value_), HashFunc, CollRes, DataCmp, FreeFuncKey, FreeFuncVal)

/**
 * A macro that sets a key-value pair in the map.
 * The macro assigns the passed key and value to the key_ and value_ members of the map struct, respectively, and calls the MapSet_ function with the address of the base member of the map struct and the addresses of the key_ and value_ members as arguments.
 * @param m Pointer to the map struct
 * @param key The key to be set in the map
 * @param value The value to be set in the map
**/
#define MapSet(m, key, value) \
	((m)->key_ = (key), \
	(m)->value_ = (value), \
	MapSet_(&(m)->base, &(m)->key_, &(m)->value_))

/**
 * A macro that returns the current size of the map.
 * The macro calls the MapSize_ function with the address of the base member of the map struct as an argument.
 * @param m Pointer to the map struct
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
#define MapSize(m) \
	MapSize_(&(m)->base)

/**
 * A macro that retrieves the value associated with a given key in the map.
 * The macro sets the key_ member of the map struct to the given key and calls the MapGet_ function with the address of the base member of the map struct and the address of the key_ member as arguments.
 * @param m Pointer to the map struct
 * @param key The key for which to retrieve the associated value
**/
#define MapGet(m, key) \
	((m)->key_ = (key), \
	MapGet_(&(m)->base, &(m)->key_))

/**
 * A macro that removes a key-value pair from the map by calling the MapRemove_ function with the address of the base member of the map struct and the address of the key_ member of the map struct as arguments.
 * @param m Pointer to the map struct
 * @param key The key to be removed from the map
 * @return The number of elements removed from the map
**/
#define MapRemove(m, key) \
	((m)->key_ = (key), \
	MapRemove_(&(m)->base, &(m)->key_))

/**
A macro that creates an iterator for a given map.
The macro calls the MapIterator_ function with the address of the base member of the map struct as an argument.
@param m Pointer to the map struct
**/
#define MapIterator(m) \
	MapIterator_(&(m)->base)

/**
 * A macro that retrieves the next element in the map.
 * The macro calls the MapNext_ function with the address of the base member of the map struct and the iterator as arguments.
 * @param m Pointer to the map struct
 * @param iter Iterator for the map
**/
#define MapNext(m, iter) \
	MapNext_(&(m)->base, iter)

/**
 * A macro that clears the map by calling the MapClear_ function with the address of the base member of the map struct as an argument.
 * @param m Pointer to the map struct
**/
#define MapClear(m) \
	MapClear_(&(m)->base)

/**
 * A macro that deletes the map by calling the MapDelete_ function with the address of the base member of the map struct as an argument.
 * @param m Pointer to the map struct
**/
#define MapDelete(m) \
	MapDelete_(&(m)->base)

	
// Helpers Predefined with library //
/* The HashFunctionStr function takes in a void pointer to a string key and a keysize, and returns an unsigned int hash value. It calculates the hash by iterating through each character of the string, updating the hash value with each character using the DJB2 algorithm. **/
unsigned int HashFunctionStr(const void* key, unsigned int keysize);

/* The HashFunctionInt function takes in a void pointer to an integer key and a keysize, and returns an unsigned int hash value. It calculates the hash by summing the bytes of the integer key and applying some bitwise operations to the sum. **/
unsigned int HashFunctionInt(const void* key, unsigned int keysize);

/* LinearProbing returns the next index by adding 1 to the original hash value,  **/ 
unsigned int LinearProbing(unsigned int hash, unsigned int i);

/* QuadraticProbing returns the next index by adding the square of the index to the original hash value **/
unsigned int QuadraticProbing(unsigned int hash, unsigned int i);

/* DoubleHashing returns the next index by adding the index multiplied by the original hash value to the original hash value. **/ 
unsigned int DoubleHashing(unsigned int hash, unsigned int i);


/**
 * Function that creates a new map and initializes the base member of the MapBase struct.
 * The function allocates memory for the array of map entries and initializes its elements with NULL.
 * The function also assigns the passed key size, value size, hash function, collision resolution function, data comparison function, and free functions for key and value to the corresponding members of the base struct.
 * The function asserts that the key size and value size passed are greater than 0.
 * @param m pointer to the map
 * @param keysize size of the key to be stored in the map
 * @param valuesize size of the value to be stored in the map
 * @param HashFunc pointer to the hash function
 * @param CollRes pointer to the collision resolution function
 * @param DataCmp pointer to the data comparison function
 * @param FreeFuncKey pointer to the free function for key
 * @param FreeFuncVal pointer to the free function for value
 * Requirements:
 *  	- m pointer should not be nullptr
 *  	- keysize and valuesize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void MapNew_(MapBase* m, unsigned int keysize, unsigned int valuesize,
	unsigned int(*HashFunc)(const void* key, unsigned int keysize),
	unsigned int(*CollRes)(unsigned int hash, unsigned int i), 
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFuncKey)(void* elems), void(*FreeFuncVal)(void* elems));
	
/**
 * Function that sets the value for a given key in the map.
 * The function uses the hash function and collision resolution function to find the index of the map entry corresponding to the given key.
 * If the key is not found in the map, a new entry is created and the key and value are inserted into it.
 * If the key is found in the map, the corresponding value is updated with the given value.
 * If the number of elements in the map is equal to the number of allocated entries, the map is resized to accomodate more elements.
 * The function asserts that the key and value pointers are not null.
 * @param m pointer to the map
 * @param key pointer to the key to be stored in the map
 * @param value pointer to the value to be stored in the map
 * Requirements:
 *  	- m pointer should not be nullptr
 *  	- key and value pointer should not be nullptr
 * Time complexity: O(1) on average, O(n) in worst case
 * Space complexity: O(1)
**/
void MapSet_(MapBase* m, void* key, void* value);

/**
 * Function that resizes the map by creating a new array of map entries and copying the existing elements to the new array.
 * The function doubles the size of the array and re-hashes the elements according to the new size.
 * The function asserts that the memory allocation for the new array is successful.
 * @param m pointer to the map
 * Requirements:
 *  	- m pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(n)
**/
void MapResize_(MapBase* m);

/**
 * Function that returns the number of elements stored in the map.
 * The function asserts that the map pointer passed is not null.
 * @param m pointer to the map
 * Requirements:
 * 		- m pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
unsigned int MapSize_(MapBase* m);

/**
 * Function that returns the value of the element with the specified key in the map.
 * The function asserts that the map pointer and key passed are not null.
 * @param m pointer to the map
 * @param key pointer to the key of the element to be retrieved
 * Requirements:
 *  	- m pointer and key pointer should not be nullptr
 * Time complexity: O(1) on average case, O(n) in worst case
 * Space complexity: O(1)
**/
void* MapGet_(MapBase* m, void* key);

/**
 * Function that removes the element with the specified key from the map.
 * The function asserts that the map pointer and key passed are not null.
 * The function also calls the free function for key and value if provided.
 * @param m pointer to the map
 * @param key pointer to the key of the element to be removed
 * Requirements:
 *  	- m pointer and key pointer should not be nullptr
 * Time complexity: O(1) on average case, O(n) in worst case
 * Space complexity: O(1)
**/
unsigned int MapRemove_(MapBase* m, void* key);

/**
 * Function that creates a new map iterator and initializes the keyindex member of the MapIter struct.
 * The function asserts that the map pointer passed is not null.
 * @param m pointer to the map
 * Requirements:
 *  	- m pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
MapIter* MapIterator_(MapBase* m);

/**
 * Function that returns the next non-empty key-value pair in the map.
 * The function asserts that the map pointer and map iterator passed are not null.
 * @param m pointer to the map
 * @param mapiter pointer to the map iterator
 * Requirements:
 *  	- m pointer and mapiter pointer should not be nullptr
 * Time complexity: O(1) on average case, O(n) in worst case
 * Space complexity: O(1)
**/
MapIter* MapNext_(MapBase* m, MapIter* mapiter);

/**
 * Function that clears all the elements from the map.
 * The function asserts that the map pointer passed is not null.
 * The function also calls the free function for key and value if provided.
 * @param m pointer to the map
 * Requirements:
 *  	- m pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void MapClear_(MapBase* m);

/**
 * Function that deletes the map and frees all the allocated memory.
 * The function asserts that the map pointer passed is not null.
 * The function also calls the free function for key and value if provided.
 * @param m pointer to the map
 * Requirements:
 *  	- m pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void MapDelete_(MapBase* m);


/**
 * Define a map of void pointer keys and void pointer values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(void*, void*) Map;

/**
 * Define a map of double keys and double values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(double, double) MapDouble;

/**
 * Define a map of float keys and float values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(float, float) MapFloat;

/**
 * Define a map of int keys and int values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(int, int) MapInt;

/**
 * Define a map of string keys and string values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char*, char*) MapString;

/**
 * Define a map of char keys and char values.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char, char) MapChar;


/**
 * Define a map template that uses a string as the key and double as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char*, double) MapStringDouble;

/**
 * Define a map template that uses a string as the key and float as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char*, float) MapStringFloat;

/**
 * Define a map template that uses a string as the key and int as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char*, int) MapStringInt;

/**
 * Define a map template that uses a string as the key and boolean as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char*, bool) MapStringBool;

/**
 * Define a map template that uses a character as the key and double as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char, double) MapCharDouble;

/**
 * Define a map template that uses a character as the key and float as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char, float) MapCharFloat;

/**
 * Define a map template that uses a character as the key and integer as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char, int) MapCharInt;

/**
 * Define a map template that uses a character as the key and boolean as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(char, bool) MapCharBool;

/**
 * Define a map template that uses a integer as the key and double as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(int, double) MapIntDouble;

/**
 * Define a map template that uses a integer as the key and float as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(int, float) MapIntFloat;

/**
 * Define a map template that uses a integer as the key and string as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(int, char*) MapIntString;

/**
 * Define a map template that uses a integer as the key and boolean as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(int, bool) MapIntBool;

/**
 * Define a map template that uses a float as the key and double as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(float, double) MapFloatDouble;

/**
 * Define a map template that uses a float as the key and string as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(float, char*) MapFloatString;

/**
 * Define a map template that uses a float as the key and integer as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(float, int) MapFloatInt;

/**
 * Define a map template that uses a float as the key and boolean as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(float, bool) MapFloatBool;


/**
 * Define a map template that uses a double as the key and string as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(double, char*) MapDoubleString;

/**
 * Define a map template that uses a double as the key and integer as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(double, int) MapDoubleInt;

/**
 * Define a map template that uses a double as the key and float as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(double, float) MapDoubleFloat;

/**
 * Define a map template that uses a double as the key and bool as the value.
 * Time complexity:
 *  	- Depends on the operations performed on the map.
**/
typedef MapT(double, bool) MapDoubleBool;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_MAP_HEADER_ */