/**
 * @file demo.c
 * @brief Demonstration program for Binary Search Tree library.
 * @author i7modes
 * @license MIT
 */

#include "bst.h"
#include <stdio.h>

static void print_val(int val)
{
    printf("%d ", val);
}

static void print_separator(const char *title)
{
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

int main(void)
{
    print_separator("1. Building Binary Search Tree");
    BSTNode *tree = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    size_t n = sizeof(values) / sizeof(values[0]);

    printf("Inserting: 50, 30, 70, 20, 40, 60, 80\n");
    for (size_t i = 0; i < n; i++)
    {
        tree = BST_Insert(tree, values[i]);
    }

    print_separator("2. Visual 2D ASCII Tree Layout");
    printf("Tree diagram (rotated horizontally, root at left):\n");
    BST_Print2D(tree);

    print_separator("3. Traversals");
    printf("In-Order (Sorted Ascending): ");
    BST_InOrder(tree, print_val);
    printf("\n");

    printf("Pre-Order  (Node, Left, Right): ");
    BST_PreOrder(tree, print_val);
    printf("\n");

    printf("Post-Order (Left, Right, Node): ");
    BST_PostOrder(tree, print_val);
    printf("\n");

    print_separator("4. Tree Metrics & Search");
    printf("Total Nodes (Size): %zu\n", BST_Size(tree));
    printf("Tree Height:        %zu\n", BST_Height(tree));
    printf("Minimum Value:      %d\n", BST_FindMin(tree)->data);
    printf("Maximum Value:      %d\n", BST_FindMax(tree)->data);
    printf("Is Valid BST?       %s\n", BST_IsValid(tree) ? "YES" : "NO");

    print_separator("5. Lowest Common Ancestor (LCA)");
    const BSTNode *lca1 = BST_LowestCommonAncestor(tree, 20, 40);
    if (lca1) printf("LCA of 20 and 40: %d\n", lca1->data);

    const BSTNode *lca2 = BST_LowestCommonAncestor(tree, 20, 80);
    if (lca2) printf("LCA of 20 and 80: %d\n", lca2->data);

    print_separator("6. Deletions (Leaf, Single-Child, Two-Children)");
    printf("Deleting leaf node (20)...\n");
    tree = BST_Delete(tree, 20);

    printf("Deleting two-children root node (50)...\n");
    tree = BST_Delete(tree, 50);

    printf("\nTree after deleting 20 and 50:\n");
    BST_Print2D(tree);
    printf("\nNew In-Order: ");
    BST_InOrder(tree, print_val);
    printf("\nNew Size: %zu\n", BST_Size(tree));

    print_separator("7. Legacy API Compatibility Check");
    TNode legacyTree = MakeEmpty(NULL);
    legacyTree = Insert(10, legacyTree);
    legacyTree = Insert(5, legacyTree);
    legacyTree = Insert(15, legacyTree);
    printf("Legacy FindMin: %d\n", FindMin(legacyTree)->Element);
    printf("Legacy FindMax: %d\n", FindMax(legacyTree)->Element);
    legacyTree = MakeEmpty(legacyTree);
    printf("Legacy tree emptied.\n");

    print_separator("8. Complete Teardown");
    BST_Destroy(&tree);
    printf("Tree root pointer: %p (0 memory leaks)\n", (void *)tree);

    printf("\nAll Binary Search Tree demonstrations completed successfully!\n");
    return 0;
}
