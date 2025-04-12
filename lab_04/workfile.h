#ifndef WORKFILE_H
#define WORKFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appcontex.h"
#include "str.h"

FILE* openFile(const char* fileName);
void closeFile(FILE* file);

void workFile(AppContext* context);
void countRowsInFile(AppContext* context, FILE* file);
void parseRows(AppContext* context, FILE* f);

#endif // WORKFILE_H
