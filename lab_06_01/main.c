#include <stdio.h>
#include <stdlib.h>

int read_data(int* size);
int check_correct_size(int size);
int check_correct_memory(int** matrix, int size);
void print_error();
int** create_matrix(int size);
void transform(int** matrix, int* vec, int size);
int input_mat(int** matrix, int size);
void swap(int* value1, int* value2);
void transpose(int** matrix, int size);
void free_arr(int** matrix, int size);
void print_result(int** matrix, int size);

int main() {
    int size;
    if (!read_data(&size) || !check_correct_size(size)) 
        print_error();
    else if (size != 0) {
        int** matrix = create_matrix(size);

        if (!check_correct_memory(matrix, size) || !input_mat(matrix, size))
            print_error();
        else {    
            transpose(matrix, size);
            print_result(matrix, size);
        }
        free_arr(matrix, size);
    }
    return 0;
}

int read_data(int* size) {
    printf("Введите размер матрицы: \n");
    return scanf("%d", size);
}

int check_correct_size(int size) {
    return size >= 0;
}

int check_correct_memory(int** matrix, int size) {
    int s = 1;
    if (matrix == NULL)
        s = 0;
    for (int i = 0; i < size; i++)
        if (matrix[i] == NULL) {
            s = 0; // Возвращаем 0, если одна из строк матрицы не выделена
            if (!s)
                break;
        }
    return s;
}

void print_error() {
    printf("Incorrect input\n");
}

int** create_matrix(int size) {
    int** matrix = (int**)calloc(size, sizeof(int*));
    if (matrix != NULL) {
        int* vec = (int*)calloc(size * size, sizeof(int));
        if (vec != NULL)
            transform(matrix, vec, size);
    }
    return matrix;
}

void transform(int** matrix, int* vec, int size) {
    for (int i = 0; i < size; i++)
        matrix[i] = vec + i * size;
}

int input_mat(int** matrix, int size) {
    int s = 1;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            s = scanf("%d", matrix[i] + j);
            if (!s)
                break;
        }
    return s;
}

void swap(int* value1, int* value2) {
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

void transpose(int** matrix, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++) 
            swap(matrix[i] + j, matrix[size - j - 1] + (size - i - 1));
}

void free_arr(int** matrix, int size) {
    free(*matrix);
    free(matrix);
}

void print_result(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}