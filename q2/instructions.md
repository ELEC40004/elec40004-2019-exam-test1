Q2 : Balanced trees
===================

Background
==========

Maps and dictionaries are common abstract data structures which
capture the general idea of mapping from a set of keys to a single value.

Binary search trees are one concrete way of implementing a map,
but they suffer from the problem that they can degenerate into
linked lists. Unfortunately this occurs for the common case of
inserting data which is already in sorted order. To alleviate
this problem various types of balancing can be used, which
can guarantee that the tree is balanced - these are used in
the C++ STL to implement data structures such as `map` from `<map>`.
However, maintaining strict balancing can be both complicated
to code and expensive at run-time.

Stochastic balancing
--------------------

Another approach is to use a probabilistic approach, which
tries to ensure that the tree is very likely to be balanced.
The approach used here is the idea of attaching a random
numeric weights to each node as it is created. We then
maintain the invariant that a parent node always has a higher (larger)
weight than its child nodes. When a new node is added as a leaf
to the tree, we compare it's weight to it's parent - if the
leaf has a higher-weight, we **rotate** the tree around the
parent node so that the leaf and parent swap order in the
tree. If necessary, this rotation process continues up the
tree, and there is a small chance that the leaf bubbles
up to become the new root.

For example, imagine we have the following tree, where keys
are given as strings, and weights are random integers from
1 to 100:
```
       +-------+
       | k:"A" |
       | w:64  |
       +-------+
              \
               \
            +-------+
            | k:"B" |
            | w:30  |
            +-------+
```
We now insert a new node "C", which is assigned the weight 70:
```
       +-------+
       | k:"A" |
       | w:64  |
       +-------+
              \
               \
            +-------+
            | k:"B" |
            | w:30  |
            +-------+
                   \
                    \
                 +-------+
                 | k:"C" |
                 | w:70  |
                 +-------+
```
This is in danger of turning into a linked list as we add "D", "E", and so
one, but notice that the weight of "C" is greater than the weight of "B",
so we "rotate left" around "B":
```
       +-------+
       | k:"A" |
       | w:64  |
       +-------+
              \
               \
            +-------+
            | k:"C" |
            | w:70  |
            +-------+
             /
            / 
     +-------+
     | k:"B" |
     | w:30  |
     +-------+
```
Now the weight relationship between A and B is incorrect, so we must rotate again:
```
                 +-------+
                 | k:"C" |
                 | w:70  |
                 +-------+
                  /
                 /
            +-------+
            | k:"A" |
            | w:64  |
            +-------+
                   \
                    \ 
                +-------+
                | k:"B" |
                | w:30  |
                +-------+
```
At this point the binary search property is maintained, but we have
also preserved the weight invariant - parents all have higher weights
than children.

If we insert D with random weight 50 and then E with random weight 25,
we end up with:
```
                 +-------+
                 | k:"C" |
                 | w:70  |
                 +-------+
                  /     \
                 /       \
            +-------+  +-------+
            | k:"A" |  | k:"D" |
            | w:64  |  | w: 50 |
            +-------+  +-------+
                   \          \
                    \          \
                +-------+    +-------+    
                | k:"B" |    | k:"E" |
                | w:30  |    | w:25  |
                +-------+    +-------+
```
This is clearly much better balanced than the linked-list which would arise
without the weight-based rebalancing. While there is no guarantee that the
tree will be well-balanced, it is highly likely that the tree will remain
mostly balanced, and so preserve fast lookup times.

Tree rotations
--------------

There are two types of rotation needed: a left-rotation, and a right
rotation.

Consider the following tree where `keys(N1) < key(n2) < keys(N3) < key(n4) < keys(n5)`,
but where `weight(n2) > weight(n4)`. The tree on the left is not weight balanced,
as `n2` has a higher weight than `n4`. The tree on the right *is* weight balanced,
but it also preserves the sorted tree property. This operation is
called a **right rotation** on node `n4`.
```
          n4              n2
         /  \            /  \
        n2  N5   --->   N1  n4
       /  \                /  \
      N1  N3              N3  N5 
```

A similar operation is performed when the right child `n4` has the higher weight,
and is called a **left rotation** on node `n2`:
```
          n2              n4
         /  \            /  \
        N1  n4   --->   n2  N5
           /  \        /  \
          N3  N5      N1  N3 
```

