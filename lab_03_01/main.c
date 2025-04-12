#include <stdio.h>
#include <math.h>

double calculate_sum(double e);
void print_result(double result);
int read_data(double* e);
void print_error();

int main(void) {
    double e;
    if (!read_data(&e)) 
        print_error();
    else 
        print_result(calculate_sum(e));
    return 0;
}
int read_data(double* e) {
    printf("Введите точность E: \n");
    return (scanf("%lf", e)) && (*e > 0);
}
void print_error() {
    printf("Incorrect input\n");
}
double calculate_sum(double e) {
    int n = 0;  
    double term = 1;
    double sum = term;  //вместо sum += term; чтобы не считать последнюю иттерацию

    while (fabs (term) > e) {
        n++;
        term /= -n;
        sum += term;
    }
    return sum;
}
void print_result(double result) {
    printf ("%.6lf\n", result);
}