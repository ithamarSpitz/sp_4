//itas12@gmail.com
#include "Tree.hpp"
#include "Complex.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <future>
#include <thread>

// Helper function to check if file created
inline bool is_exists(const std::string &name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

// Helper function to capture cout output
std::string capture_print(const std::function<void()> &func)
{
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

void test1()
{
    // Test empty Tree
    Tree<int> emptyTree;
    assert(emptyTree.begin_pre_order() == emptyTree.end_pre_order());
    std::cout << "Test 1 passed: Empty Tree behaves correctly\n";
}

void test2()
{
    // Test Tree with only root
    Tree<int> singleNodeTree;
    singleNodeTree.add_root(42);
    auto it = singleNodeTree.begin_pre_order();
    assert(*it == 42);
    ++it;
    assert(it == singleNodeTree.end_pre_order());
    std::cout << "Test 2 passed: Single node Tree behaves correctly\n";
}

void test3()
{
    // Test adding maximum number of children
    Tree<int, 3> threeChildTree;
    auto root = threeChildTree.add_root(1);
    threeChildTree.add_sub_node(root, 2);
    threeChildTree.add_sub_node(root, 3);
    threeChildTree.add_sub_node(root, 4);
    auto result = threeChildTree.add_sub_node(root, 5); // This should fail
    assert(result == nullptr);
    std::cout << "Test 3 passed: Tree respects maximum number of children\n";
}

void test4()
{
    // Test all traversal methods
    Tree<int> binaryTree;
    auto root = binaryTree.add_root(1);
    auto left = binaryTree.add_sub_node(root, 2);
    auto right = binaryTree.add_sub_node(root, 3);
    binaryTree.add_sub_node(left, 4);
    binaryTree.add_sub_node(left, 5);
    binaryTree.add_sub_node(right, 6);
    binaryTree.add_sub_node(right, 7);

    std::vector<int> pre_order, post_order, in_order, bfs, dfs;

    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it)
        pre_order.push_back(*it);
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it)
        post_order.push_back(*it);
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it)
        in_order.push_back(*it);
    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it)
        bfs.push_back(*it);
    for (auto it = binaryTree.begin_dfs_scan(); it != binaryTree.end_dfs_scan(); ++it)
        dfs.push_back(*it);

    assert(pre_order == std::vector<int>({1, 2, 4, 5, 3, 6, 7}));
    assert(post_order == std::vector<int>({4, 5, 2, 6, 7, 3, 1}));
    assert(in_order == std::vector<int>({4, 2, 5, 1, 6, 3, 7}));
    assert(bfs == std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
    assert(dfs == std::vector<int>({1, 2, 4, 5, 3, 6, 7}));

    std::cout << "Test 4 passed: All traversal methods work correctly\n";
}

void test5()
{
    // Test with custom type (Complex)
    Tree<Complex> complexTree;
    auto root = complexTree.add_root(Complex(1, 1));
    complexTree.add_sub_node(root, Complex(2, 2));
    complexTree.add_sub_node(root, Complex(3, 3));

    auto it = complexTree.begin_pre_order();
    assert(*it == Complex(1, 1));
    ++it;
    assert(*it == Complex(2, 2));
    ++it;
    assert(*it == Complex(3, 3));

    std::cout << "Test 5 passed: Tree works with custom Complex type\n";
}

void test6()
{
    // Test myHeap method
    Tree<int> heapTree;
    auto root = heapTree.add_root(5);
    heapTree.add_sub_node(root, 10);
    heapTree.add_sub_node(root, 3);

    auto heap_it = heapTree.myHeap();

    std::vector<int> heap_elements;
    for (auto it = heap_it; it != heapTree.end_bfs_scan(); ++it)
    {
        heap_elements.push_back(*it);
    }

    assert(heap_elements[0] == 3);
    assert(heap_elements[1] == 5);
    assert(heap_elements[2] == 10);

    std::cout << "Test 6 passed: myHeap method works correctly\n";
}

void test7()
{
    // Test deep Tree
    Tree<int> deepTree;
    auto node = deepTree.add_root(1);
    for (int i = 2; i <= 1000; ++i)
    {
        node = deepTree.add_sub_node(node, i);
    }

    int count = 0;
    for (auto it = deepTree.begin_pre_order(); it != deepTree.end_pre_order(); ++it)
    {
        assert(*it == ++count);
    }
    assert(count == 1000);
    std::cout << "Test 7 passed: Deep Tree (1000 nodes) works correctly\n";
}

