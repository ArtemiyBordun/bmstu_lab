#include <stdio.h>

#include "io.h"
#include "mystring.h"

void read_data(char* str) {
    fgets(str, LEN, stdin);
    unsigned len_str = strlen_my(str);
    if (str[len_str - 1] == '\n')
        str[len_str - 1] = '\0';
}

void print_str(const char* str) {
    printf("|%s|\n", str);
}

void print_error() {
    printf("Incorrect input\n");
}