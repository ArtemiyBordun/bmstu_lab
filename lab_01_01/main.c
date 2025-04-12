#include <stdio.h>
#include <math.h>

#define EPS 0.000001   //вводим погрешность
#define CORRECT 2      //Количество корректно введенных значений

int read_data (double* x, double* y);
void print_result (int s);
int calculation_point (double y_line);
double calculation_line (double x, double y);
void print_head ();
void print_error ();

int main (void) {
    double a, b;

    if (read_data (&a, &b)) {
        print_error ();
    }   
    else {
        double y_line = calculation_line (a, b);
        int s = calculation_point (y_line);
        print_result (s);
    }
    return 0;
}
void print_head () {
    printf ("Line equation: y = 0.5x + 1\n"); 
    printf ("Enter points coordinate: \n");
}
int read_data (double* x, double* y) {            //вводим координаты точки      
    print_head ();
    return scanf("%lf %lf", x, y) != CORRECT;
}
void print_error() {
    printf ("Result: Incorrect input\n");        //выводим ошибку, если координаты введины не корректно
}
double calculation_line (double x, double y) {
    return (0.5 * x + 1) - y;
}
int calculation_point (double y_line) {
    int s;

    if (fabs (y_line) < EPS) 
        s = 0;
    else if (0 > y_line) 
        s = 1;
    else 
        s = -1;
    return s;
}
void print_result (int s) {
    if (s == 1) 
        printf ("Result: Point is above the line");
    else if (s == 0) 
        printf ("Result: Point is on the line");
    else
        printf ("Result: Point is under the line");
}