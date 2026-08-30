///@file
int run_tests                         ();
bool run_one_test                     (quadratic_equation, int);
bool is_success_test                  (quadratic_equation*, quadratic_equation*);
void answer_to_test                   (quadratic_equation, quadratic_equation, bool, int);
bool additional_check                 (quadratic_equation*, quadratic_equation*);
bool if_zero_solution                 (quadratic_equation*);
bool if_one_solution                  (quadratic_equation*, quadratic_equation*);
bool if_two_solution                  (quadratic_equation*, quadratic_equation*);

int run_tests() {
    int count_success = 0;
    for (int number_of_test = 0; number_of_test < COUNT_OF_MY_TEST; number_of_test++) {
        quadratic_equation test = TESTS[number_of_test];
        count_success += run_one_test(test, number_of_test);
    }

    for (int number_of_test = 0; number_of_test < COUNT_OF_GENER_TEST; number_of_test++) {
        quadratic_equation test = gener_random_coefficients();
        count_success += run_one_test(test, number_of_test);
    }
    return count_success;
}

bool run_one_test(quadratic_equation test, int number_of_test){
    quadratic_equation real_equation  = {.count_of_roots = e_error, .x1 = NAN, .x2 = NAN};

    real_equation.a = test.a;
    real_equation.b = test.b;
    real_equation.c = test.c;

    solution_quadratic_equation(&real_equation);

    bool success = is_success_test(&test, &real_equation);

    answer_to_test(test, real_equation, success, number_of_test);

    return success;
}

bool is_success_test(quadratic_equation* test, quadratic_equation* real_equation) {
    assert(test);
    assert(real_equation);

    if (test->count_of_roots != real_equation->count_of_roots) {
        return false;
    }
    else {
        return additional_check(test, real_equation);
    }
}

bool additional_check(quadratic_equation* test, quadratic_equation* real_equation) {
    assert(test);
    assert(real_equation);

    if (test->count_of_roots == e_zero_solution || test->count_of_roots == e_many_solutions) {
        return if_zero_solution(real_equation);
    }
    else if (test->count_of_roots == e_one_solution ){
        return if_one_solution(test, real_equation);
    }
    else if (test->count_of_roots == e_two_solutions){
        sort_x(&test->x1, &test->x2);
        sort_x(&real_equation->x1, &real_equation->x2);
        return if_two_solution(test, real_equation);
    }
    else {
        return true;
    }
}

bool if_zero_solution(quadratic_equation* real_equation) {
    return isnan(real_equation->x1) && isnan(real_equation->x2);
}

bool if_one_solution(quadratic_equation* test, quadratic_equation* real_equation) {
    return is_equals(test->x1, real_equation->x1) && isnan(real_equation->x2);
}

bool if_two_solution(quadratic_equation* test, quadratic_equation* real_equation) {
    return is_equals(test->x1, real_equation->x1) && is_equals(test->x2, real_equation->x2);
}

void answer_to_test(quadratic_equation test, quadratic_equation real_equation, bool success, int number_of_test) {
    if (!success) {
        printf("\u001b[31;1m");
        printf("test %d error \n"
            "coefficients: a = %lf b = %lf c = %lf \n"
            "ref variables: count roots = %d x1 = %lf x2 = %lf \n"
            "real variables: count roots = %d x1 = %lf x2 = %lf \n",
            number_of_test, test.a, test.b, test.c, test.count_of_roots, test.x1, test.x2, real_equation.count_of_roots, real_equation.x1, real_equation.x2
        );
    }
}
