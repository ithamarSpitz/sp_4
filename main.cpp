#include "Tree.hpp"
#include "Complex.hpp"


int main(int argc, char *argv[]) {
    // Integer tree example
    Tree<int> intTree;
    auto root = intTree.add_root(1);
    intTree.add_sub_node(root, 2);
    intTree.add_sub_node(root, 3);
    std::cout << "Integer Tree:" << std::endl;
    std::cout << intTree << std::endl;
}