#ifndef APPCONTEX_H
#define APPCONTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define MAXSIZE 512

enum ERRORLIST {
    NOTERROR,
    EMPTY,
    NOTFILE,
    FILEINCOTTECT,
    REGIONMISS,
    NOTENTER
};

struct AppContext {
    List* list;
    const char* fileName;
    char regionName[MAXSIZE];
    char prevRegionName[MAXSIZE];
    ERRORLIST error;
    int isFileOpen;
    int allLines;
};

struct Metrics {                //убрать в appParam
    double* mas;
    int size;
    double min;
    double max;
    double median;
};

struct AppParam {
    Metrics metrics;
    int countRegion = 0;
    int columnId;
};

#endif // APPCONTEX_H
