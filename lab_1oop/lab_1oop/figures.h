#ifndef FIGURES_H
#define FIGURES_H

#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

#include "point.h"

enum TYPEFIGURE {
	CIRCLE = 1,
	RECTANGLE = 2,
	TRIANGLE = 3
};

// Базовый класс Фигура
class Figure {
public:
    virtual double getArea() const = 0; // Виртуальный метод? для вычисления площади фигуры
    virtual void printInfo() const = 0; // Виртуальный метод? для вывода информации о фигуре
};

#endif