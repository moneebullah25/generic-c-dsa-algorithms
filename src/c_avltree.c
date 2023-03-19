#include "../includes/c_avltree.h"
#include "../includes/c_helper.h"
#include <stdio.h>
#include <stdlib.h>

void AvlTreeNew_(AvlTreeBase* t, unsigned int elemsize,
                 int (*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
                 void (*FreeFunc)(void *elems))
{
    ASSERT(t && elemsize);
    t->data = NULL;
    t->elemsize = elemsize;
    t->left = NULL;
    t->right = NULL;
    t->logiclen = 0;
    t->DataCmp = DataCmp;
    t->FreeFunc = FreeFunc;
}

int AvlTreeHeight_(AvlTreeBase* t)
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

int AvlTreeBalance_(AvlTreeBase* t)
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

AvlTreeBase* AvlTreeLeftRotate_(AvlTreeBase* t)
{
    AvlTreeBase* newroot = t->right;
    AvlTreeBase* temp = newroot->left;
    newroot->left = t;
    t->right = temp;
    t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
    newroot->height = 1 + M_MAX(AvlTreeHeight_(newroot->left), AvlTreeHeight_(newroot->right));
    return newroot;
}

AvlTreeBase* AvlTreeRightRotate_(AvlTreeBase* t)
{
    AvlTreeBase* newroot = t->left;
    AvlTreeBase* temp = newroot->right;
    newroot->right = t;
    t->left = temp;
    t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));
    newroot->height = 1 + M_MAX(AvlTreeHeight_(newroot->left), AvlTreeHeight_(newroot->right));
    return newroot;
}

AvlTreeBase* AvlTreeInsert_(AvlTreeBase* t, void *data)
{
    ASSERT(t && data);
    AvlTreeBase* temp = t;
    AvlTreeBase* new_node = (AvlTreeBase* )malloc(sizeof(AvlTreeBase));
	new_node->data = malloc(t->elemsize);
    MemoryCopy(new_node->data, data, t->elemsize);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    t->logiclen++;

    if (temp == NULL)
    {
        return new_node;
    }
    else if (t->DataCmp(temp->data, data, t->elemsize) < 0)
    {
        temp->left = AvlTreeInsert_(temp->left, data);
    }
    else if (t->DataCmp(temp->data, data, t->elemsize))
    {
        temp->right = AvlTreeInsert_(temp->right, data);
    }
    else
    {
        free(new_node);
        return temp;
    }

    temp->height = 1 + M_MAX(AvlTreeHeight_(temp->left), AvlTreeHeight_(temp->right));
    int balance = AvlTreeBalance_(temp);

    // Left Left Case
    if (balance > 1 && t->DataCmp(temp->left->data, data, t->elemsize) < 0)
    {
        return AvlTreeRightRotate_(temp);
    }

    // Right Right Case
    if (balance < -1 && t->DataCmp(temp->right->data, data, t->elemsize))
    {
        return AvlTreeLeftRotate_(temp);
    }

    // Left Right Case
    if (balance > 1 && t->DataCmp(temp->left->data, data, t->elemsize))
    {
        temp->left = AvlTreeLeftRotate_(temp->left);
        return AvlTreeRightRotate_(temp);
    }

    // Right Left Case
    if (balance < -1 && t->DataCmp(temp->right->data, data, t->elemsize) < 0)
    {
        temp->right = AvlTreeRightRotate_(temp->right);
        return AvlTreeLeftRotate_(temp);
    }

    return temp;
}

bool AvlTreeContains_(AvlTreeBase* t, void *data)
{
    ASSERT(t && data);
    AvlTreeBase* temp = t;
    while (temp != NULL)
    {
        if (t->DataCmp(temp->data, data, t->elemsize) == 0)
        {
            break;
        }
        else if (t->DataCmp(temp->data, data, t->elemsize) < 0)
        {
            temp = temp->left;
        }
        else if (t->DataCmp(temp->data, data, t->elemsize))
        {
            temp = temp->right;
        }
    }
    if (temp) return true;
	return false;
}

