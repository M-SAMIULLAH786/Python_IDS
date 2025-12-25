#include <iostream>
#include "functions.h" // Assumes Node and List class are defined here
using namespace std;

// Function to print the linked list
void printList(const List& list) {
    Node* current = list.getHead();
    while (current) {
        cout << current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;
}

int main() {
    List list;

    // Append elements to the list
    list.append(10);
    list.append(20);
    list.append(30);
    cout << "List after appending 10, 20, 30:" << endl;
    printList(list);

    // Prepend an element to the list
    list.prepend(5);
    cout << "List after prepending 5:" << endl;
    printList(list);

    // Insert an element at a specific index
    list.insertAtIndex(15, 2);
    cout << "List after inserting 15 at index 2:" << endl;
    printList(list);

    // Delete the last element
    list.deleteFromEnd();
    cout << "List after deleting from end:" << endl;
    printList(list);

    // Delete the first element
    list.deleteFromStart();
    cout << "List after deleting from start:" << endl;
    printList(list);

    // Delete an element at a specific index
    list.deleteFromIndex(1);
    cout << "List after deleting from index 1:" << endl;
    printList(list);

    return 0;
}

