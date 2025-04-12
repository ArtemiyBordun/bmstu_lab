#include "transformmatrix.h"


TransformMatrix::TransformMatrix()
{
    for(size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            _matr[i][j] = 0;
}

TransformMatrix::TransformMatrix(vector<vector<float>> matr)
{
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            _matr[i][j] = matr[i][j];
}

TransformMatrix TransformMatrix::operator *(const TransformMatrix& mat)
{
    TransformMatrix result;
    for(size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            for (size_t k = 0; k < SIZE; k++)
                result._matr[i][j] += _matr[i][k] * mat._matr[k][j];

    return result;
}

Point3D TransformMatrix::transformPoint(Point3D point)
{
    Point3D newPoint;
    newPoint.x = _matr[0][0] * point.x + _matr[0][1] * point.y + _matr[0][TWO] * point.z + _matr[0][THREE];
    newPoint.y = _matr[1][0] * point.x + _matr[1][1] * point.y + _matr[1][TWO] * point.z + _matr[1][THREE];
    newPoint.z = _matr[TWO][0] * point.x + _matr[TWO][1] * point.y + _matr[TWO][TWO] * point.z + _matr[TWO][THREE];
    return newPoint;
}

float (*TransformMatrix::getMatrix())[SIZE]
{
    return _matr;
}
