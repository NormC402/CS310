#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double netBalance, payment, interestRatePerMonth;
    int d1, d2;

    cout << "Enter net balance: ";
    cin >> netBalance;

    cout << "Enter payment amount: ";
    cin >> payment;

    cout << "Enter number of days in billing cycle (d1): ";
    cin >> d1;

    cout << "Enter number of days before cycle payment was made (d2): ";
    cin >> d2;

    cout << "Enter interest rate per month: ";
    cin >> interestRatePerMonth;

    double averageDailyBalance = (netBalance * d1 - payment * d2) / d1;
    double interest = averageDailyBalance * interestRatePerMonth;

    cout << fixed << setprecision(2);
    locale loc("");
    cout.imbue(loc);

    cout << "Interest on unpaid balance: $" << interest << endl;

    return 0;
}
