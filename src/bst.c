/**
 * @file bst.c
 * @brief Implementation of Binary Search Tree in C.
 * @author i7modes
 * @license MIT
 */

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

BSTNode* BST_CreateNode(int value)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    if (node == NULL)
    {
        fprintf(stderr, "Error: Out of memory in BST_CreateNode.\n");
        return NULL;
    }

    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BSTNode* BST_Clear(BSTNode *root)
{
    if (root != NULL)
    {
        BST_Clear(root->left);
        BST_Clear(root->right);
        free(root);
    }
    return NULL;
}

void BST_Destroy(BSTNode **root_ptr)
{
    if (root_ptr == NULL || *root_ptr == NULL)
    {
        return;
    }

    *root_ptr = BST_Clear(*root_ptr);
}

/* -------------------------------------------------------------------------- */
/*                              Core Operations                               */
/* -------------------------------------------------------------------------- */

BSTNode* BST_Insert(BSTNode *root, int value)
{
    if (root == NULL)
    {
        return BST_CreateNode(value);
    }

    if (value < root->data)
    {
        root->left = BST_Insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = BST_Insert(root->right, value);
    }
    /* Duplicate values are ignored in standard BST */

    return root;
}

BSTNode* BST_FindMin(const BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    const BSTNode *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }

    return (BSTNode *)current;
}

BSTNode* BST_FindMax(const BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    const BSTNode *current = root;
    while (current->right != NULL)
    {
        current = current->right;
    }

    return (BSTNode *)current;
}

BSTNode* BST_Find(const BSTNode *root, int value)
{
    const BSTNode *current = root;

    while (current != NULL)
    {
        if (value == current->data)
        {
            return (BSTNode *)current;
        }
        else if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return NULL;
}

BSTNode* BST_Delete(BSTNode *root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (value < root->data)
    {
        root->left = BST_Delete(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = BST_Delete(root->right, value);
    }
    else
    {
        /* Node to be deleted found */

        /* Case 1: Node with two children */
        if (root->left != NULL && root->right != NULL)
        {
            BSTNode *minRight = BST_FindMin(root->right);
            root->data = minRight->data;
            root->right = BST_Delete(root->right, minRight->data);
        }
        else
        {
            /* Case 2: Node with zero or one child */
            BSTNode *temp = (root->left != NULL) ? root->left : root->right;
            free(root);
            return temp;
        }
    }

    return root;
}

bool BST_IsEmpty(const BSTNode *root)
{
    return (root == NULL);
}

size_t BST_Size(const BSTNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + BST_Size(root->left) + BST_Size(root->right);
}

size_t BST_Height(const BSTNode *root)
{
    if (root == NULL)
    {
        return 0;
    }

    size_t leftHeight = BST_Height(root->left);
    size_t rightHeight = BST_Height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/* -------------------------------------------------------------------------- */
/*                           Traversals & Serialization                       */
/* -------------------------------------------------------------------------- */

void BST_InOrder(const BSTNode *root, void (*visitor)(int))
{
    if (root == NULL || visitor == NULL)
    {
        return;
    }

    BST_InOrder(root->left, visitor);
    visitor(root->data);
    BST_InOrder(root->right, visitor);
}

void BST_PreOrder(const BSTNode *root, void (*visitor)(int))
{
    if (root == NULL || visitor == NULL)
    {
        return;
    }

    visitor(root->data);
    BST_PreOrder(root->left, visitor);
    BST_PreOrder(root->right, visitor);
}

void BST_PostOrder(const BSTNode *root, void (*visitor)(int))
{
    if (root == NULL || visitor == NULL)
    {
        return;
    }

    BST_PostOrder(root->left, visitor);
    BST_PostOrder(root->right, visitor);
    visitor(root->data);
}

static void in_order_collector(const BSTNode *root, int *buffer, size_t *count, size_t max_len)
{
    if (root == NULL || *count >= max_len)
    {
        return;
    }

    in_order_collector(root->left, buffer, count, max_len);
    if (*count < max_len)
    {
        buffer[(*count)++] = root->data;
    }
    in_order_collector(root->right, buffer, count, max_len);
}

size_t BST_ToArrayInOrder(const BSTNode *root, int *buffer, size_t max_len)
{
    if (root == NULL || buffer == NULL || max_len == 0)
    {
        return 0;
    }

    size_t count = 0;
    in_order_collector(root, buffer, &count, max_len);
    return count;
}

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Visualization                       */
/* -------------------------------------------------------------------------- */

static bool is_valid_bst_helper(const BSTNode *root, long min_val, long max_val)
{
    if (root == NULL)
    {
        return true;
    }

    if (root->data <= min_val || root->data >= max_val)
    {
        return false;
    }

    return is_valid_bst_helper(root->left, min_val, root->data) &&
           is_valid_bst_helper(root->right, root->data, max_val);
}

bool BST_IsValid(const BSTNode *root)
{
    return is_valid_bst_helper(root, LONG_MIN, LONG_MAX);
}

const BSTNode* BST_LowestCommonAncestor(const BSTNode *root, int val1, int val2)
{
    if (root == NULL)
    {
        return NULL;
    }

    /* Ensure both values actually exist in the tree */
    if (BST_Find(root, val1) == NULL || BST_Find(root, val2) == NULL)
    {
        return NULL;
    }

    const BSTNode *curr = root;
    while (curr != NULL)
    {
        if (val1 < curr->data && val2 < curr->data)
        {
            curr = curr->left;
        }
        else if (val1 > curr->data && val2 > curr->data)
        {
            curr = curr->right;
        }
        else
        {
            return curr;
        }
    }

    return NULL;
}

static void print_2d_util(const BSTNode *root, int space)
{
    if (root == NULL)
    {
        return;
    }

    space += 7;
    print_2d_util(root->right, space);

    printf("\n");
    for (int i = 7; i < space; i++)
    {
        printf(" ");
    }
    printf("[%d]\n", root->data);

    print_2d_util(root->left, space);
}

void BST_Print2D(const BSTNode *root)
{
    if (root == NULL)
    {
        printf("(empty tree)\n");
        return;
    }
    print_2d_util(root, 0);
}

static void print_node_val(int val)
{
    printf("%d ", val);
}

void BST_PrintInOrder(const BSTNode *root)
{
    if (root == NULL)
    {
        printf("(empty tree)\n");
        return;
    }

    printf("[ ");
    BST_InOrder(root, print_node_val);
    printf("]\n");
}
