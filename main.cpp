#include <iostream>
#include "functions.h"
using namespace std;


int main() {
    Tree tree;
    tree.insertNode(10);
    tree.insertNode(5);
    tree.insertNode(20);

    cout << "Nodes in the tree: " << endl;
    tree.printTree();
    cout << "Degree of 10: " << tree.getDegree(10) << endl;
    cout << "Degree of 12: " << tree.getDegree(5) << endl;
    cout << "Degree of 20: " << tree.getDegree(20) << endl;
    cout << "Height of the tree: " << tree.getTreeHeight() << endl;
    cout << "Height of node 10: " << tree.getHeight(10) << endl;
    cout << "Height of node 5: " << tree.getHeight(5) << endl;
    cout << "Height of node 20: " << tree.getHeight(20) << endl;


    return 0;
}
