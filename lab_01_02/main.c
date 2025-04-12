#include <stdio.h>
#include <math.h>

#define EPS 0.000001     // Вводим погрешность
#define CORRECT 2        // Количество корректно введенных значений

enum Position {
    Pos1 = 1, 
    Pos2 = 2, 
    Pos3 = 3,
    Pos4 = 4,
    Pos5 = 5,
    Pos6 = 6,
    Pos7 = 7,
    Pos11 = 11,
    Pos12 = 12,
    Pos13 = 13,
    Pos22 = 22,
    Pos23 = 23,
    Pos33 = 33
};

int read_data (double* x, double* y);
void print_result (int s);
double calculate_line_a (double x, double y);
double calculate_line_b (double x, double y);
double calculate_line_c (double x, double y);
int calculate_region (double y_line_a, double y_line_b, double y_line_c);
int calculate_lines (double y_line_a, double y_line_b, double y_line_c);
void print_head ();
void print_error ();

int main (void) {
    double a, b;
    
    if (read_data (&a, &b)) {
        print_error ();
    }
    else {
        double y_line_a = calculate_line_a (a, b);
        double y_line_b = calculate_line_b (a, b);
        double y_line_c = calculate_line_c (a, b);

        int s = calculate_region (y_line_a, y_line_b, y_line_c);
        if (s == 0)
            s = calculate_lines (y_line_a, y_line_b, y_line_c);
        print_result (s);
    }
    return 0;
}
void print_head () {
    printf("Line equations:\n1. y = 2x + 2\n2. y = 0.5x - 1\n3. y = -x + 2\nEnter point coordinates: ");
}

int read_data (double* x, double* y) { // Вводим координаты точки
    print_head ();
    return scanf ("%lf %lf", x, y) != CORRECT;
}
void print_error () {
    printf ("Result: Incorrect input\n"); // Выводим ошибку, если координаты введены некорректно
}

double calculate_line_a (double x, double y) {
    return (2 * x + 2) - y;
}

double calculate_line_b (double x, double y) {
    return (0.5 * x - 1) - y;
}

double calculate_line_c (double x, double y) {
    return (-x + 2) - y;
}

int calculate_region (double y_line_a, double y_line_b, double y_line_c) {
    int zone = 0;

    // Проверяем, где находится точка относительно зон
    if (0 < y_line_a && 0 > y_line_b && 0 > y_line_c)
        zone = Pos1;
    else if (0 < y_line_b && 0 > y_line_c)
        zone = Pos2;
    else if (0 < y_line_a && 0 < y_line_b && 0 < y_line_c)
        zone = Pos3;
    else if (0 > y_line_a && 0 < y_line_b)
        zone = Pos4;
    else if (0 > y_line_a && 0 > y_line_b && 0 < y_line_c)
        zone = Pos5;
    else if (0 > y_line_a && 0 > y_line_c)
        zone = Pos6;
    else if (0 < y_line_a && 0 > y_line_b && 0 < y_line_c)
        zone = Pos7;

    return zone;
}

int calculate_lines (double y_line_a, double y_line_b, double y_line_c) {
    int lines = 0;

    if (fabs (y_line_a) <= EPS) { // Точка лежит на прямой 1
        if (fabs (y_line_b) <= EPS) // Точка лежит и на 1 и на 2
            lines = Pos12;
        else if (fabs (y_line_c) <= EPS)
            lines = Pos13;
        else
            lines = Pos11;
    } 
    else if (fabs (y_line_b) <= EPS) {
        if (fabs (y_line_c) <= EPS)
            lines = Pos23;
        else
            lines = Pos22;
    } 
    else 
        lines = Pos33;

    return lines;
}

void print_result (int s) {
    if (s <= Pos7 && s != 0) 
        printf ("Result: Point placed in region %d", s); 
    else if (s == Pos11 || s == Pos22 || s == Pos33) 
        printf ("Result: Point placed on line %d", s/11);
    else {
        switch (s) {
            case 12:
                printf ("Result: Point placed on lines 1 and 2");
                break;
            case 13:
                printf ("Result: Point placed on lines 1 and 3");
                break;
            case 23:
                printf ("Result: Point placed on lines 2 and 3");
                break;
        }
    }
}