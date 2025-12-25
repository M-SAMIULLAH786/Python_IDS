#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
using namespace std;

class Node {
private:
    int data;
    Node* next;

public:
    Node(int data, Node* next = nullptr) : data(data), next(next) {}
    int getData() { return data; }
    void setData(int data) { this->data = data; }
    Node* getNext() { return next; }
    void setNext(Node* next) { this->next = next; }
};
class List {
private:
    Node* head;       // Pointer to the first node
    Node* tail;       // Pointer to the last node
    int count;        // Number of elements in the list

public:
    // Constructor
    List() : head(nullptr), tail(nullptr), count(0) {}

    // Destructor
    ~List() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->getNext();
            delete temp;
        }
    }

    // Check if the list is empty
    bool isEmpty() {
        return count == 0;
    }

    // Add a new node at the end of the list
    void append(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->setNext(newNode);
            tail = newNode;
        }
        count++;
    }

    // Add a new node at the start of the list
    void prepend(int data) {
        Node* newNode = new Node(data, head);
        if (isEmpty()) {
            tail = newNode;
        }
        head = newNode;
        count++;
    }

    // Insert a node at the specified index
    void insertAtIndex(int data, int index) {
        if (index < 0 || index > count) {
            cout << "Index out of bounds." << endl;
            return;
        }

        if (index == 0) {
            prepend(data);
        } else if (index == count) {
            append(data);
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->getNext();
            }
            Node* newNode = new Node(data, current->getNext());
            current->setNext(newNode);
            count++;
        }
    }

    // Delete the last node
    void deleteFromEnd() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->getNext() != tail) {
                current = current->getNext();
            }
            delete tail;
            tail = current;
            tail->setNext(nullptr);
        }
        count--;
    }

    // Delete the first node
    void deleteFromStart() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        head = head->getNext();
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        count--;
    }

    // Delete the node at the specified index
    void deleteFromIndex(int index) {
        if (index < 0 || index >= count) {
            cout << "Index out of bounds." << endl;
            return;
        }

        if (index == 0) {
            deleteFromStart();
        } else if (index == count - 1) {
            deleteFromEnd();
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->getNext();
            }
            Node* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            count--;
        }
    }

    // Get the head pointer
    Node* getHead() const {
        return head;
    }

    Node* getTail() const {
        return tail;
    }


    // Print the list
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->getData() << " -> ";
            current = current->getNext();
        }
        cout << "null" << endl;
    }
};


#endif
