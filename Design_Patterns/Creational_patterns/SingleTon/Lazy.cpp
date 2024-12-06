#include <iostream>
using namespace std;

class LazySingleton {
private:
    static LazySingleton* instance; 
    LazySingleton() {
        cout << "LazySingleton Constructor" << endl;
    }

public:
    static LazySingleton* getInstance() {
        if (instance == nullptr) {
            instance = new LazySingleton();         }
        return instance;
    }

    void showMessage() {
        std::cout << "Lazy Singleton: Hello World!" << std::endl;
    }

    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

    ~LazySingleton() {
        delete instance;
    }
};

LazySingleton* LazySingleton::instance = nullptr;

int main() {
    LazySingleton* singleton = LazySingleton::getInstance();
    singleton->showMessage();

    return 0;
}
