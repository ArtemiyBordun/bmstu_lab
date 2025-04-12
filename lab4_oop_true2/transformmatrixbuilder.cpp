#include "transformmatrixbuilder.h"
TransformMatrixBuilder::TransformMatrixBuilder() {}

TransformMatrix TransformMatrixBuilder::createMoveMatrix(float x, float y, float z) {
    vector<vector<float>> matrix= {{1, 0, 0, x},
                                   {0, 1, 0, y},
                                   {0, 0, 1, z},
                                   {0, 0, 0, 1}};
    TransformMatrix move = TransformMatrix(matrix);
    return move;
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(float x, float y, float z) {
    vector<vector<float>> matrix = {{x, 0, 0, 0},
                                    {0, y, 0, 0},
                                    {0, 0, z, 0},
                                    {0, 0, 0, 1}};
    TransformMatrix scale = TransformMatrix(matrix);
    return scale;
}

TransformMatrix TransformMatrixBuilder::createRotationXMatrix(float x) {
    float radX = (M_PI / StraightAngle) * x;
    vector<vector<float>> matrix = {{1,     0,         0,      0},
                                    {0, cos(radX), -sin(radX), 0},
                                    {0, sin(radX),  cos(radX), 0},
                                    {0,     0,         0,      1}};
    TransformMatrix rotateX = TransformMatrix(matrix);
    return rotateX;
}

TransformMatrix TransformMatrixBuilder::createRotationYMatrix(float y) {
    float radY = (M_PI / StraightAngle) * y;
    vector<vector<float>> matrix = {{cos(radY), 0, sin(radY), 0},
                                    {    0,     1,     0,     0},
                                    {-sin(radY),0, cos(radY), 0},
                                    {    0,     0,     0,     1}};
    TransformMatrix rotateY = TransformMatrix(matrix);
    return rotateY;
}

TransformMatrix TransformMatrixBuilder::createRotationZMatrix(float z) {
    float radZ = (M_PI / StraightAngle) * z;
    vector<vector<float>> matrix = {{cos(radZ), -sin(radZ), 0, 0},
                                    {sin(radZ),  cos(radZ), 0, 0},
                                    {0,              0,     1, 0},
                                    {0,              0,     0, 1}};
    TransformMatrix rotateZ = TransformMatrix(matrix);
    return rotateZ;
}