AvlTreeBase* AvlTreeRemove_(AvlTreeBase* t, void *data)
{
    ASSERT(t && data);

    if (t->DataCmp(t->data, data, t->elemsize) < 0)
    {
        t->left = AvlTreeRemove_(t->left, data);
    }
    else if (t->DataCmp(t->data, data, t->elemsize))
    {
        t->right = AvlTreeRemove_(t->right, data);
    }
    else
    {
        // Node to be deleted is found
        if (t->left == NULL || t->right == NULL)
        {
            // Node has at most one child
            AvlTreeBase* temp = t->left ? t->left : t->right;
            if (temp == NULL)
            {
                // Node has no child
                temp = t;
                t = NULL;
            }
            else
            {
                // Node has one child
                *t = *temp;
            }
            free(temp);
        }
        else
        {
            // Node has two children
            AvlTreeBase* temp = AvlTreeMin_(t->right);
            MemoryCopy(t->data, temp->data, t->elemsize);
            t->right = AvlTreeRemove_(t->right, temp->data);
        }
    }

    if (t == NULL)
    {
        return t;
    }

    t->height = 1 + M_MAX(AvlTreeHeight_(t->left), AvlTreeHeight_(t->right));

    int balance = AvlTreeBalance_(t);
    if (balance > 1 && AvlTreeBalance_(t->left) >= 0)
    {
        return AvlTreeRightRotate_(t);
    }
    if (balance > 1 && AvlTreeBalance_(t->left) < 0)
    {
        t->left = AvlTreeLeftRotate_(t->left);
        return AvlTreeRightRotate_(t);
    }
    if (balance < -1 && AvlTreeBalance_(t->right) <= 0)
    {
        return AvlTreeLeftRotate_(t);
    }
    if (balance < -1 && AvlTreeBalance_(t->right))
    {
        t->right = AvlTreeRightRotate_(t->right);
        return AvlTreeLeftRotate_(t);
    }

    return t;
}

void AvlTreeClear_(AvlTreeBase* t)
{
    if (t != NULL)
    {
        AvlTreeClear_(t->left);
        AvlTreeClear_(t->right);
        t->logiclen = 0;
        t->FreeFunc(t->data);
        t->left = NULL;
        t->right = NULL;
    }
}

void AvlTreeDelete_(AvlTreeBase* t)
{
    if (t != NULL)
    {
        AvlTreeDelete_(t->left);
        AvlTreeDelete_(t->right);
        if (t->data != NULL)
        {
            t->FreeFunc(t->data);
        }
        free(t);
        t = NULL;
    }
    t->logiclen = 0;
}

unsigned int AvlTreeSize_(AvlTreeBase* t)
{
    return t->elemsize;
}

bool AvlTreeEmpty_(AvlTreeBase* t)
{
    return (t->elemsize) ? true : false;
}

AvlTreeBase* AvlTreeMin_(AvlTreeBase* t)
{
    ASSERT(t);
    AvlTreeBase* temp = t;
    while (temp && temp->left->data != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

AvlTreeBase* AvlTreeMax_(AvlTreeBase* t)
{
    ASSERT(t);
    AvlTreeBase* temp = t;
    while (temp && temp->right->data != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

void AvlTreeInOrder_(AvlTreeBase* t, const char *data_format)
{
    if (t != NULL)
    {
        AvlTreeInOrder_(t->left, data_format);
        fprintf(stdout, data_format, t->data);
        AvlTreeInOrder_(t->right, data_format);
    }
}

void AvlTreePreOrder_(AvlTreeBase* t, const char *data_format)
{
    if (t != NULL)
    {
        fprintf(stdout, data_format, t->data);
        AvlTreeInOrder_(t->left, data_format);
        AvlTreeInOrder_(t->right, data_format);
    }
}

void AvlTreePostOrder_(AvlTreeBase* t, const char *data_format)
{
    if (t != NULL)
    {
        AvlTreeInOrder_(t->left, data_format);
        AvlTreeInOrder_(t->right, data_format);
        fprintf(stdout, data_format, t->data);
    }
}
