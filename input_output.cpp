///@file
bool input_coefficient          (double*, double*, double*);
void get_line_equation          (char*);
int get_int_variant_of_input    ();

void clear_spaces_in_line       (char*);
void format_after_equal         (char*);
bool get_coefficient_from_line  (double*, double*, double*);
bool to_separate_line           (char*, double*, double*, double*);
void convert_from_str_to_double (char*, double*, double*, double*);
double make_double_coefficient  (char*, char, bool);
bool is_okey_coefficient        (char*);
bool is_okey_str                (char*);

void get_coefficient_sep        (double *, double *, double *);
void output_solution            (options_of_count_solution, double, double);
bool one_input_sep              (double*, double*, double*, FILE*);
bool get_coefficient_from_file  (double*, double*, double*);
bool is_bad_char                (int);
void skip_line                  (FILE*);

/// функция для инициализации a, b и c
/**
 * организует ввод коэффициентов уравнения, предлагая при этом различные варианты ввода
 * \param a, b, c - указатели на переменные, значения которых будут введены
 * \return true в случае успешной инициализации и false в случае неудачи
 */

bool input_coefficient(double* a, double* b, double* c) {
    assert(a);
    assert(b);
    assert(c);

    int view_of_input = get_int_variant_of_input();

    switch(view_of_input){
        case(separated):
            get_coefficient_sep(a, b, c);
            return true;
        case(full_equation):
            return get_coefficient_from_line(a, b, c);
        case(from_file):
            return get_coefficient_from_file(a, b, c);
        default:
            return false;
    }
}

// предлагает пользователю варианты ввода коэффициентов
/**
 * \return числовое значение какого-то вида ввода
 * \return 1 - ввод коэффициентов через пробел
 * \return 2 - ввод всего уравнения целиком
 * \return 3 - ввод коэффициентов, записанных через пробел в файле input.txt
 */

int get_int_variant_of_input() {
    printf("какой будет ввод?\n(1)только коэффициенты\n(2)уравнение целиком\n(3)из файла\n");
    int input = 0;
    scanf("%d", &input);
    return input;
}

/// получает коэффициенты a b c из строки
/**
 * ВСЁ, ЧТО СВЯЗАНО С ЭТОЙ ФУНКЦИЕЙ ИМЕЕТ ПРИПИСКУ (УБОГИЙ ПАРСЕР) \n
 * строка должна иметь вид "ax^2 + bx + c = 0", могут обрабатываться операторы '+' и '-' \n
 * пример корректного ввода: x^2 - 8x + 3x^2 - 4x + 10 = 9
 * \param a, b, c - указатели на коэффициенты
 * \return true при удачном вводе и false, когда ввод некорректен
 */

bool get_coefficient_from_line(double* a, double* b, double* c) {
    assert(a);
    assert(b);
    assert(c);

    char str[MAX_LEN] = "";
    get_line_equation(str);

    if (!is_okey_str(str)){
        return false;
    }

    clear_spaces_in_line(str);

    return to_separate_line(str, a, b, c);
}

/// разделение строки на подстроки(УБОГИЙ ПАРСЕР)
/**
 * делит строку str на подстроки и запускает с каждой подстрокой функцию convert_from_str_to_double \n
 * разделителями служат знаки, т. е. каждая подстрока начинается с знака '+' или '-'
 * \param str, a, b, c - указатели на введённую строку и коэффициенты уравнения
 * \return true когда нет ошибок в введённой строке и false если ввод был некорректен
 */

bool to_separate_line(char* str, double* a, double* b, double* c) {
    assert(str);
    assert(a);
    assert(b);
    assert(c);

    int index = 0;
    while(str[index] != '=') {
        char temp_line[MAX_LEN] = "";
        int substr_index = 0;
        do {
            temp_line[substr_index] = str[index];
            index++;
            substr_index++;
        }
        while(str[index] != '+' && str[index] != '-' && str[index] != '=');

        if (!is_okey_coefficient(temp_line)) {
            return false;
        }
        convert_from_str_to_double(temp_line, a, b, c);
    }

    return true;
}

/// очистка строки от лишних символов(УБОГИЙ ПАРСЕР)
/**
 * убирает из строки все пробелы, табуляции и знаки '*' \n
 * переносит все значения стоящие правее знака '=' в левую часть строки, меняя знаки '+' на '-' и  '-' на '+'
 * \param str - обрабатываемая строка
 */

void clear_spaces_in_line(char* str) {
    assert(str);

    size_t str_len = strlen(str);
    int iterator = 0;

    for(size_t i = 0; i < str_len; i++){
        if (str[i] != ' ' && str[i] != '*' && str[i] != '\t' && str[i] != '\n') {
            str[iterator] = str[i];
            iterator++;
        }
    }
    str[iterator] = '\0';
    format_after_equal(str);
}

// TODO УПРОСТИТЬ ФУНКЦИЮ
// переносит всё что после пробела влево, меняя при этом знаки(УБОГИЙ ПАРСЕР)
void format_after_equal(char* str) {
    assert(str);

    size_t len = strlen(str), iterator = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '=') {
            iterator = i;
            if (str[i+1] != '-' && str[i+1] != '+'){
                str[iterator] = '-';
                iterator++;
            }
        }
        else if (iterator) {
            switch (str[i]) {
                case ('+'):
                    str[iterator] = '-'; break;
                case ('-'):
                    str[iterator] = '+'; break;
                default:
                    str[iterator] = str[i]; break;
            }

            iterator++;
        }
    }
    str[iterator] = '=';
    str[iterator+1] = '0';
    str[iterator+2] = '\0';
}

