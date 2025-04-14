/*
  Author: Norman Cervantes
  Course: CS310 – Programming with C++
  Assignment: Ch05Exercise33 – Revised Submission
  Description:
    Calculates how many full dishes Bianca can prepare based on the time
    required for the first dish, incremental time per dish, and total time available.
*/


#include <iostream>

int main() {
    int firstDishTime = 0;
    int timeIncrease = 0;
    int availableTime = 0;

    std::cout << "Enter the time required for the first dish: ";
    std::cin >> firstDishTime;

    if (firstDishTime <= 0) {
        std::cout << "Time must be a positive value.\n";
        return 1;
    }

    std::cout << "Enter the extra time added for each new dish: ";
    std::cin >> timeIncrease;

    if (timeIncrease < 0) {
        std::cout << "Extra time cannot be negative.\n";
        return 1;
    }

    std::cout << "Enter the total available time: ";
    std::cin >> availableTime;

    if (availableTime <= 0) {
        std::cout << "Total time must be positive.\n";
        return 1;
    }

    int timeSpent = 0;
    int dishCounter = 0;

    while (true) {
        int currentDishTime = firstDishTime + dishCounter * timeIncrease;
        if (timeSpent + currentDishTime > availableTime) {
            break;
        }
        timeSpent += currentDishTime;
        dishCounter++;
    }

    std::cout << "Bianca can make " << dishCounter << " full dishes.\n";
    return 0;
}

