#include <iostream>
#include "functions.h"

using namespace std;

int main() {
        MyArray<int> arr1;
        arr1.append(1);
        arr1.append(2);
        arr1.append(3);
        arr1.prepend(0);
    arr1.deleteFromStart();
    arr1.display();
        arr1.deleteFromEnd();
        arr1.display();
    return 0;
}
