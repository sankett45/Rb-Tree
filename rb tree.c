#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
struct Node
{
    int key;
    struct Node *left, *right, *parent;
    int color;
};
struct RBTree
{
    struct Node *root;
    struct Node *nil;
};
struct Node *createNode(struct RBTree *T, int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = T->nil;
    node->color = RED;
    return node;
}
void leftRotate(struct RBTree *T, struct Node *x)
{
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
void rightRotate(struct RBTree *T, struct Node *y)
{
    struct Node *x = y->left;
    y->left = x->right;
    if (x->right != T->nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}
void RBInsertFixup(struct RBTree *T, struct Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct Node *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(T, z->parent->parent);
            }
        }
        else
        {
            struct Node *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}
void RBInsert(struct RBTree *T, struct Node *z)
{
    struct Node *y = T->nil;
    struct Node *x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    RBInsertFixup(T, z);
}
struct RBTree *initializeRBTree()
{
    struct RBTree *T = (struct RBTree *)malloc(sizeof(struct RBTree));
    T->nil = (struct Node *)malloc(sizeof(struct Node));
    T->nil->color = BLACK;
    T->root = T->nil;
    return T;
}
void inorder(struct RBTree *T, struct Node *n)
{
    if (n != T->nil)
    {
        printf("%d ", n->key);
        inorder(T, n->left);
        inorder(T, n->right);
    }
}
int main()
{
    struct RBTree *T = initializeRBTree();
    RBInsert(T, createNode(T, 40));
    RBInsert(T, createNode(T, 20));
    RBInsert(T, createNode(T, 50));
    RBInsert(T, createNode(T, 10));
    RBInsert(T, createNode(T, 30));
    RBInsert(T, createNode(T, 60));
    RBInsert(T, createNode(T, 25));
    RBInsert(T, createNode(T, 35));
    printf("In-order traversal of the Red-Black Tree:\n");
    inorder(T, T->root);
    return 0;
}
