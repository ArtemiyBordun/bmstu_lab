#include <stdio.h>
#include <math.h>

#define CORRECT 3
#define MIN 2

int read_data(double* left_border, double* right_border, int* iteration);
void print_result(double i);
int check_data(double left_border, double right_border, double iteration);
void calculation_circle_for(double left_border, double right_border, double interval);
void calculation_circle_while(double left_border, double right_border, double interval);
void calculation_circle_do_while(double left_border, double right_border, double interval);
double calculation_interval(double left_border, double right_border, int iteration);
void print_error();
double func(double x);

int main(void) {
    double left_border, right_border;
    int iteration;
    if (!read_data(&left_border, &right_border, &iteration) || !check_data(left_border, right_border, iteration))
        print_error();
    else {
        double interval = calculation_interval(left_border, right_border, iteration);
        calculation_circle_for(left_border, right_border, interval);
        calculation_circle_while(left_border, right_border, interval);
        calculation_circle_do_while(left_border, right_border, interval);
    }
    return 0;
}
int check_data(double left_border, double right_border, double iteration) {
    int err = 1;
    if (left_border >= right_border || iteration < MIN) 
        err = 0;
    return err;
}
double func(double x) {
    double fx = (sin (x) * sin (x)) / x;
    double result = 0;
    if (isnan (fx) || isinf (fx)) 
        result = NAN;
    else
        result = fx;
    return result;
}
int read_data(double* left_border, double* right_border, int* iteration) {
    return scanf ("%lf %lf %d", left_border, right_border, iteration) == CORRECT;
}
void print_error() {
    printf ("Incorrect input");
}
double calculation_interval(double left_border, double right_border, int iteration) {
    return (right_border - left_border) / (iteration - 1);
}
void calculation_circle_for(double left_border, double right_border, double interval) { 
    printf ("for: \nx\t|");
    for (double i = left_border; i <= right_border; i += interval) {
        print_result (i);
    }
    printf ("\nf(x)\t|");
    for (double i = left_border; i <= right_border; i += interval) {
        print_result (func (i));
    }
    printf("\n\n");
}
void calculation_circle_while(double left_border, double right_border, double interval) {
    double i = left_border;
    printf ("while: \nx\t|");
    while (i <= right_border) {
        print_result (i);
        i += interval;
    }
    i = left_border;
    printf ("\nf(x)\t|");
    while (i <= right_border) {
        print_result (func (i));
        i += interval;
    }
    printf ("\n\n");
}
void calculation_circle_do_while(double left_border, double right_border, double interval) {
    double i = left_border;

    printf ("do while: \nx\t|");
    do {
        print_result (i);
        i += interval;
    } while (i <= right_border);
    
    i = left_border;
    printf ("\nf(x)\t|");
    do {
        print_result (func (i));
        i += interval;
    } while (i <= right_border);
    printf ("\n\n");
}
void print_result(double i) {
    printf ("%.3lf\t|", i);
}