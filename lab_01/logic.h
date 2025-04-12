#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "appcontext.h"
#include "entrypoint.h"

#define MAXVAL 2147483647   //2^16-1
#define MAXNEGVAL -2147483648

void checkNum(AppContext* context);
ERRORTYPE checkBase(AppContext* context);
int checkValid(char* num, int base);
void checkNegative(AppContext* context);
void convertTo(AppContext* context);
int convertToDecimal(char* num, int base);
void mystrcpy(AppContext* context, const char* cstr);
void init(AppContext* context);
char* convertToBase(unsigned int num, int base);
int convertTotwos(int num);
char* addbit(char* num);
char* reverse(char* s, int index);

#endif // LOGIC_H
