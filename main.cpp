#include <iostream>
#include "functions.h"
using namespace std;
int main() {
    Graph graph;
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 15);
    cout << "Edge cost from 1 to 2:" << graph.getEdgeCost(1, 2) << endl;
    cout << "Edge cost from 1 to 3:" << graph.getEdgeCost(1, 3) << endl;
    graph.updateNode(2, 4);
    cout << "Edge cost from 1 to 4 after update:" << graph.getEdgeCost(1, 4) << endl;
    graph.deleteNode(4);
    cout << "Edge cost from 1 to 4 after deleting node 4: " << graph.getEdgeCost(1, 4) << endl;
    cout << "Final node count: " << graph.getNodeCount() << endl;
    return 0;

}
