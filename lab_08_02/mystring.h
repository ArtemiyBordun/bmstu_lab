#ifndef MYSTRING_H
#define MYSTRING_H

#define LEN 128
#define CORRECT 3

unsigned strlen_my(const char* str);
unsigned count_words(const char* str);
unsigned strcmp_my(const char* s1, const char* s2);

char* strcpy_my(char* new_str, const char* str);
char* strncpy_my(char* destination, const char* source, unsigned num);
char* get_lastname(char* str);

void replace_subs(char* str, const char* end1, const char* end2);

#endif