#include "entrypoint.h"

void initialization(AppContext* context) {
    context->error = NOTFILE;
    context->isFileOpen = 0;
}

void openFileLogic(AppContext* context) {
    clearList(context->list);

    processData(context->list, context->fileName);

    if (context->list->size)
        context->isFileOpen = 1;
    else
        context->isFileOpen = 0;
}

void checkName(AppContext* context, AppParam* param) {
    if (!strlen(context->regionName)) {
        context->error = EMPTY;
        return;
    }

    if (!strcmp(context->prevRegionName, context->regionName)) { //если предыдущее название совпадает с нынешним, мы его не проверяем
        return;
    }

    if (context->error != NOTFILE) {
        int count = 0;
        List* curList = (List*)malloc(sizeof(List));
        curList->head = context->list->head;
        while (hasNext(curList)) {
            if (!strcmp(context->regionName, curList->head->data.region))
                count++;
            next(curList);
        }
        if (count == 0) {
            context->error = REGIONMISS;
            param->countRegion = 0;
        }
        else {
            context->error = NOTERROR;
            param->countRegion = count;
        }
        free(curList);
    }
    strncpy(context->prevRegionName, context->regionName, strlen(context->regionName)); //сохраняем новое название
}

void findMetrics(AppContext* context, AppParam* param) {
    List* listRegion = filterList(context->list, context->regionName);
    double* mas = getMasOnColumn(listRegion, param);
    if (mas == NULL)
        return;
    calculateMetrics(mas, param->countRegion, param);
    free(mas);
    deleteList(listRegion);
}

double* getMasOnColumn(List* listRegion, AppParam* param) {
    double* mas = (double*)malloc(param->countRegion * sizeof(double));
    if (mas == NULL)
        return NULL;
    int i = 0;

    List* curList = (List*)malloc(sizeof(List));
    curList->head = listRegion->head;

    while (hasNext(curList)) {
        switch (param->columnId) {
            case (NPG):
                mas[i] = curList->head->data.npg;
                break;
            case (BR):
                mas[i] = curList->head->data.br;
                break;
            case (DR):
                mas[i] = curList->head->data.dr;
                break;
            case (GDW):
                mas[i] = curList->head->data.gdw;
                break;
            case (URBAN):
                mas[i] = curList->head->data.urban;
                break;
        }
        i++;
        next(curList);
    }

    return mas;
}

void calculateMetrics(double* mas, int size, AppParam* param) {
    sortMas(mas, size);

    param->metrics.min = mas[0];
    param->metrics.max = mas[size - 1];
    if (size % TWO)
        param->metrics.median = mas[size / TWO];
    else
        param->metrics.median = (mas[size / TWO] + mas[size / TWO - 1]) / TWO;
}

void sortMas(double* mas, int size) {
    int noSwap;
    for (int i = size - 1; i >= 0; i--) {
        noSwap = 1;
        for (int j = 0; j < i; j++) {
            if (mas[j] > mas[j + 1]) {
                swap(mas + j, mas + j + 1);
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }
}

void swap (double* value1, double* value2) {
    double temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}
