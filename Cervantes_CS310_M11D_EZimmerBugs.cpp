#include <iostream>
#include <vector>

template <typename T>
T average(const std::vector<T>& nums) { // changed return type from int to T
    if (nums.empty()) return T{};
    T sum = T{};
    for (const T& val : nums) sum += val;
    return sum / static_cast<T>(nums.size());
}

int main() {
    std::vector<int> intNums{ 1, 2, 3, 4, 5 };
    std::vector<double> doubleNums{ 1.2, 3.4, 5.6, 7.8 }; // changed T to double

    std::cout << "Average (int): " << average(intNums) << "\n";
    std::cout << "Average (double): " << average(doubleNums) << "\n";
    return 0;
}
