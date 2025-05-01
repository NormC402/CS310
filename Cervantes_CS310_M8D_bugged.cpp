#include <iostream>
#include <vector>
#include <string>

using namespace std;

// CLASS 1: BankAccount
class BankAccount {
private:
    string ownerName;
    double balance;
public:
    BankAccount(string name, double initialBalance) {
        ownerName = name;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount.\n";
    }

    void withdraw(double amount) {
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

    string getOwner() const {
        return ownerName;
    }

    void printInfo() const {
        cout << "Account Owner: " << ownerName << ", Balance: $" << balance << endl;
    }
};

// CLASS 2: TransactionLogger
class TransactionLogger {
private:
    vector<string> logs;
public:
    void logTransaction(string description) {
        logs.push_back(description);
    }

    void printLogs() const {
        for (int i = 0; i <= logs.size(); i++) {
            cout << logs[i] << endl;
        }
    }

    totalTransactions() const {
        return logs.size();
    }
};

int main() {
    BankAccount acc("Norman", 500.00);
    TransactionLogger logger;

    acc.deposit(150.0);
    logger.logTransaction("Deposited $150");

    acc.withdraw(700.0);  
    logger.logTransaction("Withdrew $700");

    acc.printInfo();
    logger.printLogs();

    cout << "Total Transactions: " << logCount << endl;

    return 0;
}
