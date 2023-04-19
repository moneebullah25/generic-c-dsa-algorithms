#include "../includes/c_tree.h"
#include "../includes/c_helper.h"
#include <stdio.h>
#include <stdlib.h>

static void TreeNodeNew(TreeNode* tn, unsigned int elemsize, void* data)
{
	tn->elemsize = elemsize;
	tn->data = malloc(tn->elemsize);
	MemoryCopy(tn->data, data, tn->elemsize);
	tn->left = NULL;
	tn->right = NULL;
}

static void TreeNodeDelete(TreeNode* tn, void(*FreeFunc)(void* elems))
{
	if (tn == NULL) {
		return;
	}
	TreeNodeDelete(tn->left, FreeFunc);
	TreeNodeDelete(tn->right, FreeFunc);
	FreeFunc(tn->data);
	FreeFunc(tn);
}

static TreeNode* TreeNodeMin(TreeNode* tn)
{
	ASSERT(tn && tn->data);
	TreeNode* current = tn;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

void TreeNew_(TreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
    ASSERT(t && elemsize);
	t->root = NULL;
    t->logiclen = 0;
	t->elemsize = elemsize;
    t->DataCmp = DataCmp;
    t->FreeFunc = FreeFunc;
}

TreeNode* TreeInsert_(TreeBase* t, void* data)
{
	ASSERT(t && data);
	if (t->root == NULL) {
		t->root = malloc(sizeof(TreeNode));
		TreeNodeNew(t->root, t->elemsize, data);
		t->logiclen++;
		return t->root;
	}
	TreeNode* current = t->root;
	while (current != NULL) {
		int cmp = t->DataCmp(data, current->data, t->elemsize);
		if (cmp < 0) {
			if (current->left == NULL) {
				current->left = malloc(sizeof(TreeNode));
				TreeNodeNew(current->left, t->elemsize, data);
				t->logiclen++;
				return current;
			}
			current = current->left;
		}
		else if (cmp > 0) {
			if (current->right == NULL) {
				current->right = malloc(sizeof(TreeNode));
				TreeNodeNew(current->right, t->elemsize, data);
				t->logiclen++;
				return current;
			}
			current = current->right;
		}
		else 
		{
			return NULL;
		}
	}
	ASSERT(0);
	return NULL;
}

bool TreeContains_(TreeBase* t, void* data) {
	ASSERT(t && data);
	TreeNode* current = t->root;
	while (current != NULL) {
		int cmp = t->DataCmp(data, current->data, t->elemsize);
		if (cmp < 0) {
			current = current->left;
		}
		else if (cmp > 0) {
			current = current->right;
		}
		else {
			return true;
		}
	}
	return false;
}


void TreeRemove_(TreeBase *t, void *data)
{
	ASSERT(t && data);
	TreeNode *current = t->root;
	TreeNode *parent = NULL;
	while (current != NULL) {
		int cmp = t->DataCmp(data, current->data, t->elemsize);
		if (cmp == 0) {
			// Node with the same data found, remove it
			if (current->left == NULL && current->right == NULL) {
				// Node is a leaf, simply delete it
				if (parent == NULL) {
					t->root = NULL;
				}
				else if (parent->left == current) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
				t->logiclen--;
				TreeNodeDelete(current, t->FreeFunc);
				return;
			}
			else if (current->left == NULL) {
				// Node has only right child, replace it with the child
				if (parent == NULL) {
					t->root = current->right;
				}
				else if (parent->left == current) {
					parent->left = current->right;
				}
				else {
					parent->right = current->right;
				}
				t->logiclen--;
				t->FreeFunc(current->data);
				return;
			}
			else if (current->right == NULL) {
				// Node has only left child, replace it with the child
				if (parent == NULL) {
					t->root = current->left;
				}
				else if (parent->left == current) {
					parent->left = current->left;
				}
				else {
					parent->right = current->left;
				}
				t->logiclen--;
				t->FreeFunc(current->data);
				return;
			}
			else {
				// Node has both left and right children, find the successor
				TreeNode *successor = TreeNodeMin(current->right);
				void* temp = malloc(t->elemsize);
				MemoryCopy(temp, successor->data, t->elemsize);
				TreeRemove_(t, successor->data);
				MemoryCopy(current->data, temp, t->elemsize);
				return;
			}
		}
		else if (cmp < 0) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}
	}
	return;
}

