//Liskov Substitution Principle
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bird {
protected:
    string name;
public:
    Bird(const string& birdName) : name(birdName) {}
    virtual void describe() const {
        cout << name << " is a bird." << endl;
    }
    virtual ~Bird() {}
};

class FlyingBird : public Bird {
public:
    FlyingBird(const string& birdName) : Bird(birdName) {}
    void describe() const override {
        cout << name << " can fly." << endl;
    }
};

class SwimmingBird : public Bird {
public:
    SwimmingBird(const string& birdName) : Bird(birdName) {}
    void describe() const override {
        cout << name << " can swim but cannot fly." << endl;
    }
};

class RunningBird : public Bird {
public:
    RunningBird(const string& birdName) : Bird(birdName) {}
    void describe() const override {
        cout << name << " can run fast but cannot fly." << endl;
    }
};

class Sparrow : public FlyingBird {
public:
    Sparrow() : FlyingBird("Sparrow") {}
    void describe() const override {
        cout << "The sparrow is small and agile, capable of quick flight." << endl;
    }
};

class Eagle : public FlyingBird {
public:
    Eagle() : FlyingBird("Eagle") {}
    void describe() const override {
        cout << "The eagle soars high and is known for its sharp vision." << endl;
    }
};

class Penguin : public SwimmingBird {
public:
    Penguin() : SwimmingBird("Penguin") {}
    void describe() const override {
        cout << "The penguin is a master swimmer and lives in cold regions." << endl;
    }
};

class Ostrich : public RunningBird {
public:
    Ostrich() : RunningBird("Ostrich") {}
    void describe() const override {
        cout << "The ostrich is the largest bird and can run very fast." << endl;
    }
};

class Duck : public SwimmingBird, public FlyingBird {
public:
    Duck() : Bird("Duck"), SwimmingBird("Duck"), FlyingBird("Duck") {}
    void describe() const override {
        cout << "The duck can both swim and fly, making it a versatile bird." << endl;
    }
};

class BirdSanctuary {
    
private:
    vector<Bird*> birds;
    
public:
    void addBird(Bird* bird) {
        birds.push_back(bird);
    }

    void displayAllBirds() const {
        for (const auto& bird : birds) {
            bird->describe();
            cout << endl;
        }
    }

    ~BirdSanctuary() {
        for (auto bird : birds) {
            delete bird;
        }
    }
};

int main() {
    BirdSanctuary sanctuary;

    sanctuary.addBird(new Sparrow());
    sanctuary.addBird(new Eagle());
    sanctuary.addBird(new Penguin());
    sanctuary.addBird(new Ostrich());
    sanctuary.addBird(new Duck());

    cout << "Bird Sanctuary Details:\n" << endl;
    sanctuary.displayAllBirds();

    return 0;
}

