#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figures.h"

#include <string>
#include <iostream>

using namespace std;

// Класс Прямоугольник
class Rectangle : public Figure {
private:
    string name;
    Point coordTop;
    Point coordBottom;

public:
    Rectangle(const string& name, Point inputTop, Point inputBottom)
        : name(name), coordTop(inputTop), coordBottom(inputBottom) {
        if (coordTop.getX() >= coordBottom.getX() || coordTop.getY() <= coordBottom.getY()) {
            throw invalid_argument("Invalid rectangle coordinates\n");
        }
    }
    double getArea() const override;
    void printInfo() const override;
};

#endif