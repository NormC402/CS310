/*
Author: Norman Cervantes
Course: CS310
Assignment: Vowel Remover
*/

/*
Approach: Read a full line, validate it, then extract non‑vowel segments via substr to build the result.
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

// Test a character for vowel membership (case‑insensitive)
bool is_vowel_char(char c)
{
    char low = std::tolower(static_cast<unsigned char>(c));
    return (low == 'a' || low == 'e' || low == 'i' ||
        low == 'o' || low == 'u');
}

// C++ std::string always stores a null terminator internally.
// If it were missing, any substr or append would be undefined behavior.

// Remove all vowels from 'source' by slicing out the non‑vowel runs
std::string remove_vowels_from(const std::string& source)
{
    std::string result;
    std::size_t start_index = 0;
    std::size_t total_len = source.length();

    // Scan each character; when we hit a vowel, append the prior run
    for (std::size_t i = 0; i < total_len; ++i) {
        if (is_vowel_char(source[i])) {
            if (i > start_index) {
                // take the substring of non‑vowels
                result.append(source.substr(start_index, i - start_index));
            }
            start_index = i + 1;  // skip over this vowel
        }
    }

    // Append any trailing non‑vowel characters
    if (start_index < total_len) {
        result.append(source.substr(start_index));
    }

    return result;
}

int main()
{
    std::cout << "Please type a line and press ENTER:\n";
    std::string input_line;

    // Read the entire line (including spaces)
    if (!std::getline(std::cin, input_line)) {
        std::cerr << "Error: failed to read input.\n";
        return EXIT_FAILURE;
    }

    // Handle case: user just pressed ENTER
    if (input_line.empty()) {
        std::cerr << "Error: no text entered.\n";
        return EXIT_FAILURE;
    }

    // Perform vowel removal
    std::string output_line = remove_vowels_from(input_line);

    // Handle case: string had no vowels at all
    if (output_line == input_line) {
        std::cout << "No vowels found; output unchanged:\n"
            << output_line << '\n';
    }
    // Handle case: every character was a vowel
    else if (output_line.empty()) {
        std::cout << "All characters were vowels; result is empty.\n";
    }
    // Normal case: some vowels removed
    else {
        std::cout << "Text without vowels:\n"
            << output_line << '\n';
    }

    return EXIT_SUCCESS;
}
