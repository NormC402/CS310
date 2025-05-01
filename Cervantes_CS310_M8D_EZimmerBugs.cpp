#include <iostream>
#include <string>

using namespace std;

class Foe {
private:
    string name;
public:
    Foe(const string& name) : name(name) {}
    string getName() const { return name; }
};

class Friend {
private:
    string name;
public:
    Friend(const string& name) : name(name) {}
    string getName() const { return name; }
    void stomp(const Foe& foe) const {
        cout << name << " stomps " << foe.getName() << "!" << endl; // fixed: use getter to access private member
    }
};

int main() {
    Friend mario("Mario");      // fixed: proper object instantiation
    Foe    goomba("Goomba");    // fixed: proper object instantiation

    mario.stomp(goomba);        // fixed: call stomp on mario, not as a free function

    return 0;
}
