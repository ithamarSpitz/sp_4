//itas12@gmail.com
#ifndef TREE_HPP
#define TREE_HPP

#include "Complex.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

template <typename T, int K = 2>
class Tree
{
private:
    struct Node
    {
        T data;
        std::vector<Node *> children;
        Node(const T &value) : data(value) {}
    };

    Node *root;

    void deleteTree(Node *node);
    void preOrderTraversal(Node *node, std::vector<T> &result) const;
    void postOrderTraversal(Node *node, std::vector<T> &result) const;
    void inOrderTraversal(Node *node, std::vector<T> &result) const;

public:
    Tree();
    ~Tree();

    Node *add_root(const T &value);
    Node *getRoot() const;
    Node *add_sub_node(Node *parent, const T &value);

    class iterator
    {
    private:
        std::vector<T> traversal;
        size_t index;

    public:
        iterator(const std::vector<T> &trav, size_t idx = 0);

        T &operator*();
        const T &operator*() const;

        iterator &operator++();
        iterator operator++(int);

        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
    };

    iterator begin_pre_order() const;
    iterator end_pre_order() const;
    iterator begin_post_order() const;
    iterator end_post_order() const;
    iterator begin_in_order() const;
    iterator end_in_order() const;
    iterator begin_bfs_scan() const;
    iterator end_bfs_scan() const;
    iterator begin_dfs_scan() const;
    iterator end_dfs_scan() const;

    iterator begin() const;
    iterator end() const;

    iterator myHeap();

    template <typename U, int L>
    friend std::ostream &operator<<(std::ostream &os, const Tree<U, L> &tree);

    std::string to_string() const;

    void print(std::string fileName);
    void print();
};

#include "Tree.tpp" // Include the implementation file for template definitions

#endif // TREE_HPP
