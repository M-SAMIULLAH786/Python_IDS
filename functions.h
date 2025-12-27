#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
using namespace std;

class Stack {
private:
    int* array;      // Pointer to the dynamic array
    int size;        // Current size of the stack
    int capacity;    // Current capacity of the stack

public:
    // Constructor
    Stack() {
        capacity = 10;            // Initial capacity of the stack
        size = 0;                 // Stack initially empty
        array = new int[capacity]; // Allocate memory for the stack
    }

    // Destructor
    ~Stack() {
        delete[] array; // Free the allocated memory
    }

    // Check if the stack is empty
    bool isEmpty() {
        return size == 0;
    }

    // Push an element onto the stack
    void push(int data) {
        if (size == capacity) {
            // Double the capacity if the array is full
            int newCapacity = capacity * 2;
            int* newArray = new int[newCapacity];

            // Copy existing elements to the new array
            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }

            // Free old array and update capacity
            delete[] array;
            array = newArray;
            capacity = newCapacity;
        }

        // Add the new element and update size
        array[size] = data;
        size++;
    }

    // Pop the top element from the stack
    void pop() {
        if (isEmpty()) {
            cout << "Error: Stack is empty, cannot pop!" << endl;
            return;
        }

        // Remove the top element
        size--;

        // Shrink the array if necessary
        if (size <= capacity / 4 && capacity > 10) {
            int newCapacity = capacity / 2;
            int* newArray = new int[newCapacity];

            // Copy existing elements to the new array
            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }

            // Free old array and update capacity
            delete[] array;
            array = newArray;
            capacity = newCapacity;
        }
    }

    // Get the number of elements in the stack
    int getSize() {
        return size;
    }

    // Clear all elements from the stack
    void clear() {
        size = 0;
    }

    // Print all elements in the stack from top to bottom
    void printStack() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return;
        }

        for (int i = size - 1; i >= 0; i--) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    // Access the internal array (added for testing)
    int* getStack() {
        return array;
    }
};


class Queue {
private:
    int* array;
    int size;
    int capacity;
    int front;
    int rear;

public:

    Queue() : size(0), capacity(10), front(0), rear(0) {
        array = new int[capacity];
    }

    ~Queue() {
        delete[] array;
    }

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(int data) {
        if (size >= capacity) {
            cout << "Queue is full " << data  <<endl;
            return;
        }
        array[size] = data;
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
           cout<< "Queue is empty." << endl;
            return;
        }
        for (int i = 0; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        size--;
    }


    int getSize() {
        return size;
    }
int *getQueue() {
  return array;
}
    void printQueue() {
        for (int i = front; i < front + size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
    void clear() {
        size = 0;
    }
};


#endif
