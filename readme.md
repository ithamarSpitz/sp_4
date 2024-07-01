itas12@gmail.com
# Tree Data Structure Project

This project implements a generic tree data structure in C++ with various traversal methods and visualization capabilities.

## Class Hierarchy

1. `Tree<T, K>` (in Tree.hpp)
   - Main class implementing the tree data structure
   - Template parameters:
     - T: Type of data stored in the tree
     - K: Maximum number of children per node (default is 2 for binary trees)

2. `Complex` (in Complex.hpp and Complex.cpp)
   - Auxiliary class representing complex numbers
   - Used to demonstrate the tree's functionality with a custom data type

## File Descriptions

### Tree.hpp and Tree.tpp

Contains the implementation of the `Tree<T, K>` class template.

Key functions:

- `add_root(const T &value)`: Adds or updates the root node
- `add_sub_node(Node *parent, const T &value)`: Adds a child node to a parent node
- Traversal methods:
  - `begin_pre_order()` / `end_pre_order()`: Pre-order traversal
  - `begin_post_order()` / `end_post_order()`: Post-order traversal
  - `begin_in_order()` / `end_in_order()`: In-order traversal (for binary trees)
  - `begin_bfs_scan()` / `end_bfs_scan()`: Breadth-first search traversal
  - `begin_dfs_scan()` / `end_dfs_scan()`: Depth-first search traversal
- `myHeap()`: Creates a heap from the tree (for binary trees only)
- `print(std::string fileName)`: Generates a visual representation of the tree using graphviz, DOT lang and inkview
- `to_string()`: Returns a string representation of the tree

### Complex.hpp and Complex.cpp

Implement the `Complex` class for complex numbers.

Key functions:

- Arithmetic operators: `+`, `-`, `*`
- Comparison operators: `==`, `<`, `>`
- `std::to_string(const Complex& c)`: Converts a Complex number to a string

### demo.cpp

Demonstrates the usage of the `Tree` class with both `double` and `Complex` data types.

### tests.cpp

Contains comprehensive unit tests for the `Tree` class, covering various scenarios and edge cases.

## Compilation and Execution

To compile and run the project:

1. Install required dependencies:
sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
sudo apt-get install inkscape
sudo apt install graphviz

2. Compile the project:
make

3. Run the demo:
./demo

4. Run the tests:
./tests

5. Clean up compiled files:
make clean