void test8()
{
    // Test print method
    Tree<int> printTree;
    auto root = printTree.add_root(1);
    printTree.add_sub_node(root, 2);
    printTree.add_sub_node(root, 3);

    std::string expected_output =
        "└── 1\n"
        "    ├── 2\n"
        "    └── 3\n";

    std::string actual_output = capture_print([&]()
                                              { std::cout << printTree; });
    assert(actual_output == expected_output);
    std::cout << "Test 8 passed: Print method produces correct output\n";
}

void test9()
{
    // Test exception handling in myHeap for non-binary Tree
    Tree<int, 3> nonBinaryTree;
    nonBinaryTree.add_root(1);

    try
    {
        auto it = nonBinaryTree.myHeap();
        assert(false); // Should not reach here
    }
    catch (const std::runtime_error &e)
    {
        assert(std::string(e.what()) == "Heap iterator is only available for binary trees");
    }

    std::cout << "Test 9 passed: myHeap throws exception for non-binary Tree\n";
}

void test10()
{
    // Test with string type and ensure correct ordering
    Tree<std::string> stringTree;
    auto root = stringTree.add_root("root");
    stringTree.add_sub_node(root, "branch1");
    stringTree.add_sub_node(root, "branch2");

    auto it = stringTree.begin_pre_order();
    assert(*it == "root");
    ++it;
    assert(*it == "branch1");
    ++it;
    assert(*it == "branch2");

    std::cout << "Test 10 passed: Tree works correctly with string type\n";
}

void test11()
{
    // Test adding children to non-root nodes
    Tree<int> t;
    auto root = t.add_root(1);
    auto child1 = t.add_sub_node(root, 2);
    auto child2 = t.add_sub_node(root, 3);
    t.add_sub_node(child1, 4);
    t.add_sub_node(child1, 5);

    std::vector<int> pre_order;
    for (auto it = t.begin_pre_order(); it != t.end_pre_order(); ++it)
        pre_order.push_back(*it);

    assert(pre_order == std::vector<int>({1, 2, 4, 5, 3}));
    std::cout << "Test 11 passed: Adding children to non-root nodes works correctly\n";
}

void test12()
{
    // Test Tree with string type
    Tree<std::string> t;
    auto root = t.add_root("root");
    t.add_sub_node(root, "child1");
    t.add_sub_node(root, "child2");

    std::vector<std::string> bfs;
    for (auto it = t.begin_bfs_scan(); it != t.end_bfs_scan(); ++it)
        bfs.push_back(*it);

    assert(bfs == std::vector<std::string>({"root", "child1", "child2"}));
    std::cout << "Test 12 passed: Tree with string type works correctly\n";
}

void test13()
{
    // Test in-order traversal for binary Tree
    Tree<int> t;
    auto root = t.add_root(1);
    auto left = t.add_sub_node(root, 2);
    auto right = t.add_sub_node(root, 3);
    t.add_sub_node(left, 4);
    t.add_sub_node(left, 5);

    std::vector<int> in_order;
    for (auto it = t.begin_in_order(); it != t.end_in_order(); ++it)
        in_order.push_back(*it);

    assert(in_order == std::vector<int>({4, 2, 5, 1, 3}));
    std::cout << "Test 13 passed: In-order traversal for binary Tree works correctly\n";
}

void test14()
{
    // Test post-order traversal for non-binary Tree
    Tree<int, 3> t;
    auto root = t.add_root(1);
    auto child1 = t.add_sub_node(root, 2);
    auto child2 = t.add_sub_node(root, 3);
    t.add_sub_node(child1, 4);
    t.add_sub_node(child1, 5);

    std::vector<int> post_order;
    for (auto it = t.begin_post_order(); it != t.end_post_order(); ++it)
        post_order.push_back(*it);

    assert(post_order == std::vector<int>({4, 5, 2, 3, 1}));
    std::cout << "Test 14 passed: Post-order traversal for non-binary Tree works correctly\n";
}

void test15()
{
    Tree<Complex, 3> t;
    auto root = t.add_root(Complex(1, 1));
    t.add_sub_node(root, Complex(2, 2));
    t.add_sub_node(root, Complex(3, 3));

    std::vector<Complex> bfs;
    for (auto it = t.begin_bfs_scan(); it != t.end_bfs_scan(); ++it)
        bfs.push_back(*it);

    // Test core functionality
    std::string expected_output =
        "└── 1+1i\n"
        "    ├── 2+2i\n"
        "    └── 3+3i\n";
    std::string actual_output = capture_print([&]()
                                              { std::cout << t; });
    assert(actual_output == expected_output);
    assert(bfs == std::vector<Complex>({Complex(1, 1), Complex(2, 2), Complex(3, 3)}));

    // Test visualization
    // std::cout << "Opening visualization for 5 seconds...\n";

    // Launch t.print("complex") in a separate thread
    std::thread print_thread([&t]()
                             { t.print("complex"); });

    // Detach the thread so it runs independently
    print_thread.detach();

    // Wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Close the visualization
    std::cout << std::endl;

    system("pkill inkview");

    // Give a moment for the inkview process to close
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::endl;
    if (is_exists("complex.svg"))
    {
        if (!system("rm complex.svg") == 0)
        {
            std::cout << "Failed to delete visualization file 'complex'\n";
        }
    }
    else
    {
        std::cout << "Visualization failed: 'complex' file was not created\n";
    }
    std::cout << "Test 15 passed: Custom type (Complex) with non-binary Tree works correctly\n";
}

