#include <iostream>

using namespace std;
class Base {
public:
    void print() {
        cout << "Inside Base";
    }
};

class Pod1 : public Base {
public:
    void print() {
        cout << "Inside Pod1";
    }
};

class Pod2 : public Pod1 {};

int main(void){
    Pod2 r;
    r.print();
    return 0;
}
