#include "../includes/c_avltree.h"
#include "../includes/c_helper.h"
#include <stdio.h>
#include <stdlib.h>

static void AvlTreeNodeNew(AvlTreeNode *tn, unsigned int elemsize, void *data)
{
	tn->elemsize = elemsize;
	tn->data = malloc(tn->elemsize);
	MemoryCopy(tn->data, data, tn->elemsize);
	tn->left = NULL;
	tn->right = NULL;
	tn->parent = NULL;
	tn->height = 0;
}

static void AvlTreeNodeDelete(AvlTreeNode *tn, void(*FreeFunc)(void *elems))
{
	if (tn == NULL)
	{
		return;
	}
	FreeFunc(tn->data);
	FreeFunc(tn);
}

static AvlTreeNode* AvlTreeNodeMin(AvlTreeNode *tn)
{
	ASSERT(tn && tn->data);
	AvlTreeNode *current = tn;
	while (current->left != NULL)
	{
		current = current->left;
	}

	return current;
}

void AvlTreeNew_(AvlTreeBase *t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void *elems))
{
	t->root = NULL;
	t->logiclen = 0;
	t->elemsize = elemsize;
	t->DataCmp = DataCmp;
	t->FreeFunc = FreeFunc;
}

int AvlTreeHeight_(AvlTreeNode *t)
{
	if (t == NULL)
	{
		return -1;
	}
	else
	{
		return t->height;
	}
}

int AvlTreeBalance_(AvlTreeNode *t)
{
	if (t == NULL)
	{
		return 0;
	}
	else
	{
		return AvlTreeHeight_(t->left) - AvlTreeHeight_(t->right);
	}
}

AvlTreeNode* AvlTreeLeftRotate_(AvlTreeNode *t)
{
	AvlTreeNode *new_root = t->right;
	AvlTreeNode *old_right = new_root->left;

	new_root->left = t;
	t->right = old_right;

	t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
	new_root->height = 1 + M_MAX(AvlTreeHeight_(new_root->left), AvlTreeHeight_(new_root->right));

	new_root->parent = t->parent;
	t->parent = new_root;

	if (old_right != NULL) {
		old_right->parent = t;
	}

	return new_root;
}

AvlTreeNode* AvlTreeRightRotate_(AvlTreeNode *t)
{
	AvlTreeNode *new_root = t->left;
	AvlTreeNode *old_left = new_root->right;

	new_root->right = t;
	t->left = old_left;

	t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
	new_root->height = 1 + M_MAX(AvlTreeHeight_(new_root->left), AvlTreeHeight_(new_root->right));

	new_root->parent = t->parent;
	t->parent = new_root;

	if (old_left != NULL) {
		old_left->parent = t;
	}

	return new_root;
}


AvlTreeNode* AvlTreeInsert_(AvlTreeBase *t, void *data)
{
	AvlTreeNode *tn = malloc(sizeof(AvlTreeNode));
	if (tn == NULL)
	{
		return NULL;
	}

	AvlTreeNodeNew(tn, t->elemsize, data);

	if (t->root == NULL)
	{
		t->root = tn;
	}
	else
	{
		AvlTreeNode *current = t->root;
		AvlTreeNode *prev = current;
		AvlTreeNode *parent = NULL;
		while (1)
		{
			int cmp = t->DataCmp(data, current->data, t->elemsize);
			if (cmp == 0)
			{
				AvlTreeNodeDelete(tn, t->FreeFunc);
				return current;
			}
			else if (cmp < 0)
			{
				if (current->left == NULL)
				{
					current->left = tn;
					tn->parent = current;
					break;
				}
				current = current->left;
			}        
			else
			{
				if (current->right == NULL)
				{
					current->right = tn;
					tn->parent = current;
					break;
				}
				current = current->right;
			}
		}

		// Update height and balance factor of all nodes in the path to the root
		while (current != NULL)
		{
			current->height = 1 + M_MAX(AvlTreeHeight_(current->left), AvlTreeHeight_(current->right));
			int balance = AvlTreeBalance_(current);
			if (balance > 1 && t->DataCmp(data, current->left->data, t->elemsize) <= 0)
			{
				current = AvlTreeRightRotate_(current);
				prev = current;
				current = current->parent;
				current->left = prev;
				continue;
			}
			else if (balance < -1 && t->DataCmp(data, current->right->data, t->elemsize) >= 0)
			{
				current = AvlTreeLeftRotate_(current);
				prev = current;
				current = current->parent;
				current->right = prev;
				continue;
			}
			else if (balance > 1 && t->DataCmp(data, current->left->data, t->elemsize) > 0)
			{
				current->left = AvlTreeLeftRotate_(current->left);
				current = AvlTreeRightRotate_(current);
				prev = current;
				current = current->parent;
				current->left = prev;
				continue;
			}
			else if (balance < -1 && t->DataCmp(data, current->right->data, t->elemsize) < 0)
			{
				current->right = AvlTreeRightRotate_(current->right);
				current = AvlTreeLeftRotate_(current);
				prev = current;
				current = current->parent;
				current->right = prev;
				continue;
			}
			current = current->parent;
		}
	}

	t->logiclen++;
	return tn;
}

