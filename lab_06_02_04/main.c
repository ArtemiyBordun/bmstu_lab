#include <stdio.h>
#include <stdlib.h>

//4 вар. Удалить строку с последним минимальным элементом под главной диагональю

#define CORRECT 2

int read_data(int* rows, int* cols);
int check_correct_size(int rows, int cols);
void print_error();
int** create_matrix(int rows, int cols);
void transform(int** mat, int* vec, int rows, int cols);
int check_correct_memory(int** mat);
int input_mat(int** matrix, int rows, int cols);
int find_str_last_min(int** matrix, int rows, int cols);
void delete_rows(int** matrix, int* rows, int cols, int rows_last_min);
void free_matrix(int** matrix, int rows);
void print_result(int** matrix, int rows, int cols);

int main() {
    int rows = 0, cols = 0;
    if (!read_data(&rows, &cols) || !check_correct_size(rows, cols)) 
        print_error();
    else if (rows != 0) {
        int** matrix = create_matrix(rows, cols);
        if (!check_correct_memory(matrix) || !input_mat(matrix, rows, cols))
            print_error();
        else {    
            if (rows > 1 && cols >= 1) {  //проверяем что количество строк и столбцов достаточно, для работы следующих функций
                int row_min = find_str_last_min(matrix, rows, cols);
                delete_rows(matrix, &rows, cols, row_min);
            }
            print_result(matrix, rows, cols);
        }
        free_matrix(matrix, rows);
    }
    return 0;
}

int read_data(int* rows, int* cols) {   
    printf("Введите количество строк и столбцов матрицы: \n");
    return scanf("%d%d", rows, cols) == CORRECT;
}

int check_correct_size(int rows, int cols) {
    return rows >= 0 && cols >= 0;
}

void print_error() {
    printf("Incorrect input\n");
}

int** create_matrix(int rows, int cols) {
    int** matrix = (int**)calloc(rows, sizeof(int*));
    if (matrix != NULL) {
        int* vec = (int*)calloc(rows * cols, sizeof(int));
        if (vec != NULL) 
            transform(matrix, vec, rows, cols);
    }
    return matrix;
}

void transform(int** matrix, int* vec, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        matrix[i] = vec + i * cols;
}

int check_correct_memory(int** matrix) {
    return matrix != NULL;
}

int input_mat(int** matrix, int rows, int cols) {
    int s = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            s = scanf("%d", matrix[i] + j);
            if (!s)
                break;
        }
    return s;
}

int find_str_last_min(int** matrix, int rows, int cols) {
    int min_row = 1;
    int min = matrix[min_row][0];
    for (int i = min_row; i < rows; i++) {
        for (int j = 0; j < i && j < cols; j++) {
            if (matrix[i][j] <= min) {
                min = matrix[i][j];
                min_row = i;
            }
        }
    }
    return min_row;
}

void delete_rows(int** matrix, int* rows, int cols, int rows_last_min) {
    for (int i = rows_last_min; i < *rows - 1; i++) 
        for (int j = 0; j < cols; j++) 
            matrix[i][j] = matrix[i + 1][j];
    (*rows)--;
}

void free_matrix(int** matrix, int rows) {
    free(*matrix);
    free(matrix);
}

void print_result(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}
