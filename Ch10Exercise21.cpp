/*
Name: Norman Cervantes
Course: CS 310
Assignment: Module 8 - Bank Account System
Approach: Polymorphic Account classes (base and derived with interest) using static unique IDs. Menu manages up to 10 accounts with deposit/withdraw (limit $800) operations, monthly interest, sorting, searching, and transaction history.
*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>

// Base Account class - abstract because of pure virtual functions.
class Account {
protected:
    inline static int next_account_number = 1000; // static counter for unique account numbers
    int account_number;
    double balance;
    std::vector<std::string> history; // transaction history logs
    // Protected helper to add an entry to the history
    void add_history(const std::string& entry) {
        history.push_back(entry);
    }
public:
    // Constructor to initialize account with a starting balance (default 0.0)
    Account(double initial_balance = 0.0) : balance(initial_balance) {
        account_number = ++next_account_number; // generate unique account number
        // Log initial deposit if non-zero initial balance
        if (initial_balance != 0.0) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2);
            oss << "Initial deposit: +$" << initial_balance
                << " -> Balance: $" << balance;
            add_history(oss.str());
        }
    }
    // Virtual destructor for safe polymorphic deletion
    virtual ~Account() {}
    // Accessors
    int get_account_number() const {
        return account_number;
    }
    double get_balance() const {
        return balance;
    }
    // Deposit money into the account. Returns true if successful.
    virtual bool deposit(double amount) {
        if (amount <= 0) {
            // Invalid deposit amount (must be positive)
            return false;
        }
        balance += amount;
        // Log deposit in history
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Deposit: +$" << amount << " -> Balance: $" << balance;
        add_history(oss.str());
        return true;
    }
    // Withdraw money from the account. Returns true if successful.
    virtual bool withdraw(double amount) {
        if (amount <= 0) {
            // Withdrawal amount must be positive
            return false;
        }
        if (amount > 800) {
            // Exceeds per-transaction withdrawal limit
            return false;
        }
        if (amount > balance) {
            // Insufficient balance to withdraw
            return false;
        }
        balance -= amount;
        // Log withdrawal in history
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Withdrawal: -$" << amount << " -> Balance: $" << balance;
        add_history(oss.str());
        return true;
    }
    // Print the transaction history for this account.
    void print_history() const {
        if (history.empty()) {
            std::cout << "No transactions yet." << std::endl;
        }
        else {
            std::cout << "Transaction history for Account " << account_number << ":\n";
            for (const std::string& entry : history) {
                std::cout << "  " << entry << std::endl;
            }
        }
    }
    // Pure virtual function to get the account type (to be defined by derived classes)
    virtual std::string get_account_type() const = 0;
    // Pure virtual function to accrue monthly interest (defined by derived classes)
    virtual void accrue_interest() = 0;
    // Virtual function to get interest rate (default 0 for base or non-interest accounts, override if applicable)
    virtual double get_interest_rate() const {
        return 0.0;
    }
};

// Derived class for a Checking Account (no interest accrual)
class CheckingAccount : public Account {
public:
    // Constructor: call base class constructor to set initial balance
    CheckingAccount(double initial_balance = 0.0) : Account(initial_balance) {}
    // Override accrue_interest: Checking accounts have no interest, so do nothing
    void accrue_interest() override {
        // No interest for checking account
    }
    // Override get_account_type: return a string identifying this as a checking account
    std::string get_account_type() const override {
        return "Checking";
    }
    // get_interest_rate is inherited (returns 0.0 by default)
};

// Derived class for a Savings Account (earns interest monthly)
class SavingsAccount : public Account {
private:
    double interest_rate; // annual interest rate in decimal (e.g., 0.05 for 5%)
public:
    // Constructor: call base class constructor for initial balance, set interest rate
    SavingsAccount(double initial_balance = 0.0, double rate = 0.0)
        : Account(initial_balance), interest_rate(rate) {
    }
    // Override accrue_interest: apply monthly interest to balance
    void accrue_interest() override {
        if (interest_rate <= 0 || balance <= 0) {
            // No interest to accrue if rate is zero or balance is zero
            return;
        }
        // Calculate monthly interest amount (annual rate divided by 12)
        double interest_amount = balance * (interest_rate / 12.0);
        if (interest_amount == 0) {
            // If interest is too small to affect balance (rounding to cents)
            return;
        }
        balance += interest_amount;
        // Log interest accrual in history
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "Interest: +$" << interest_amount << " -> Balance: $" << balance;
        add_history(oss.str());
    }
    // Override get_account_type: return a string identifying this as a savings account
    std::string get_account_type() const override {
        return "Savings";
    }
    // Override get_interest_rate to return the interest rate for this savings account
    double get_interest_rate() const override {
        return interest_rate;
    }
};

// Global storage for accounts: up to 10 accounts
static std::unique_ptr<Account> accounts[10];
static int account_count = 0;

// Utility function to find an account by account number. Returns pointer or nullptr if not found.
Account* find_account_by_number(int acct_num) {
    for (int i = 0; i < account_count; ++i) {
        if (accounts[i] && accounts[i]->get_account_number() == acct_num) {
            return accounts[i].get();
        }
    }
    return nullptr;
}

// Helper for safe integer input
int input_int() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Helper for safe double input
double input_double() {
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

int main() {
    std::cout << "Welcome to the Bank Account System\n";
    bool running = true;
    while (running) {
        // Display menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Create new account\n";
        std::cout << "2. Deposit into account\n";
        std::cout << "3. Withdraw from account\n";
        std::cout << "4. Apply monthly interest to all accounts\n";
        std::cout << "5. Display all accounts\n";
        std::cout << "6. Sort accounts by balance\n";
        std::cout << "7. Search account by account number\n";
        std::cout << "8. Show transaction history for an account\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        int choice = input_int();
        std::cout << std::endl;
        switch (choice) {
        case 1: {
            if (account_count >= 10) {
                std::cout << "Cannot create more accounts (maximum 10 reached).\n";
                break;
            }
            // Account creation
            std::cout << "Select account type (1 for Checking, 2 for Savings): ";
            int type_choice = input_int();
            if (type_choice != 1 && type_choice != 2) {
                std::cout << "Invalid account type selection.\n";
                break;
            }
            std::cout << "Enter initial deposit amount: ";
            double initial_deposit = input_double();
            if (initial_deposit < 0) {
                std::cout << "Initial deposit cannot be negative. Using $0.00.\n";
                initial_deposit = 0.0;
            }
            if (type_choice == 1) {
                // Create CheckingAccount
                accounts[account_count] = std::make_unique<CheckingAccount>(initial_deposit);
                std::cout << "Created Checking Account #" << accounts[account_count]->get_account_number()
                    << " with balance $" << std::fixed << std::setprecision(2)
                    << accounts[account_count]->get_balance() << ".\n";
            }
            else {
                // Create SavingsAccount (need interest rate)
                std::cout << "Enter annual interest rate (as decimal, e.g., 0.05 for 5%): ";
                double rate = input_double();
                if (rate < 0) {
                    std::cout << "Interest rate cannot be negative. Using 0.\n";
                    rate = 0.0;
                }
                accounts[account_count] = std::make_unique<SavingsAccount>(initial_deposit, rate);
                std::cout << "Created Savings Account #" << accounts[account_count]->get_account_number()
                    << " with balance $" << std::fixed << std::setprecision(2)
                    << accounts[account_count]->get_balance()
                    << " and interest rate " << rate << ".\n";
            }
            account_count++;
            break;
        }
        case 2: {
            // Deposit
            if (account_count == 0) {
                std::cout << "No accounts available. Please create an account first.\n";
                break;
            }
            std::cout << "Enter account number to deposit into: ";
            int acct_num = input_int();
            Account* acc = find_account_by_number(acct_num);
            if (!acc) {
                std::cout << "Account #" << acct_num << " not found.\n";
                break;
            }
            std::cout << "Enter amount to deposit: ";
            double amount = input_double();
            if (!acc->deposit(amount)) {
                std::cout << "Deposit failed. Amount must be positive.\n";
            }
            else {
                std::cout << "Deposited $" << std::fixed << std::setprecision(2) << amount
                    << " into account #" << acc->get_account_number()
                    << ". New balance: $" << std::fixed << std::setprecision(2)
                    << acc->get_balance() << ".\n";
            }
            break;
        }
        case 3: {
            // Withdraw
            if (account_count == 0) {
                std::cout << "No accounts available. Please create an account first.\n";
                break;
            }
            std::cout << "Enter account number to withdraw from: ";
            int acct_num = input_int();
            Account* acc = find_account_by_number(acct_num);
            if (!acc) {
                std::cout << "Account #" << acct_num << " not found.\n";
                break;
            }
            std::cout << "Enter amount to withdraw: ";
            double amount = input_double();
            if (!acc->withdraw(amount)) {
                if (amount <= 0) {
                    std::cout << "Withdrawal failed. Amount must be positive.\n";
                }
                else if (amount > 800) {
                    std::cout << "Withdrawal failed. Amount exceeds $800 limit per transaction.\n";
                }
                else if (amount > acc->get_balance()) {
                    std::cout << "Withdrawal failed. Insufficient balance.\n";
                }
                else {
                    std::cout << "Withdrawal failed due to unknown error.\n";
                }
            }
            else {
                std::cout << "Withdrew $" << std::fixed << std::setprecision(2) << amount
                    << " from account #" << acc->get_account_number()
                    << ". New balance: $" << std::fixed << std::setprecision(2)
                    << acc->get_balance() << ".\n";
            }
            break;
        }
        case 4: {
            // Apply interest to all accounts
            if (account_count == 0) {
                std::cout << "No accounts available.\n";
                break;
            }
            std::cout << "Applying monthly interest to all applicable accounts...\n";
            for (int i = 0; i < account_count; ++i) {
                accounts[i]->accrue_interest();
            }
            std::cout << "Monthly interest applied.\n";
            break;
        }
        case 5: {
            // Display all accounts
            if (account_count == 0) {
                std::cout << "No accounts to display.\n";
            }
            else {
                std::cout << "Account List:\n";
                std::cout << std::fixed << std::setprecision(2);
                for (int i = 0; i < account_count; ++i) {
                    Account* acc = accounts[i].get();
                    std::string type = acc->get_account_type();
                    double bal = acc->get_balance();
                    std::cout << "  #" << acc->get_account_number() << " (" << type << ") - Balance: $"
                        << bal;
                    double rate = acc->get_interest_rate();
                    if (rate > 0) {
                        std::cout << ", Rate: " << rate;
                    }
                    std::cout << std::endl;
                }
            }
            break;
        }
        case 6: {
            // Sort accounts by balance and display
            if (account_count < 2) {
                std::cout << "Need at least 2 accounts to sort.\n";
            }
            else {
                std::sort(accounts, accounts + account_count, [](const std::unique_ptr<Account>& a, const std::unique_ptr<Account>& b) {
                    if (!a || !b) return false;
                    return a->get_balance() < b->get_balance();
                    });
                std::cout << "Accounts sorted by balance (ascending):\n";
                std::cout << std::fixed << std::setprecision(2);
                for (int i = 0; i < account_count; ++i) {
                    Account* acc = accounts[i].get();
                    std::cout << "  #" << acc->get_account_number() << " - $" << acc->get_balance()
                        << " (" << acc->get_account_type() << ")\n";
                }
            }
            break;
        }
        case 7: {
            // Search by account number
            if (account_count == 0) {
                std::cout << "No accounts available.\n";
                break;
            }
            std::cout << "Enter account number to search: ";
            int acct_num = input_int();
            Account* acc = find_account_by_number(acct_num);
            if (!acc) {
                std::cout << "Account #" << acct_num << " not found.\n";
            }
            else {
                std::cout << "Account found: #" << acc->get_account_number() << " ("
                    << acc->get_account_type() << ") - Balance: $"
                    << std::fixed << std::setprecision(2) << acc->get_balance();
                double rate = acc->get_interest_rate();
                if (rate > 0) {
                    std::cout << ", Interest Rate: " << rate;
                }
                std::cout << std::endl;
            }
            break;
        }
        case 8: {
            // Show transaction history
            if (account_count == 0) {
                std::cout << "No accounts available.\n";
                break;
            }
            std::cout << "Enter account number to view history: ";
            int acct_num = input_int();
            Account* acc = find_account_by_number(acct_num);
            if (!acc) {
                std::cout << "Account #" << acct_num << " not found.\n";
            }
            else {
                acc->print_history();
            }
            break;
        }
        case 9: {
            // Exit
            std::cout << "Exiting program. Goodbye!\n";
            running = false;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please select a valid option.\n";
            break;
        }
        }
    }
    return 0;
}
