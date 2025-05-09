#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <cassert>
#include <limits>

// Name: Norman Cervantes
// Course: CS 310
// Assignment: Module 9 Assignment

// Approach: Define a base BankAccount class and derived CheckingAccount and SavingsAccount. 
// Use a factory for account creation. Implement file I/O, menu-driven interface, and exception handling.

class BankingException : public std::exception {
protected:
    std::string message;
public:
    BankingException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept {
        return message.c_str();
    }
};

class InvalidTransactionException : public BankingException {
public:
    InvalidTransactionException(const std::string& msg) : BankingException(msg) {}
};

class InsufficientFundsException : public BankingException {
public:
    InsufficientFundsException(const std::string& msg) : BankingException(msg) {}
};

class AccountNotFoundException : public BankingException {
public:
    AccountNotFoundException(const std::string& msg) : BankingException(msg) {}
};

class BankAccount {
protected:
    int account_number;
    double balance;
public:
    BankAccount(int acct_num = 0, double bal = 0.0) : account_number(acct_num), balance(bal) {}
    virtual ~BankAccount() {}

    void set_account_number(int acct) {
        account_number = acct;
    }
    int get_account_number() const {
        return account_number;
    }
    void set_balance(double bal) {
        balance = bal;
    }
    double get_balance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidTransactionException("Deposit amount must be positive.");
        }
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidTransactionException("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Insufficient funds for withdrawal.");
        }
        balance -= amount;
    }

    virtual void post_interest() {
        // Base account does not have interest by default
    }

    virtual void print_account_info() const {
        std::cout << "Account Number: " << account_number << ", Balance: " << balance << std::endl;
    }

    virtual std::string serialize() const {
        std::ostringstream oss;
        oss << "B " << account_number << " " << balance;
        return oss.str();
    }
};

class CheckingAccount : public BankAccount {
    double interest_rate;
    double min_balance;
    double service_charge;
public:
    CheckingAccount(int acct_num = 0, double bal = 0.0, double interest = 0.0, double min_bal = 0.0, double service = 0.0)
        : BankAccount(acct_num, bal), interest_rate(interest), min_balance(min_bal), service_charge(service) {
    }

    void set_interest_rate(double rate) {
        interest_rate = rate;
    }
    double get_interest_rate() const {
        return interest_rate;
    }
    void set_min_balance(double min_bal) {
        min_balance = min_bal;
    }
    double get_min_balance() const {
        return min_balance;
    }
    void set_service_charge(double charge) {
        service_charge = charge;
    }
    double get_service_charge() const {
        return service_charge;
    }

    void post_interest() override {
        if (interest_rate > 0) {
            double interest = balance * interest_rate / 100.0;
            balance += interest;
        }
    }

    void write_check(double amount) {
        // Writing a check uses withdraw logic
        withdraw(amount);
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            throw InvalidTransactionException("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Insufficient funds for withdrawal.");
        }
        double new_balance = balance - amount;
        if (new_balance < min_balance) {
            // After withdrawal, below minimum, charge service fee
            if (new_balance - service_charge < 0) {
                throw InsufficientFundsException("Insufficient funds for service charge after withdrawal.");
            }
            balance = new_balance - service_charge;
        }
        else {
            balance = new_balance;
        }
    }

    void print_account_info() const override {
        std::cout << "Checking Account - Number: " << account_number
            << ", Balance: " << balance
            << ", Interest Rate: " << interest_rate
            << "%, Min Balance: " << min_balance
            << ", Service Charge: " << service_charge
            << std::endl;
    }

    std::string serialize() const override {
        std::ostringstream oss;
        oss << "C " << account_number << " " << balance << " " << interest_rate << " "
            << min_balance << " " << service_charge;
        return oss.str();
    }
};

class SavingsAccount : public BankAccount {
    double interest_rate;
public:
    SavingsAccount(int acct_num = 0, double bal = 0.0, double interest = 0.0)
        : BankAccount(acct_num, bal), interest_rate(interest) {
    }

    void set_interest_rate(double rate) {
        interest_rate = rate;
    }
    double get_interest_rate() const {
        return interest_rate;
    }

    void post_interest() override {
        if (interest_rate > 0) {
            double interest = balance * interest_rate / 100.0;
            balance += interest;
        }
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            throw InvalidTransactionException("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Insufficient funds for withdrawal.");
        }
        balance -= amount;
    }

    void print_account_info() const override {
        std::cout << "Savings Account - Number: " << account_number
            << ", Balance: " << balance
            << ", Interest Rate: " << interest_rate
            << "%" << std::endl;
    }

    std::string serialize() const override {
        std::ostringstream oss;
        oss << "S " << account_number << " " << balance << " " << interest_rate;
        return oss.str();
    }
};

