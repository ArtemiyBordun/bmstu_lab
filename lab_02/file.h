#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "appcontex.h"

#define CORRECT 7

FILE* openFile(const char* fileName);
void closeFile(FILE* file);

void processData(List* list, const char* fileName);

#endif // FILE_H
