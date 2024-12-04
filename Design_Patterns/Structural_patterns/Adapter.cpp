#include <iostream>
using namespace std;

class LegacyRectangle {
public:
    void setCoordinates(int x1, int y1, int x2, int y2) {
        cout << "Setting coordinates: (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";
    }
};

class Rectangle {
public:
    virtual void setDimensions(int width, int height) = 0;
    virtual ~Rectangle() = default;
};

class RectangleAdapter : public Rectangle {
private:
    LegacyRectangle* legacyRectangle;
public:
    RectangleAdapter(LegacyRectangle* legacy) : legacyRectangle(legacy) {}

    void setDimensions(int width, int height) override {
        int x1 = 0, y1 = 0; 
        int x2 = x1 + width;
        int y2 = y1 + height;
        legacyRectangle->setCoordinates(x1, y1, x2, y2);
    }
};

int main() {
    LegacyRectangle legacyRectangle;
    Rectangle* rectangle = new RectangleAdapter(&legacyRectangle);

    rectangle->setDimensions(5, 10);

    delete rectangle;
    return 0;
}

