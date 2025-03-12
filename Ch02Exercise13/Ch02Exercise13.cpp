#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Declare variables
    double originalPrice, markupPercentage, salesTaxRate;

    // Get input from user
    cout << "Enter the original price of the item: $";
    cin >> originalPrice;

    cout << "Enter the markup percentage (without % sign): ";
    cin >> markupPercentage;

    cout << "Enter the sales tax rate (without % sign): ";
    cin >> salesTaxRate;

    // Convert percentage values to decimal form
    markupPercentage /= 100;
    salesTaxRate /= 100;

    // Calculate selling price
    double sellingPrice = originalPrice + (originalPrice * markupPercentage);

    // Calculate sales tax
    double salesTax = sellingPrice * salesTaxRate;

    // Calculate final price
    double finalPrice = sellingPrice + salesTax;

    // Output results
    cout << fixed << setprecision(2);
    cout << "\n==============================\n";
    cout << "Original Price: $" << originalPrice << endl;
    cout << "Markup Percentage: " << (markupPercentage * 100) << "%" << endl;
    cout << "Selling Price: $" << sellingPrice << endl;
    cout << "Sales Tax Rate: " << (salesTaxRate * 100) << "%" << endl;
    cout << "Sales Tax: $" << salesTax << endl;
    cout << "Final Price: $" << finalPrice << endl;
    cout << "==============================\n";

    return 0;
}
