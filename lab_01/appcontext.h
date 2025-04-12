#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define SIZE 33 //32 бита + 1 для нуля

enum ERRORTYPE{
    NOERROR = 0,
    EMPTY = -1,
    NOTINT = -2,
    NOTBASE = -3,
    NUMBERLONG = -4,
    RESULTLONG = -5,
    BASESMALL = -6,
    BASEBIG = -7
};

struct AppContext {
    char number[SIZE];
    ERRORTYPE error;
    int isNegative;
    int sourceBase;
    int newBase;
};

#endif // APPCONTEXT_H
