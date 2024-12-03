#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Prototype {
public:
    virtual ~Prototype() {}
    virtual Prototype* clone() const = 0;
    virtual void display() const = 0;
};

class ConcretePrototypeA : public Prototype {
private:
    string name;
public:
    ConcretePrototypeA(const string& name) : name(name) {}
    
    Prototype* clone() const override {
        return new ConcretePrototypeA(*this);
    }

    void display() const override {
        cout << "Prototype A: " << name << endl;
    }
};

class ConcretePrototypeB : public Prototype {
private:
    int id;
public:
    ConcretePrototypeB(int id) : id(id) {}
    
    Prototype* clone() const override {
        return new ConcretePrototypeB(*this);
    }

    void display() const override {
        cout << "Prototype B: " << id << endl;
    }
};

class PrototypeManager {
private:
    unordered_map<string, Prototype*> prototypes;
public:
    ~PrototypeManager() {
        // Clean up dynamically allocated prototypes
        for (auto& pair : prototypes) {
            delete pair.second;
        }
    }

    void addPrototype(const string& key, Prototype* prototype) {
        prototypes[key] = prototype;
    }

    Prototype* getPrototype(const string& key) {
        return prototypes[key]->clone();
    }
};

int main() {
    PrototypeManager prototypeManager;

    prototypeManager.addPrototype("A", new ConcretePrototypeA("Object A"));
    prototypeManager.addPrototype("B", new ConcretePrototypeB(12345));

    Prototype* prototypeA = prototypeManager.getPrototype("A");
    prototypeA->display();
    
    Prototype* prototypeB = prototypeManager.getPrototype("B");
    prototypeB->display();

    delete prototypeA;
    delete prototypeB;

    return 0;
}
