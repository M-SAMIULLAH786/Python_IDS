#include <iostream>
#include "functions.h"
using namespace std;

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Push to Stack" << endl;
    cout << "2. Pop from Stack" << endl;
    cout << "3. Display Stack" << endl;
    cout << "4. Enqueue to Queue" << endl;
    cout << "5. Dequeue from Queue" << endl;
    cout << "6. Display Queue" << endl;
    cout << "7. Clear Stack" << endl;
    cout << "8. Clear Queue" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Stack myStack;
    Queue myQueue;
    int choice, data;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push into stack: ";
                cin >> data;
                myStack.push(data);
                cout << "Pushed " << data << " to stack." << endl;
                break;
            case 2:
                if (!myStack.isEmpty()) {
                    myStack.pop();
                    cout << "Popped from stack." << endl;
                }
                break;
            case 3:
                if (!myStack.isEmpty()) {
                    cout << "Stack contents: ";
                    myStack.printStack();
                }
                break;
            case 4:
                cout << "Enter value to enqueue into queue: ";
                cin >> data;
                myQueue.enqueue(data);
                cout << "Enqueued to queue." << endl;
                break;

            case 5:
                if (!myQueue.isEmpty()) {
                    myQueue.dequeue();
                    cout << "Dequeued from queue." << endl;
                }
                break;

            case 6:
                if (!myQueue.isEmpty()) {
                    cout << "Queue contents: ";
                    myQueue.printQueue();
                }
                break;

            case 7:
                myStack.clear();
                cout << "Stack cleared." << endl;
                break;

            case 8:
                myQueue.clear();
                cout << "Queue cleared." << endl;
                break;

            case 9:
                cout << "Exiting lab" << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