class AccountFactory {
public:
    static std::unique_ptr<BankAccount> create_account(char type, int acct_num, double bal,
        double interest = 0.0, double min_bal = 0.0, double service = 0.0) {
        if (type == 'C' || type == 'c') {
            return std::unique_ptr<BankAccount>(new CheckingAccount(acct_num, bal, interest, min_bal, service));
        }
        else if (type == 'S' || type == 's') {
            return std::unique_ptr<BankAccount>(new SavingsAccount(acct_num, bal, interest));
        }
        else {
            throw InvalidTransactionException("Unknown account type for creation.");
        }
    }
};

// Find an account by number in a vector of accounts
BankAccount* find_account(std::vector<std::unique_ptr<BankAccount>>& accounts, int acct_num) {
    for (auto& acct_ptr : accounts) {
        if (acct_ptr->get_account_number() == acct_num) {
            return acct_ptr.get();
        }
    }
    return nullptr;
}

// Save all accounts to a file
void save_accounts(const std::vector<std::unique_ptr<BankAccount>>& accounts, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing.");
    }
    for (const auto& acct_ptr : accounts) {
        file << acct_ptr->serialize() << std::endl;
    }
}

// Load accounts from a file
void load_accounts(std::vector<std::unique_ptr<BankAccount>>& accounts, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // File may not exist initially
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        iss >> type;
        if (type == 'C') {
            int num;
            double bal, interest, minbal, service;
            iss >> num >> bal >> interest >> minbal >> service;
            accounts.push_back(std::unique_ptr<BankAccount>(
                new CheckingAccount(num, bal, interest, minbal, service)
            ));
        }
        else if (type == 'S') {
            int num;
            double bal, interest;
            iss >> num >> bal >> interest;
            accounts.push_back(std::unique_ptr<BankAccount>(
                new SavingsAccount(num, bal, interest)
            ));
        }
    }
}

// Unit tests for major functionalities
void run_unit_tests() {
    // Test BankAccount deposit and withdrawal
    BankAccount base_acct(1001, 100.0);
    base_acct.deposit(50.0);
    assert(base_acct.get_balance() == 150.0);
    try {
        base_acct.withdraw(200.0);
        assert(false); // should not reach here
    }
    catch (const InsufficientFundsException&) {
    }
    base_acct.withdraw(50.0);
    assert(base_acct.get_balance() == 100.0);

    // Test CheckingAccount operations
    CheckingAccount chk(2001, 500.0, 5.0, 100.0, 25.0);
    chk.post_interest(); // 5% of 500 = 25
    assert(chk.get_balance() == 525.0);
    chk.withdraw(400.0); // leaves 125, above min, no charge
    assert(chk.get_balance() == 125.0);
    chk.withdraw(50.0);  // leaves 75, below min, apply $25 fee, final 50
    assert(chk.get_balance() == 50.0);
    try {
        chk.withdraw(100.0); // 50-100 < 0, should fail
        assert(false);
    }
    catch (const InsufficientFundsException&) {
    }
    // Test writing checks
    chk = CheckingAccount(2002, 200.0, 3.0, 50.0, 10.0);
    chk.write_check(100.0); // leaves 100, above min
    assert(chk.get_balance() == 100.0);
    chk.write_check(60.0); // leaves 40, below min -> $10 fee, final 30
    assert(chk.get_balance() == 30.0);

    // Test SavingsAccount operations
    SavingsAccount sav(3001, 1000.0, 2.0);
    sav.post_interest(); // 2% of 1000 = 20
    assert(sav.get_balance() == 1020.0);
    sav.withdraw(20.0); // 1000 left
    assert(sav.get_balance() == 1000.0);
    try {
        sav.withdraw(2000.0); // too much
        assert(false);
    }
    catch (const InsufficientFundsException&) {
    }
    try {
        sav.deposit(-10.0); // invalid deposit
        assert(false);
    }
    catch (const InvalidTransactionException&) {
    }

    // Test file save and load
    {
        std::vector<std::unique_ptr<BankAccount>> accts;
        accts.push_back(std::unique_ptr<BankAccount>(new CheckingAccount(4001, 250.0, 4.0, 50.0, 5.0)));
        accts.push_back(std::unique_ptr<BankAccount>(new SavingsAccount(5001, 1000.0, 1.0)));
        save_accounts(accts, "test_accounts.txt");
        std::vector<std::unique_ptr<BankAccount>> loaded;
        load_accounts(loaded, "test_accounts.txt");
        assert(loaded.size() == 2);
        CheckingAccount* lchk = dynamic_cast<CheckingAccount*>(loaded[0].get());
        SavingsAccount* lsav = dynamic_cast<SavingsAccount*>(loaded[1].get());
        assert(lchk && lsav);
        assert(lchk->get_account_number() == 4001);
        assert(lsav->get_account_number() == 5001);
        std::remove("test_accounts.txt");
    }
}

