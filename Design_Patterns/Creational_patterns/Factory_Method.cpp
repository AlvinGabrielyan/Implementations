#include <iostream>
#include <memory>
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
    virtual unique_ptr<Shape> createShape() const = 0; 
    virtual ~ShapeFactory() = default;
};

class CircleFactory : public ShapeFactory {
public:
    unique_ptr<Shape> createShape() const override {
        return make_unique<Circle>();
    }
};

class RectangleFactory : public ShapeFactory {
public:
    unique_ptr<Shape> createShape() const override {
        return make_unique<Rectangle>();
    }
};

int main() {
    unique_ptr<ShapeFactory> factory;
    factory = make_unique<CircleFactory>();
    auto circle = factory->createShape();
    circle->draw();
    factory = make_unique<RectangleFactory>();
    auto rectangle = factory->createShape();
    rectangle->draw();

    return 0;
}

