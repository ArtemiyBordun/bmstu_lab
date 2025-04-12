#ifndef APPCONTEX_H
#define APPCONTEX_H

#include "stdlib.h"

#define LEN 256

enum ErrorList
{
    notError,
    notSetNormalParam,
    inCorrectParam,
    memoryError,
    fileError
};

struct Point {
    double x;
    double y;
    double z;
};

struct NormalParam {
    double min;
    double max;
    double step;
};

enum Rotate {
    X,
    Y,
    Z,
    NONE
};

struct AppContext
{
    const char* fileName;
    ErrorList error;
    NormalParam normalParam;

    size_t rows, columns;
    double** mat;

    size_t countPoint;
    Point* model;

    Point k;

    Rotate rotateAxis;
    double rotate;
};

#endif // APPCONTEX_H
