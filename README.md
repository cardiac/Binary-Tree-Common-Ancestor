Binary-Tree-Common-Ancestor
===========================

A series of attempts at algorithms to find the first common ancestor given two nodes in a binary tree.

All of these algorithms work with unbalanced binary trees and contain no optimization for a balanced version.

The A algorithm was planned out very quickly is pretty much a mess, but it got the job done.

The B algorithm is likely the fastest for a small binary tree.

The C algorithm is likely faster than B for a large data set. 

Compile Statements
==================
gcc (GCC) 4.8.3 20140624 (Red Hat 4.8.3-1)

```
gcc -std=c11 -Wall -Wpedantic -o algoA algoA.c
gcc -std=c11 -Wall -Wpedantic -o algoB algoB.c
gcc -std=c11 -Wall -Wpedantic -o algoC algoC.c
```
