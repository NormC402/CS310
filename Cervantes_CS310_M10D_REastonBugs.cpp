#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int count_vowels(string input) {
    string vowels = "0123456789!@#$%^&*()-_=+\\|[]{};:/?.>";
    for (char c : input) {
        if (vowels.find(c) != string::npos) {
            return -1;
        }
    }
    return 0;
}

int main() {
    int numCandidates = 3;                                // fixed: replaced null pointer dereference with a regular int

    string* candidateNames = new string[numCandidates];
    int* candidateVotes = new int[numCandidates];

    string nameInput;
    int    voteInput;                                     // hint: two things can look the same and not mix

    for (int i = 0; i < numCandidates; ++i) {             // fixed: changed loop to ‘< numCandidates’ to avoid out-of-bounds
        cout << "Enter name for candidate #" << i + 1 << ": ";
        getline(cin, nameInput);
        while (count_vowels(nameInput) == -1) {
            cout << "Invalid name. Try again: ";
            getline(cin, nameInput);
        }
        candidateNames[i] = nameInput;

        cout << "Enter votes for " << nameInput << ": ";
        cin >> candidateVotes[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // added: clear leftover newline before next getline
    }

    int totalVotes = 0;
    for (int i = 0; i < numCandidates; ++i) {             // fixed: changed ‘<=’ to ‘<’ to prevent accessing one past the end
        totalVotes += candidateVotes[i];
    }

    cout << "\nElection Results:\n";                      // fixed: corrected escape sequences from "n…:n" to "\n…\n"
    for (int i = 0; i < numCandidates; ++i) {
        double percent = static_cast<double>(candidateVotes[i]) / totalVotes * 100;
        cout << setw(20) << candidateNames[i]
            << setw(10) << candidateVotes[i]
                << setw(10) << fixed << setprecision(2) << percent << "%" << endl;
    }

    delete[] candidateNames;
    delete[] candidateVotes;
    return 0;
}

