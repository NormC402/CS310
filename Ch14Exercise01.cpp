#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

// Custom exception for negative number input
class negative_number : public exception {
public:
    const char* what() const noexcept override {
        return "Negative number entered. Only non-negative values are allowed.";
    }
};

// Custom exception for non-numeric input
class non_number : public exception {
public:
    const char* what() const noexcept override {
        return "Non-numeric input entered. Please enter numeric values only.";
    }
};

/*
Name: Norman Cervantes
Course: CS 310
Assignment: Module 12 Assignment
*/

/*
Solution Approach:
Prompts user for feet and inches, validating input through custom exceptions. Uses loops to limit attempts and converts the valid input to centimeters for output.
*/

// Function to prompt and get a non-negative numeric input (feet or inches).
double get_non_negative_input(const string& prompt) {
    string line;
    double value;
    // Loop for up to 5 attempts for a valid input
    for (int attempt = 1; attempt <= 5; ++attempt) {
        cout << prompt;
        cout.flush();  // ensure prompt is displayed immediately
        if (!getline(cin, line)) {
            // End-of-file or other input error encountered.
            throw runtime_error("Input stream error or EOF encountered.");
        }
        try {
            // Check if the input line is empty or only whitespace
            if (line.find_first_not_of(" \t\r\n") == string::npos) {
                // No actual characters (user just pressed Enter or input only spaces)
                throw non_number();
            }
            size_t pos;
            // Try to convert the line to a double value
            value = stod(line, &pos);
            // Skip any trailing whitespace characters after the number
            while (pos < line.length() && isspace(static_cast<unsigned char>(line[pos]))) {
                pos++;
            }
            // If there are leftover characters that are not whitespace, input is invalid
            if (pos != line.length()) {
                throw non_number();
            }
            // Check for negative value
            if (value < 0) {
                throw negative_number();
            }
            // Valid input: return the value
            return value;
        }
        catch (const non_number& e) {
            cerr << e.what() << endl;
        }
        catch (const negative_number& e) {
            cerr << e.what() << endl;
        }
        catch (const invalid_argument&) {
            // stod couldn't convert the input to a number at all
            cerr << "Non-numeric input entered. Please enter numeric values only." << endl;
        }
        catch (const out_of_range&) {
            // stod converted the number but it is out of range for a double
            cerr << "The number entered is too large. Please enter a smaller value." << endl;
        }
        // If we reach here, the input was invalid. Loop will repeat for another attempt.
        if (attempt == 5) {
            // After 5 unsuccessful attempts, throw an exception to signal too many failures
            throw runtime_error("Too many invalid input attempts.");
        }
        // Otherwise, automatically loop for the next attempt
    }
    // This point should never be reached (we return or throw above).
    throw runtime_error("Unexpected error in input function.");
}

int main() {
    // Constants for conversion factors
    const double CM_PER_INCH = 2.54;
    const int INCHES_PER_FOOT = 12;

    double feet = 0.0;
    double inches = 0.0;
    try {
        // Prompt user for feet and inches using the helper function.
        feet = get_non_negative_input("Enter length - feet: ");
        inches = get_non_negative_input("Enter length - inches: ");
    }
    catch (const runtime_error& e) {
        // Handles too many invalid attempts or input stream errors.
        cerr << e.what() << endl;
        return 1;  // exit with an error code
    }
    catch (const exception& e) {
        // Catch-all for any other exceptions (if any slipped through).
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    // Compute total length in centimeters
    double total_inches = feet * INCHES_PER_FOOT + inches;
    double centimeters = total_inches * CM_PER_INCH;

    // Output the result of conversion
    cout << feet << " feet, " << inches << " inches = " << centimeters << " centimeters." << endl;
    return 0;
}
