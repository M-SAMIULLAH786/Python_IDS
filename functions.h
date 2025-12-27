#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
using namespace std;

class Edge {
    int destination;
    int cost;
    Edge* next;

public:
    Edge(int dest, int c) : destination(dest), cost(c), next(nullptr) {

    }
    int getDestination() const {
      return destination;
    }
    int getCost() const {
      return cost;
    }
    Edge* getNext() const {
      return next;
    }

    void setNext(Edge* nextEdge) {
      next = nextEdge;
    }
    void setDestination(int dest) {
      destination = dest;
    }
};

class Node {
  private:
    int data;
    Node* next;
    Edge* edges;
    int edgeCount;

public:
    Node(int val) : data(val), next(nullptr), edges(nullptr), edgeCount(0) {}

    int getData() const {
      return data;
    }
    Node* getNext() const {
      return next;
    }
    Edge* getEdges() const {
      return edges;
    }
    int getEdgeCount() const {
      return edgeCount;
    }

    void setNext(Node* nextNode) {
      next = nextNode;
    }
    void setEdges(Edge* edgeList) {
      edges = edgeList;
    }
    void incrementEdgeCount() {
      edgeCount++;
    }
    void decrementEdgeCount() {
        edgeCount--;
    }
    void setData(int value) {
      data = value;
    }
};

class Graph {
    Node* nodes;
    int nodeCount;

public:
    Graph() : nodes(nullptr), nodeCount(0) {

    }
    void addNode(int nodeValue) {
        if (!hasNode(nodeValue)) {
            Node* newNode = new Node(nodeValue);
            newNode->setNext(nodes);
            nodes = newNode;
            nodeCount++;
        }
    }
    void addEdge(int source, int destination, int cost) {
        Node* sourceNode = findNode(source);
        Node* destinationNode = findNode(destination);
        Edge* edge;
        edge = sourceNode->getEdges();
        while (edge) {
            if (edge->getDestination() == destination)
              return;
            edge = edge->getNext();
        }
        Edge* newEdge;
        newEdge = new Edge(destination, cost);
        newEdge->setNext(sourceNode->getEdges());
        sourceNode->setEdges(newEdge);
        sourceNode->incrementEdgeCount();
    }
    int getEdgeCost(int source, int destination) const {
        Node* sourceNode = findNode(source);
        if (sourceNode) {
            Edge* edge = sourceNode->getEdges();
            while (edge) {
                if (edge->getDestination() == destination) return edge->getCost();
                edge = edge->getNext();
            }
        }
        return -1;
    }
    int getEdgeCountForNode(int nodeValue) const {
        Node* node;
        node = findNode(nodeValue);
        if (node) {
            return node->getEdgeCount();
        } else {
            return -1;
        }
    }
    int getNodeCount() const {
      return nodeCount;
    }
    void updateNode(int oldValue, int newValue) {
        if (hasNode(newValue)){
          return;
        }
        Node* node = findNode(oldValue);
        if (node) {
            node->setData(newValue);
            Node* currentNode = nodes;
            while (currentNode) {
                Edge* edge = currentNode->getEdges();
                while (edge) {
                    if (edge->getDestination() == oldValue) edge->setDestination(newValue);
                    edge = edge->getNext();
                }
                currentNode = currentNode->getNext();
            }
        }
    }
    void deleteNode(int nodeValue) {
        Node* prevNode = nullptr;
        Node* currentNode = nodes;
        while (currentNode && currentNode->getData() != nodeValue) {
            prevNode = currentNode;
            currentNode = currentNode->getNext();
        }
        if (!currentNode){
          return;
          }

        if (prevNode) {
            prevNode->setNext(currentNode->getNext());
        } else {
            nodes = currentNode->getNext();
        }
        Edge* edge = currentNode->getEdges();
        while (edge) {
            Edge* tempEdge = edge;
            edge = edge->getNext();
            delete tempEdge;
        }
        delete currentNode;
        nodeCount--;
        Node* otherNode = nodes;
        while (otherNode) {
            deleteEdge(otherNode->getData(), nodeValue);
            otherNode = otherNode->getNext();
        }
    }
    bool hasNode(int nodeValue) const {
      return findNode(nodeValue) != nullptr;
    }
    void deleteEdge(int source, int destination) {
        Node* sourceNode = findNode(source);
        if (!sourceNode){
          return;
          }
        Edge* prevEdge = nullptr;
        Edge* currentEdge = sourceNode->getEdges();
        while (currentEdge && currentEdge->getDestination() != destination) {
            prevEdge = currentEdge;
            currentEdge = currentEdge->getNext();
        }
        if (currentEdge) {
            if (prevEdge) {
                prevEdge->setNext(currentEdge->getNext());
            } else {
                sourceNode->setEdges(currentEdge->getNext());
            }
            delete currentEdge;
            sourceNode->decrementEdgeCount();
        }
    }
    Node* findNode(int value) const {
        Node* current = nodes;
        while (current) {
            if (current->getData() == value){
              return current;
              }
            current = current->getNext();
        }
        return nullptr;
    }
};


#endif
