#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class MyArray {
private:
    T* arr1D;
    T** arr2D;
    T*** arr3D;
    int d0, d1, d2;

public:

    T* get1DArray() {
        return arr1D;
    }
    T** get2DArray() {
        return arr2D;
    }
    T*** get3DArray() {
        return arr3D;
    }
    MyArray(int d0, int d1 = 0, int d2 = 0) : d0(d0), d1(d1), d2(d2), arr1D(0), arr2D(0), arr3D(0) {
        if (d1 == 0 && d2 == 0) {
            arr1D = new T[d0];
        } else if (d2 == 0) {
            arr2D = new T*[d1];
            for (int m = 0; m < d1; m++) {
                arr2D[m] = new T[d0];
            }
        } else {
            arr3D = new T**[d2];
            for (int n = 0; n < d2; n++) {
                arr3D[n] = new T*[d1];
                for (int m = 0; m < d1; m++) {
                    arr3D[n][m] = new T[d0];
                }
            }
        }
    }

    // Destructor
    ~MyArray() {
        if (arr1D) {
            delete[] arr1D;
        } else if (arr2D) {
            for (int m = 0; m < d1; m++) {
                delete[] arr2D[m];
            }
            delete[] arr2D;
        } else if (arr3D) {
            for (int n = 0; n < d2; n++) {
                for (int m = 0; m < d1; m++) {
                    delete[] arr3D[n][m];
                }
                delete[] arr3D[n];
            }
            delete[] arr3D;
        }
    }

    // Create method
    static MyArray* create(int d0 = 0, int d1 = 0, int d2 = 0) {
        return new MyArray(d0, d1, d2);
    }

    // Set element
    void setElement(T value, int index0, int index1 = 0, int index2 = 0) {
        if (arr1D) {
            if (index0 >= d0) {
                cout << "Index out of bound";
                return;
            }
            arr1D[index0] = value;
        } else if (arr2D) {
            if (index1 >= d1 || index0 >= d0) {
                cerr << "Index out of bounds";
                return;
            }
            arr2D[index1][index0] = value;
        } else if (arr3D) {
            if (index2 >= d2 || index1 >= d1 || index0 >= d0) {
                cerr << "Index out of bounds";
                return;
            }
            arr3D[index2][index1][index0] = value;
        }
    }

    // Get element
    T getElement(int index0, int index1 = 0, int index2 = 0) const {
        if (arr1D) {
            if (index0 >= d0) {
                cout << "Index out of bounds";
                return T();
            }
            return arr1D[index0];
        } else if (arr2D) {
            if (index1 >= d1 || index0 >= d0) {
                cout << "Index out of bounds!";
                return T();
            }
            return arr2D[index1][index0];
        } else if (arr3D) {
            if (index2 >= d2 || index1 >= d1 || index0 >= d0) {
                cout << "Index out of bounds!";
                return T();
            }
            return arr3D[index2][index1][index0];
        }
        return T();
    }

    // Get dimensions
    int getDimensions() const {
        if (arr1D) {
            return 1;
        } else if (arr2D) {
            return 2;
        } else if (arr3D) {
            return 3;
        }
        return 0;
    }

    // Display array
    void display() const {
        if (arr1D) {
            for (int l = 0; l < d0; l++) {
                cout << arr1D[l] << "\t";
            }
            cout << endl;
        } else if (arr2D) {
            for (int m = 0; m < d1; m++) {
                for (int l = 0; l < d0; l++) {
                    cout << arr2D[m][l] << "\t";
                }
                cout << endl;
            }
        } else if (arr3D) {
            for (int n = 0; n < d2; n++) {
                cout << "Layer " << n + 1 << ":\n";
                for (int m = 0; m < d1; m++) {
                    for (int l = 0; l < d0; l++) {
                        cout << arr3D[n][m][l] << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    T* getRow3D(int r, int l) const {
        if (arr3D && r < d1 && l < d2) {
            return arr3D[l][r];
        }
    }
    void radixSort1D(T* array, int size) {
        T maxval = array[0];
        for (int l = 1; l < size; l++) {
            if (array[l] > maxval) {
                maxval = array[l];
            }
        }
        int maxDigits = 0;
        while (maxval > 0) {
            maxDigits++;
            maxval /= 10;
        }
        T* result = new T[size];

        int exponent = 1;
        for (int d = 0; d < maxDigits; d++) {
            int arr[10] = {0};
            for (int l = 0; l < size; l++) {
                int digit = (array[l] / exponent) % 10;
                arr[digit]++;
            }
            for (int l = 1; l < 10; l++) {
                arr[l] += arr[l - 1];
            }
            for (int l = size - 1; l >= 0; l--) {
                int digit = (array[l] / exponent) % 10;
                result[--arr[digit]] = array[l];
            }
            for (int l = 0; l < size; l++) {
                array[l] = result[l];
            }
            exponent *= 10;
        }
        delete[] result;
    }
void countSort1D(T* array, int size) {
    T maxVal = array[0], minVal = array[0];
    for (int l = 1; l < size; l++) {
        if (array[l] > maxVal) maxVal = array[l];
        if (array[l] < minVal) minVal = array[l];
    }
    int range = maxVal - minVal + 1;
    int* count = new int[range] {0};
    for (int l = 0; l < size; l++) {
        count[array[l] - minVal]++;
    }

    for (int l = 1; l < range; l++) {
        count[l] += count[l - 1];
    }
    T* output = new T[size];
    for (int l = size - 1; l >= 0; l--) {
        count[array[l] - minVal]--;
        int index = count[array[l] - minVal];
        output[index] = array[l];

    }
    for (int l = 0; l < size; l++) {
        array[l] = output[l];
    }

    delete[] count;
    delete[] output;
}

    void radixSort2D() {
        for (int m = 0; m < d1; m++) {
            radixSort1D(arr2D[m], d0);
        }
    }
    void countSort2D() {
        for (int m = 0; m < d1; m++) {
            countSort1D(arr2D[m], d0);
        }
    }

    void radixSort3D() {
        for (int n = 0; n < d2; n++) {
            for (int m = 0; m < d1; m++) {
                radixSort1D(arr3D[n][m], d0);
            }
        }
    }

    void countSort3D() {
        for (int n = 0; n < d2; n++) {
            for (int m = 0; m < d1; m++) {
                countSort1D(arr3D[n][m], d0);
            }
        }
    }
};

#endif
