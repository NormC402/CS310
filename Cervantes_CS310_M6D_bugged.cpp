#include <iostream>
#include <string>

enum color_option
{
    red_option,
    green_option,
    blue_option
};

int main()
{
    std::cout << "Enter color number (0=red,1=green,2=blue): ";
    std::string user_input;
    std::getline(std::cin, user_input);

    color_option chosen_color = static_cast<color_option>(user_input);

    int iteration = 0;
    do
    {
        std::cout << "Iteration " << iteration << std::endl
            iteration++;
    } while (iteration < 3)

        std::cout << "Color enum value: " << chosen_color << std::endl;

    return "0";
}