bool AvlTreeContains_(AvlTreeBase *t, void *data)
{
	AvlTreeNode *node = t->root;
	while (node != NULL)
	{
		int cmp_result = t->DataCmp(data, node->data, node->elemsize);
		if (cmp_result < 0)
		{
			node = node->left;
		}
		else if (cmp_result > 0)
		{
			node = node->right;
		}
		else
		{
			return true;
		}
	}

	return false;
}

static AvlTreeNode* AvlTreeRemoveNode(AvlTreeBase *t, AvlTreeNode *tn, void *data)
{
	if (tn == NULL) {
		return NULL;
	}
	int cmp = t->DataCmp(data, tn->data, t->elemsize);
	if (cmp < 0) {
		tn->left = AvlTreeRemoveNode(t, tn->left, data);
	}
	else if (cmp > 0) {
		tn->right = AvlTreeRemoveNode(t, tn->right, data);
	}
	else {
		if (tn->left == NULL && tn->right == NULL) {  // leaf node
			AvlTreeNodeDelete(tn, t->FreeFunc);
			tn = NULL;
		}
		else if (tn->left == NULL) {  // one child (right)
			AvlTreeNode *temp = tn;
			tn = tn->right;
			tn->parent = temp->parent;
			AvlTreeNodeDelete(temp, t->FreeFunc);
		}
		else if (tn->right == NULL) {  // one child (left)
			AvlTreeNode *temp = tn;
			tn = tn->left;
			tn->parent = temp->parent;
			AvlTreeNodeDelete(temp, t->FreeFunc);
		}
		else {  // two children
			AvlTreeNode *min = AvlTreeNodeMin(tn->right);
			MemoryCopy(tn->data, min->data, t->elemsize);
			tn->right = AvlTreeRemoveNode(t, tn->right, min->data);
		}
	}
	if (tn == NULL) {
		return NULL;
	}
	tn->height = 1 + M_MAX(AvlTreeHeight_(tn->left), AvlTreeHeight_(tn->right));
	int balance = AvlTreeBalance_(tn);
	if (balance > 1 && AvlTreeBalance_(tn->left) >= 0) {  // left left case
		return AvlTreeRightRotate_(tn);
	}
	if (balance > 1 && AvlTreeBalance_(tn->left) < 0) {  // left right case
		tn->left = AvlTreeLeftRotate_(tn->left);
		return AvlTreeRightRotate_(tn);
	}
	if (balance < -1 && AvlTreeBalance_(tn->right) <= 0) {  // right right case
		return AvlTreeLeftRotate_(tn);
	}
	if (balance < -1 && AvlTreeBalance_(tn->right) > 0) {  // right left case
		tn->right = AvlTreeRightRotate_(tn->right);
		return AvlTreeLeftRotate_(tn);
	}
	return tn;
}

void AvlTreeRemove_(AvlTreeBase *t, void *data)
{
	t->root = AvlTreeRemoveNode(t, t->root, data);
	if (t->root != NULL) {
		t->root->parent = NULL;
	}
	t->logiclen--;
}

void AvlTreeClear_(AvlTreeBase *t)
{
	AvlTreeNodeDelete(t->root, t->FreeFunc);
	t->root = NULL;
	t->logiclen = 0;
}

void AvlTreeDelete_(AvlTreeBase *t)
{
	AvlTreeClear_(t);
	free(t);
}

unsigned int AvlTreeSize_(AvlTreeBase *t)
{
	return t->logiclen;
}

bool AvlTreeEmpty_(AvlTreeBase *t)
{
	return t->root == NULL;
}

void *AvlTreeMin_(AvlTreeBase *t)
{
	AvlTreeNode *node = t->root;
	while (node != NULL && node->left != NULL)
	{
		node = node->left;
	}

	return node != NULL ? node->data : NULL;
}

void *AvlTreeMax_(AvlTreeBase *t)
{
	AvlTreeNode *node = t->root;
	while (node != NULL && node->right != NULL)
	{
		node = node->right;
	}

	return node != NULL ? node->data : NULL;
}

static void AvlTreeInOrderHelper(AvlTreeNode *tn, const char *data_format)
{
	if (tn == NULL)
	{
		return;
	}

	AvlTreeInOrderHelper(tn->left, data_format);
	fprintf(stdout, data_format, tn->data);
	AvlTreeInOrderHelper(tn->right, data_format);
}

void AvlTreeInOrder_(AvlTreeBase *t, const char *data_format)
{
	AvlTreeInOrderHelper(t->root, data_format);
}

static void AvlTreePreOrderHelper(AvlTreeNode *tn, const char *data_format)
{
	if (tn == NULL)
	{
		return;
	}

	fprintf(stdout, data_format, tn->data);
	AvlTreePreOrderHelper(tn->left, data_format);
	AvlTreePreOrderHelper(tn->right, data_format);
}

void AvlTreePreOrder_(AvlTreeBase *t, const char *data_format)
{
	AvlTreePreOrderHelper(t->root, data_format);
}

static void AvlTreePostOrderHelper(AvlTreeNode *tn, const char *data_format)
{
	if (tn == NULL)
	{
		return;
	}

	AvlTreePostOrderHelper(tn->left, data_format);
	AvlTreePostOrderHelper(tn->right, data_format);
	fprintf(stdout, data_format, tn->data);
}

void AvlTreePostOrder_(AvlTreeBase *t, const char *data_format)
{
	AvlTreePostOrderHelper(t->root, data_format);
}