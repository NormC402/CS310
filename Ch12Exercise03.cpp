#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

int main() {
    /* Norman Cervantes, CS 310, Module 10 Assignment
     *
     * This program dynamically allocates arrays for candidate names and votes,
     * validates user input (non-empty names containing vowels, non-negative integer votes),
     * logs input errors, computes voting statistics, and outputs election results.
     */

     // Open error log file for logging invalid inputs
    std::ofstream log_file("error_log.txt");
    if (!log_file) {
        std::cerr << "Unable to open error_log.txt for writing." << std::endl;
        return 1;
    }

    // Prompt user for the number of candidates and validate the input
    int candidate_count = 0;
    std::string input_str;
    while (true) {
        std::cout << "Enter the number of candidates: ";
        std::getline(std::cin, input_str);
        // Remove leading/trailing whitespace from input
        size_t first = input_str.find_first_not_of(" \t\n\r\f\v");
        size_t last = input_str.find_last_not_of(" \t\n\r\f\v");
        std::string trimmed = (first == std::string::npos ? "" : input_str.substr(first, last - first + 1));
        if (trimmed.empty()) {
            // No input given
            log_file << "Invalid input for number of candidates (empty input)." << std::endl;
            std::cout << "Error: Number of candidates cannot be blank. Please try again." << std::endl;
            continue;
        }
        // Convert to integer with error checking
        try {
            size_t idx;
            long val = std::stol(trimmed, &idx); // using stol to allow larger range if needed
            if (idx != trimmed.size()) {
                // Some non-numeric characters present
                log_file << "Invalid input for number of candidates ('" << trimmed << "' contains non-numeric characters)." << std::endl;
                std::cout << "Error: Please enter a valid integer for the number of candidates." << std::endl;
                continue;
            }
            if (val <= 0) {
                log_file << "Invalid number of candidates (" << val << " is not a positive integer)." << std::endl;
                std::cout << "Error: Number of candidates must be a positive integer." << std::endl;
                continue;
            }
            // If value is very large beyond int range, also treat as error
            if (val > std::numeric_limits<int>::max()) {
                log_file << "Invalid input for number of candidates (value " << val << " out of range for int)." << std::endl;
                std::cout << "Error: Number of candidates is too large. Please enter a smaller number." << std::endl;
                continue;
            }
            candidate_count = static_cast<int>(val);
            break; // valid input obtained
        }
        catch (const std::invalid_argument& ia) {
            // No conversion could be performed
            log_file << "Invalid input for number of candidates ('" << trimmed << "' is not an integer)." << std::endl;
            std::cout << "Error: Please enter a valid integer for the number of candidates." << std::endl;
        }
        catch (const std::out_of_range& oor) {
            // Number outside the range of long (very unlikely for reasonable input)
            log_file << "Invalid input for number of candidates ('" << trimmed << "' is out of range)." << std::endl;
            std::cout << "Error: Number of candidates is too large. Please enter a smaller number." << std::endl;
        }
    }

    // Dynamically allocate arrays to hold candidate names and votes
    std::string* candidate_names = new std::string[candidate_count];
    int* candidate_votes = new int[candidate_count];

    // Input candidate names and votes with validation
    for (int i = 0; i < candidate_count; ++i) {
        // Prompt for candidate last name with validation
        while (true) {
            std::cout << "Enter last name for candidate #" << (i + 1) << ": ";
            std::string name;
            std::getline(std::cin, name);
            // Trim whitespace
            size_t first = name.find_first_not_of(" \t\n\r\f\v");
            size_t last = name.find_last_not_of(" \t\n\r\f\v");
            std::string trimmed_name = (first == std::string::npos ? "" : name.substr(first, last - first + 1));
            if (trimmed_name.empty()) {
                log_file << "Candidate " << (i + 1) << ": Empty last name entered." << std::endl;
                std::cout << "Error: Last name cannot be empty. Please try again." << std::endl;
                continue;
            }
            // Check that name contains at least one vowel (a, e, i, o, u or uppercase)
            std::string vowels = "aeiouAEIOU";
            bool has_vowel = (trimmed_name.find_first_of(vowels) != std::string::npos);
            if (!has_vowel) {
                log_file << "Candidate " << (i + 1) << ": Last name '" << trimmed_name << "' has no vowels." << std::endl;
                std::cout << "Error: Last name must contain at least one vowel (A, E, I, O, U). Please try again." << std::endl;
                continue;
            }
            // If we reach here, the name is valid
            candidate_names[i] = trimmed_name;
            break;
        }

        // Prompt for vote count with validation
        while (true) {
            std::cout << "Enter votes received by " << candidate_names[i] << ": ";
            std::string votes_str;
            std::getline(std::cin, votes_str);
            // Trim whitespace
            size_t first = votes_str.find_first_not_of(" \t\n\r\f\v");
            size_t last = votes_str.find_last_not_of(" \t\n\r\f\v");
            std::string trimmed_votes = (first == std::string::npos ? "" : votes_str.substr(first, last - first + 1));
            if (trimmed_votes.empty()) {
                log_file << "Candidate " << (i + 1) << " (" << candidate_names[i] << "): Empty vote count entered." << std::endl;
                std::cout << "Error: Vote count cannot be empty. Please enter a non-negative integer." << std::endl;
                continue;
            }
            // Use std::stoi to parse integer and validate the entire string:contentReference[oaicite:0]{index=0}
            try {
                size_t idx;
                int votes = std::stoi(trimmed_votes, &idx);
                if (idx != trimmed_votes.size()) {
                    // Extra characters after number (e.g., letters) found
                    log_file << "Candidate " << (i + 1) << " (" << candidate_names[i] << "): Invalid vote input '" << trimmed_votes << "' (non-integer characters present)." << std::endl;
                    std::cout << "Error: Please enter a valid integer for votes." << std::endl;
                    continue;
                }
                if (votes < 0) {
                    log_file << "Candidate " << (i + 1) << " (" << candidate_names[i] << "): Invalid vote count " << votes << " (negative value)." << std::endl;
                    std::cout << "Error: Vote count cannot be negative. Please enter a non-negative integer." << std::endl;
                    continue;
                }
                candidate_votes[i] = votes;
                break;
            }
            catch (const std::invalid_argument& ia) {
                log_file << "Candidate " << (i + 1) << " (" << candidate_names[i] << "): Invalid vote input '" << trimmed_votes << "' (not a number)." << std::endl;
                std::cout << "Error: Please enter a valid integer for votes." << std::endl;
            }
            catch (const std::out_of_range& oor) {
                log_file << "Candidate " << (i + 1) << " (" << candidate_names[i] << "): Invalid vote input '" << trimmed_votes << "' (number out of range)." << std::endl;
                std::cout << "Error: Vote count is too large. Please enter a smaller integer value." << std::endl;
            }
        }
    }

    // Calculate total votes and percentage of total for each candidate
    long total_votes = 0;
    for (int i = 0; i < candidate_count; ++i) {
        total_votes += candidate_votes[i];
    }
    // Note: If using char arrays for names, ensure the last character is '\0' to terminate the string.
    // C++11 std::string is guaranteed to be null-terminated in its internal array:contentReference[oaicite:1]{index=1}, so we rely on that property.

    // Determine the candidate(s) with the maximum votes
    int max_votes = -1;
    for (int i = 0; i < candidate_count; ++i) {
        if (candidate_votes[i] > max_votes) {
            max_votes = candidate_votes[i];
        }
    }
    // Count how many candidates have max_votes (to detect tie)
    int winner_count = 0;
    for (int i = 0; i < candidate_count; ++i) {
        if (candidate_votes[i] == max_votes) {
            winner_count++;
        }
    }

    // Output election results
    std::cout << "\nElection Results:\n";
    std::cout << "-----------------\n";
    std::cout << "Candidate\tVotes Received\t% of Total Votes\n";
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);
    for (int i = 0; i < candidate_count; ++i) {
        double percent = 0.0;
        if (total_votes > 0) {
            percent = (static_cast<double>(candidate_votes[i]) / total_votes) * 100.0;
        }
        std::cout << candidate_names[i] << "\t\t" << candidate_votes[i] << "\t\t";
        std::cout << percent << "%\n";
    }
    std::cout << "Total Votes: " << total_votes << std::endl;

    if (winner_count == 1) {
        // Find the single winner
        for (int i = 0; i < candidate_count; ++i) {
            if (candidate_votes[i] == max_votes) {
                std::cout << "Winner: " << candidate_names[i] << std::endl;
                break;
            }
        }
    }
    else {
        // There is a tie for the top number of votes
        std::cout << "Result: No single winner - a tie between ";
        // List all candidates who tied for first place
        bool first_name_printed = false;
        for (int i = 0; i < candidate_count; ++i) {
            if (candidate_votes[i] == max_votes) {
                if (first_name_printed) {
                    std::cout << ", ";
                }
                std::cout << candidate_names[i];
                first_name_printed = true;
            }
        }
        std::cout << " with " << max_votes << " votes each." << std::endl;
    }

    // Clean up dynamic memory (delete allocated arrays):contentReference[oaicite:2]{index=2}
    delete[] candidate_names;
    delete[] candidate_votes;
    candidate_names = nullptr;
    candidate_votes = nullptr;
    log_file.close();

    return 0;
}
