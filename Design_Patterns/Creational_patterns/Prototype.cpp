//The Prototype Design Pattern is a creational pattern used to create new objects by copying (cloning) 
//an existing object (the prototype), rather than creating a new object from scratch.

/*The meaning of this design pattern
Objects are created by cloning existing prototypes.
You can add, retrieve, and duplicate objects without knowing their concrete types.
It supports the idea of dynamic object creation at runtime.*/

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
