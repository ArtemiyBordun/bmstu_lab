#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H
#include "point.h"
#include "iostream"
#include "vector"

using namespace std;

enum Num
{
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    SIZE = 4
};

class TransformMatrix {
private:
    float _matr[SIZE][SIZE];
public:
    TransformMatrix();
    explicit TransformMatrix(vector<vector<float>> matr);
    float (*getMatrix())[4];
    TransformMatrix operator *(const TransformMatrix& matrix);
    Point3D transformPoint(Point3D);
};

#endif // TRANSFORMMATRIX_H
