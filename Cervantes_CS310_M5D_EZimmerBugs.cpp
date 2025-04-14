#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// Correction: Added forward declarations
vector<double> mergeSort(const vector<double>& list);
vector<double> merge(const vector<double>& list1, const vector<double>& list2);

int main() {
    vector<double> numList = { 5, 3, 7, 1, 9, 4, 2, 8, 10, 6 };

    cout << "List of numbers before sorting: ";
    for (double num : numList) {
        cout << num << " ";
    }
    cout << endl;

    // Correction: Fixed incorrect mergeSort call syntax
    numList = mergeSort(numList);

    cout << "The list has been sorted." << endl;

    cout << "List of numbers after sorting: ";
    for (double num : numList) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

vector<double> mergeSort(const vector<double>& list) {
    if (list.size() <= 1) {
        return list;
    }

    size_t mid = list.size() / 2;

    // Correction: Replaced manual loop-splitting with range constructors
    vector<double> left(list.begin(), list.begin() + mid);
    vector<double> right(list.begin() + mid, list.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

// Correction: Return type changed from void to vector<double>
vector<double> merge(const vector<double>& list1, const vector<double>& list2) {
    vector<double> result;
    size_t i = 0, j = 0;

    while (i < list1.size() && j < list2.size()) {
        if (list1[i] < list2[j]) {
            result.push_back(list1[i]);
            i++;
        }
        else {
            result.push_back(list2[j]);
            j++;
        }
    }

    while (i < list1.size()) {
        result.push_back(list1[i]);
        i++;
    }

    while (j < list2.size()) {
        result.push_back(list2[j]);
        j++;
    }

    return result;
}
