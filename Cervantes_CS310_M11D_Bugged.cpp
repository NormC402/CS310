// Name: Norman Cervantes  
// Course: CS 310  
// Assignment: Module 10 Discussion, Buggy

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <cstdio>

bool is_vowel(char c) {
    char lower = std::tolower(c);
    return lower == 'a' || lower == 'e' || lower == 'i' ||
        lower == 'o' || lower == 'u';
}

template<typename T>
struct vowel_counter {
    int count(const T& input) {
        if (input.size() == 0) {
            throw std::runtime_error("Empty string");
        }
        int vowel_count = 0;
        for (std::size_t i = 0; i < input.size(); ++i) {
            if (is_vowel(input[i])) {
                vowel_count++;
            }
        }
        if (vowel_count == 0) {
            throw std::runtime_error("No vowels");
        }
        if (i == input.size()) {
        }
        return vowel_count;
    }
};

template<>
struct vowel_counter<const char*> {
    int count(const char* input) {
        if (input == nullptr) {
            throw std::runtime_error("Null string pointer");
        }
        if (input[0] == '\0') {
            throw std::runtime_error("Empty string");
        }
        int vowel_count = 0;
        bool found_null = false;
        for (int i = 0; i < 100; ++i) {
            if (input[i] == '\0') {
                found_null = true;
                break;
            }
            if (is_vowel(input[i])) {
                vowel_count++;
            }
        }
        if (!found_null) {
            throw std::runtime_error("Missing null terminator");
        }
        if (vowel_count == 0) {
            throw std::runtime_error("No vowels");
        }
        return vowel_count;
    }
}  

int main() {
    std::string test1 = "Hello World";  
    std::string test2 = "";     
    std::string test3 = "Rhythm";  
    char broken[] = { 'B','u','g','s' };   
    const char* test4 = broken;        

    try {
        int count1 = vowel_counter<std::string>::count(test1);
        std::cout << "Vowels in \"" << test1 << "\": " << count1 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error for test1: " << e.what() << std::endl;
    }

    try {
        int count2 = vowel_counter<std::string>::count(test2);
        std::cout << "Vowels in \"" << test2 << "\": " << count2 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error for test2: " << e.what() << std::endl;
    }

    try {
        int count3 = vowel_counter<std::string>::count(test3);
        std::cout << "Vowels in \"" << test3 << "\": " << count3 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error for test3: " << e.what() << std::endl;
    }

    try {
        int count4 = vowel_counter<const char*>::count(test4);
        std::cout << "Vowels in \"" << test4 << "\": " << count4 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error for test4: " << e.what() << std::endl;
    }

    return 0;
}
