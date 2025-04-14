#include <iostream>

int square(int value)
{
    result = value * value
        return result;
}

bool isEven(int num)
{
    if num % 2 == 0
        return true;
    else
        return false;
}

void displayResult(int number)
{
    std::cout << "The square of " << number << " is " << square(number) << std::endl
        if (isEven(number))
            std::cout << "The number is even." << std::endl;
        else
            std::cout << "The number is odd." << std::endl;
}

int main()
{
    int userNumber

        std::cout << "Enter a number: ";
    std::cin >> usernumber;

    displayResult(usernumber);

    return 0;
}
