#include "entrypoint.h"

void doOperation(OPERATION operation, AppContext* context, AppParams* param) {
    switch(operation) {
        case CONVERT:
            convertTo(context);
            break;
        case CHECK:
            checkNum(context);
            break;
        case MYSTRCPY:
            mystrcpy(context, param->cstr);
            break;
        case INITIALIZATION:
            init(context);
            break;
    }
}
