/*
Name: Norman Cervantes
Course: CS310
Assignment: Exercise 07‑04 – Vowel Filter
*/

/*
Plan: Read a full line input, validate emptiness, then scan and copy segments without vowels using substr calls to generate the filtered string.
*/

#include <iostream>
#include <string>
#include <cctype>

// Return true if c is one of A, E, I, O or U (case‑insensitive)
bool letter_vowel(char c)
{
    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    switch (lower)
    {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        return true;
    default:
        return false;
    }
}

// Generate a new string omitting every vowel found in src
// Note: std::string handles its own termination; we just rely on size() here.
std::string filter_vowels(const std::string& src)
{
    std::string result;
    size_t segment_start = 0;

    // Walk through each character index in src
    for (size_t i = 0; i < src.size(); ++i)
    {
        if (letter_vowel(src[i]))
        {
            // Copy everything from segment_start up to (but not including) this vowel
            if (i > segment_start)
                result += src.substr(segment_start, i - segment_start);

            // Jump past the vowel for the next segment
            segment_start = i + 1;
        }
    }

    // Copy any trailing text after the final vowel
    if (segment_start < src.size())
        result += src.substr(segment_start);

    return result;
}

auto main() -> int
{
    std::cout << "Enter text and press ENTER:\n";
    std::string user_text;

    // Read the full line (spaces allowed)
    if (!std::getline(std::cin, user_text))
    {
        std::cerr << "Error reading input.\n";
        return 1;
    }

    // Handle empty submission
    if (user_text.empty())
    {
        std::cerr << "No text entered; exiting.\n";
        return 1;
    }

    // Remove vowels
    std::string cleaned = filter_vowels(user_text);

    // All‑vowel case yields empty result
    if (cleaned.empty())
    {
        std::cout << "Result is empty (all characters were vowels).\n";
    }
    // No vowels found leaves text unchanged
    else if (cleaned == user_text)
    {
        std::cout << "No vowels removed. Text stays the same:\n"
            << cleaned << '\n';
    }
    // Normal case: some vowels removed
    else
    {
        std::cout << "Filtered text (no vowels):\n"
            << cleaned << '\n';
    }

    return 0;
}