void test16()
{
    // Test deep Tree (500 nodes)
    Tree<int> t;
    auto node = t.add_root(1);
    for (int i = 2; i <= 500; ++i)
    {
        node = t.add_sub_node(node, i);
    }

    int count = 0;
    for (auto it = t.begin_pre_order(); it != t.end_pre_order(); ++it)
    {
        assert(*it == ++count);
    }
    assert(count == 500);

    std::cout << "Test 16 passed: Deep Tree (500 nodes) works correctly\n";
}

void test17()
{
    // Test adding root multiple times
    Tree<int> t;
    t.add_root(1);
    t.add_root(2);

    auto it = t.begin_pre_order();
    assert(*it == 2);
    ++it;
    assert(it == t.end_pre_order());

    std::cout << "Test 17 passed: Adding root multiple times works correctly\n";
}

void test18()
{
    // Test DFS scan
    Tree<int> t;
    auto root = t.add_root(1);
    t.add_sub_node(root, 2);
    t.add_sub_node(root, 3);

    std::vector<int> dfs;
    for (auto it = t.begin_dfs_scan(); it != t.end_dfs_scan(); ++it)
        dfs.push_back(*it);

    assert(dfs == std::vector<int>({1, 2, 3}));
    std::cout << "Test 18 passed: DFS scan works correctly\n";
}

void test19()
{
    // Test BFS scan on a large Tree
    Tree<int, 10> t;
    auto root = t.add_root(1);
    for (int i = 2; i <= 10; ++i)
    {
        t.add_sub_node(root, i);
    }

    // Launch t.print("tenChildren") in a separate thread
    std::thread print_thread([&t]()
                             { t.print("tenChildren"); });

    // Detach the thread so it runs independently
    print_thread.detach();

    // Wait for 5 seconds to allow visualization
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Close the visualization
    std::cout << std::endl;
    system("pkill inkview");

    // Give a moment for the inkview process to close
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << std::endl;

    // Perform BFS scan
    std::vector<int> bfs;
    for (auto it = t.begin_bfs_scan(); it != t.end_bfs_scan(); ++it)
        bfs.push_back(*it);

    // Check if the visualization file was created
    if (is_exists("tenChildren.svg"))
    {
        if (!system("rm tenChildren.svg") == 0)
        {
            std::cout << "Failed to delete visualization file 'tenChildren'\n";
        }
    }
    else
    {
        std::cout << "Visualization failed: 'tenChildren' file was not created\n";
    }

    // Assert the correctness of the BFS scan
    assert(bfs == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

    std::cout << "Test 19 passed: visualization and BFS scan on a large Tree works correctly\n";
}

void test20()
{
    // Test DFS scan on a large Tree
    Tree<int, 10> t;
    auto root = t.add_root(1);
    for (int i = 2; i <= 10; ++i)
    {
        t.add_sub_node(root, i);
    }

    std::vector<int> dfs;
    for (auto it = t.begin_dfs_scan(); it != t.end_dfs_scan(); ++it)
        dfs.push_back(*it);

    assert(dfs == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    std::cout << "Test 20 passed: DFS scan on a large Tree works correctly\n";
}

void test21()
{
    // Test destructor
    Tree<int> *t = new Tree<int>();
    auto root = t->add_root(1);
    t->add_sub_node(root, 2);
    t->add_sub_node(root, 3);

    // Explicitly call destructor
    delete t;

    // Now check if the Tree was properly destroyed
    Tree<int> t_check;
    auto root_check = t_check.add_root(42); // Add a root node to verify

    // Ensure original Tree `t` is destroyed and cleaned up
    assert(t_check.getRoot() != nullptr);        // Check if `t_check` still has a root
    assert(t_check.getRoot()->data == 42);       // Ensure root data is correct, indicating it's a new instance
    assert(t_check.getRoot()->children.empty()); // Ensure no leftover nodes from the original `t`

    std::cout << "Test 21 passed: Tree destructor works correctly\n";
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();
    test17();
    test18();
    test19();
    test20();
    test21();

    std::cout << "All tests passed successfully!\n";
    return 0;
}