#include "entrypoint.h"

void doOperation(AppContext* context, Operation oper)
{
    switch (oper)
    {
    case (Init):
        break;
    case (LoadData):
        loadData(context);
        break;
    case (Scale):
        scale(context);
        break;
    case (Move):
        move(context);
        break;
    case (Rotate):
        rotateMat(context);
        break;
    }
}
