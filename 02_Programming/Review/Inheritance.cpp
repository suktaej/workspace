#include <iostream>
using namespace std;

class Parent{
public:
    virtual void print() {
        cout << "Parent" << endl;
    }
};

class Child : public Parent{
public:
    void print() override{
        cout << "Child" << endl;
    }
};

void main() 
{
    Parent* p = new Parent;
    Child* c = new Child;
    Parent* cp = new Child;
    // Child* pc = new Parent;
    
    p->print();
    c->print();
    cp->print();

    p = c;
    p->print();

    Child* vc = dynamic_cast<Child*>(cp);

}
