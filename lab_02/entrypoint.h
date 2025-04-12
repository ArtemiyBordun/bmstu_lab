#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdio.h>
#include <stdlib.h>

#include "mainwindow.h"
#include "logic.h"
#include "appcontex.h"
#include "file.h"

enum Operation {
    INIT,
    OPENFILE,
    CHECKNAME,
    CALCULATE,
    DELETE
};

void doOperation(Operation operation, AppContext* context, AppParam* param);

#endif // ENTRYPOINT_H
