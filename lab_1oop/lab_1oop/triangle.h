#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figures.h"

#include <string>
#include <iostream>

using namespace std;

// Класс Треугольник
class Triangle : public Figure {
private:
    string name;
    Point coord1;
    Point coord2;
    Point coord3;

public:
    Triangle(const string& name, Point input1, Point input2, Point input3)
        : name(name), coord1(input1), coord2(input2), coord3(input3) {
        if (!getArea()) {
            throw invalid_argument("Invalid triangle coordinates\n");
        }
    }

    double getArea() const override;
    void printInfo() const override;
};

#endif