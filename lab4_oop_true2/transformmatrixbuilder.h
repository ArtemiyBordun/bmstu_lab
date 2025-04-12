#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H
#include "transformmatrix.h"
#include "math.h"

#define StraightAngle 180

class TransformMatrixBuilder {

public:
    TransformMatrixBuilder();
    static TransformMatrix createRotationXMatrix(float z);
    static TransformMatrix createRotationYMatrix(float z);
    static TransformMatrix createRotationZMatrix(float z);
    static TransformMatrix createMoveMatrix(float x, float y, float z);
    static TransformMatrix createScaleMatrix(float x, float y, float z);
};

#endif // TRANSFORMMATRIXBUILDER_H
