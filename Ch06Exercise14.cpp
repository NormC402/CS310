#include <iostream>

// Function to calculate billing amount based on income and consulting time
double computeBilling(double hourlyRate, int minutes, double income) {
    double billingAmount = 0.0;
    bool isLowIncome = income <= 25000;
    int freeTime = isLowIncome ? 30 : 20;
    double ratePercent = isLowIncome ? 0.4 : 0.7;

    if (minutes > freeTime) {
        int extraMinutes = minutes - freeTime;
        billingAmount = hourlyRate * ratePercent * (extraMinutes / 60.0);
    }

    return billingAmount;
}

int main() {
    double hourlyRate;
    int consultingMinutes;
    double income;

    std::cout << "Enter the hourly rate: ";
    std::cin >> hourlyRate;

    std::cout << "Enter the consulting time (in minutes): ";
    std::cin >> consultingMinutes;

    std::cout << "Enter your income: ";
    std::cin >> income;

    // Call function to compute how much the person owes
    double amountDue = computeBilling(hourlyRate, consultingMinutes, income);

    std::cout << "The billing amount is: $" << amountDue << std::endl;

    return 0;
}
