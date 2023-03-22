#ifndef _C_TREE_HEADER_
#define _C_TREE_HEADER_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef NULL
#define NULL 0
#endif

#define bool _Bool
#define false 0
#define true 1

/**
 * A structure that represents the basic functionality of a binary tree node.
 * @param data A pointer to the data of the tree node
 * @param left A pointer to the left child node
 * @param right A pointer to the right child node
 * @param elemsize The size of an element
**/
typedef struct TreeNode TreeNode;
typedef struct TreeNode {
	void* data;
	TreeNode* left;
	TreeNode* right;
	unsigned int elemsize;
};

/**
 * A structure that represents the basic functionality of a binary tree.
 * @param root A pointer to the base of the tree node
 * @param elemsize The size of an each element
 * @param logiclen The number of elements stored in the node
 * @param DataCmp A pointer to a function that compares two keys of the tree node
 * @param FreeFunc A pointer to a function that frees the memory allocated for the data of the node
**/
typedef struct TreeBase TreeBase;
struct TreeBase {
	TreeNode* root;
	unsigned int logiclen;
	unsigned int elemsize;
	int(*DataCmp)(const void* key1, const void* key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
};

/**
 * A macro that creates a tree template for a given data type T.
 * The macro creates a struct with a TreeBase as a member and an additional member with the name data_ of the type T.
 * @param T The type of the data the tree will hold
**/
#define TreeT(T) \
    struct { TreeBase base; T data_; } 

/**
 * A macro that creates a new tree node.
 * @param t A pointer to the tree
 * @param DataCmp A pointer to a function that compares two keys of the tree node
 * @param FreeFunc A pointer to a function that frees the memory allocated for the data of the node
**/
#define TreeNew(t, DataCmp, FreeFunc) \
    TreeNew_(&(t)->base, sizeof((t)->data_), DataCmp, FreeFunc)

/**
 * A macro that inserts a new data element into the tree.
 * @param t A pointer to the tree
 * @param data A pointer to the data to be inserted
**/
#define TreeInsert(t, data) \
	((t)->data_ = data, \
    TreeInsert_(&(t)->base, &(t)->data_))

/**
 * A macro that checks if the tree contains a given data element.
 * @param t A pointer to the tree
 * @param data A pointer to the data to be searched
**/
#define TreeContains(t, data) \
	((t)->data_ = data, \
    TreeContains_(&(t)->base, &(t)->data_))

/**
 * A macro that removes a data element from the tree.
 * @param t A pointer to the tree
 * @param data A pointer to the data to be removed
**/
#define TreeRemove(t, data) \
	((t)->data_ = data, \
    TreeRemove_(&(t)->base, &(t)->data_))

/**
 * A macro that clears the contents of the tree.
 * @param t A pointer to the tree
**/
#define TreeClear(t) \
    TreeClear_(&(t)->base)

/**
 * A macro that deletes the tree and frees its allocated memory.
 * @param t A pointer to the tree
**/
#define TreeDelete(t) \
    TreeDelete_(&(t)->base)

/**
 * A macro that returns the number of data elements in the tree.
 * @param t A pointer to the tree
**/
#define TreeSize(t) \
    TreeSize_(&(t)->base)

/**
 * A macro that checks if the tree is empty.
 * @param t A pointer to the tree
**/
#define TreeEmpty(t) \
	TreeEmpty_(&(t)->base)

/**
 * A macro that returns a pointer to the minimum value in the tree.
 * @param t A pointer to the tree
**/
#define TreeMin(t) \
	TreeMin_(&(t)->base)

/**
 * A macro that returns a pointer to the maximum value in the tree.
 * @param t A pointer to the tree
**/
#define TreeMax(t) \
	TreeMax_(&(t)->base)
	
/**
 * A macro that traverses the tree in order and applies a formatting function to each data element.
 * @param t A pointer to the tree
 * @param data_format A pointer to a function that formats the data element to be printed
**/
#define TreeInOrder(t, data_format)\
	TreeInOrder_(&(t)->base, data_format)

/**
 * A macro that traverses the tree in pre-order and applies a formatting function to each data element.
 * @param t A pointer to the tree
 * @param data_format A pointer to a function that formats the data element to be printed
**/
#define TreePreOrder(t, data_format)\
	TreePreOrder_(&(t)->base, data_format)

/**
 * A macro that traverses the tree in post-order and applies a formatting function to each data element.
 * @param t A pointer to the tree
 * @param data_format A pointer to a function that formats the data element to be printed
**/
#define TreePostOrder(t, data_format) \
    TreePostOrder_(&(t)->base, data_format)

/**
 * Function that creates a new binary tree and initializes the base member of the TreeBase struct.
 * The function allocates memory for the root node of the binary tree and initializes its data and value members with NULL.
 * The function also assigns the passed element size, data comparison function and free function to the corresponding members of the base struct.
 * The function asserts that the element size passed is greater than 0.
 * @param t pointer to the binary tree
 * @param elemsize size of the element to be stored in the binary tree
 * @param DataCmp pointer to the data comparison function
 * @param FreeFunc pointer to the free function
 * Requirements:
 * - t pointer should not be nullptr
 * - elemsize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void TreeNew_(TreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

/**
 * Function that inserts a new node with the specified data into the binary tree.
 * If the binary tree already contains a node with the same data, the function does nothing
 * @param t pointer to the binary tree
 * @param data pointer to the data to be inserted
 * @return pointer to the tree node
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
**/
TreeNode* TreeInsert_(TreeBase* t, void* data);

/**
 * Function that checks if the binary tree contains a node with the specified data.
 * @param t pointer to the binary tree
 * @param data pointer to the data to be searched for
 * @return true if the binary tree contains a node with the specified data, false otherwise
 * Requirements:
 *  - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
**/
bool TreeContains_(TreeBase* t, void* data);

/**
 * Function that removes the node with the specified data from the binary tree.
 * If the binary tree does not contain a node with the specified data, the function does nothing.
 * @param t pointer to the binary tree
 * @param data pointer to the data to be removed
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
**/
void TreeRemove_(TreeBase* t, void* data);

/**
 * Function that clears the binary tree, removing all nodes from it and freeing the memory.
 * @param t pointer to the binary tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void TreeClear_(TreeBase* t);

/**
 * Function that deletes the binary tree, freeing the memory occupied by its nodes.
 * @param t pointer to the binary tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
void TreeDelete_(TreeBase* t);

/**
 * Function that returns the number of nodes in the binary tree.
 * @param t pointer to the binary tree
 * @return number of nodes in the binary tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
**/
unsigned int TreeSize_(TreeBase* t);

/**
 * Function that checks if the binary tree is empty.
 * @param t pointer to the binary tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
bool TreeEmpty_(TreeBase* t);

/**
 * Function that returns a pointer to the node with the minimum data value in the binary tree.
 * @param t pointer to the binary tree
 * @return a pointer to the node with the minimum data value in the binary tree or nullptr if the binary tree is empty
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(h), where h is the height of the binary tree
 * Space complexity: O(1)
**/
void* TreeMin_(TreeBase* t);

/**
 * Function that returns a pointer to the node with the maximum data value in the binary tree.
 * @param t pointer to the binary tree
 * @return a pointer to the node with the maximum data value in the binary tree or nullptr if the binary tree is empty
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(h), where h is the height of the binary tree
 * Space complexity: O(1)
**/
void* TreeMax_(TreeBase* t);

/**
 * Function that performs an in-order traversal of the binary tree and applies the passed format string to the data of each node.
 * @param t pointer to the binary tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the binary tree
**/
void TreeInOrder_(TreeBase* t, const char *data_format);

/**
 * Function that performs a pre-order traversal of the binary tree and applies the passed format string to the data of each node.
 * @param t pointer to the binary tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the binary tree
**/
void TreePreOrder_(TreeBase* t, const char *data_format);

/**
 * Function that performs a post-order traversal of the binary tree and applies the passed format string to the data of each node.
 * @param t pointer to the binary tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the binary tree
*/
void TreePostOrder_(TreeBase* t, const char *data_format);

/**
 * Define a binary tree of void pointers.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(void*) Tree;

/**
 * Define a binary tree of integers.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(int) TreeInt;

/**
 * Define a binary tree of floats.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(float) TreeFloat;

/**
 * Define a binary tree of doubles.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(double) TreeDouble;

/**
 * Define a binary tree of characters.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(char) TreeChar;

/**
 * Define a binary tree of strings.
 * Time complexity:
 * Depends on the operations performed on the binary tree.
**/
typedef TreeT(char*) TreeString;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_TREE_HEADER_ */