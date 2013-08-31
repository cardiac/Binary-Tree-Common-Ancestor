//
//    A series of attempts at algorithms to find the first common ancestor given two nodes in a binary tree.
//    Copyright (C) 2013  Ryan
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//  algoC.c
//  
//
//  Created by Ryan Strug on 8/29/13.
//
//  This algorithm is nearly identical to B, but shows speed gains over large data sets.
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

int left = 0, right = 0;

int main()
{
    printf("Algorithm C\n");
    
    struct Node *root = build_tree();
    
    printf("6, 4: %u, expects: 5\n", traverse(root, 6, 4)->value), left = 0, right = 0;
    printf("7, 4: %u, expects: 2\n", traverse(root, 7, 4)->value), left = 0, right = 0;
    printf("7, 5: %u, expects: 5\n", traverse(root, 7, 5)->value), left = 0, right = 0;
    printf("1, 0: %u, expects: 1\n", traverse(root, 1, 0)->value), left = 0, right = 0;
    printf("2, 8: %u, expects: 3\n", traverse(root, 2, 8)->value), left = 0, right = 0;
    
    return 0;
}

struct Node *traverse(struct Node *node, int first, int second)
{
    if (right == 1 && left == 1)
        return NULL;
    
    struct Node *l = node->left, *r = node->right;
    if (l != NULL) {
        if (l->value != first && l->value != second)
            l = traverse(l, first, second);
        else
            left = 1;
    }
    if (r != NULL) {
        if (r->value != first && r->value != second)
            r = traverse(r, first, second);
        else
            right = 1;
    }

    if (l != NULL && r != NULL)
        return node;
    if (r != NULL)
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
