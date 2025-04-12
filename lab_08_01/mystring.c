#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"
#include "io.h"

unsigned strlen_my(const char* str) {
    unsigned i;
    for (i = 0; str[i]; i++);
    return i;
}

char* remove_extra_space(char* str) {
    unsigned len = strlen_my(str);
    char* result_str = (char*)malloc((len + 1) * sizeof(char));
    if (result_str != NULL) {
        // удаляем пробелы в начале
        while (*str == ' ')
            str++;

        int j = 0;
        for (unsigned i = 0; str[i]; i++) {
            if (str[i] == ' ')
                if (str[i + 1] == ' ' || is_pts(str + i + 1))
                    continue;
            result_str[j++] = str[i];
        }

        if (result_str[j - 1] == ' ') //если последний пробел, убираем его
            result_str[j - 1] = '\0';
        else
            result_str[j] = '\0';
    }
    result_str = reduce_memory(result_str);
    return result_str;
}

int is_pts(char* str) {
    const char* pts = ",.?!;:()-";
    int k = 0;
    for (int i = 0; pts[i]; i++)
        if (pts[i] == *str)
            k = 1;
    return k;
}

char* strcpy_my(char* new_str, const char* str) {
    unsigned i = 0;
    for (; str[i]; i++)
        new_str[i] = str[i];
    return new_str;
}

char* reduce_memory(char* str) {
    unsigned len = strlen_my(str);
    char* new_str = (char*)malloc((len + 1) * sizeof(char));
    if (new_str == NULL)
        print_error();
    else {
        strcpy_my(new_str, str);
        new_str[len] = '\0';
        free(str);
    }
    return new_str;
}