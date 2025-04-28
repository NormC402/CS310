#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

/*
Author: Norman Cervantes
Course: CS 310
Assignment: Module 6 Assignment

Description: This program reads a string from the user, uses the substr function
to build a new string without vowels, and outputs the result with appropriate
error handling.
*/

// Function to determine if a character is a vowel (case-insensitive)
bool isVowelCharacter(char ch) {
    // Convert character to lowercase for uniform comparison
    char lowerCh = std::tolower(static_cast<unsigned char>(ch));
    // Check if the character is one of the vowels (a, e, i, o, u)
    return (lowerCh == 'a' || lowerCh == 'e' || lowerCh == 'i' || lowerCh == 'o' || lowerCh == 'u');
}

// Function to remove all vowels from the given string using substr
std::string removeVowelsFromText(const std::string& input) {
    std::ostringstream oss;
    size_t lastIndex = 0;
    // Iterate over each character to find vowels
    for (size_t i = 0; i < input.length(); ++i) {
        if (isVowelCharacter(input[i])) {
            // Append the substring from lastIndex up to the character before this vowel
            oss << input.substr(lastIndex, i - lastIndex);
            // Skip the current vowel by moving lastIndex past this character
            lastIndex = i + 1;
        }
    }
    // Append any remaining characters after the last vowel
    if (lastIndex < input.length()) {
        oss << input.substr(lastIndex);
    }
    // The resulting string in the stream is the input string with vowels removed
    std::string result = oss.str();
    // Ensure the result string is null-terminated (std::string handles this automatically)
    // (std::string stores a '\0' at the end of its character array by default)
    return result;
}

// Function to handle user input retrieval
std::string getInputString() {
    std::string userInput;
    std::cout << "Enter a string: " << std::flush;
    std::getline(std::cin, userInput);
    return userInput;
}

// Function to validate the input string for errors (e.g., empty string)
void validateInput(const std::string& str) {
    if (str.empty()) {
        // Throw an exception if the input string is empty
        throw std::invalid_argument("Input string is empty.");
    }
    // (Optional) Check if the string contains only whitespace characters
    bool allSpaces = true;
    for (char ch : str) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            allSpaces = false;
            break;
        }
    }
    if (allSpaces) {
        throw std::invalid_argument("Input string is empty (only whitespace).");
    }
}

// Function to display the result to the user
void displayResult(const std::string& original, const std::string& modified) {
    if (original == modified) {
        // If original equals modified, either there were no vowels or the string was empty
        if (original.empty()) {
            // This case should be handled by validation before this point
            std::cout << "No input provided." << std::endl;
        }
        else {
            // No vowels were removed (because none were found in the input)
            std::cout << "No vowels were found in the input string." << std::endl;
            std::cout << "Output (unchanged): " << modified << std::endl;
        }
    }
    else {
        // Vowels were removed successfully, output the modified string
        std::cout << "String after removing vowels: " << modified << std::endl;
    }
}

int main() {
    try {
        // Execute main program logic within a try block to handle exceptions
        // Get input from the user
        std::string input = getInputString();

        // Validate the input string (check for empty or whitespace-only string)
        validateInput(input);

        // Remove all vowels from the input text using the helper function
        std::string result = removeVowelsFromText(input);

        // Output the result to the user (special handling if no vowels were removed)
        displayResult(input, result);

    }
    catch (const std::exception& ex) {
        // Catch any thrown exceptions (e.g., empty input)
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
