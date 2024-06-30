#include "tree.hpp"
#include "Complex.hpp"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    
    system("echo 'digraph {fontname=\"Arial\"node [fontname=\"Arial\"]edge [fontname=\"Arial\"]graph [rankdir = \"up\"];node [fontsize = \"16\"shape = \"circle\"];edge [shape = \"record\"];\"node0\":f0 -> \"node1\":f0 [id = 0];\"node0\":f1 -> \"node2\":f0 [id = 1];}' | dot -Tsvg > output1.svg");
    system("inkview output1.svg");
    QApplication app(argc, argv);

    // Create a main window
    QMainWindow window;
    window.setWindowTitle("Tree Visualization");
    window.resize(1800, 1600);

    // Integer tree example
    tree<int> intTree;
    auto root = intTree.add_root(1);
    intTree.add_sub_node(root, 2);
    intTree.add_sub_node(root, 3);

    std::cout << "Integer Tree:" << std::endl;
    intTree.print();

    // Display the tree using Qt
    intTree.printQT(&window);

    window.show();
    return app.exec();
}