#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

unsigned strlen_my(const char* str) {
    unsigned i;
    for (i = 0; str[i]; i++);
    return i;
}

unsigned count_words(const char* str) {
    int count = 0;
    for (unsigned i = 0; i < strlen_my(str); i++)
        if (str[i] != ' ' && (i == 0 || str[i - 1] == ' ')) // если текущий символ не €вл€етс€ пробелом, а предыдущий символ был пробелом или началом строки, то увеличиваем счетчик слов на 1
            count++;
    return count;
}

unsigned strcmp_my(const char* s1, const char* s2) {
    unsigned i;
    for (i = 0; s1[i] && s1[i] == s2[i]; i++);
    return s1[i] - s2[i];
}

char* get_lastname(char* str) {
    char* lastname = str;

    // ѕоиск последнего пробела в строке
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ')
            lastname = str + i + 1;
    return lastname;
}

char* strcpy_my(char* new_str, const char* str) {
    for (unsigned i = 0; str[i]; i++)
        new_str[i] = str[i];
    return new_str;
}

char* strncpy_my(char* str, const char* end2, unsigned count) {
    unsigned i;
    for (i = 0; i < count && end2[i]; i++)
        str[i] = end2[i];
    for (; i < count; i++)
        str[i] = '\0'; //добавл€ем терманальный ноль
    return str;
}

void replace_subs(char* lastname, const char* end1, const char* end2) {
    unsigned len_old_end = strlen_my(end1);
    unsigned len_new_end = strlen_my(end2);
    unsigned len = strlen_my(lastname);

    if (len >= len_old_end && !strcmp_my(lastname + len - len_old_end, end1)) { // ѕроверка, что фамили€ содержит окончание end1
        if (len > len_old_end) { // ѕроверка, что слово не состоит только из окончани€
            strncpy_my(lastname + len - len_old_end, end2, len_new_end); // «амена окончани€
            lastname[len - len_old_end + len_new_end] = '\0';
        }
    }
}