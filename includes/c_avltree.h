#ifndef _C_AvlTree_HEADER_
#define _C_AvlTree_HEADER_

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
 * A structure that represents the basic functionality of an AVL tree node.
 * @param data A pointer to the data of the AVL tree node
 * @param elemsize The size of an element
 * @param logiclen The number of elements stored in the node
 * @param height The height of the AVL tree node
 * @param left A pointer to the left child node
 * @param right A pointer to the right child node
 * @param DataCmp A pointer to a function that compares two keys of the AVL tree node
 * @param FreeFunc A pointer to a function that frees the memory allocated for the data of the AVL tree node
**/
typedef struct AvlTreeBase AvlTreeBase;
struct AvlTreeBase {
    void* data; unsigned int elemsize, logiclen, height;
    AvlTreeBase* left, *right;
    int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize);
	void(*FreeFunc)(void* elems);
};

/**
 * A macro that creates an AVL tree template for a given data type T.
 * The macro creates a struct with an AvlTreeBase as a member and an additional member with the name data_ of the type T.
 * @param T The type of the data the AVL tree will hold
**/
#define AvlTreeT(T) \
    struct { AvlTreeBase base; T data_; } 

/**
 * A macro that initializes a new AVL tree.
 * @param t A pointer to the AVL tree struct to initialize.
 * @param DataCmp A function pointer to a comparison function that takes two arguments of type T and returns an integer indicating their order.
 * @param FreeFunc A function pointer to a function that frees a single node of the AVL tree.
**/
#define AvlTreeNew(t, DataCmp, FreeFunc) \
    AvlTreeNew_(&(t)->base, sizeof((t)->data_), DataCmp, FreeFunc)

/**
 * A macro that returns the height of the AVL tree.
 * @param t A pointer to the AVL tree struct.
 * @return The height of the AVL tree.
**/
#define AvlTreeHeight(t) \
    AvlTreeHeight_(&(t)->base)

/**
 * A macro that returns the balance factor of the root of the AVL tree.
 * @param t A pointer to the AVL tree struct.
 * @return The balance factor of the root of the AVL tree.
**/
#define AvlTreeBalance(t) \
    AvlTreeBalance_(&(t)->base)

/**
 * A macro that performs a left rotation on the root of the AVL tree.
 * @param t A pointer to the AVL tree struct.
**/
#define AvlTreeLeftRotate(t) \
    AvlTreeLeftRotate_(&(t)->base)

/**
 * A macro that performs a right rotation on the root of the AVL tree.
 * @param t A pointer to the AVL tree struct.
**/
#define AvlTreeRightRotate(t) \
    AvlTreeRightRotate_(&(t)->base)

/**
 * A macro that creates a AVL tree template for a given data type T.
 * The macro creates a struct with an AvlTreeBase as a member and an additional member with the name data_ of the type T and value_ of the type T.
 * @param T The type of the data the AVL tree will hold.
**/
#define AvlTreeInsert(t, data) \
    AvlTreeInsert_(&(t)->base, &(t)->data_)

/**
 * Macro that inserts an element into an AVL tree.
 * @param t The AVL tree into which the element will be inserted.
 * @param data The element to be inserted.
**/
#define AvlTreeContains(t, data) \
    AvlTreeContains_(&(t)->base, &(t)->data_)

/**
 * Macro that removes an element from an AVL tree.
 * @param t The AVL tree from which the element will be removed.
 * @param data The element to be removed.
**/
#define AvlTreeRemove(t, data) \
    AvlTreeRemove_(&(t)->base, &(t)->data_)

/**
 * Macro that removes all elements from an AVL tree.
 * @param t The AVL tree to be cleared.
**/
#define AvlTreeClear(t) \
    AvlTreeClear_(&(t)->base)

/**
 * Macro that deletes an AVL tree and frees all associated memory.
 * @param t The AVL tree to be deleted.
**/
#define AvlTreeDelete(t) \
    AvlTreeDelete_(&(t)->base)

/**
 * Macro that returns the number of elements in an AVL tree.
 * @param t The AVL tree whose size will be returned.
 * @return The number of elements in the AVL tree.
**/
#define AvlTreeSize(t) \
    AvlTreeSize_(&(t)->base)

