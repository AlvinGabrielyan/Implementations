#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    string name, interest;
    static Singleton* instancePtr;
    static mutex mtx;
    Singleton() {}

public:
    Singleton(const Singleton& obj) = delete;
    static Singleton* getInstance() {
        if (instancePtr == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (instancePtr == nullptr) {
                instancePtr = new Singleton();
            }
        }
        return instancePtr;
    }

    void setValues(const string& name, const string& interest) {
        this->name = name;
        this->interest = interest;
    }

    void print() const {
        cout << name << " is interested in " << interest << "." << endl;
    }
};

Singleton* Singleton::instancePtr = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    s1->setValues("Alex", "coding");
    s1->print();

    Singleton* s2 = Singleton::getInstance();
    s2->setValues("Jordan", "designing");
    s2->print();

    return 0;
}
