///@file
#include "TXLib.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "conf.h"
#include "input_output.cpp"
#include "rand_test.cpp"
#include "tests.cpp"
#include "print_parabola.cpp"

int main (void)
{
    make_color();

    int count_success = run_tests();
    if (count_success != COUNT_OF_TEST) {
        printf("не все тесты пройдены \n");
        return -1;
    }

    quadratic_equation equation = {.a = 0, .b = 0, .c = 0, .count_of_roots = e_error, .x1 = NAN, .x2 = NAN};

    if (!input_coefficient(&equation.a, &equation.b, &equation.c)) {
        printf("Ввод некорректный\n");
        return -1;
    }

    solution_quadratic_equation(&equation);

    tx_print_parabola(equation.a, equation.b, equation.c);
    output_solution(equation.count_of_roots, equation.x1, equation.x2);

    printf("%lf, %lf, %lf", equation.a, equation.b, equation.c);

    return 0;
}


/// @brief функция для решения квадратного уравнения
/**
 * записывает корни в получаемую структуру
 * \param equation - указатель на структуру квадратного уравнения
 */

void solution_quadratic_equation(quadratic_equation* equation) {
    assert(equation);

    if (is_equals(equation->a, 0)) {
        no_full_quadratic_equation(equation);
    }
    else {                       // ax^2 + bx + c = 0
        solution_full_quadratic_equation(equation);
    }
}

/// @brief функция для решения квадратного уравнения, когда a != 0
/**
 * записывает корни в получаемую структуру
 * \param equation - указатель на структуру квадратного уравнения
 */

void solution_full_quadratic_equation(quadratic_equation* equation) {
    assert(equation);

    double disc = (equation->b * equation->b) - 4 * equation->a * equation->c;

    if (disc > 0) {
        equation->x1 = solution_linear_equation(2 * equation->a, equation->b + sqrt(disc));
        equation->x2 = solution_linear_equation(2 * equation->a, equation->b - sqrt(disc));
        if(!is_equals(equation->x1, equation->x2)) {
            equation->count_of_roots = e_two_solutions;
        }
        else{
            equation->count_of_roots = e_one_solution;
            equation->x2 = NAN;
        }
    }
    else if (is_equals(disc, 0)) {
        equation->x1 = solution_linear_equation(2 * equation->a, equation->b);
        equation->count_of_roots = e_one_solution;
    }
    else {
        equation->count_of_roots = e_zero_solution;
    }
}

/// @brief функция для решения квадратного уравнения, когда a = 0
/**
 * записывает корни в получаемую структуру
 * \param equation - указатель на структуру квадратного уравнения
 */

void no_full_quadratic_equation(quadratic_equation* equation) {
    assert(equation);

    if (is_equals(equation->b, 0)) {
        equation->count_of_roots = (is_equals(equation->c, 0)) ? e_many_solutions : e_zero_solution;
    }
    else {
        equation->x1 = solution_linear_equation(equation->b, equation->c);
        equation->count_of_roots = e_one_solution;
    }
}

/// @brief функция для решения линейного уравнения
/**
 * решает линейное уравнение вида ax + b = 0
 * \warning коэффициент a не должен быть 0
 * \param a, b - коэффициенты уравнения
 * \return решение линейного уравнения
 */

double solution_linear_equation(double a, double b) {
    assert(isfinite(a));
    assert(isfinite(b));

    return - b / a;
}

///@brief меняет цвет текста в терминале
/**
 * просит пользователя ввести определённое число в зависимости от желаемого цвета и устанавливает такой цвет текста в терминале \n
 * 0 - чёрный \n
 * 1 - красный \n
 * 2 - зелёный \n
 * 3 - жёлтый \n
 * 4 - синий \n
 * 5 - пурпурный \n
 * в случае неверного ввода, цвет не меняется и функция заканчивает работу
 */

void make_color() {
    printf("доступные цвета: \n(0)NO COLOR\n(1)RED\n(2)GREEN\n(3)YELLOW\n(4)BLUE\n(5)PURPURE \n");
    printf("выбирай цвет: ");

    int number_of_color = 0;
    int scanf_result = scanf("%d", &number_of_color);
    int char_after_scanf = '0';

    if(scanf_result != 1
    || ((char_after_scanf = getchar()) != ' ' && NOT_CHAR(char_after_scanf))
    || NOT_NUMBER(number_of_color)) {
        printf("Ввод некорректен, цвет не изменён\n");
        while(char_after_scanf != '\n' && (char_after_scanf = getchar()) != '\n');
        return;
    }

    find_color(number_of_color);
}

void find_color(int number_of_color) {
    switch(number_of_color) {
        case(e_no_color):
            printf("%s", NO_COLOR);   break;
        case(e_red):
            printf("%s", RED);        break;
        case(e_green):
            printf("%s", GREEN);      break;
        case(e_yellow):
            printf("%s", YELLOW);     break;
        case(e_blue):
            printf("%s", BLUE);       break;
        case(e_purpure):
            printf("%s", PURPURE);    break;
        default:
            printf("%s", NO_COLOR);
    }
}

/// @brief печать структуры квадратного уравнения

void print_struct(quadratic_equation equation) {
    printf("\u001b[36;1m");
    printf("a = %lf b = %lf c = %lf \n"
    "count of roots = %d  x1 = %lf x2 = %lf \n",
    equation.a, equation.b, equation.c, equation.count_of_roots, equation.x1, equation.x2);
}

/// @brief функция для оценки равенства двух чисел
/**
 * сравнивает два числа с определённой точностью EPSILON(conf.h)
 * \param a, b - сравниваемые числа
 * \return true в том случае, когда два числа равны с точностью до EPSILON, иначе false
 */

bool is_equals(double a, double b) {
    assert(isfinite(a));
    assert(isfinite(b));

    return (fabs(a - b) < EPSILON);
}

void sort_x(double* x1, double* x2){
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (*x1 < *x2) {
        swap(x1, x2);
    }
}

/// @brief меняет между собой значения двух чисел
/// @param a, b - указатели на числа, значения которых нужно поменять

void swap(double* a, double* b){
    assert(a);
    assert(b);
    assert(a != b);

    double temp = *a;
    *a = *b;
    *b = temp;
}

