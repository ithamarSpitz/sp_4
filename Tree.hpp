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

    void deleteTree(Node *node)
    {
        if (node)
        {
            for (Node *child : node->children)
            {
                deleteTree(child);
            }
            delete node;
        }
    }

    void preOrderTraversal(Node *node, std::vector<T> &result) const
    {
        if (node)
        {
            result.push_back(node->data);
            for (Node *child : node->children)
            {
                preOrderTraversal(child, result);
            }
        }
    }

    void postOrderTraversal(Node *node, std::vector<T> &result) const
    {
        if (node)
        {
            for (Node *child : node->children)
            {
                postOrderTraversal(child, result);
            }
            result.push_back(node->data);
        }
    }

    void inOrderTraversal(Node *node, std::vector<T> &result) const
    {
        if (node)
        {
            if (K == 2)
            {
                if (!node->children.empty())
                {
                    inOrderTraversal(node->children[0], result);
                }
                result.push_back(node->data);
                if (node->children.size() > 1)
                {
                    inOrderTraversal(node->children[1], result);
                }
            }
            else
            {
                preOrderTraversal(node, result);
            }
        }
    }

public:
    Tree() : root(nullptr) {}

    ~Tree()
    {
        deleteTree(root);
    }

    Node *add_root(const T &value)
    {
        if (!root)
        {
            root = new Node(value);
        }
        else
        {
            root->data = value;
        }
        return root;
    }

    Node *getRoot() const
    {
        return root;
    }

    Node *add_sub_node(Node *parent, const T &value)
    {
        if (parent && parent->children.size() < K)
        {
            Node *new_node = new Node(value);
            parent->children.push_back(new_node);
            return new_node;
        }
        return nullptr;
    }

    class iterator
    {
    private:
        std::vector<T> traversal;
        size_t index;

    public:
        iterator(const std::vector<T> &trav, size_t idx = 0) : traversal(trav), index(idx) {}

        T &operator*() { return traversal[index]; }
        const T &operator*() const { return traversal[index]; }

        iterator &operator++()
        {
            ++index;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++index;
            return tmp;
        }

        bool operator==(const iterator &other) const { return index == other.index; }
        bool operator!=(const iterator &other) const { return !(*this == other); }
    };

    iterator begin_pre_order() const
    {
        std::vector<T> result;
        preOrderTraversal(root, result);
        return iterator(result);
    }

    iterator end_pre_order() const
    {
        std::vector<T> result;
        preOrderTraversal(root, result);
        return iterator(result, result.size());
    }

    iterator begin_post_order() const
    {
        std::vector<T> result;
        postOrderTraversal(root, result);
        return iterator(result);
    }

    iterator end_post_order() const
    {
        std::vector<T> result;
        postOrderTraversal(root, result);
        return iterator(result, result.size());
    }

    iterator begin_in_order() const
    {
        std::vector<T> result;
        inOrderTraversal(root, result);
        return iterator(result);
    }

    iterator end_in_order() const
    {
        std::vector<T> result;
        inOrderTraversal(root, result);
        return iterator(result, result.size());
    }

    iterator begin_bfs_scan() const
    {
        std::vector<T> result;
        if (root)
        {
            std::queue<Node *> q;
            q.push(root);
            while (!q.empty())
            {
                Node *current = q.front();
                q.pop();
                result.push_back(current->data);
                for (Node *child : current->children)
                {
                    q.push(child);
                }
            }
        }
        return iterator(result);
    }

    iterator end_bfs_scan() const
    {
        std::vector<T> result;
        if (root)
        {
            std::queue<Node *> q;
            q.push(root);
            while (!q.empty())
            {
                Node *current = q.front();
                q.pop();
                result.push_back(current->data);
                for (Node *child : current->children)
                {
                    q.push(child);
                }
            }
        }
        return iterator(result, result.size());
    }

    iterator begin() const
    {
        return begin_bfs_scan();
    }

    iterator end() const
    {
        return end_bfs_scan();
    }

    iterator begin_dfs_scan() const
    {
        std::vector<T> result;
        if (root)
        {
            std::stack<Node *> s;
            s.push(root);
            while (!s.empty())
            {
                Node *current = s.top();
                s.pop();
                result.push_back(current->data);
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                {
                    s.push(*it);
                }
            }
        }
        return iterator(result);
    }

    iterator end_dfs_scan() const
    {
        std::vector<T> result;
        if (root)
        {
            std::stack<Node *> s;
            s.push(root);
            while (!s.empty())
            {
                Node *current = s.top();
                s.pop();
                result.push_back(current->data);
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
                {
                    s.push(*it);
                }
            }
        }
        return iterator(result, result.size());
    }

    iterator myHeap()
    {
        if (K != 2)
        {
            throw std::runtime_error("Heap iterator is only available for binary trees");
        }

        std::vector<T> heap;
        std::function<void(Node *)> heapify = [&](Node *node)
        {
            if (node)
            {
                heap.push_back(node->data);
                for (Node *child : node->children)
                {
                    heapify(child);
                }
            }
        };

        heapify(root);
        std::make_heap(heap.begin(), heap.end(), std::less<T>());
        std::sort_heap(heap.begin(), heap.end(), std::less<T>());

        return iterator(heap);
    }

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree)
    {
        return os << tree.to_string();
    }

    std::string to_string() const
    {
        if (!root)
        {
            std::cerr << "Empty tree" << std::endl;
            return "";
        }

        std::function<std::string(Node *, std::string, bool)> tree_str = [&](Node *node, std::string prefix, bool isLast) -> std::string
        {
            if (node)
            {
                std::string res;
                res += prefix;
                res += (isLast ? "└── " : "├── ");
                res += std::to_string(node->data);
                res += "\n";
                for (size_t i = 0; i < node->children.size(); ++i)
                {
                    res += tree_str(node->children[i], prefix + (isLast ? "    " : "│   "), i == node->children.size() - 1);
                }
                return res;
            }
            else
            {
                return "";
            }
        };

        return tree_str(root, "", true);
    }

    void print(std::string fileName)
    {
        std::function<std::string(Node *)> recEdges = [&](Node *node)
        {
            if (node)
            {
                if (node->children.size() == 0)
                {
                    return std::string("");
                }
                std::string res;
                for (size_t i = 0; i < node->children.size(); ++i)
                {
                    std::string parent = std::to_string(node->data);
                    std::string child = std::to_string(node->children[i]->data);
                    std::string edge = "\"" + parent + "\"->\"" + child + "\";";
                    std::string childEdges = recEdges(node->children[i]);
                    res = res + edge + childEdges;
                }
                return res;
            }
            std::cerr << "Empty tree" << std::endl;
            return std::string("");
        };

        std::string start = "echo 'digraph {fontname=\"Arial\"node [fontname=\"Arial\"]edge [fontname=\"Arial\"]graph [rankdir = \"up\"];node [fontsize = \"16\"shape = \"circle\"];edge [shape = \"record\"];";
        std::string end = "}' | dot -Tsvg >" + fileName + ".svg";
        std::string command = start + recEdges(root) + end;
        system(command.c_str());
        start = "inkview ";
        end = ".svg";
        command = start + fileName + end;
        system(command.c_str());
    }

    void print()
    {
        print("output1");
    }
};

#endif // TREE_HPP