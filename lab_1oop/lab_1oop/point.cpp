#include "point.h"

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::printCoords() const {
    cout << "(" << getX() << ", " << getY() << "), ";
}