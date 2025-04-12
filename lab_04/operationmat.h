#ifndef OPERATIONMAT_H
#define OPERATIONMAT_H

#include <math.h>
#include <string.h>

#include "appcontex.h"

#define SIZE 4

void normalize(AppContext* context);

double getMinZValue(AppContext* context);
double getMaxZValue(AppContext* context);

void multiplyVectorMatrix(AppContext* context, double matrix[][SIZE]);
void scale(AppContext* context);
void move(AppContext* context);

void rotateX(AppContext* context);
void rotateY(AppContext* context);
void rotateZ(AppContext* context);

#endif // OPERATIONMAT_H