Both rotations are accomplished locally, and only require the modifications
of the `left` and `right` pointers of `n2` and `n4`.

Balancing algorithm
-------------------

Inserting into a balanced tree is a small modification of the
standard process for inserting into a binary search tree. In
pseudo-code, the standard process is:
```
Node insert(Node n, Key k):
   if n is Null:
      n = Node(k, Null, Null)
   else:
      if key < n.key:
         n.left = insert(n.left, k)
      elif key > n.key:
         n.right = insert(n.right, k)
   return n
```

In comparison, the balanced insertion is:
```
Node insert(Node n, Key k):
   if n is Null:
      n = Node(k, random_weight(), Null, Null)
   else:
      if key < n.key:
         n.left = insert(n.left, k)

         # Ensure weight relationship
         if n.left.weight > n.weight:
            n = rotate_right(n)
      elif key > n.key:
         n.right = insert(n.right, k)

         # Ensure weight relationship
         if n.right.weight > n.weight:
            n = rotate_left(n)
   return n
```

The balanced insertion has three additions:

1. Adding a new random weight to each new leaf node
2. Conditionally rotating right when inserting into the left child
3. Conditionally rotating left when inserting into the right child


Tasks
=====

T1 - Generic node operations (30%)
----------------------------------

The file `tree_operations.hpp` provides generic functions
for binary search trees which can operate with any node with at least
three members:
- `key` : A key of some comparable type.
- `left` : A pointer to a child of the same node type.
- `right` : A pointer to a child of the same node type.

Any trees passed to these functions will not be deep enough to
cause stack overflow, so recursive functions can be safely used.

### T1.1 - Implement lookup

Implement the function `tree_lookup` so that it will return
the node containing the key `k`, or `nullptr` if there is
no such node.

### T1.2 - Implement tree deletion

Implement the function `tree_delete` so that it will recursively
free all storage associated with the tree.

You should assume that all nodes have been allocated with scalar `delete`.

### T1.3 - Provide a checker `tree_is_search_tree`

Implement the function `tree_is_search_tree` which checks a
given tree is a valid binary search tree.

The function should take time proportional to the tree depth.

This function should not allocate any memory.

_Hint: you may find it useful to create one or more helper functions_
_in order to track the upper and lower keys around the current node._

T2 - Tree rotations (20%)
-------------------------

### T2.1 - Implement rotate_left and rotate_right

Implement the two functions rotate_left and rotate_right
in the file `tree_rotations.hpp`.

### T2.2 - Create a program test_tree_rotations

Create a program called `test_tree_rotations.cpp` which checks
that both `rotate_left` and `rotate_right` operate correctly.

Your test program should build at least one test tree, and
ensure that the binary search property is preserved.

_You should assume that your program will be tested with both your_
_implementation of rotate_left and rotate_right, as well as incorrect versions._

T3 - Unbalanced Map (20%)
-------------------------

The file `unbalanced_map.hpp` provides a class called `UnBalancedMap`
which implements a naive unbalanced binary tree.

### T3.1 - Add a destructor

Add a destructor to the class which releases all tree nodes.

### T3.2 - Add a copy constructor

Add a copy constructor to the class, which creates a fresh
copy of the map.

### T3.3 - Disable assignment construction

Modify the class so that clients are unable to access the
assignment operator.


T4 - Balanced Map (30%)
-----------------------

The file `balanced_map.hpp` provides a class called `BalancedMap`
which initially implements the same naive unbalanced binary tree.

You are not required to perform the tasks from T3 within `balanced_map.hpp`.

### T4.1 - Modify the class BalancedMap to add weights

Modify the class so that every node contains a weight, which
is assigned to a random value when each node is created.

You can generate random weights using the helper function
`new_weight`.

### T4.2 - Modify the class to use re-balancing

Modify the class so that the tree is rebalanced as necessary
when new nodes are inserted, so that both the weight invariants
and the binary search tree invariants are preserved.

### T4.3 - Performance testing

The program `test_map_performance.cpp` estimates the time taken
per map insertion. Currently it only tests `STLMap` and `NaiveMap`, which use
the same interface as `UnBalancedMap` and `BalancedMap`, but
are based on C++ STL `map` and `vector`.

Modify the program so that it also benchmarks `UnBalancedMap`
and `BalancedMap`, 

Compile the program on your machine, and commit the output
as `map.perf.txt`.