void TreeClear_(TreeBase *t)
{
	ASSERT(t);
	TreeNodeDelete(t->root, t->FreeFunc);
	t->root = NULL;
	t->logiclen = 0;
}

void TreeDelete_(TreeBase *t)
{
	ASSERT(t);
	TreeClear_(t);
	free(t);
}

unsigned int TreeSize_(TreeBase *t)
{
    return t->logiclen;
}

bool TreeEmpty_(TreeBase *t)
{
    return (t->elemsize) ? true : false;
}

void *TreeMin_(TreeBase *t)
{
	ASSERT(t && t->root);
	TreeNode *curr = t->root;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	return curr->data;
}

void *TreeMax_(TreeBase *t)
{
	ASSERT(t && t->root);
	TreeNode *curr = t->root;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	return curr->data;
}

void TreeInOrder_(TreeBase *t, const char *data_format)
{
	ASSERT(t && t->root && data_format);
	TreeNode *curr = t->root;
	TreeNode *prev = NULL;
	while (curr != NULL) {
		if (prev == curr->left) {
			prev = curr;
			if (curr->left != NULL) {
				curr = curr->left;
				continue;
			}
		}
		fprintf(stdout, data_format, curr->data);
		prev = curr;
		if (curr->right != NULL) {
			curr = curr->right;
			continue;
		}
		while (prev != NULL && (prev->right == NULL || prev->right == curr)) {
			curr = prev;
			prev = curr->right;
		}
		curr = prev;
	}
}

void TreePreOrder_(TreeBase *t, const char *data_format)
{
	ASSERT(t && t->root && data_format);
	TreeNode *curr = t->root;
	TreeNode *prev = NULL;
	while (curr != NULL) {
		if (prev == curr->left) {
			// curr is the left child of prev
			prev = curr;
			fprintf(stdout, data_format, curr->data);
			if (curr->left != NULL) {
				curr = curr->left;
				continue;
			}
		}
		if (prev == curr->right || curr->left == NULL) {
			// curr is the right child of prev or has no left child
			prev = curr;
			if (curr->right != NULL) {
				curr = curr->right;
				continue;
			}
		}
		// curr has no right child or prev is the parent of curr
		while (prev != NULL && (prev->right == NULL || prev->right == curr)) {
			curr = prev;
			prev = curr->right;
		}
		if (prev != NULL) {
			curr = prev->right;
			prev = prev->right;
		}
	}
}

void TreePostOrder_(TreeBase *t, const char *data_format)
{
	ASSERT(t && t->root && data_format);
	TreeNode *curr = t->root;
	TreeNode *prev = NULL;
	while (curr != NULL) {
		if (prev == NULL || prev->left == curr || prev->right == curr) {
			// curr is a child of prev, traverse left subtree
			if (curr->left != NULL) {
				prev = curr;
				curr = curr->left;
			}
			else if (curr->right != NULL) {
				prev = curr;
				curr = curr->right;
			}
			else {
				// curr is a leaf node
				fprintf(stdout, data_format, curr->data);
				prev = curr;
				curr = NULL;
			}
		}
		else if (curr->left == prev) {
			// done with left subtree, traverse right subtree
			if (curr->right != NULL) {
				prev = curr;
				curr = curr->right;
			}
			else {
				// curr is a leaf node
				fprintf(stdout, data_format, curr->data);
				prev = curr;
				curr = NULL;
			}
		}
		else if (curr->right == prev) {
			// done with both subtrees, return to parent
			prev = curr;
			curr = NULL;
		}
	}
}
