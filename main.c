#include <stdio.h>
#include <stdlib.h>

typedef struct Node *TNode;

struct Node
{

    int Element;
    struct Node *Left;
    struct Node *Right;
};

TNode MakeEmpty(TNode);
TNode Find(int, TNode);
TNode FindMin(TNode);
TNode FindMax(TNode);
TNode Insert(int, TNode);
TNode Delete(int, TNode);

int main()
{
    TNode myTree = MakeEmpty(NULL);
    myTree = Insert(2, myTree);
    myTree = Insert(1, myTree);
    myTree = Insert(3, myTree);

    if (FindMin(myTree) == NULL)
    {
        printf("Empty Tree!\n");
    }
    else
    {
        printf("Min Number: %d\n", FindMin(myTree)->Element);
    }

    if (FindMax(myTree) == NULL)
    {
        printf("Empty Tree!\n");
    }
    else
    {
        printf("Max Number Before Deletion: %d\n", FindMax(myTree)->Element);
    }

    myTree = Delete(3, myTree);

    if (FindMax(myTree) == NULL)
    {
        printf("Empty Tree!\n");
    }
    else
    {
        printf("Max Number After Deletion: %d\n", FindMax(myTree)->Element);
    }

    if (Find(2, myTree) == NULL)
    {
        printf("Empty Tree!\n");
    }
    else
    {
        printf("Left element of element 2: %d\n", Find(2, myTree)->Left->Element);
    }

    printf("\nDone!\n");
    return 0;
}

TNode MakeEmpty(TNode T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }

    return NULL;
}

TNode Find(int X, TNode T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else if (X < T->Element)
    {
        return Find(X, T->Left);
    }
    else if (X > T->Element)
    {
        return Find(X, T->Right);
    }
    else
    {
        return T;
    }
}

TNode FindMin(TNode T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else if (T->Left == NULL)
    {
        return T;
    }
    else
    {
        return FindMin(T->Left);
    }
}

/*
TNode FindMin(TNode T){
    if(T != NULL) {
        while(T->Left != NULL)
    }

    T = T->Left;
    return T;
}
*/

TNode FindMax(TNode T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else if (T->Right == NULL)
    {
        return T;
    }
    else
    {
        return FindMax(T->Right);
    }
}

/*
TNode FindMax(TNode T){
    if(T != NULL) {
        while( T->Right != NULL)
    }

    T = T->Right;
    return T;
}
*/

TNode Insert(int X, TNode T)
{
    if (T == NULL)
    {

        T = (struct Node *)malloc(sizeof(struct Node));

        if (T == NULL)
        {
            printf("Out of space");
            exit(1);
        }
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
    }

    return T;
}

TNode Delete(int X, TNode T)
{
    TNode TmpCell;

    if (T == NULL)
    {
        printf("Element not found");
    }
    else if (X < T->Element)
    {
        T->Left = Delete(X, T->Left);
    }
    else if (X > T->Element)
    {
        T->Right = Delete(X, T->Right);
    }
    else
    {
        if (T->Left && T->Right)
        {
            TmpCell = FindMin(T->Right);
            T->Element = TmpCell->Element;
            T->Right = Delete(T->Element, T->Right);
        }
        else
        {
            TmpCell = T;

            if (T->Left == NULL)
            {
                T = T->Right;
            }
            else if (T->Right == NULL)
            {
                T = T->Left;
            }
            free(TmpCell);
        }
    }
    return T;
}