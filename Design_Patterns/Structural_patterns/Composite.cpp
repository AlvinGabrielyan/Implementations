/* "The Composite Pattern is for working with tree-like structures in a uniform way. 
It lets you treat individual objects (leaves) and groups of objects (composites) exactly the same, which simplifies your code. */

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

//inqy tree-i leaf node-na
class Leaf : public Component {
private:
    string name;
    
public:
    Leaf(const string& name) : name(name) {}
    
    void operation() const override {
        cout << "Leaf " << name << " operation" << endl;
    }
};

//inqy tree-i cankacac node a , baci leaf-ic, 
//inqy kam kara leaf node unena as jarang, kam kara composite unena as jarang

class Composite : public Component {
private:
    string name;
    vector<shared_ptr<Component>> children;
    
public:
    Composite(const string& name) : name(name) {}
    
    void add(shared_ptr<Component> component) {
        children.push_back(component);
    }
    
    void operation() const override {
        cout << "Composite " << name << " operation" << endl;
        for (const auto& child : children) {
            child->operation();
        }
    }
};

int main() {
    auto leaf1 = make_shared<Leaf>("A");
    auto leaf2 = make_shared<Leaf>("B");
    auto leaf3 = make_shared<Leaf>("C");
    
    auto composite1 = make_shared<Composite>("X");
    auto composite2 = make_shared<Composite>("Y");
    
    composite1->add(leaf1);
    composite1->add(leaf2);
    
    composite2->add(leaf3);
    composite2->add(composite1);
    
    cout << "Calling operation on leaf:" << endl;
    leaf1->operation();
    
    cout << "\nCalling operation on composite1:" << endl;
    composite1->operation();
    
    cout << "\nCalling operation on composite2:" << endl;
    composite2->operation();
    
    return 0;
}
