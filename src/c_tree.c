#include "../includes/c_tree.h"
#include "../includes/c_helper.h"
#include <stdio.h>
#include <stdlib.h>

void TreeNew_(TreeBase* t, unsigned int elemsize,
	int(*DataCmp)(const void *key1, const void *key2, unsigned int keysize),
	void(*FreeFunc)(void* elems))
{
    ASSERT(t && elemsize > 0);
    t->data = malloc(elemsize);
    ASSERT(t->data);
    t->data = NULL;
    t->elemsize = elemsize;
    t->left = NULL;
    t->right = NULL;
    t->logiclen = 0;
    t->DataCmp = DataCmp;
    t->FreeFunc = FreeFunc;
}

TreeBase* TreeInsert_(TreeBase* t, void* data)
{
    ASSERT(t && data);
    TreeBase* temp = t;
    while (temp != NULL)
    {
        if (t->DataCmp(temp->data, data, t->elemsize) < 0)
        {
            temp = temp->left;
        } else if (t->DataCmp(temp->data, data, t->elemsize) >= 0)
        {
            temp = temp->right;
        }
    }
    MemoryCopy(temp->data, data, t->elemsize);
    t->logiclen++;
    return temp;
}

bool TreeContains_(TreeBase* t, void* data)
{
    ASSERT(t && data);
    TreeBase* temp = t;
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
        else if (t->DataCmp(temp->data, data, t->elemsize) > 0)
        {
            temp = temp->right;
        }
    }
    if (temp != NULL) return true;
    else return false;
    return;
}

TreeBase* TreeRemove_(TreeBase* t, void* data)
{
    ASSERT(t && data);

    TreeBase* parent = NULL;
    TreeBase* curr = t;

    // Traverse the tree to find the node to remove
    while (curr != NULL && t->DataCmp(curr->data, data, t->elemsize) != 0) {
        parent = curr;
        if (t->DataCmp(curr->data, data, t->elemsize) < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr == NULL) {
        // Node not found
        return t;
    }

    if (curr->left == NULL && curr->right == NULL) {
        // Node has no children
        if (parent == NULL) {
            // Node is the root of the tree
            t = NULL;
        } else if (parent->left == curr) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (curr->left == NULL || curr->right == NULL) {
        // Node has one child
        TreeBase* child;
        if (curr->left == NULL) {
            child = curr->right;
        } else {
            child = curr->left;
        }
        if (parent == NULL) {
            // Node is the root of the tree
            t = child;
        } else if (parent->left == curr) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        // Node has two children
        TreeBase* successor = TreeMin(curr->right);
        curr->data = successor->data;
        curr->right = TreeRemove_(curr->right, successor->data);
    }

    // Deallocate memory for the removed node
    if (t->FreeFunc != NULL) {
        t->FreeFunc(curr->data);
    }
    free(curr);

    t->logiclen--;
    return t;
}

void TreeClear_(TreeBase* t)
{
    if (t != NULL) {
        TreeClear_(t->left);
        TreeClear_(t->right);
        t->logiclen = 0;
        t->FreeFunc(t->data)
        t->left = NULL;
        t->right = NULL;
    }
}


void TreeDelete_(TreeBase* t)
{
    if (t != NULL) {
        TreeDelete_(t->left);
        TreeDelete_(t->right);
        if (t->data != NULL) {
            t->FreeFunc(t->data);
        }
        free(t);
        t = NULL;
    }
    t->logiclen = 0;
}


unsigned int TreeSize_(TreeBase* t)
{
    return t->elemsize;
}

bool TreeEmpty_(TreeBase* t)
{
    return (t->elemsize)? true: false;
}

TreeBase* TreeMin(TreeBase* t)
{
    ASSERT(t);
    TreeBase* temp = t;
    while (temp && temp->left->data != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

TreeBase* TreeMax(TreeBase* t)
{
    ASSERT(t);
    TreeBase* temp = t;
    while (temp && temp->right->data != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

void TreeInOrder_(TreeBase* t, const char *data_format)
{
    if (t != NULL) {
        TreeInOrder_(t->left, data_format);
        fprintf(stdout, data_format, t->data);
        TreeInOrder_(t->right, data_format);
    }
}

void TreePreOrder_(TreeBase* t, const char *data_format)
{
    if (t != NULL) {
        fprintf(stdout, data_format, t->data);
        TreeInOrder_(t->left, data_format);
        TreeInOrder_(t->right, data_format);
    }
}

void TreePostOrder_(TreeBase* t, const char *data_format)
{
    if (t != NULL) {
        TreeInOrder_(t->left, data_format);
        TreeInOrder_(t->right, data_format);
        fprintf(stdout, data_format, t->data);
    }
}