void get_line_equation(char* str) {
    assert(str);

    printf("ну раз себе на беду запустил, то вводи\n");
    skip_line(stdin);
    fgets(str, MAX_LEN, stdin);
}

/// проверяет, что в строке есть только один знак '=' (УБОГИЙ ПАРСЕР)
/**
 * \param str - введённая строка
 * \return true если в строке только один знак '=',в противном случае false
 */

bool is_okey_str(char* str) {
    assert(str);

    size_t len = strlen(str), count_of_equals = 0;
    for(size_t i = 0; i < len; i++) {
        if (str[i] == '=') {
            count_of_equals++;
        }
    }
    return (count_of_equals == 1);
}

// проверяет, можно ли строку str передавать в функцию convert_from_str_to_double(УБОГИЙ ПАРСЕР)
bool is_okey_coefficient(char* str) {
    assert(str);

    size_t len = strlen(str);
    size_t place_x = 0, count_of_dot = 0;

    for (size_t i = 0; i < len; i++) {
        if (isalpha(str[i]) && str[i] != 'x') {
            return false;
        }
        else if (str[i] == 'x') {
            place_x = i;
        }
        if (str[i] == '.') {
            count_of_dot++;
        }
    }

    if (count_of_dot > 1 || (strstr(str, "x") && NOT_OKAY_SYMBOLS_AFTER_X(len, place_x, str))) {
        return false;
    }
    return true;
}

//(УБОГИЙ ПАРСЕР)
// меняет значение a b или c в зависимости от подаваемой строки
void convert_from_str_to_double(char* str, double* a, double* b, double* c) {
    assert(str);
    assert(a);
    assert(b);
    assert(c);

    if (strstr(str, "x^2")) {
        *a += make_double_coefficient(str, STOP_SYMBOL_AB, ITS_A_OR_B);
    }
    else if(strstr(str, "x")) {
        *b += make_double_coefficient(str, STOP_SYMBOL_AB, ITS_A_OR_B);
    }
    else {
        *c += make_double_coefficient(str, STOP_SYMBOL_C, ITS_C);
    }
}

/// перевод строки в double(УБОГИЙ ПАРСЕР)
/**
 * читает строку до стоп-символа или её конца(смотря что будет раньше) \n
 * считанную часть строки переводит в double и возвращает это число
 */

double make_double_coefficient(char* str, char stop_symbol, bool is_a_or_b) {
    assert(str);

    char temp_line[MAX_LEN] = "";
    size_t len = strlen(str), i = 0;
    while (i < len && str[i] != stop_symbol){
        temp_line[i] = str[i];
        i++;
    }

    if (is_a_or_b && (i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))) {
        temp_line[i] = '1';
    }
    return atof(temp_line);
}

/// считывает коэффициенты, введённые через пробел из консоли
/**
 * просит ввести коэффициенты до тех пор, пока ввод не будет корректным
 * \param a, b, c - указатели на переменные, значения которых будут введены
 */


void get_coefficient_sep(double* a, double* b, double* c) {
    assert(a);
    assert(b);
    assert(c);

    bool error_input = false;
    printf("ну вводи коэффициенты \n");
    do{
        error_input = !(one_input_sep(a, b, c, stdin));
        if (error_input) {
            printf("ввод некорректен \n");
        }
    }while(error_input);
}

/// один раз получает значения коэффициентов из файла
/**
 * \param a, b, c - указатели на коэффициенты
 * \param file - файл, из которого будет организован ввод
 * \return true при успешном вводе, иначе false
 */

bool one_input_sep(double* a, double* b, double* c, FILE* file){
    assert(a);
    assert(b);
    assert(c);
    assert(file);

    int char_after_coef = ' ', count_of_coefficients = 0;
    count_of_coefficients += fscanf(file, "%lg %lg %lg", a, b, c);
    char_after_coef = getc(file);

    if (is_bad_char(char_after_coef) || count_of_coefficients != 3) {
        skip_line(file);
        return false;
    }
    else{
        return true;
    }
}
/// получение коэффициентов уравнения из файла
/**
 * получает коэффициенты из заранее созданного файла "input.txt"
 * \param a, b, c - указатели на переменные, значения которых будут введены
 * \warning коэффициенты должны быть записаны в файле через пробел
 */

bool get_coefficient_from_file(double* a, double* b, double* c) {
    assert(a);
    assert(b);
    assert(c);

    FILE* input_file = fopen(MY_FILE, "r");
    assert(input_file);
    return one_input_sep(a, b, c, input_file);
}

/// @brief  пропускает одну строку в читаемом файле
/// @param file - указатель на файл, в котором нужно пропустить строку
void skip_line(FILE* file) {
    assert(file);

    int ch = '0';
    while ((ch = getc(file)) != '\n');
}

bool is_bad_char(int char_after_coef) {
    return (char_after_coef != ' '  && char_after_coef != '\n' && char_after_coef != '\t');
}

/// вывод количества решений уравнения и самих решений
/**
 * \param count_of_solution - количество решений уравнения
 * \param x1, x2 - сами решения уравнения
 */

void output_solution(options_of_count_solution count_of_solution, double x1, double x2) {

    switch (count_of_solution) {
        case e_error:
            printf("на этапе решения уравнения произошла ошибка");
            break;
        case e_zero_solution:
            printf("нет решений \n");
            break;
        case e_one_solution:
            printf("одно решение x = %lf \n", x1);
            break;
        case e_two_solutions:
            printf("два решения: x1 = %lf, x2 = %lf \n", x1, x2);
            break;
        case e_many_solutions:
            printf("бесконечно много решений \n");
            break;
        default:
            printf("ошибка вывода \n");
            break;
    }
}
