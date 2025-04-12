#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

int read_count_str(int* count);
int check_count(int count);
int read_strings(char** mas_str, int count_str);

char* allocate_str();
char* read_string();
char** allocate_mas_str(int count_str);

char** find_solution(char** mas_str, int count_str);
void print_error();
void print_result(const char** str, int count_str);
char* reduce_memory(char* str, int dif);
void free_str(char** str, int count_str);
void free_end(char* end1, char* end2);

int main(void) {
    int count_str;
    if (!read_count_str(&count_str) || !check_count(count_str))
        print_error();
    else {
        char** mas_str = allocate_mas_str(count_str); //создаем массив строк
        if (mas_str == NULL)
            print_error();
        else {
            if (!read_strings(mas_str, count_str)) //сощдаем сами строки
                print_error();
            else {
                mas_str = find_solution(mas_str, count_str);
                print_result((const char**)mas_str, count_str);
                free_str(mas_str, count_str);
            }
        }
    }
    return 0;
}

int read_count_str(int* count) {
    int s = scanf("%d", count);
    getchar();
    return s;
}

int check_count(int count) {
    return count > 0;
}

char** allocate_mas_str(int count_str) {
    return (char**)malloc(count_str * sizeof(char*));
}

char* allocate_str() {
    return (char*)malloc(LEN * sizeof(char));
}

int read_strings(char** mas_str, int count_str) {
    int k = 1;
    for (int i = 0; i < count_str; i++) {
        mas_str[i] = read_string();
        if (mas_str[i] == NULL || count_words(mas_str[i]) != CORRECT) {
            k = 0;
            free_str(mas_str, i - 1); //очищаем предыдущие строки
            break;
        }
    }
    return k;
}

char* read_string() {
    char* string = allocate_str();
    if (string != NULL) {
        fgets(string, LEN, stdin);
        unsigned len = strlen_my(string);
        if (string[len - 1] == '\n')
            string[len - 1] = '\0';
    }
    return string;
}

char** find_solution(char** mas_str, int count_str) {
    char* end1 = read_string();
    char* end2 = read_string();  //записываем окончания

    int dif = strlen_my(end1) - strlen_my(end2);

    for (int i = 0; i < count_str; i++) {
        char* lastname = get_lastname(mas_str[i]);
        replace_subs(lastname, end1, end2);
        mas_str[i] = reduce_memory(mas_str[i], dif + 1);
    }
    free_end(end1, end2);
    return mas_str;
}

char* reduce_memory(char* str, int dif) {
    unsigned len = strlen_my(str);
    char* new_str = (char*)malloc((len + dif + 1) * sizeof(char));
    if (new_str == NULL)
        print_error();
    else {
        strcpy_my(new_str, str);
        new_str[len] = '\0';
        free(str);
    }
    return new_str;
}


void print_error() {
    printf("Incorrect input\n");
}

void free_str(char** mas_str, int count_str) {
    for (int i = 0; i < count_str; i++)
        free(mas_str[i]); //очищаем строки
    free(mas_str);  //очищаем массив строк
}

void free_end(char* end1, char* end2) {
    free(end1);
    free(end2); //очищаем окончания
}

void print_result(const char** str, int count_str) {
    for (int i = 0; i < count_str; i++)
        printf("%s\n", str[i]);
}