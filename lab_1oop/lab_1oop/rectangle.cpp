#include "rectangle.h"

double Rectangle::getArea() const {
    return (coordBottom.getX() - coordTop.getX()) * (coordTop.getY() - coordBottom.getY());
}

void Rectangle::printInfo() const {
    cout << "Rectangle: " << name << ", Top Left: ";
    coordTop.printCoords();
    cout << "Bottom Right: ";
    coordBottom.printCoords();
    cout << endl;
}