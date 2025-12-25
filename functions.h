#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
using namespace std;


template <typename T>
class MyArray {
private:
    T* data;
    int size;
    int capacity;


public:
    MyArray();//constructor
    ~MyArray();//destructor
    void append(T value);//Add function to add an element at the last index of the array
    void prepend(T value);// Add function to add an element at the start index of the array
    void deleteFromEnd();// Add function to contract an array by deleting a value from the last index
    void deleteFromStart();// Add function to contract an array by deleting a value from the first index
    void display() const;// Add function to display the elements of the array
    void resize(int newCapacity);
    int get_size() const;//getsizeofarray
    int get_capacity() const;
    T* get_array() const;
};
template <typename T>
int MyArray<T>::get_size()const {
    return size;
}
template <typename T>
int MyArray<T>::get_capacity() const {
    return capacity;
}
template <typename T>
T* MyArray<T>::get_array()const {
    return data;
}

template <typename T>
MyArray<T>::MyArray() {
    size=0;
    capacity=15;
    data =new T[capacity];
}
template <typename T>
MyArray<T>::~MyArray() {
    delete[] data;
}
template <typename T>
void MyArray<T>::append(T value) {
    if (size==capacity) {
        resize(capacity*2);
    }
    data[size]=value;
    ++size;
}
template <typename T>
void MyArray<T>::prepend(T value) {
    if (size==capacity) {
        resize(capacity*2);
    }
    for (int i=size; i>0;--i) {
        data[i]=data[i-1];
    }
    data[0]=value;
    ++size;
}
template <typename T>
void MyArray<T>::deleteFromEnd() {
    if(size>0) {
        --size;
    }
}
template <typename T>
void MyArray<T>::deleteFromStart() {
    if (size>0){
        for(int i=0; i<size-1; ++i) {
            data[i]=data[i+1];
        }
        --size;
    }
}
template <typename T>
void MyArray<T>::display() const{
    for (int i=0; i<size;++i) {
        cout<<data[i]<<", ";
    }
    cout<<endl;
}
template <typename T>
void MyArray<T>::resize(int newCapacity) {
    T* temp= new T[newCapacity];
    for (int i=0; i<size; ++i) {
        temp[i]=data[i];
    }
    delete[] data;
    data=temp;
    capacity=newCapacity;
}




#endif
