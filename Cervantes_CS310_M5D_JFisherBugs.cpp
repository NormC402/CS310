

#include <iostream>
#include <string>

using namespace std;

// Function declarations
double power(int a, int b);
double fact(int a);
double sum(int a, int b);
double diff(int a, int b);

int main() {
    int user_input;

    cout << "\n\n  Welcome to my mathematics program. Please enter only positive numbers.";
    cout << "\n  What would you like to do?";
    cout << "\n  1. Power: a^b";
    cout << "\n  2. Factorial of a";
    cout << "\n  3. Sum: a + b";
    cout << "\n  4. Difference: a - b" << endl << "  ";
    cin >> user_input;

    switch (user_input) {
    case 1: {
        int a, b;
        cout << "\n  Enter an integer for a: ";
        cin >> a;
        cout << "  Enter an integer for b: ";
        cin >> b;
        cout << "\n  " << a << " to the power of " << b << " is " << power(a, b);
        break;
    }
    case 2: {
        int a;
        cout << "\n  Enter an integer for a: ";
        cin >> a;
        cout << "\n  The factorial of " << a << " is " << fact(a);
        break;
    }
    case 3: {
        int a, b;
        cout << "\n  Enter an integer for a: ";
        cin >> a;
        cout << "  Enter an integer for b: ";
        cin >> b;
        cout << "\n  " << a << " plus " << b << " is " << sum(a, b);
        break; //  Correction: Added missing break
    }
    case 4: {
        int a, b;
        cout << "\n  Enter an integer for a: ";
        cin >> a;
        cout << "  Enter an integer for b: ";
        cin >> b;
        cout << "\n  " << a << " minus " << b << " is " << diff(a, b);
        break;
    }
    default:
        cout << "\n  Invalid option. Please enter a number between 1 and 4.";
    }

    cout << "\n\n  Press Enter to exit...";
    cin.ignore();
    cin.get(); //  Correction: Replaced _getch() with cin.get()
    return 0;
}

double power(int a, int b) {
    double result = 1;
    for (int i = 1; i <= b; i++) { //  Correction: Fixed for-loop syntax
        result *= a;
    }
    return result;
}

double fact(int a) {
    double result = 1;
    for (int i = 1; i <= a; i++) { //  Correction: Moved i++ to for-loop
        result *= i;
    }
    return result;
}

double sum(int a, int b) {
    return a + b; //  Correction: Removed unnecessary initialization
}

double diff(int a, int b) {
    return a - b; // Correction: Removed unnecessary initialization
}
