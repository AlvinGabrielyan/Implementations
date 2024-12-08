// Open/closed Principle
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0; 
    virtual ~Shape() {}
};

class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {}
        double area() const override { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(double w, double h) : width(w), height(h) {}
        double area() const override { return width * height; }
};

class Triangle : public Shape {
    private:
        double base, height;
    public:
        Triangle(double b, double h) : base(b), height(h) {}
        double area() const override { return 0.5 * base * height; }
};

class Square : public Shape {
    private:
        double side;
    public:
        Square(double s) : side(s) {}
        double area() const override { return side * side; }
};

class Ellipse : public Shape {
    private:
        double majorAxis, minorAxis;
    public:
        Ellipse(double a, double b) : majorAxis(a), minorAxis(b) {}
        double area() const override { return 3.14 * majorAxis * minorAxis; }
};

int main() {
    Shape* c = new Circle(5);
    Shape* r = new Rectangle(4, 6);
    Shape* t = new Triangle(5, 10);
    Shape* s = new Square(4);
    Shape* e = new Ellipse(3, 5);

    cout << "Circle area: " << c->area() << endl;
    cout << "Rectangle area: " << r->area() << endl;
    cout << "Triangle area: " << t->area() << endl;
    cout << "Square area: " << s->area() << endl;
    cout << "Ellipse area: " << e->area() << endl;

    delete c;
    delete r;
    delete t;
    delete s;
    delete e;

    return 0;
}
