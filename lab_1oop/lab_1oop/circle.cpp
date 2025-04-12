#include "circle.h"

double Circle::getArea() const {
    return M_PI * radius * radius;
}

void Circle::printInfo() const {
    cout << "Circle: " << name << ", Center: ";
    coord.printCoords();
    cout << "Radius: " << radius << endl;
}