int main() {
    std::vector<std::unique_ptr<BankAccount>> accounts;
    const std::string filename = "accounts.txt";

    // Load existing accounts from file
    try {
        load_accounts(accounts, filename);
    }
    catch (const std::exception& e) {
        std::cout << "Warning: could not load accounts: " << e.what() << std::endl;
    }

    int choice;
    while (true) {
        std::cout << "\nBanking System Menu:\n";
        std::cout << "1. Create Checking Account\n";
        std::cout << "2. Create Savings Account\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Withdraw\n";
        std::cout << "5. Write Check (Checking only)\n";
        std::cout << "6. Post Interest\n";
        std::cout << "7. Print Account Info\n";
        std::cout << "8. List All Accounts\n";
        std::cout << "9. Save Accounts to File\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter choice (1-10): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 10) {
            break; // exit loop
        }

        try {
            if (choice == 1 || choice == 2) {
                // Create account
                char type = (choice == 1 ? 'C' : 'S');
                int acct_num;
                double balance, interest;
                double min_bal = 0.0, service = 0.0;
                std::cout << "Enter account number: ";
                std::cin >> acct_num;
                if (!std::cin || acct_num <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid account number.");
                }
                if (find_account(accounts, acct_num) != nullptr) {
                    throw InvalidTransactionException("Account number already exists.");
                }
                std::cout << "Enter initial balance: ";
                std::cin >> balance;
                if (!std::cin || balance < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid balance amount.");
                }
                std::cout << "Enter interest rate (%): ";
                std::cin >> interest;
                if (!std::cin || interest < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid interest rate.");
                }
                if (type == 'C') {
                    std::cout << "Enter minimum balance: ";
                    std::cin >> min_bal;
                    if (!std::cin || min_bal < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw InvalidTransactionException("Invalid minimum balance.");
                    }
                    std::cout << "Enter service charge: ";
                    std::cin >> service;
                    if (!std::cin || service < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw InvalidTransactionException("Invalid service charge.");
                    }
                }
                accounts.push_back(AccountFactory::create_account(type, acct_num, balance, interest, min_bal, service));
                std::cout << "Account created successfully.\n";
            }
            else if (choice == 3 || choice == 4) {
                // Deposit or withdraw
                bool is_deposit = (choice == 3);
                int acct_num;
                double amount;
                std::cout << "Enter account number: ";
                std::cin >> acct_num;
                if (!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid account number input.");
                }
                BankAccount* acct = find_account(accounts, acct_num);
                if (!acct) {
                    throw AccountNotFoundException("Account not found.");
                }
                std::cout << "Enter amount: ";
                std::cin >> amount;
                if (!std::cin || amount <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid amount.");
                }
                if (is_deposit) {
                    acct->deposit(amount);
                    std::cout << "Deposit successful.\n";
                }
                else {
                    acct->withdraw(amount);
                    std::cout << "Withdrawal successful.\n";
                }
            }
            else if (choice == 5) {
                // Write check (checking accounts)
                int acct_num;
                double amount;
                std::cout << "Enter checking account number: ";
                std::cin >> acct_num;
                if (!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid account number.");
                }
                BankAccount* acct = find_account(accounts, acct_num);
                CheckingAccount* chk = dynamic_cast<CheckingAccount*>(acct);
                if (!chk) {
                    throw InvalidTransactionException("Checking account not found.");
                }
                std::cout << "Enter check amount: ";
                std::cin >> amount;
                if (!std::cin || amount <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid check amount.");
                }
                chk->write_check(amount);
                std::cout << "Check written successfully.\n";
            }
            else if (choice == 6) {
                // Post interest for an account
                int acct_num;
                std::cout << "Enter account number: ";
                std::cin >> acct_num;
                if (!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid account number.");
                }
                BankAccount* acct = find_account(accounts, acct_num);
                if (!acct) {
                    throw AccountNotFoundException("Account not found.");
                }
                acct->post_interest();
                std::cout << "Interest posted.\n";
            }
            else if (choice == 7) {
                // Print account info
                int acct_num;
                std::cout << "Enter account number: ";
                std::cin >> acct_num;
                if (!std::cin) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw InvalidTransactionException("Invalid account number.");
                }
                BankAccount* acct = find_account(accounts, acct_num);
                if (!acct) {
                    throw AccountNotFoundException("Account not found.");
                }
                acct->print_account_info();
            }
            else if (choice == 8) {
                // List all accounts
                std::cout << "Listing all accounts:\n";
                for (const auto& acct_ptr : accounts) {
                    acct_ptr->print_account_info();
                }
            }
            else if (choice == 9) {
                // Save accounts
                save_accounts(accounts, filename);
                std::cout << "Accounts saved to file.\n";
            }
            else {
                std::cout << "Invalid choice, try again.\n";
            }
        }
        catch (const BankingException& be) {
            std::cout << "Error: " << be.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }
    }

    // Save accounts before exiting
    try {
        save_accounts(accounts, filename);
    }
    catch (const std::exception& e) {
        std::cout << "Warning: could not save accounts: " << e.what() << std::endl;
    }

    // Run unit tests
    std::cout << "Running unit tests...\n";
    run_unit_tests();
    std::cout << "All unit tests passed.\n";
    std::cout << "Exiting program.\n";
    return 0;
}
