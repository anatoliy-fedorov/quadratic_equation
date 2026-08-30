///@file
quadratic_equation gener_random_coefficients          ();
double gener_random_double                            (double);
int gener_random_int                                  ();
quadratic_equation gener_equation_with_one_roots      ();
quadratic_equation gener_equation_with_zero_roots     ();
quadratic_equation gener_equation_with_two_roots      ();
quadratic_equation gener_equation_with_many_roots     ();

/// @brief автоматическа€ генераци€ теста
/**
 * создаЄт тест, в котором может быть 0, 1, 2, или бесконечно много корней \n
 * количество корней в тесте определ€етс€ случайно
 * \return структура квадратного уравнени€(quadratic_equation) с готовыми коэффициентами, количеством корней и самими корн€ми
 */

quadratic_equation gener_random_coefficients() {

    int var_for_count_roots = gener_random_int();
    switch(var_for_count_roots % 4){
        case(e_zero_solution):
            return gener_equation_with_zero_roots();
        case(e_one_solution):
            return gener_equation_with_one_roots();
        case(e_two_solutions):
            return gener_equation_with_two_roots();
        case(e_many_solutions):
            return gener_equation_with_many_roots();
        default:
            return {};
    }

    return {};
}

/// @brief генераци€ теста, в котором нет корней
/**
 * создаЄт тест, в котором 0 решений \n
 * ни один коэффициент при этом не равен 0
 * \return структура квадратного уравнени€(quadratic_equation) где .count_of_roots = e_zero_solution, корни имеют значение NAN
 */

quadratic_equation gener_equation_with_zero_roots() {
    double a = 0, b = 0, c = 0, disc = 0;
    do {
        disc = gener_random_double(DIAPASON_FOR_B) - DIAPASON_FOR_B;
        b = gener_random_double(DIAPASON_FOR_B);
        c = gener_random_double(DIAPASON_FOR_B);
        a = - (disc - b * b) / (4 * c);
    } while (is_equals(a, 0));

    return {.a = a, .b = b, .c = c, .count_of_roots = e_zero_solution, .x1 = NAN, .x2 = NAN};
}

/// @brief генераци€ теста, в котором 1 решение
/**
 * создаЄт тест, в котором 1 корень \n
 * коэффициенты b и c могут принимать значение 0
 * \return структура квадратного уравнени€(quadratic_equation) где .count_of_roots = e_one_solution, .x1 не NAN, .x2 = NAN
 */

quadratic_equation gener_equation_with_one_roots() {
    double a = 0, b = 0, c = 0;
    double x1 = gener_random_double(DIAPASON_FOR_X);

    a =  gener_random_double(DIAPASON_FOR_A);
    b = - (x1 + x1) * a;
    c = x1 * x1 * a;

    return {.a = a, .b = b, .c = c, .count_of_roots = e_one_solution, .x1 = x1, .x2 = NAN};
}

/// @brief генераци€ теста, в котором 2 решени€
/**
 * создаЄт тест, в котором 2 корен€ \n
 * коэффициенты c может принимать значение 0
 * \return структура квадратного уравнени€(quadratic_equation) где .count_of_roots = e_two_solutions, .x1 и .x2 не NAN
 */

quadratic_equation gener_equation_with_two_roots() {
    double a = 0, b = 0, c = 0;
    double x1 = gener_random_double(DIAPASON_FOR_X);
    double x2 = gener_random_double(DIAPASON_FOR_X);
    quadratic_equation test = {};

    a =  gener_random_double(DIAPASON_FOR_A);
    b = - (x1 + x2) * a;
    c = x1 * x2 * a;

    if (!is_equals(x1, x2)){
        test = {.a = a, .b = b, .c = c, .count_of_roots = e_two_solutions, .x1 = x1, .x2 = x2};
    }
    else {
        test = {.a = a, .b = b, .c = c, .count_of_roots = e_one_solution, .x1 = x1, .x2 = NAN};
    }

    return test;
}

/// @brief генераци€ теста, в котором бесконечно много решений
/**

 * коэффициенты всегда одинаковы: a = 0, b = 0, c = 0
 * \return структура квадратного уравнени€(quadratic_equation) где .count_of_roots = e_many_solutions, .x1 = NAN, .x2 = NAN
 */

quadratic_equation gener_equation_with_many_roots() {
    return {.a = 0, .b = 0, .c = 0, .count_of_roots = e_many_solutions, .x1 = NAN, .x2 = NAN};
}

/// @brief создание случайного числа типа double
/**
 *\param diapason - диапазон, в котором будет сгенерировано число
 *\warning diapason должен быть положителен
 *\return число в диапазоне от -diapason до +diapason
 */
double gener_random_double(double diapason) {
    assert(isfinite(diapason));

    double rand_var = 0;
    do{
        rand_var = (double)rand() / RAND_MAX * (2*diapason) - diapason;
    }
    while(is_equals(rand_var, 0));
    return rand_var;
}
/// @brief создание случайного числа типа int
int gener_random_int() {
    return rand();
}
