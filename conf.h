///@file
#ifndef CONF_H
#define CONF_H

#define RED   "\u001b[31;1m"
#define GREEN "\u001b[32;1m"
#define YELLOW "\u001b[33;1m"
#define BLUE "\u001b[34;1m"
#define PURPURE "\u001b[35;1m"
#define NO_COLOR "\u001b[30m"
#define NOT_CHAR(char_after_scanf) (char_after_scanf != '\t' && char_after_scanf != '\n')
#define NOT_NUMBER(number_of_color) (number_of_color > 5 || number_of_color < 0)
#define NOT_OKAY_SYMBOLS_AFTER_X(len, place_x, str) ((len - place_x == 3 && (str[place_x+1] != '^' || str[place_x+2] != '2')) || (len - place_x != 1 && len - place_x != 3))

/// @brief количество корней у квадратного уравнения
enum options_of_count_solution {e_zero_solution, e_one_solution,
    e_two_solutions, e_many_solutions, e_error
};

/// @brief варианты цвета текста в терминале
enum colors {e_no_color, e_red, e_green, e_yellow, e_blue, e_purpure};

/// @brief варианты вида ввода
enum views_of_input {separated = 1, full_equation = 2, from_file = 3};

/// @brief структура квадратного уравнения
/**
 * \param a, b, c - коэффициенты уравнения
 * \param count_of_roots - количество решений уравнения
 * \param x1, x2 - корни уравнения
 */
struct quadratic_equation {
    double a;
    double b;
    double c;
    options_of_count_solution count_of_roots;
    double x1;
    double x2;
};

const double SIZE_X = 900;
const double SIZE_Y = 400;

const int COUNT_OF_VARIABLE = 6;
const double EPSILON =0.0001;

const int COUNT_OF_MY_TEST = 7;
const int COUNT_OF_GENER_TEST = 1000;
const int COUNT_OF_TEST = COUNT_OF_MY_TEST + COUNT_OF_GENER_TEST;

const double DIAPASON_FOR_X = 1000;
const double DIAPASON_FOR_A = 50;
const double DIAPASON_FOR_B = 2000;

const int MAX_LEN = 1000;
const int MIN_LEN = 3;

const char STOP_SYMBOL_AB = 'x';
const char STOP_SYMBOL_C = '=';
const bool ITS_A_OR_B = true;
const bool ITS_C = false;

/// @brief файл, из которого будут браться коэффициенты при вводе из файла
const char MY_FILE[MAX_LEN] = "C:/projects/quadratic_equation/input.txt";

/// @brief массив тестов, которые создаются вручную
const quadratic_equation TESTS[COUNT_OF_MY_TEST] = {
    {0, 0, 0, e_many_solutions, NAN, NAN},
    {1, 2, 1, e_one_solution, -1, NAN},
    {1, -12, 35, e_two_solutions, 7, 5},
    {0, 5, -10, e_one_solution, 2, NAN},
    {1, 8, 100, e_zero_solution, NAN, NAN},
    {1, 0, 0, e_one_solution, 0, NAN},
    {1, -5, 6, e_two_solutions, 2, 3}
};

void solution_quadratic_equation      (quadratic_equation*);
void solution_full_quadratic_equation (quadratic_equation*);
void no_full_quadratic_equation       (quadratic_equation*);
double solution_linear_equation       (double, double);
bool is_equals                        (double, double);
void swap                             (double*, double*);
void sort_x                           (double*, double*);
void make_color                       ();
void find_color                       (int);
void print_struct                     (quadratic_equation);

#endif
