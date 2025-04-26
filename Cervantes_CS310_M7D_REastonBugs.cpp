#include <iostream>
using namespace std;

int main() {
    int testScores[3][2];

    for (int i = 0; i < 3; i++) // fixed loop bound and increment operator
    {
        cout << "Enter test score 1 for student " << i + 1 << ": ";
        cin >> testScores[i][0];

        cout << "Enter test score 2 for student " << i + 1 << ": ";
        cin >> testScores[i][1];
    }

    for (int i = 0; i < 3; i++)
    {
        cout << "Student #" << i + 1 << " scores: ";
        cout << testScores[i][0] << " and " << testScores[i][1] << endl; // fixed indexing syntax and added missing semicolon
    }

    return 0;
}
