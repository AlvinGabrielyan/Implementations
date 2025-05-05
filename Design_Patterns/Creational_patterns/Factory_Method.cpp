//The Factory Method Pattern is a creational design pattern that provides an interface for creating objects in a superclass 
//but allows subclasses (or a factory class) to alter the type of objects that will be created.

/*
Object creation is handled outside the client, making it easier to manage and extend.
The client code (main) doesn’t directly use new to create Circle or Rectangle—it relies on the factory to decide what to instantiate.
*/

#include <iostream>
#include <string>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0; 
    virtual ~Shape() = default;   
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a Circle\n";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a Rectangle\n";
    }
};

class ShapeFactory {
public:
    static Shape* getShape(const string& type) {
        if (type == "Circle" || type == "circle") {
            return new Circle();
        } else if (type == "Rectangle" || type == "rectangle") {
            return new Rectangle();
        }
        return nullptr; 
    }
};

int main() {
    Shape* shape;

    shape = ShapeFactory::getShape("circle");
    if (shape) {
        shape->draw();
        delete shape;
        } else {
        cout << "Invalid shape type for Circle\n";
    }

    shape = ShapeFactory::getShape("rectangle");
    if (shape) {
        shape->draw();
        delete shape; 
    } else {
        cout << "Invalid shape type for Rectangle\n";
    }

    shape = ShapeFactory::getShape("triangle");
    if (!shape) {
        cout << "Invalid shape type for Triangle\n";
    }

    return 0;
}
