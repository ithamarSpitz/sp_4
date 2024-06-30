/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Tree.hpp"

using namespace std;

int main()
{
    Tree<double> binaryTree;
    auto root = binaryTree.add_root(1.1);
    auto left = binaryTree.add_sub_node(root, 1.2);
    auto right = binaryTree.add_sub_node(root, 1.3);
    binaryTree.add_sub_node(left, 1.4);
    binaryTree.add_sub_node(left, 1.5);
    binaryTree.add_sub_node(right, 1.6);
    // The Tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it)
        cout << *it << " ";
    cout << endl;
    // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it)
        cout << *it << " ";
        cout << endl;
    // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it)
        cout << *it << " ";
        cout << endl;
    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it)
        cout << *it << " ";
        cout << endl;
    // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    for (auto node : binaryTree)
    {
        cout << node << " ";
    }
    cout << endl;
    // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    Tree<double, 3> trinaryTree;
    auto root3 = trinaryTree.add_root(1.1);
    auto left3 = trinaryTree.add_sub_node(root3, 1.2);
    auto middle3 = trinaryTree.add_sub_node(root3, 1.3);
    auto right3 = trinaryTree.add_sub_node(root3, 1.4);
    trinaryTree.add_sub_node(left3, 1.5);
    trinaryTree.add_sub_node(middle3, 1.6);
    trinaryTree.print(); // Should print the graph using GUI.
    std::cout << trinaryTree << endl; // Should print the graph to stdout
     // The Tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
}