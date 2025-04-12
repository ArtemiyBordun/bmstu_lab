#include "operationmat.h"

void normalize(AppContext* context) {
    if (context->normalParam.max <= context->normalParam.min || context->normalParam.step <= 0) {
        context->error = notSetNormalParam;
        return;
    }
    context->error = notError;
    for (size_t i = 0; i < context->countPoint; i++) {
        context->model[i].x = context->model[i].x * context->normalParam.step;
        context->model[i].y = context->model[i].y * context->normalParam.step;
    }
    double min_z = getMinZValue(context);
    double max_z = getMaxZValue(context);
    for (size_t i = 0; i < context->countPoint; i++) {
        context->model[i].z = context->normalParam.min + ((context->model[i].z - min_z) / (max_z - min_z)) * (context->normalParam.max - context->normalParam.min);
    }
}

double getMinZValue(AppContext* context) {
    double min = context->model[0].z;
    for (size_t i = 1; i < context->countPoint; i++)
    {
        if (context->model[i].z < min)
            min = context->model[i].z;
    }
    return min;
}

double getMaxZValue(AppContext* context) {
    double max = context->model[0].z;
    for (size_t i = 1; i < context->countPoint; i++)
    {
        if (context->model[i].z > max)
            max = context->model[i].z;
    }
    return max;
}

void scale(AppContext* context) {
    if (context->k.x <= 0 || context->k.y <= 0 || context->k.z <= 0)
    {
        context->error = inCorrectParam;
        return;
    }
    double x = context->k.x;
    double y = context->k.y;
    double z = context->k.z;
    double matrix[SIZE][SIZE] = {{x, 0, 0, 0},
                                {0, y, 0, 0},
                                {0, 0, z, 0},
                                {0, 0, 0, 1}};
    multiplyVectorMatrix(context, matrix);
}


void multiplyVectorMatrix(AppContext* context, double matrix[][SIZE]) {
    for (size_t i = 0; i < context->countPoint; i++)
    {
        Point tmpPoint = context->model[i];
        context->model[i].x = matrix[0][0] * tmpPoint.x + matrix[0][1] * tmpPoint.y + matrix[0][2] * tmpPoint.z + matrix[0][3];
        context->model[i].y = matrix[1][0] * tmpPoint.x + matrix[1][1] * tmpPoint.y + matrix[1][2] * tmpPoint.z + matrix[1][3];
        context->model[i].z = matrix[2][0] * tmpPoint.x + matrix[2][1] * tmpPoint.y + matrix[2][2] * tmpPoint.z + matrix[2][3];
    }
}

void move(AppContext* context) {
    double x = context->k.x;
    double y = context->k.y;
    double z = context->k.z;
    double matrix[SIZE][SIZE] = {{1, 0, 0, x},
                                {0, 1, 0, y},
                                {0, 0, 1, z},
                                {0, 0, 0, 1}};
    multiplyVectorMatrix(context, matrix);
}

void rotateX(AppContext* context) {
    double radX = (M_PI / 180) * context->rotate;
    double matrix[SIZE][SIZE] = {{1,     0,         0,      0},
                                {0, cos(radX), -sin(radX), 0},
                                {0, sin(radX),  cos(radX), 0},
                                {0,     0,         0,      1}};
    multiplyVectorMatrix(context, matrix);
}

void rotateY(AppContext* context) {
    double radY = (M_PI / 180) * context->rotate;
    double matrix[SIZE][SIZE] = {{cos(radY), 0, sin(radY), 0},
                                {    0,     1,     0,     0},
                                {-sin(radY),0, cos(radY), 0},
                                {    0,     0,     0,     1}};
    multiplyVectorMatrix(context, matrix);
}

void rotateZ(AppContext* context)
{
    double radZ = (M_PI / 180) * context->rotate;
    double matrix[SIZE][SIZE] = {{cos(radZ), -sin(radZ), 0, 0},
                                {sin(radZ),  cos(radZ), 0, 0},
                                {0,              0,     1, 0},
                                {0,              0,     0, 1}};
    multiplyVectorMatrix(context, matrix);
}

