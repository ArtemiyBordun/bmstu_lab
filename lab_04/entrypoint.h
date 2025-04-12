#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontex.h"
#include "logic.h"
#include "operationmat.h"

enum Operation
{
    Init,
    LoadData,
    Scale,
    Move,
    Rotate
};

void doOperation(AppContext* context, Operation oper);

#endif // ENTRYPOINT_H
