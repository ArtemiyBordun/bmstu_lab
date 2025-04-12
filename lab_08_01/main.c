#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"
#include "io.h"

char* allocate_str();
void free_str(char* old_str, char* new_str);

int main(void) {
    char* str = allocate_str();
    if (str == NULL)
        print_error();
    else {
        read_data(str);
        print_str(str);

        char* result = remove_extra_space(str);

        str = reduce_memory(str);
        print_str(result);
        free_str(str, result);
    }
    return 0;
}

char* allocate_str() {
    return (char*)malloc(LEN * sizeof(char));
}

void free_str(char* old_str, char* new_str) {
    free(old_str);
    free(new_str);
}