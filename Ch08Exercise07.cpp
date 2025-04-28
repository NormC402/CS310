/*
    Norman Cervantes
    CS 310
    Module 7 Assignment
*/

/*
This program collects 5 candidates' last names and vote counts, then calculates vote percentages, determines the winner (or identifies a tie) with robust input validation and error handling.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>

struct Candidate {
    std::string name;
    int votes;
};

// Parse a string to an integer vote count, using stringstream for validation
int parseVotes(const std::string& input) {
    // Trim leading and trailing whitespace from the input string
    size_t start = input.find_first_not_of(" \t\n\r\f\v");
    size_t end = input.find_last_not_of(" \t\n\r\f\v");
    std::string trimmed = (start == std::string::npos) ? "" : input.substr(start, end - start + 1);
    if (trimmed.empty()) {
        throw std::invalid_argument("empty input");
    }
    // Use stringstream to attempt to parse an integer from the trimmed string
    std::stringstream ss(trimmed);
    int value;
    ss >> value;
    if (ss.fail()) {
        throw std::invalid_argument("non-numeric input");
    }
    ss >> std::ws;  // Skip any remaining whitespace
    if (!ss.eof()) {
        // If there are any non-whitespace characters left, the input was not a pure number
        throw std::invalid_argument("extra characters");
    }
    if (value < 0) {
        throw std::invalid_argument("negative number");
    }
    return value;
}

int main() {
    const int NUM_CANDIDATES = 5;
    std::vector<Candidate> candidates;
    candidates.resize(NUM_CANDIDATES);
    // Input 5 candidates' data with validation
    for (int i = 0; i < NUM_CANDIDATES; ++i) {
        // Get candidate last name (ensure it's not empty)
        while (true) {
            std::cout << "Enter last name for candidate #" << i + 1 << ": ";
            std::string name;
            std::getline(std::cin, name);
            // Note: std::string is guaranteed to have a null terminator at the end of its data in C++11 and later.
            // Trim whitespace for validation
            size_t start = name.find_first_not_of(" \t\n\r\f\v");
            size_t end = name.find_last_not_of(" \t\n\r\f\v");
            std::string trimmedName = (start == std::string::npos) ? "" : name.substr(start, end - start + 1);
            if (trimmedName.empty()) {
                std::cout << "Name cannot be empty. Please enter a valid last name.\n";
            }
            else {
                candidates[i].name = trimmedName;
                break;
            }
        }
        // Get votes (ensure it's a non-negative integer)
        while (true) {
            std::cout << "Enter votes received by " << candidates[i].name << ": ";
            std::string votesInput;
            std::getline(std::cin, votesInput);
            try {
                candidates[i].votes = parseVotes(votesInput);
                break;
            }
            catch (const std::invalid_argument& e) {
                // If parseVotes threw an invalid_argument, print error and retry
                std::cout << "Invalid input (" << e.what() << "). Please enter a non-negative integer.\n";
            }
            catch (const std::exception& e) {
                // Catch-all for any other exceptions
                std::cout << "Error: " << e.what() << ". Try again.\n";
            }
        }
    }
    // Calculate total votes
    long totalVotes = 0;
    for (const Candidate& c : candidates) {
        totalVotes += c.votes;
    }
    // Output each candidate's results and percentage of total votes
    std::cout << "\nElection Results:\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const Candidate& c : candidates) {
        double percent = (totalVotes > 0) ? (double)c.votes / totalVotes * 100.0 : 0.0;
        // Calculate percentage (avoid division by zero if totalVotes is 0)
        std::cout << c.name << " - " << c.votes << " votes - " << percent << "% of total\n";
    }
    std::cout << "Total votes: " << totalVotes << "\n";
    // Determine the winner or if there is a tie for the highest vote count
    if (totalVotes > 0) {
        // Find the maximum votes received by any candidate
        int maxVotes = candidates[0].votes;
        for (const Candidate& c : candidates) {
            if (c.votes > maxVotes) {
                maxVotes = c.votes;
            }
        }
        // Collect all candidates who have the max vote count (to check for ties)
        std::vector<std::string> winners;
        for (const Candidate& c : candidates) {
            if (c.votes == maxVotes) {
                winners.push_back(c.name);
            }
        }
        if (winners.size() == 1) {
            std::cout << "Winner: " << winners[0] << " with " << maxVotes << " votes.\n";
        }
        else {
            std::cout << "Tie between ";
            // If multiple winners, list their names separated by commas and "and"
            for (size_t idx = 0; idx < winners.size(); ++idx) {
                if (idx == 0) {
                    std::cout << winners[idx];
                }
                else if (idx == winners.size() - 1) {
                    std::cout << " and " << winners[idx];
                }
                else {
                    std::cout << ", " << winners[idx];
                }
            }
            std::cout << " - each with " << maxVotes << " votes.\n";
        }
    }
    else {
        std::cout << "No votes were cast, so there is no winner.\n";
    }
    return 0;
}
