#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrypoint.h"
#include "appcontex.h"
#include "list.h"

#define TWO 2

void initialization(AppContext* context);

void openFileLogic(AppContext* context);
void checkName(AppContext* context, AppParam* param);
void findMetrics(AppContext* context, AppParam* param);
void calculateMetrics(double* mas, int size, AppParam* param);
double* getMasOnColumn(List* listRegion, AppParam* param);
void sortMas(double* mas, int size);
void swap (double* value1, double* value2);

#endif // LOGIC_H
