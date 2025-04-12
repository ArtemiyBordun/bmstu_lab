#ifndef CIRCLE_H
#define CIRCLE_H

#include "figures.h"

#include <string>
#include <cctype>
#include <iostream>

//#include <math.h>

#define M_PI 3.14159265358979323846

using namespace std;

class Circle : public Figure {
private:
    string name;
    Point coord;
    double radius;

public:
    Circle(const string& name, Point input, double radius)
        : name(name), coord(input), radius(radius) {
        if (radius <= 0) {
            throw invalid_argument("Invalid data\n");
        }
    }

    double getArea() const override;
    void printInfo() const override;
};

#endif // CIRCLE_H