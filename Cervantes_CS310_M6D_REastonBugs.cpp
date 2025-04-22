#include <algorithm>
#include <iostream>
#include <string>               // added to recognize std::string

using namespace std;

enum vowel_level            // fixed: added 'enum' keyword
{
    LOW = 7,
    MEDIUM = 14,
    HIGH = 21,
    DANGER = 28
};

int count_vowels(const string& input) {
    int adjusted = 0;
    string vowels = "aeiouAEIOU";
    for (char charc : input) {
        if (vowels.find(charc) != string::npos) {  // fixed: use string::npos
            adjusted += 1;
        }
    }
    return adjusted;
}

string get_vowel_level(int count) {
    if (count < LOW)        return "Very Low";
    else if (count < MEDIUM) return "Low";
    else if (count < HIGH)   return "Medium";
    else if (count < DANGER) return "High";
    else                     return "DANGER";
}

int main() {
    string strInput;
    cout << "Enter a string: " << endl;
    getline(cin, strInput);

    int vowel_count = count_vowels(strInput);      // fixed: changed type from string to int
    string level = get_vowel_level(vowel_count);

    cout << "\nYour string contains " << vowel_count << " vowels." << endl;
    cout << "Vowel Level: " << level << endl;

    cout << count_vowels(strInput) << endl;

    return 0;
}
