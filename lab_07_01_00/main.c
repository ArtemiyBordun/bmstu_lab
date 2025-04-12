#include <stdio.h>
#include <stdlib.h>

//0 вар. змейка горизонтальная, начиная с левого верхнего элемента матрицы

#define TWO 2

int read_data(int* rows, int* cols);
int check_correct_size(int rows, int cols);
void print_error();
int** create_matrix(int rows, int cols);
void transform(int** matrix, int* vec, int rows, int cols);
int check_correct_memory(const int** matrix);
int input_mat(int** matrix, int rows, int cols);
void sort_mas(int* array, int len);
void reverse_rows(int** matrix, int rows, int cols);
void reverse_row(int** matrix, int cols);
void swap(int* value1, int* value2);
void free_arr(int** matrix);
void print_result(const int** matrix, int rows, int cols);

int main() {
    int rows, cols;
    if (!read_data(&rows, &cols) || !check_correct_size(rows, cols)) 
        print_error();
    else {
        int** matrix = create_matrix(rows, cols);

        if (!check_correct_memory((const int**)matrix) || !input_mat(matrix, rows, cols))
            print_error();
        else {    
            int len = rows * cols;
            sort_mas(*matrix, len);
            reverse_rows(matrix, rows, cols);
            print_result((const int**)matrix, rows, cols);
        }
        free_arr(matrix);
    }
    return 0;
}

int read_data(int* rows, int* cols) {
    printf("Введите размер матрицы: \n");
    return scanf("%d %d", rows, cols) == TWO;
}

int check_correct_size(int rows, int cols) {
    return rows > 0 && cols > 0;
}

void print_error() {
    printf("Incorrect input\n");
}

int** create_matrix(int rows, int cols) {
    int** matrix = 0;
    if (check_correct_size(rows, cols)) {
        matrix = (int**)calloc(rows, sizeof(int*));
            if (matrix != NULL) {
            int* vec = (int*)calloc(rows * cols, sizeof(int));
            if (vec == NULL) {
                free(matrix);
                matrix = NULL;
            }
            else
                transform(matrix, vec, rows, cols);
        }
    }
    return matrix;
}

void transform(int** matrix, int* vec, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        matrix[i] = vec + i * cols;
}

int check_correct_memory(const int** matrix) {
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

void sort_mas(int* array, int len) {
    for (int i = len - 1; i >= 0; i--)
        for (int j = 0; j < i; j++)
            if (*(array + j) > *(array + j + 1))
                swap(array + j, array + j + 1);
        
}

void reverse_row(int** matrix, int cols) {
    for (int i = 0, j = cols - 1; i < j; i++, j--)
        swap(*matrix + i, *matrix + j);
}

void reverse_rows(int** matrix, int rows, int cols) {
    for (int row = 1; row < rows; row += TWO)
        reverse_row(matrix + row, cols);
}

void swap(int* value1, int* value2) {
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

void free_arr(int** matrix) {
    free(*matrix);
    free(matrix);
}

void print_result(const int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
        }
}