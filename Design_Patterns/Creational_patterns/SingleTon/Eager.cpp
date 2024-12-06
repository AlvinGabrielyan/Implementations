#include <iostream>
using namespace std;

class EagerSingleton {
private:
    static EagerSingleton instance; 
    EagerSingleton() {
        cout << "EagerSingleton Constructor" << endl;
    }

public:

    static EagerSingleton& getInstance() {
        return instance;
    }

    void showMessage() {
        cout << "Eager Singleton: Hello World!" << endl;
    }

    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;
};

EagerSingleton EagerSingleton::instance;

int main() {
    EagerSingleton& singleton = EagerSingleton::getInstance();
    singleton.showMessage();

    return 0;
}
