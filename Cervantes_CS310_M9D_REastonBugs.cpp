#include <iostream>
using namespace std;

class School {
public:
    void Studenttype() {
        cout << "This is a student \n";
    }
}; // added missing closing brace and semicolon

class Freshman : public School { // added colon and public inheritance
public:
    void Studenttype() {
        cout << "This is a Freshman Student \n";
    }
};

class Senior : public School { // added inheritance so Senior also derives from School
public:
    void Studenttype() {
        cout << "This is a Senior Student \n";
    }
};

int main() {
    School   mySchool;
    Freshman myFreshman;
    Senior   mySenior;

    mySchool.Studenttype();
    myFreshman.Studenttype();
    mySenior.Studenttype();

    return 0;
}
