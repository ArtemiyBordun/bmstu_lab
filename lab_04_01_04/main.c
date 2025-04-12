#include <stdio.h>
#include <stdlib.h>

//4 вар. Найти сумму каждого второго элемента,после первого максимального, больших max / 2

#define TWO 2

int read_data(int* size);
void print_error();
int* create_arr(int size);
int check_correct_size(int size);
int check_correct_memory(int* arr);
void clear_arr(int* arr);
int input_mas(int* arr, int size);
int find_index_max_elem(const int* arr, int size);
int sum_elem(int* startmax, int* size);
int find_solution(int* arr, int size);
void print_result(int sum);

int main() { 
    int size;
    if (!read_data(&size) || !check_correct_size(size)) 
        print_error();
    else {
        int* arr = create_arr(size);

        int result = find_solution(arr, size);
        if (result == -1)
            print_error();
        else
            print_result(result);
        clear_arr(arr);
    }
    return 0;
}

int read_data(int* size) {
    printf ("Введите размер массива: \n");
    return scanf ("%d", size);
}

int check_correct_size(int size) {
    return size > 0;
}

int* create_arr(int size) {
    return (int*)malloc(size * sizeof(int));
}

int check_correct_memory(int* arr) {
    return arr != NULL;
}

void print_error() {
    printf ("Incorrect input\n");
}

int input_mas(int* arr, int size) {
    int s = 1;
    printf ("Введите элементы массива: \n");
    for (int i = 0; i < size; i++) {
        s = scanf ("%d", arr + i);
        if (!s)
            break;
    }
    return s;
}

int find_index_max_elem(const int* arr, int size) {
    int index_max = 0;
    for (int i = 1; i < size; i++)
        if (arr[index_max] < arr[i])
            index_max = i;
    return index_max;
}

int sum_elem(int* startmax, int* size) {
    int sum = 0.0;
    double half_max = *startmax / TWO;
    for (int* ptr = startmax + TWO; ptr < size; ptr += TWO) 
        if (*ptr > half_max)
            sum += *ptr;
    return sum;
}

int find_solution(int* arr, int size) {
    int result = 0;
    if (!check_correct_memory(arr) || !input_mas(arr, size)) 
        result = -1;
    else {
        int index_max = find_index_max_elem(arr, size);
        result = sum_elem(arr + index_max, arr + size);
    }
    return result;
}

void clear_arr(int* arr) {
    free(arr);
}

void print_result(int sum) {
    printf ("%d\n", sum);
}