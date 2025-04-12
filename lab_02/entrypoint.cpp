#include "entrypoint.h"

void doOperation(Operation operation, AppContext* context, AppParam* param) {
    switch (operation) {
        case (INIT):
            initialization(context);
            break;
        case (OPENFILE):
            openFileLogic(context);
            break;
        case(CHECKNAME):
            checkName(context, param);
            break;
        case(CALCULATE):
            findMetrics(context, param);
            break;
        case(DELETE):
            deleteList(context->list);
            break;
    }
}