/**
 * Macro that checks if an AVL tree is empty.
 * @param t The AVL tree to be checked.
 * @return Returns true if the AVL tree is empty, false otherwise.
**/
#define AvlTreeEmpty(t) \
    AvlTreeEmpty_(&(t)->base)

/**
 * Macro that returns the minimum element in an AVL tree.
 * @param t The AVL tree whose minimum element will be returned.
 * @return The minimum element in the AVL tree.
**/
#define AvlTreeMin(t) \
	AvlTreeMin_(&(t)->base)	

/**
 * 
 * Macro that returns the maximum element in an AVL tree.
 * @param t The AVL tree whose maximum element will be returned.
 * @return The maximum element in the AVL tree.
**/
#define AvlTreeMax(t) \
	AvlTreeMax_(&(t)->base)

/**
 * Macro that traverses an AVL tree in-order and applies a given function to each element.
 * @param t The AVL tree to be traversed.
 * @param data_format A format string for printing the data of each element.
**/
#define AvlTreeInOrder(t, data_format) \
    AvlTreeInOrder_(&(t)->base, data_format)

/**
 * Macro that traverses an AVL tree pre-order and applies a given function to each element.
 * @param t The AVL tree to be traversed.
 * @param data_format A format string for printing the data of each element.
**/
#define AvlTreePreOrder(t, data_format) \
    AvlTreePreOrder_(&(t)->base, data_format)

/**
 * Macro that traverses an AVL tree post-order and applies a given function to each element.
 * @param t The AVL tree to be traversed.
 * @param data_format A format string for printing the data of each element.
**/
#define AvlTreePostOrder(t, data_format) \
    AvlTreePostOrder_(&(t)->base, data_format)

/**
 * Function that creates a new AVL tree and initializes the base member of the AvlTreeBase struct.
 * The function allocates memory for the root node of the AVL tree and initializes its data and value members with NULL.
 * The function also assigns the passed element size, data comparison function and free function to the corresponding members of the base struct.
 * The function asserts that the element size passed is greater than 0.
 * @param t pointer to the AVL tree
 * @param elemsize size of the element to be stored in the AVL tree
 * @param DataCmp pointer to the data comparison function
 * @param FreeFunc pointer to the free function
 * Requirements:
 * - t pointer should not be nullptr
 * - elemsize should be greater than zero
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
void AvlTreeNew_(AvlTreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems));

/**
 * Function that returns the height of the AVL tree.
 * The height of the AVL tree is the number of edges in the longest path from the root to a leaf node.
 * If the AVL tree is empty, the function returns -1.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
**/
int AvlTreeHeight_(AvlTreeBase* t);

/**
 * Function that returns the balance factor of the AVL tree.
 * The balance factor of the AVL tree is the difference between the heights of its left and right subtrees.
 * If the AVL tree is empty, the function returns 0.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
*/
int AvlTreeBalance_(AvlTreeBase* t);

/**
 * Function that performs a left rotation on the AVL tree.
 * The function assumes that the AVL tree is not empty and that its right subtree is not empty.
 * The function returns a pointer to the new root of the subtree after the rotation.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * - t->right pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
AvlTreeBase* AvlTreeLeftRotate_(AvlTreeBase* t);

/**
 * Function that performs a right rotation on the AVL tree.
 * The function assumes that the AVL tree is not empty and that its left subtree is not empty.
 * The function returns a pointer to the new root of the subtree after the rotation.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * - t->left pointer should not be nullptr
 * Time complexity: O(1)
 * Space complexity: O(1)
**/
AvlTreeBase* AvlTreeRightRotate_(AvlTreeBase* t);

/**
 * Function that inserts a new element into the AVL tree and balances the tree if necessary.
 * @param t pointer to the AVL tree
 * @param data pointer to the data to be inserted
 * @return pointer to the AVL tree with the new element inserted
 * Requirements:
 * - t pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(log n)
**/
AvlTreeBase* AvlTreeInsert_(AvlTreeBase* t, void* data);

