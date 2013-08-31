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
//  algoA.c
//  
//
//  Created by Ryan Strug on 8/29/13.
//
//  A first attempt at finding the least common ancestor in a binary tree when given two values. This was first idea that I had after immediately viewing the problem.
//
//
//
//            _______3______
//           /              \
//       ___5__           __1__
//      /      \         /     \
//     6        2       0       8
//    /  \
//   7   4
//
//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *left, *right;
};

struct Wrapper {
    int height;
    struct Wrapper *parent;
    struct Node *node;
};

// function definitions
int find_common(int first, int second);

struct Node *traverse(struct Wrapper *first, struct Wrapper *second);
void locate_data(struct Wrapper *wrapper, int height);
void parse_data(struct Wrapper *wrapper, struct Node *node, int height);
void test(struct Wrapper *wrapper);

struct Wrapper *wrap_node(struct Wrapper *parent, struct Node *node, int height);

struct Node *root_node = NULL;
struct Wrapper *root_wrapper = NULL, *first_wrapper = NULL, *second_wrapper = NULL;
int first_val, second_val;

void build_tree();
struct Node *create_node(int value, struct Node *left, struct Node *right);

// main function
int main(int argc, char **argv)
{
    argc = 0, argv = NULL;
    
    printf("Algorithm A\n");
    
    build_tree();
    
    printf("6, 4: %u, expects: 5\n", find_common(6, 4));
    printf("7, 4: %u, expects: 2\n", find_common(7, 4));
    printf("7, 5: %u, expects: 5\n", find_common(7, 5));
    printf("1, 0: %u, expects: 1\n", find_common(1, 0));
    printf("2, 8: %u, expects: 3\n", find_common(2, 8));
    
    return 0;
}

// finds the common ancestor
int find_common(int first, int second)
{
    first_val = first, second_val = second;
    
    if (root_node->value == first)
        return first;
    else if (root_node->value == second)
        return second;
    
    struct Wrapper *root_wrapper = wrap_node(NULL, root_node, 0);
    locate_data(root_wrapper, 1);

    struct Node *common = traverse(first_wrapper, second_wrapper);
    return common->value;
}

// crawls back up the tree to find the common ancestor
struct Node *traverse(struct Wrapper *first, struct Wrapper *second)
{
    if (first->height < second->height)
        return traverse(first, second->parent);
    else if (first->height > second->height)
        return traverse(first->parent, second);
    else if (first->node->value != second->node->value)
        return traverse(first->parent, second->parent);
    return first->node;
}

// finds the two values specified
void locate_data(struct Wrapper *wrapper, int height)
{
    if (wrapper->node->left != NULL)
        parse_data(wrapper, wrapper->node->left, height);
    
    if (wrapper->node->right != NULL)
        parse_data(wrapper, wrapper->node->right, height);
}

// parses each wrapper for values
void parse_data(struct Wrapper *wrapper, struct Node *node, int height)
{
    struct Wrapper *new = wrap_node(wrapper, node, height);
    test(new);
    locate_data(new, height + 1);
}

// tests the node values against the specified values
void test(struct Wrapper *wrapper)
{
    if (wrapper->node->value == first_val)
        first_wrapper = wrapper;
    
    if (wrapper->node->value == second_val)
        second_wrapper = wrapper;
}

// stores each node in a wrapper
struct Wrapper *wrap_node(struct Wrapper *parent, struct Node *node, int height)
{
    struct Wrapper *wrapper = malloc(sizeof(struct Wrapper));
    wrapper->parent = parent;
    wrapper->node = node;
    wrapper->height = height;
    return wrapper;
}

// constructs a binary tree
void build_tree()
{
    struct Node *threeOne = create_node(7, NULL, NULL);
    struct Node *threeTwo = create_node(4, NULL, NULL);
    struct Node *twoOne = create_node(6, NULL, NULL);
    struct Node *twoTwo = create_node(2, threeOne, threeTwo);
    struct Node *twoThree = create_node(0, NULL, NULL);
    struct Node *twoFour = create_node(8, NULL, NULL);
    struct Node *oneOne = create_node(5, twoOne, twoTwo);
    struct Node *oneTwo = create_node(1, twoThree, twoFour);
    root_node = create_node(3, oneOne, oneTwo);
}

// creates a node
struct Node *create_node(int value, struct Node *left, struct Node *right)
{
    struct Node *new = malloc(sizeof(struct Node));
    new->value = value;
    new->left = left;
    new->right = right;
    return new;
}
