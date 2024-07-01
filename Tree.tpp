//itas12@gmail.com
#ifndef TREE_TPP
#define TREE_TPP

#include "Tree.hpp"

// Constructor for Tree class
template <typename T, int K>
Tree<T, K>::Tree() : root(nullptr) {}

// Destructor for Tree class
template <typename T, int K>
Tree<T, K>::~Tree()
{
    // Deletes the entire tree starting from the root
    deleteTree(root);
}

// Recursive helper function to delete the tree
template <typename T, int K>
void Tree<T, K>::deleteTree(Node *node)
{
    if (node)
    {
        // Delete all children recursively
        for (Node *child : node->children)
        {
            deleteTree(child);
        }
        // Delete the current node
        delete node;
    }
}

// Function to add or update the root node
template <typename T, int K>
typename Tree<T, K>::Node *Tree<T, K>::add_root(const T &value)
{
    if (!root)
    {
        // If the tree has no root, create a new root node
        root = new Node(value);
    }
    else
    {
        // If the root already exists, update its value
        root->data = value;
    }
    return root;
}

// Function to get the root node
template <typename T, int K>
typename Tree<T, K>::Node *Tree<T, K>::getRoot() const
{
    return root;
}

// Function to add a sub-node to a parent node
template <typename T, int K>
typename Tree<T, K>::Node *Tree<T, K>::add_sub_node(Node *parent, const T &value)
{
    if (parent && parent->children.size() < K)
    {
        // Create a new node with the specified value
        Node *new_node = new Node(value);
        // Add the new node to the parent's children list
        parent->children.push_back(new_node);
        return new_node;
    }
    return nullptr;
}

// Pre-order traversal: visit root, then left subtree, then right subtree
template <typename T, int K>
void Tree<T, K>::preOrderTraversal(Node *node, std::vector<T> &result) const
{
    if (node)
    {
        // Add the current node's data to the result
        result.push_back(node->data);
        // Traverse all children
        for (Node *child : node->children)
        {
            preOrderTraversal(child, result);
        }
    }
}

// Post-order traversal: visit left subtree, then right subtree, then root
template <typename T, int K>
void Tree<T, K>::postOrderTraversal(Node *node, std::vector<T> &result) const
{
    if (node)
    {
        // Traverse all children first
        for (Node *child : node->children)
        {
            postOrderTraversal(child, result);
        }
        // Add the current node's data to the result
        result.push_back(node->data);
    }
}

// In-order traversal for binary trees (K==2), otherwise use pre-order traversal
template <typename T, int K>
void Tree<T, K>::inOrderTraversal(Node *node, std::vector<T> &result) const
{
    if (node)
    {
        if (K == 2)
        {
            // If the node has children, traverse the left subtree
            if (!node->children.empty())
            {
                inOrderTraversal(node->children[0], result);
            }
            // Add the current node's data to the result
            result.push_back(node->data);
            // If the node has more than one child, traverse the right subtree
            if (node->children.size() > 1)
            {
                inOrderTraversal(node->children[1], result);
            }
        }
        else
        {
            // For non-binary trees, use pre-order traversal
            preOrderTraversal(node, result);
        }
    }
}

// Iterator constructor: initializes the iterator with a traversal result and an index
template <typename T, int K>
Tree<T, K>::iterator::iterator(const std::vector<T> &trav, size_t idx) : traversal(trav), index(idx) {}

// Dereference operator for iterator: returns the current element
template <typename T, int K>
T &Tree<T, K>::iterator::operator*()
{
    return traversal[index];
}

// Dereference operator for constant iterator: returns the current element
template <typename T, int K>
const T &Tree<T, K>::iterator::operator*() const
{
    return traversal[index];
}

// Pre-increment operator for iterator: advances the iterator to the next element
template <typename T, int K>
typename Tree<T, K>::iterator &Tree<T, K>::iterator::operator++()
{
    ++index;
    return *this;
}

// Post-increment operator for iterator: advances the iterator to the next element and returns the previous state
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::iterator::operator++(int)
{
    iterator tmp = *this;
    ++index;
    return tmp;
}

// Equality operator for iterator: checks if two iterators are equal
template <typename T, int K>
bool Tree<T, K>::iterator::operator==(const iterator &other) const
{
    return index == other.index;
}

// Inequality operator for iterator: checks if two iterators are not equal
template <typename T, int K>
bool Tree<T, K>::iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

// Begin iterator for pre-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin_pre_order() const
{
    std::vector<T> result;
    preOrderTraversal(root, result);
    return iterator(result);
}

