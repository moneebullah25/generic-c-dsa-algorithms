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
	tn->height = 0;
}

static void AvlTreeNodeDelete(AvlTreeNode *tn, void(*FreeFunc)(void *elems))
{
	if (tn == NULL)
	{
		return;
	}

	AvlTreeNodeDelete(tn->left, FreeFunc);
	AvlTreeNodeDelete(tn->right, FreeFunc);
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
	AvlTreeNode *y = t->right;
	AvlTreeNode *x = y->left;
	y->left = t;
	t->right = x;
	t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
	y->height = 1 + M_MAX(AvlTreeHeight_(y->left), AvlTreeHeight_(y->right));
	y->parent = t->parent;
	t->parent = y;
	if (x != NULL) {
		x->parent = t;
	}
	return y;
}

AvlTreeNode* AvlTreeRightRotate_(AvlTreeNode *t)
{
	AvlTreeNode *y = t->left;
	AvlTreeNode *x = y->right;
	y->right = t;
	t->left = x;
	t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
	y->height = 1 + M_MAX(AvlTreeHeight_(y->left), AvlTreeHeight_(y->right));
	y->parent = t->parent;
	t->parent = y;
	if (x != NULL) {
		x->parent = t;
	}
	return y;
}

AvlTreeNode* AvlTreeInsert_(AvlTreeBase *t, void *data)
{
	AvlTreeNode *tn = malloc(sizeof(AvlTreeNode));
	if (tn == NULL)
	{
		return NULL;
	}

	AvlTreeNodeNew(tn, t->elemsize, data);
	tn->parent = NULL;
	tn->left = NULL;
	tn->right = NULL;

	if (t->root == NULL)
	{
		t->root = tn;
	}
	else
	{
		AvlTreeNode *current = t->root;
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
			if (balance > 1 && t->DataCmp(data, current->left->data, t->elemsize) < 0)
			{
				current = AvlTreeRightRotate_(current);
			}
			else if (balance < -1 && t->DataCmp(data, current->right->data, t->elemsize) > 0)
			{
				current = AvlTreeLeftRotate_(current);
			}
			else if (balance > 1 && t->DataCmp(data, current->left->data, t->elemsize) > 0)
			{
				current->left = AvlTreeLeftRotate_(current->left);
				current = AvlTreeRightRotate_(current);
			}
			else if (balance < -1 && t->DataCmp(data, current->right->data, t->elemsize) < 0)
			{
				current->right = AvlTreeRightRotate_(current->right);
				current = AvlTreeLeftRotate_(current);
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

void AvlTreeRemove_(AvlTreeBase *t, void *data)
{
	AvlTreeNode *node = t->root;
	AvlTreeNode *parent = NULL;
	while (node != NULL)
	{
		int cmp_result = t->DataCmp(data, node->data, node->elemsize);
		if (cmp_result < 0)
		{
			parent = node;
			node = node->left;
		}
		else if (cmp_result > 0)
		{
			parent = node;
			node = node->right;
		}
		else
		{
			AvlTreeNode * tmp_node;
			if (node->left == NULL)
			{
				tmp_node = node->right;
			}
			else if (node->right == NULL)
			{
				tmp_node = node->left;
			}
			else
			{
				AvlTreeNode *successor = AvlTreeNodeMin(node->right);
				if (successor->right != NULL)
				{
					AvlTreeNode *successor_parent = node;
					while (successor->left != NULL)
					{
						successor_parent = successor;
						successor = successor->left;
					}

					successor_parent->left = successor->right;
					successor->right = node->right;
				}

				successor->left = node->left;
				tmp_node = successor;
			}

			if (parent == NULL)
			{
				t->root = tmp_node;
			}
			else if (parent->left == node)
			{
				parent->left = tmp_node;
			}
			else
			{
				parent->right = tmp_node;
			}

			AvlTreeNodeDelete(node, t->FreeFunc);
			t->logiclen--;
			break;
		}
	}
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