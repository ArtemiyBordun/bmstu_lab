#ifndef STR_H
#define STR_H

#include "string.h"
#include "stdlib.h"

char* strSub(char* subs, const char* s, unsigned len);
size_t countWords(const char* str, const char* sep);
size_t parseWords(char*** words, char* str, const char* sep);

#endif // STR_H
