#include "triangle.h"

double Triangle::getArea() const {
    return abs((coord1.getX() * (coord2.getY() - coord3.getY()) + coord2.getX() * (coord3.getY() - coord1.getY()) + coord3.getX() * (coord1.getY() - coord2.getY())) / 2);
}

void Triangle::printInfo() const {
    cout << "Triangle: " << name << ", Vertex 1: ";
    coord1.printCoords();
    cout << "Vertex 2: "; 
    coord2.printCoords();
    cout << "Vertex 3: "; 
    coord3.printCoords();
    cout << endl;
}
