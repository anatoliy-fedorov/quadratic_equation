#include <stdio.h>
#include <TXLib.h>
#include <assert.h>
#include <math.h>
#include "input.h"
enum options_of_count_solution {e_zero_solution, e_one_solution,
    e_two_solutions, e_many_solutions, e_error};

const double EPSILON = 0.000001;

void output_solution           (int, double, double);
int solution_quadratic_equation(double, double, double, double *, double *);
double solution_linear_equation(double, double);
bool is_zero                   (double);

int main(void)
{
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    coefficient_input(&a, &b, &c);

    int count_solution = solution_quadratic_equation(a, b, c, &x1, &x2);

    output_solution(count_solution, x1, x2);
    printf("%lg %lg %lg", a, b, c);
    return 0;
}

void output_solution(int count_solution, double x1, double x2) {
    switch (count_solution) {
        case e_zero_solution:
            printf("нет решений \n");
            break;
        case e_one_solution:
            printf("один корень x = %lf \n", x1);
            break;
        case e_two_solutions:
            printf("два корня: x1 = %lf, x2 = %lf \n", x1, x2);
            break;
        case e_many_solutions:
            printf("бесконечное число корней \n");
            break;
        default:
            printf("программа завершена с ошибкой \n");
            break;
    }
}

int solution_quadratic_equation(double a, double b, double c, double *x1, double *x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (is_zero(a)) {
        if (is_zero(b)) {
            if (is_zero(c)) {    // 0x^2 + 0x + 0 = 0
                return e_many_solutions;
            }
            else {               // 0x^2 + 0x + c = 0
                return e_zero_solution;
            }
        }
        else {                   // 0x^2 + bx + c = 0
            *x1 = solution_linear_equation(b, c);
            return e_one_solution;
        }
    }
    else {                       // ax^2 + bx + c = 0
        double disc = (b * b) - 4 * a * c;
        if (disc > 0) {
            *x1 = solution_linear_equation(2 * a, b + sqrt(disc));
            *x2 = solution_linear_equation(2 * a, b - sqrt(disc));
            return e_two_solutions;
        }
        if (is_zero(disc)) {
            *x1 = solution_linear_equation(2 * a, b);
            return e_one_solution;
        }
        if (disc < 0) {
            return e_zero_solution;
        }
    }
    return e_error;
}

double solution_linear_equation(double a, double b) {
    return - b / a;
}

bool is_zero(double a) {
    if (abs(a) < EPSILON){
        return true;
    }
    return false;
}
