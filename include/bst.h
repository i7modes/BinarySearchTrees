/**
 * @file bst.h
 * @brief Binary Search Tree (BST) Implementation in C.
 * @author i7modes
 * @license MIT
 */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Node in a Binary Search Tree.
 */
typedef struct BSTNode {
    int data;                   /**< Data payload */
    struct BSTNode *left;       /**< Pointer to left child (keys < data) */
    struct BSTNode *right;      /**< Pointer to right child (keys > data) */
} BSTNode;

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocates and initializes a new BST node.
 * @param value The value to store.
 * @return Pointer to new node, or NULL on allocation failure.
 */
BSTNode* BST_CreateNode(int value);

/**
 * @brief Recursively frees all nodes in the tree, returning NULL.
 * @param root Pointer to tree root.
 * @return NULL.
 */
BSTNode* BST_Clear(BSTNode *root);

/**
 * @brief Completely frees all nodes in the tree, setting *root_ptr to NULL.
 * @param root_ptr Pointer to the root pointer variable.
 */
void BST_Destroy(BSTNode **root_ptr);

/* -------------------------------------------------------------------------- */
/*                              Core Operations                               */
/* -------------------------------------------------------------------------- */

/**
 * @brief Inserts a value into the BST maintaining the BST property.
 * Duplicates are ignored.
 * @param root Pointer to the tree root.
 * @param value The value to insert.
 * @return Pointer to the (potentially updated) root node.
 */
BSTNode* BST_Insert(BSTNode *root, int value);

/**
 * @brief Deletes a value from the BST using in-order successor replacement for two-child nodes.
 * @param root Pointer to the tree root.
 * @param value The value to delete.
 * @return Pointer to the (potentially updated) root node.
 */
BSTNode* BST_Delete(BSTNode *root, int value);

/**
 * @brief Searches for a node containing the specified value in O(log n) average time.
 * @return Pointer to matching node, or NULL if not found.
 */
BSTNode* BST_Find(const BSTNode *root, int value);

/**
 * @brief Finds the node with the minimum value in the tree.
 * @return Pointer to minimum node, or NULL if tree is empty.
 */
BSTNode* BST_FindMin(const BSTNode *root);

/**
 * @brief Finds the node with the maximum value in the tree.
 * @return Pointer to maximum node, or NULL if tree is empty.
 */
BSTNode* BST_FindMax(const BSTNode *root);

/**
 * @brief Checks if the tree is empty.
 */
bool BST_IsEmpty(const BSTNode *root);

/**
 * @brief Returns the total number of nodes in the tree.
 */
size_t BST_Size(const BSTNode *root);

/**
 * @brief Returns the height of the tree (empty = 0, single node = 1).
 */
size_t BST_Height(const BSTNode *root);

/* -------------------------------------------------------------------------- */
/*                           Traversals & Serialization                       */
/* -------------------------------------------------------------------------- */

/**
 * @brief In-Order traversal (Left -> Node -> Right). Produces values in ascending sorted order.
 */
void BST_InOrder(const BSTNode *root, void (*visitor)(int));

/**
 * @brief Pre-Order traversal (Node -> Left -> Right).
 */
void BST_PreOrder(const BSTNode *root, void (*visitor)(int));

/**
 * @brief Post-Order traversal (Left -> Right -> Node).
 */
void BST_PostOrder(const BSTNode *root, void (*visitor)(int));

/**
 * @brief Copies tree elements into an output array in sorted ascending order.
 * @return Number of elements copied.
 */
size_t BST_ToArrayInOrder(const BSTNode *root, int *buffer, size_t max_len);

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Visualization                       */
/* -------------------------------------------------------------------------- */

/**
 * @brief Validates whether the binary tree strictly satisfies all BST properties.
 * @return true if valid BST, false otherwise.
 */
bool BST_IsValid(const BSTNode *root);

/**
 * @brief Finds the Lowest Common Ancestor (LCA) of two values in the BST.
 * @return Pointer to the LCA node, or NULL if either value is not present.
 */
const BSTNode* BST_LowestCommonAncestor(const BSTNode *root, int val1, int val2);

/**
 * @brief Prints an ASCII 2D graphical representation of the tree structure.
 */
void BST_Print2D(const BSTNode *root);

/**
 * @brief Prints in-order elements formatted horizontally: [1, 2, 3, 4]
 */
void BST_PrintInOrder(const BSTNode *root);

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */

typedef BSTNode* TNode;

#define Node BSTNode
#define Element data
#define Left left
#define Right right

static inline TNode MakeEmpty(TNode T) {
    return BST_Clear(T);
}

static inline TNode Find(int X, TNode T) {
    return BST_Find(T, X);
}

static inline TNode FindMin(TNode T) {
    return (TNode)BST_FindMin(T);
}

static inline TNode FindMax(TNode T) {
    return (TNode)BST_FindMax(T);
}

static inline TNode Insert(int X, TNode T) {
    return BST_Insert(T, X);
}

static inline TNode Delete(int X, TNode T) {
    return BST_Delete(T, X);
}

#ifdef __cplusplus
}
#endif

#endif /* BST_H */
