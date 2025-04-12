#include "logic.h"

void init(AppContext* context)
{
    context->error = notSetNormalParam;
    context->rotate = 0;
    context->columns = 0;
    context->rows = 0;
    context->model = NULL;
    context->mat = NULL;
    context->rotateAxis = NONE;
    context->countPoint = 0;
    context->k.x = 0;
    context->k.y = 0;
    context->k.z = 0;
}

void loadData(AppContext* context)
{
    workFile(context);
    Point* model = (Point*)malloc(context->rows * context->columns * sizeof(Point));
    if (model == NULL)
    {
        context->error = memoryError;
        return;
    }
    int index = 0;
    for (size_t i = 0; i < context->rows; i++)
        for (size_t j = 0; j < context->columns; j++)
        {
            model[index].x = i;
            model[index].y = j;
            model[index].z = context->mat[i][j];
            index++;
        }
    context->countPoint = index;
    context->model = model;
    normalize(context);
}

void rotateMat(AppContext* context) {
    switch(context->rotateAxis) {
    case X:
        rotateX(context);
        break;
    case Y:
        rotateY(context);
        break;
    case Z:
        rotateZ(context);
        break;
    default:
       break;
    }
}
