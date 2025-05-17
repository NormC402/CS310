// Created by Norman Cervantes
// CS310 - Module 10 Discussion

#include <iostream>
#include <string>

using namespace std;

int main() {
    int numbers[3] = { 10, 20, 30 };
    int* ptr = numbers;

    for (int i = 0; i < 3; ++i) {
        cout << "Value at index " << i << ": " << *(ptr + i) << endl;
    }

    int* uninitializedPtr;
    cout << "Random value: " << *uninitializedPtr << endl;

    string name = "Norman";
    void* genericPtr = &name;
    genericPtr++;

    double* ratePtr = &missingRate;

    string message = "Module 10 complete"

        return 0;
}

