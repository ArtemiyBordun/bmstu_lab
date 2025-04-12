#include <stdio.h>
#include <stdlib.h>

//1 вар. нули, положительные по возрастанию, отрицательные по возрастанию

int read_data(int* size);
void print_error();
int* create_arr(int size);
int check_correct_size(int size);
int check_correct_memory(int* arr);
void clear_arr(int* arr);
int input_mas(int* arr, int size);
void swap(int* value1, int* value2);
int group_arr(int* arr, int size);
void sort_arr(int* arr, int size);
void find_solution(int* arr, int size);
void print_result(int* arr, int size);

int main() {
    int size;

    if (!read_data(&size) || !check_correct_size(size)) 
        print_error();
    else {
        int* arr = create_arr(size);

        if (!check_correct_memory(arr) || !input_mas(arr, size)) 
            print_error();
        else {
            find_solution(arr, size);
            print_result(arr, size);
        }
        clear_arr(arr);
    }

    return 0;
}

int read_data(int* size) {
    printf ("Введите размер массива: \n");
    return scanf("%d", size);
}

int check_correct_size(int size) {
    return size >= 0;
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

int group_arr(int* arr, int size) {
    //переносим отрицательные в конец
    int negative_index = 0;
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++)
            if (arr[j] < 0)
                swap(arr + j, arr + j + 1);
        for (int i = size - 1; arr[i] < 0; i--)
            negative_index = i;
    }
    return negative_index;
}

void sort_arr(int* arr, int size) {
    for (int i = size - 1; i >= 0; i--) {
        int k = 1; //пока массив не отсартирован
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr + j, arr + j + 1);
                k = 0;
            }
        }
        if (k)
            break;
    }
}

void swap(int* value1, int* value2) {
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

void find_solution(int* arr, int size) {
    int negative_index = group_arr(arr, size);
    sort_arr(arr, negative_index); //сначала сортировка для нулей и положительных

    sort_arr(arr + negative_index, size - negative_index); //затем для отрицательных
}

void clear_arr(int* arr) {
    free(arr);
}

void print_result(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf ("\n");
}