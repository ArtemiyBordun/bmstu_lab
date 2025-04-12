#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point
{
private:
    double x, y;
public:

    Point(double coordX, double coordY)
        : x(coordX), y(coordY) {}

    double getX() const;
    double getY() const;
    void printCoords() const;
};

#endif