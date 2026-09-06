/**
 * @file test_bst.c
 * @brief Automated unit test suite for Binary Search Tree library.
 * @author i7modes
 * @license MIT
 */

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int total_tests = 0;
static int passed_tests = 0;

#define TEST_ASSERT(expr, msg) do { \
    total_tests++; \
    if (expr) { \
        passed_tests++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while (0)

static void test_empty_tree_safety(void)
{
    printf("\n--- Test: Empty Tree Safety ---\n");
    BSTNode *tree = NULL;

    TEST_ASSERT(BST_IsEmpty(tree) == true, "NULL tree is empty");
    TEST_ASSERT(BST_Size(tree) == 0, "NULL tree size is 0");
    TEST_ASSERT(BST_Height(tree) == 0, "NULL tree height is 0");
    TEST_ASSERT(BST_Find(tree, 10) == NULL, "Find on empty tree returns NULL");
    TEST_ASSERT(BST_FindMin(tree) == NULL, "FindMin on empty tree returns NULL");
    TEST_ASSERT(BST_FindMax(tree) == NULL, "FindMax on empty tree returns NULL");
    TEST_ASSERT(BST_Delete(tree, 10) == NULL, "Delete on empty tree returns NULL");
    TEST_ASSERT(BST_IsValid(tree) == true, "Empty tree is valid BST");

    BST_Destroy(&tree);
    TEST_ASSERT(tree == NULL, "BST_Destroy on NULL tree is safe");
}

static void test_insertions_and_sorted_inorder(void)
{
    printf("\n--- Test: Insertions, Size, Height & In-Order Sorting ---\n");
    BSTNode *tree = NULL;

    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
    {
        tree = BST_Insert(tree, vals[i]);
    }

    TEST_ASSERT(BST_Size(tree) == 7, "Tree size is 7");
    TEST_ASSERT(BST_Height(tree) == 3, "Balanced tree height is 3");
    TEST_ASSERT(BST_IsEmpty(tree) == false, "Tree is not empty");
    TEST_ASSERT(BST_IsValid(tree) == true, "Tree satisfies BST invariant");

    // Duplicate insertion
    tree = BST_Insert(tree, 50);
    TEST_ASSERT(BST_Size(tree) == 7, "Duplicate insertion does not increase size");

    // In-Order array serialization
    int buffer[7];
    size_t copied = BST_ToArrayInOrder(tree, buffer, 7);
    TEST_ASSERT(copied == 7, "Copied 7 elements to array");
    TEST_ASSERT(buffer[0] == 20 && buffer[1] == 30 && buffer[2] == 40 &&
                buffer[3] == 50 && buffer[4] == 60 && buffer[5] == 70 && buffer[6] == 80,
                "In-order array is strictly sorted in ascending order (20..80)");

    BST_Destroy(&tree);
    TEST_ASSERT(tree == NULL, "BST_Destroy nullifies tree pointer");
}

static void test_search_min_max(void)
{
    printf("\n--- Test: Search, Min, Max ---\n");
    BSTNode *tree = NULL;
    int vals[] = {45, 12, 78, 3, 25, 60, 99};
    for (int i = 0; i < 7; i++) tree = BST_Insert(tree, vals[i]);

    TEST_ASSERT(BST_Find(tree, 25) != NULL && BST_Find(tree, 25)->data == 25, "Find 25");
    TEST_ASSERT(BST_Find(tree, 1000) == NULL, "Find non-existent 1000 returns NULL");

    TEST_ASSERT(BST_FindMin(tree)->data == 3, "FindMin is 3");
    TEST_ASSERT(BST_FindMax(tree)->data == 99, "FindMax is 99");

    BST_Destroy(&tree);
}

static void test_deletions_all_cases(void)
{
    printf("\n--- Test: Deletions (Leaf, 1 Child, 2 Children) ---\n");
    BSTNode *tree = NULL;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) tree = BST_Insert(tree, vals[i]);

    // Case 1: Delete leaf node (20)
    tree = BST_Delete(tree, 20);
    TEST_ASSERT(BST_Size(tree) == 6, "Size is 6 after deleting leaf 20");
    TEST_ASSERT(BST_Find(tree, 20) == NULL, "20 is no longer in tree");
    TEST_ASSERT(BST_IsValid(tree) == true, "Tree remains valid BST");

    // Case 2: Node 30 now has only one child (40). Delete 30.
    tree = BST_Delete(tree, 30);
    TEST_ASSERT(BST_Size(tree) == 5, "Size is 5 after deleting 1-child node 30");
    TEST_ASSERT(BST_Find(tree, 30) == NULL, "30 is no longer in tree");
    TEST_ASSERT(BST_Find(tree, 40) != NULL, "Child 40 is preserved");
    TEST_ASSERT(BST_IsValid(tree) == true, "Tree remains valid BST");

    // Case 3: Delete root node with 2 children (50). Replaced by in-order successor (60).
    tree = BST_Delete(tree, 50);
    TEST_ASSERT(BST_Size(tree) == 4, "Size is 4 after deleting 2-child root 50");
    TEST_ASSERT(tree->data == 60, "New root is in-order successor 60");
    TEST_ASSERT(BST_IsValid(tree) == true, "Tree remains valid BST");

    // Delete non-existent
    tree = BST_Delete(tree, 999);
    TEST_ASSERT(BST_Size(tree) == 4, "Size remains 4 after deleting non-existent");

    // Delete remaining nodes
    tree = BST_Delete(tree, 60);
    tree = BST_Delete(tree, 40);
    tree = BST_Delete(tree, 70);
    tree = BST_Delete(tree, 80);
    TEST_ASSERT(tree == NULL, "Tree is empty after deleting all elements");
    TEST_ASSERT(BST_Size(tree) == 0, "Size is 0");
}

static void test_lowest_common_ancestor(void)
{
    printf("\n--- Test: Lowest Common Ancestor (LCA) ---\n");
    BSTNode *tree = NULL;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) tree = BST_Insert(tree, vals[i]);

    // LCA of 20 and 40 is 30
    const BSTNode *lca1 = BST_LowestCommonAncestor(tree, 20, 40);
    TEST_ASSERT(lca1 != NULL && lca1->data == 30, "LCA of 20 and 40 is 30");

    // LCA of 20 and 80 is 50 (root)
    const BSTNode *lca2 = BST_LowestCommonAncestor(tree, 20, 80);
    TEST_ASSERT(lca2 != NULL && lca2->data == 50, "LCA of 20 and 80 is 50");

    // LCA when one value is ancestor of another: LCA of 30 and 40 is 30
    const BSTNode *lca3 = BST_LowestCommonAncestor(tree, 30, 40);
    TEST_ASSERT(lca3 != NULL && lca3->data == 30, "LCA of 30 and 40 is 30");

    // Non-existent value returns NULL
    TEST_ASSERT(BST_LowestCommonAncestor(tree, 20, 999) == NULL, "LCA with non-existent returns NULL");

    BST_Destroy(&tree);
}

int main(void)
{
    printf("========================================\n");
    printf("  Binary Search Tree Automated Tests\n");
    printf("========================================\n");

    test_empty_tree_safety();
    test_insertions_and_sorted_inorder();
    test_search_min_max();
    test_deletions_all_cases();
    test_lowest_common_ancestor();

    printf("\n========================================\n");
    printf("  Results: %d/%d assertions passed\n", passed_tests, total_tests);
    printf("========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
