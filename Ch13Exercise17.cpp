/*
Name: Norman Cervantes
Course: CS 310
Assignment: Module 11 Assignment
Description: Uses C++11 <random> (mt19937, uniform_real_distribution) to generate 25 unique random floats between 10 and 100; demonstrates custom generator logic, error handling, and formatted output.
*/
#include <iostream>
#include <random>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <exception>

int main() {
    // Initialize Mersenne Twister random number engine with a random seed
    std::mt19937 engine;
    try {
        std::random_device rd;            // Non-deterministic random device for true randomness
        engine.seed(rd());               // Seed the engine with the random device
    }
    catch (const std::exception& e) {
        // If std::random_device is unavailable or throws, fall back to a time-based seed
        std::cerr << "Warning: std::random_device failed (" << e.what()
            << "), using time(0) as seed.\n";
        engine.seed(static_cast<unsigned long>(std::time(nullptr)));
    }

    // Define a uniform real distribution for doubles in the range [10, 100)
    std::uniform_real_distribution<double> dist(10.0, 100.0);

    // Custom functor (callable object) to generate unique random numbers using the above engine and distribution
    struct UniqueRandomGenerator {
        std::mt19937& eng;
        std::uniform_real_distribution<double>& distribution;
        std::unordered_set<double> seen; // Stores numbers that have been generated so far

        UniqueRandomGenerator(std::mt19937& e, std::uniform_real_distribution<double>& d)
            : eng(e), distribution(d) {
        }

        double operator()() {
            // Generate numbers until a unique one is found
            double value;
            do {
                value = distribution(eng);
            } while (seen.find(value) != seen.end());
            // Record the new unique number and return it
            seen.insert(value);
            return value;
        }
    };

    UniqueRandomGenerator uniqueGen(engine, dist);
    // Generate 25 unique random doubles and store them in a vector
    std::vector<double> numbers(25);
    std::generate(numbers.begin(), numbers.end(), std::ref(uniqueGen));

    // Display the 25 numbers in a formatted output (5 numbers per line, 2 decimal places)
    std::cout << "25 unique random floats between 10 and 100:\n";
    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << std::setw(8) << numbers[i];
        if ((i + 1) % 5 == 0)
            std::cout << '\n';
    }

    return 0;
}
