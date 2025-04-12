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

// ������� ����� ������
class Figure {
public:
    virtual double getArea() const = 0; // ����������� �����? ��� ���������� ������� ������
    virtual void printInfo() const = 0; // ����������� �����? ��� ������ ���������� � ������
};

#endif