void tx_print_parabola                (double, double, double);
void print_coordinate_place           (double, double, double, double);
quadratic_equation value_of_x         (double, double, double, double);
double make_normal_y                  (double);
void print_point                      (double, double);
double make_y_coefficient             (double, double);
double division_price                 (double);
double make_normal_x                  (double);
void print_div_line_x                 (double, double);
void print_div_line_y                 (double, double);

void tx_print_parabola(double a, double b, double c) {
    txClearConsole();
    txCreateWindow(SIZE_X, SIZE_Y);

    double coordinate_of_top_x = - b / (2 * a);
    double coordinate_of_top_y = a * (coordinate_of_top_x * coordinate_of_top_x) + b * coordinate_of_top_x + c;
    double COEFFICIENT_Y = make_y_coefficient(coordinate_of_top_y, a);
    double COEFFICIENT_X = 0.5;
    double div_price_x = division_price(COEFFICIENT_X)*5;
    double div_price_y = division_price(COEFFICIENT_Y)*5;
    //printf("%lg %lg \n", div_price_x, div_price_y);
    double DELTA_Y = 1;
    //printf("%lg %lg \n", COEFFICIENT_X, COEFFICIENT_Y);
    print_coordinate_place(div_price_x, div_price_y, COEFFICIENT_X, COEFFICIENT_Y);

    for(double y = -(SIZE_Y / 2)/ COEFFICIENT_Y; y < (SIZE_Y / 2) / COEFFICIENT_Y; y += DELTA_Y / COEFFICIENT_Y) {
        quadratic_equation equation_with_y = value_of_x(a, b, c, y);

        if (!isnan(equation_with_y.x1)) {
            print_point(equation_with_y.x1 * COEFFICIENT_X, y * COEFFICIENT_Y);
        }
        if (!isnan(equation_with_y.x2)) {
            print_point(equation_with_y.x2 * COEFFICIENT_X, y * COEFFICIENT_Y);
        }
    }



}

double make_y_coefficient(double coordinate_of_top_y, double a) {
    if (fabs(a) < 2 && (coordinate_of_top_y < -200 || coordinate_of_top_y > 200)) {
        return 100 / (fabs(coordinate_of_top_y));
    }
    else if(coordinate_of_top_y < -200 || coordinate_of_top_y > 200) {
        return 100 / (fabs(coordinate_of_top_y) * sqrt(fabs(a)));
    }
    return 1;
}


double division_price (double coefficient) {

    double div_price_double = 1;
    while (div_price_double * coefficient < 1){
        div_price_double *= 10;
    }
    return div_price_double;
}

void print_point(double x, double y) {
    txSetPixel(make_normal_x(x), make_normal_y(y), RGB(255, 0, 0));
}

double make_normal_y(double y) {
    return (SIZE_Y / 2 - y);
}

double make_normal_x(double x) {
    return (SIZE_X / 2 + x);
}

quadratic_equation value_of_x(double a, double b, double c, double y) {
    quadratic_equation equation = {.a = a, .b = b, .c = c - y, .count_of_roots = e_error, .x1 = NAN, .x2 = NAN};
    solution_quadratic_equation(&equation);

    return equation;
}

void print_coordinate_place(double div_price_x, double div_price_y, double coefficient_x, double coefficient_y) {
    txLine(0, SIZE_Y / 2, SIZE_X, SIZE_Y / 2);
    txLine(SIZE_X / 2, 0, SIZE_X / 2, SIZE_Y);

    for(double x = 0; x < (SIZE_X / 2); x += div_price_x*coefficient_x) {
        print_div_line_x(x, coefficient_x);
    }
    for(double y = 0; y < (SIZE_Y / 2); y += div_price_y*coefficient_y) {
        print_div_line_y(y, coefficient_y);
    }
    for(double x = 0; x > -(SIZE_X / 2); x -= div_price_x*coefficient_x) {
        print_div_line_x(x, coefficient_x);
    }
    for(double y = 0; y > -(SIZE_Y / 2); y -= div_price_y*coefficient_y) {
        print_div_line_y(y, coefficient_y);
    }

    printf("цена деления x: %lg \n", div_price_x);
    printf("цена деления y: %lg \n", div_price_y);
}

void print_div_line_x(double x, double coefficient){
    txLine(make_normal_x(x), make_normal_y(-3), make_normal_x(x), make_normal_y(3));
}

void print_div_line_y(double y, double coefficient){
    txLine(make_normal_x(-3), make_normal_y(y), make_normal_x(3), make_normal_y(y));
}
