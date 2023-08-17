
# Binary Search Tree in C

A straightforward implementation of a Binary Search Tree (BST) in C, featuring essential operations for efficient data management.


## Features

- Create a new BST and manage its lifecycle.
- Insert elements into the BST.
- Search for and remove specific elements.
- Easily determine the height and size of the tree.
- Check whether the tree is empty.
- Traverse the tree and perform user-defined action on each node.
- Multiple travesral modes: in-order, pre-order and post-order.


## Usage

Note: by compiling the files (using makefile), a `bst.out` file will be created, which is an executable for the testing I performed.<br>
If you want to use the stack by itself, only download the `stack.c` file. 

1. Clone this repository.
2. Compile the files using the makefile in the terminal:
      ```bash
      make
      ```
3. Run the executable in the terminal:
      ```bash
      ./bst.out
      ```
4. Review the comments in the `bst.h` / `bst.c` files to understand the purpose and functionality of each function.


## Behavioral Guidelines

Exercise caution when using the BST remove function, as attempting to remove non-existent or already removed elements may result in a segmentation fault.
