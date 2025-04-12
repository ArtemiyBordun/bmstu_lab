#include <stdio.h>
#include <math.h>

#define CORRECT 3 
#define TWO 2

int read_data(double* a, double* b, double* e);
int check_data(double a, double b, double e);
void print_error();
void print_result(double result);
double calculate_step(double a, double b, int n);
double calculate_xi(double a, double h, int i);
double calculate_sum(double a, double b, double e);
double calculate_integral(double a, double b, int n);

int main(void) {
    double a, b, e;
    if (!read_data(&a, &b, &e) || !check_data(a, b, e))
        print_error();
    else 
        print_result(calculate_sum(a, b, e));
    return 0;
}
int read_data(double* a, double* b, double* e) {
    printf ("Введите пределы интегрирования a и b и точность E: \n");
    return (scanf ("%lf %lf %lf", a, b, e) == CORRECT);
}
int check_data(double a, double b, double e) {
    return (e > 0) && (a > 0) && (b > 0);
}
void print_error() {
    printf ("Incorrect input\n");
}
double func(double x) {
    return log(x);
}
double calculate_step(double a, double b, int n) {
    return (b - a) / n;
}
double calculate_xi(double a, double h, int i) {
    return a + (i + 0.5) * h;
}
double calculate_integral(double a, double b, int n) {
    double s = 0.0;
    double h = calculate_step(a, b, n);
    for (int i = 0; i < n; i++) {
        double x_i = calculate_xi(a, h, i); //вычисляем высоту i-прямоугольника
        s += func(x_i) * h; //интеграл, через площади i-прямоугольников
    }
    return s;
}
double calculate_sum(double a, double b, double e) {
    int n = 2;
    double s = calculate_integral(a, b, n), prev_s = 0;
    do {
        prev_s = s; 
        n *= TWO;
        s = calculate_integral(a, b, n);
    } while (fabs (s - prev_s) > e);
    return s;
}
void print_result(double result) {
    printf ("%.6lf\n", result);
}