// End iterator for pre-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end_pre_order() const
{
    std::vector<T> result;
    preOrderTraversal(root, result);
    return iterator(result, result.size());
}

// Begin iterator for post-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin_post_order() const
{
    std::vector<T> result;
    postOrderTraversal(root, result);
    return iterator(result);
}

// End iterator for post-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end_post_order() const
{
    std::vector<T> result;
    postOrderTraversal(root, result);
    return iterator(result, result.size());
}

// Begin iterator for in-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin_in_order() const
{
    std::vector<T> result;
    inOrderTraversal(root, result);
    return iterator(result);
}

// End iterator for in-order traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end_in_order() const
{
    std::vector<T> result;
    inOrderTraversal(root, result);
    return iterator(result, result.size());
}

// Begin iterator for breadth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin_bfs_scan() const
{
    std::vector<T> result;
    if (root)
    {
        // Queue for level-order traversal
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            // Add current node's data to result
            result.push_back(current->data);
            // Add all children to the queue
            for (Node *child : current->children)
            {
                q.push(child);
            }
        }
    }
    return iterator(result);
}

// End iterator for breadth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end_bfs_scan() const
{
    std::vector<T> result;
    if (root)
    {
        // Queue for level-order traversal
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            // Add current node's data to result
            result.push_back(current->data);
            // Add all children to the queue
            for (Node *child : current->children)
            {
                q.push(child);
            }
        }
    }
    return iterator(result, result.size());
}

// Begin iterator for depth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin_dfs_scan() const
{
    std::vector<T> result;
    if (root)
    {
        // Stack for depth-first traversal
        std::stack<Node *> s;
        s.push(root);
        while (!s.empty())
        {
            Node *current = s.top();
            s.pop();
            // Add current node's data to result
            result.push_back(current->data);
            // Add all children to the stack in reverse order
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
            {
                s.push(*it);
            }
        }
    }
    return iterator(result);
}

// End iterator for depth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end_dfs_scan() const
{
    std::vector<T> result;
    if (root)
    {
        // Stack for depth-first traversal
        std::stack<Node *> s;
        s.push(root);
        while (!s.empty())
        {
            Node *current = s.top();
            s.pop();
            // Add current node's data to result
            result.push_back(current->data);
            // Add all children to the stack in reverse order
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
            {
                s.push(*it);
            }
        }
    }
    return iterator(result, result.size());
}

// Default begin iterator using breadth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::begin() const
{
    return begin_bfs_scan();
}

// Default end iterator using breadth-first traversal
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::end() const
{
    return end_bfs_scan();
}

// Function to get a heap-ordered iterator for binary trees
// i decendents are in 2i+1,2i+2
template <typename T, int K>
typename Tree<T, K>::iterator Tree<T, K>::myHeap()
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
            // Add node data to heap
            heap.push_back(node->data);
            // Recursively heapify all children
            for (Node *child : node->children)
            {
                heapify(child);
            }
        }
    };

    // Heapify the tree starting from the root
    heapify(root);
    // Convert the vector into a max-heap
    std::make_heap(heap.begin(), heap.end(), std::less<T>());
    // Sort the heap to get a sorted iterator
    std::sort_heap(heap.begin(), heap.end(), std::less<T>());

    return iterator(heap);
}

// Overload the output operator to print the tree as a string
template <typename T, int K>
std::ostream &operator<<(std::ostream &os, const Tree<T, K> &tree)
{
    return os << tree.to_string();
}

// Function to convert the tree to a string representation
template <typename T, int K>
std::string Tree<T, K>::to_string() const
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
            // Traverse all children
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

// Function to generate a visualization of the tree and save it as an SVG file
template <typename T, int K>
void Tree<T, K>::print(std::string fileName)
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

    // Create a command string to generate an SVG file using Graphviz
    std::string start = "echo 'digraph {fontname=\"Arial\"node [fontname=\"Arial\"]edge [fontname=\"Arial\"]graph [rankdir = \"up\"];node [fontsize = \"16\"shape = \"circle\"];edge [shape = \"record\"];";
    std::string end = "}' | dot -Tsvg >" + fileName + ".svg";
    std::string command = start + recEdges(root) + end;
    // Execute the command to generate the SVG
    system(command.c_str());
    // Command to open the SVG file using Inkscape
    start = "inkview ";
    end = ".svg";
    command = start + fileName + end;
    system(command.c_str());
}

// Function to print the tree visualization to a default file
template <typename T, int K>
void Tree<T, K>::print()
{
    print("output1");
}

#endif // TREE_TPP
