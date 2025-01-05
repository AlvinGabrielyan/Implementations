#include <iostream>
#include <memory>
using namespace std;
//interface
class IC {
public:
    virtual void performTask() const = 0;
    virtual ~IC() = default;
};
//implem
class C : public IC {
public:
    void performTask() const override {
        cout << "Task performed by C." << endl;
    }
};
//interface
class IB {
public:
    virtual void execute() const = 0;
    virtual ~IB() = default;
};
//implem
class B : public IB {
private:
    shared_ptr<IC> c;

public:
    B(shared_ptr<IC> cInstance) : c(cInstance) {}

    void execute() const override {
        cout << "Executing in B, delegating to C..." << endl;
        c->performTask();
    }
};

// Class A depends on IB, not B directly
class A {
private:
    shared_ptr<IB> b;

public:
    A(shared_ptr<IB> bInstance) : b(bInstance) {}

    void performAction() const {
        cout << "Performing action in A, delegating to B..." << endl;
        b->execute();
    }
};


int main() {
    shared_ptr<IC> cInstance = make_shared<C>();
    shared_ptr<IB> bInstance = make_shared<B>(cInstance);
    A aInstance(bInstance);

    // Use A to perform actions
    aInstance.performAction();

    return 0;
}
