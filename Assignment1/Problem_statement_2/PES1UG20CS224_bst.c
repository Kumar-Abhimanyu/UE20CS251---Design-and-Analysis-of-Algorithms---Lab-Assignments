// Name: Kumar Abhimanyu
// SRN: PES1UG20CS224
#include "bst.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
*/

// Initializes the root of the bst
void init_bst(bst_t *bst)
{
    bst->root = NULL;
}

//Helper function to create node
static node_t* getnode(int new_key)
{
  node_t *newNode = calloc(1, sizeof(node_t));
  newNode->key = new_key;
  newNode->right = NULL;
  newNode->left = NULL;
  return newNode;
}

node_t* recursiveInsert(node_t* node, int key, int* count_ptr)
{
    if (node == NULL)
    {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->key = key;
        return temp;
    }
    else
    {
        if ((node->key) > key)
        {
            *count_ptr++;
            node->left = recursiveInsert(node->left, key, count_ptr);
        }
        else
        {
            *count_ptr++;
            node->right = recursiveInsert(node->right, key, count_ptr);           
        }
    }
    return node;
}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr)
{
    tree->root = recursiveInsert(tree->root,key,count_ptr);
}

node_t* deleteR(node_t* r, int key, int* count_ptr)
{
    node_t* temp;
    node_t* p;

    if (r == NULL) return r;

    if (key < r->key)
    {
        *count_ptr++;
        r->left = deleteR(r->left, key, count_ptr);
    }

    else if (key > r->key)
    {
        *count_ptr++;
        r->right = deleteR(r->right, key, count_ptr);
    }

    else
    {
        if (r->left == NULL)
        {
            *count_ptr++;
            temp = r->right;
            free(r);
            return temp;
        }

        else if (r->right == NULL)
        {
            *count_ptr++;
            temp = r->left;
            free(r);
            return temp;
        }

        else
        {
            p = r->right;
            while (p->left != NULL) p = p->left;
            r->key = p->key;
            r->right = deleteR(r->right, p->key, count_ptr);
        }
    }
    return r;
}

// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root = deleteR(tree->root, key, count_ptr);
}

int searchR(node_t* node, int key, int* count_ptr)
{
    if (node == NULL) return -1;

    else
    {
        if (node->key == key)
        {
            *count_ptr++;
            return key;
        }

        else if (node->key < key)
        {
            *count_ptr++;
            return searchR(node->right, key, count_ptr);
        }

        else
        {
            *count_ptr++;
            return searchR(node->left, key, count_ptr);
        }
    }
}

// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    return searchR(tree->root, key, count_ptr);
}

// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    node_t* p = tree->root;
    if(p->right == NULL && count_ptr++)
		return p->key;
	else
	{
		find_max(p->right,*count_ptr);
	}
}

void freeR(node_t* node)
{
    if (node == NULL) return;

    freeR(node->left);
    freeR(node->right);

    free(node);
}

// Deletes all the elements of the bst
void free_bst(bst_t *bst) 
{
    freeR(bst->root);
    free(bst);
}

// Deletes all the elements of the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    freeR(bst->root);
    bst->root = NULL;
}