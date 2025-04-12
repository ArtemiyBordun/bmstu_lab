#ifndef MYSTRING_H
#define MYSTRING_H

#define LEN 128

unsigned strlen_my(const char* str);
char* remove_extra_space(char* str);
int is_pts(char* str);
char* strcpy_my(char* result_str, const char* str);
char* reduce_memory(char* str);

#endif