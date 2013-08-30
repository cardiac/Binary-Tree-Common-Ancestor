//
//  algoB.c
//  
//
//  Created by Ryan Strug on 8/29/13.
//
//  A second attempt at finding a common ancestor in a binary tree given two values.
//
//
//
//            _______3______
//           /              \
//       ___5__           __1__
//      /      \         /     \
//     6        2       0       8
//             / \
//            7   4
//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *left, *right;
};

struct Node *traverse(struct Node *node, int first, int second);

struct Node *build_tree();
struct Node *create_node(int value, struct Node *left, struct Node *right);

int main()
{
    printf("Algorithm B\n");
    
    struct Node *root = build_tree();
    
    printf("6, 4: %u, expects: 5\n", traverse(root, 6, 4)->value);
    printf("7, 4: %u, expects: 2\n", traverse(root, 7, 4)->value);
    printf("7, 5: %u, expects: 5\n", traverse(root, 7, 5)->value);
    printf("1, 0: %u, expects: 1\n", traverse(root, 1, 0)->value);
    printf("2, 8: %u, expects: 3\n", traverse(root, 2, 8)->value);
    
    return 0;
}

struct Node *traverse(struct Node *node, int first, int second)
{
    struct Node *l = node->left, *r = node->right;
    if (l != NULL && l->value != first && l->value != second)
        l = traverse(l, first, second);
    if (r != NULL && r->value != first && r->value != second)
        r = traverse(r, first, second);
    
    if (l != NULL && r != NULL)
        return node;
    else if (r != NULL)
        return r;
    else if (l != NULL)
        return l;
    return NULL;
}

struct Node *build_tree()
{
    struct Node *threeOne = create_node(7, NULL, NULL);
    struct Node *threeTwo = create_node(4, NULL, NULL);
    struct Node *twoOne = create_node(6, NULL, NULL);
    struct Node *twoTwo = create_node(2, threeOne, threeTwo);
    struct Node *twoThree = create_node(0, NULL, NULL);
    struct Node *twoFour = create_node(8, NULL, NULL);
    struct Node *oneOne = create_node(5, twoOne, twoTwo);
    struct Node *oneTwo = create_node(1, twoThree, twoFour);
    return create_node(3, oneOne, oneTwo);
}

struct Node *create_node(int value, struct Node *left, struct Node *right)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->value = value;
    new->left = left;
    new->right = right;
    return new;
}
