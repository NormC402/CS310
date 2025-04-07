#include <iostream>
using namespace std;

int main() {
    int a, b, t;
    int totalTime = 0;
    int dishCount = 0;

    // Ask the user to enter the starting time for the first dish
    cout << "How many minutes does the first dish take? ";
    cin >> a;

    // Ask how much more time each next dish takes
    cout << "How many extra minutes does each next dish need? ";
    cin >> b;

    // Ask how much time Bianca has in total
    cout << "How many total minutes does Bianca have? ";
    cin >> t;

    // Keep making dishes as long as there's enough time
    while (totalTime + a + (dishCount * b) <= t) {
        totalTime += a + (dishCount * b);
        dishCount++;
    }

    // Show how many dishes Bianca can finish
    cout << "Bianca can make " << dishCount << " dishes in the time she has." << endl;

    return 0;
}