/**
 * Function that checks if the AVL tree contains the specified data.
 * @param t pointer to the AVL tree
 * @param data pointer to the data to be checked
 * @return true if the data is found in the AVL tree, false otherwise
 * Requirements:
 * - t pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
**/
bool AvlTreeContains_(AvlTreeBase* t, void* data);

/**
 * Function that removes an element from the AVL tree and balances the tree if necessary.
 * @param t pointer to the AVL tree
 * @param data pointer to the data to be removed
 * @return pointer to the AVL tree with the specified element removed
 * Requirements:
 * - t pointer should not be nullptr
 * - data pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(log n)
**/
AvlTreeBase* AvlTreeRemove_(AvlTreeBase* t, void* data);

/**
 * Function that removes all elements from the AVL tree and frees the memory allocated to the elements and nodes.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(n)
**/
void AvlTreeClear_(AvlTreeBase* t);

/**
 * Function that deletes the AVL tree and deallocates all the memory associated with it.
 * The function uses a post-order traversal to delete all the nodes of the tree.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(n)
**/
void AvlTreeDelete_(AvlTreeBase* t);

/**
 * Function that returns the number of nodes in the AVL tree.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(1)
 * @return number of nodes in the tree
**/
unsigned int AvlTreeSize_(AvlTreeBase* t);

/**
 * Function that checks if the AVL tree is empty.
 * @param t pointer to the AVL tree
 * Time complexity: O(1)
 * Space complexity: O(1)
 * @return true if the tree is empty, false otherwise
**/
bool AvlTreeEmpty_(AvlTreeBase* t);

/**
 * Function that returns the minimum element in the AVL tree.
 * The function starts from the root and traverses to the leftmost node to find the minimum element.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
 * @return pointer to the minimum element in the tree
**/
AvlTreeBase* AvlTreeMin_(AvlTreeBase* t);

/**
 * Function that returns the maximum element in the AVL tree.
 * The function starts from the root and traverses to the rightmost node to find the maximum element.
 * @param t pointer to the AVL tree
 * Requirements:
 * - t pointer should not be nullptr
 * Time complexity: O(log n)
 * Space complexity: O(1)
 * @return pointer to the maximum element in the tree
**/
AvlTreeBase* AvlTreeMax_(AvlTreeBase* t);

/**
 * Function that traverses the AVL tree in-order and performs a specified action on each node.
 * The function recursively traverses the left subtree, then performs the specified action on the current node,
 * and finally recursively traverses the right subtree.
 * @param t pointer to the AVL tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the tree
**/
void AvlTreeInOrder_(AvlTreeBase* t, const char *data_format);

/**
 * Function that traverses the AVL tree pre-order and performs a specified action on each node.
 * The function recursively performs the specified action on the current node(Just Print), then traverses the left subtree, then
 * finally recursively traverses the right subtree.
 * @param t pointer to the AVL tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the tree
**/
void AvlTreePreOrder_(AvlTreeBase* t, const char *data_format);

/**
 * Function that traverses the AVL tree in-order and performs a specified action on each node.
 * The function recursively traverses the left subtree, then recursively traverses the right subtree,
 * and then finally performs the specified action on the current node(Just Print)
 * @param t pointer to the AVL tree
 * @param data_format A format string for printing the data of each element.
 * Requirements:
 * - t pointer should not be nullptr
 * - data_format pointer should not be nullptr
 * Time complexity: O(n)
 * Space complexity: O(h), where h is the height of the tree
**/
void AvlTreePostOrder_(AvlTreeBase* t, const char *data_format);

/**
 * Define a generic AVL tree that can store void pointers.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(void) AvlTree;

/**
 * Define an AVL tree that stores integers.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(int) AvlTreeInt;

/**
 * Define an AVL tree that stores single-precision floating-point numbers.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(float) AvlTreeFloat;

/**
 * Define an AVL tree that stores double-precision floating-point numbers.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(double) AvlTreeDouble;

/**
 * Define an AVL tree that stores characters.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(char) AvlTreeChar;

/**
 * Define an AVL tree that stores strings.
 * Time complexity:
 * Depends on the operations performed on the AVL tree.
**/
typedef AvlTreeT(char) AvlTreeString;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _C_AvlTree_HEADER_ */