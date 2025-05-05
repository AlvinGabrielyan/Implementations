//The Abstract Factory Pattern is a creational pattern that provides an interface for creating families of related
//or dependent objects without specifying their concrete classes.

/*
The client (main) depends on abstract interfaces (AnimalFactory, Animal) and doesn't know the concrete classes like Cat or Dog.
It allows easy extension by adding new factories and animal types without changing the client code.
*/

#include <iostream>
#include <memory>

using namespace std;

class Animal {
public:
    virtual void sound() const = 0; 
    virtual ~Animal() = default;
};

class Cat : public Animal {
public:
    void sound() const override {
        cout << "Meow!" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() const override {
        cout << "Woof!" << endl;
    }
};

class AnimalFactory {
public:
    virtual unique_ptr<Animal> createAnimal() const = 0;  
    virtual ~AnimalFactory() = default;
};

class CatFactory : public AnimalFactory {
public:
    unique_ptr<Animal> createAnimal() const override {
        return make_unique<Cat>(); 
    }
};

class DogFactory : public AnimalFactory {
public:
    unique_ptr<Animal> createAnimal() const override {
        return make_unique<Dog>(); 
    }
};

int main() {
    unique_ptr<AnimalFactory> catFactory = make_unique<CatFactory>();
    unique_ptr<AnimalFactory> dogFactory = make_unique<DogFactory>();

    unique_ptr<Animal> cat = catFactory->createAnimal();
    unique_ptr<Animal> dog = dogFactory->createAnimal();

    cat->sound(); 
    dog->sound(); 

    return 0;
}
