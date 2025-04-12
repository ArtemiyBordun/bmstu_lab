#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appcontext.h"
#include "logic.h"


enum BASE {
    BINARY = 2,
    DECIMAL = 10,
    HEXADECIMAL = 16,
    MAXBASE = 36
};

enum OPERATION {
    CONVERT,
    CHECK,
    MYSTRCPY,
    INITIALIZATION,
};

struct AppParams {
    const char* cstr;
};

void doOperation(OPERATION operation, AppContext* context, AppParams* param);

#endif // ENTRYPOINT_H
