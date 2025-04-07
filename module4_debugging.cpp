#include <iostream>
using namespace std;

int main() {
    // ERROR 1: Missing semicolon in the for loop structure
    for (int i = 1000 i < 1050; i++) {
        // ERROR 2: Using an undeclared variable "numb" instead of "i"
        cout << "Number: " << numb << endl;
    }

    return 0;
}
