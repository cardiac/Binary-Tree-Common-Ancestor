/*
    A series of attempts at algorithms to find the first common ancestor given two nodes in a binary tree.
    Copyright (C) 2013  Ryan

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

  algoB.c


  Created by Ryan Strug on 8/29/13.

  This algorithm is the fastest of these algorithms for finding the least common ancestor in a small binary tree (as it searches the entire tree).



            _______3______
           /              \
       ___5__            __1__
      /      \          /     \
     6        2        0       8
             / \
            7   4
*/

#include <stdio.h>
#include <stdlib.h>

#define kTestCnt 11

struct Node {
    int value;
    struct Node *left, *right;
};

struct Node *traverse(struct Node *node, int first, int second);

void test_tree(struct Node *root);
struct Node *build_tree();
struct Node *build_tree_one();
struct Node *build_tree_root();
struct Node *build_tree_null();
struct Node *create_node(int value, struct Node *left, struct Node *right);

int values[kTestCnt][3] = {{6, 4, 5}, {7, 4, 2}, {7, 5, 5}, {1, 0, 1}, {2, 8, 3},
    {5, 1, 3}, {3, 7, 3}, {3, 5, 3}, {3, 0, 3}, {5, 2, 5}, {5, 0, 3}};

int main()
{
    printf("Algorithm B\n");
    
    test_tree(build_tree());
    test_tree(build_tree_one());
    test_tree(build_tree_root());
    test_tree(build_tree_null());
    
    return 0;
}

struct Node *traverse(struct Node *node, int first, int second)
{
    if (!node)
        return NULL;
    
    struct Node *l = node->left, *r = node->right;
    if (l && l->value != first && l->value != second)
        l = traverse(l, first, second);
    if (r && r->value != first && r->value != second)
        r = traverse(r, first, second);
    
    if ((l && r) || ((node->value == first || node->value == second) && (!r || !l)))
        return node;
    else if (r)
        return r;
    else if (l)
        return l;
    return NULL;
}

void test_tree(struct Node *root)
{
    for (int i = 0; i < kTestCnt; i++) {
        struct Node *node = traverse(root, values[i][0], values[i][1]);
        printf("%u, %u => %u == ", values[i][0], values[i][1], values[i][2]);
        if (node) {
            printf("%u", node->value);
            if (node->value != values[i][2])
                printf(" DOES NOT MATCH!");
        } else
            printf("NULL");
        printf("\n");
    }
}

struct Node *build_tree()
{
    printf("Full tree.\n");
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

struct Node *build_tree_one()
{
    printf("The following trees do not contain all of the values from the test cases. They will return NULL in those instances.\n");
    printf("Two level tree.\n");
    struct Node *oneOne = create_node(5, NULL, NULL);
    struct Node *oneTwo = create_node(1, NULL, NULL);
    return create_node(3, oneOne, oneTwo);
}

struct Node *build_tree_root()
{
    printf("Root only tree.\n");
    return create_node(3, NULL, NULL);
}

struct Node *build_tree_null()
{
    printf("Null tree.\n");
    return NULL;
}

struct Node *create_node(int value, struct Node *left, struct Node *right)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->value = value;
    new->left = left;
    new->right = right;
    return new;
}
