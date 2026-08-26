#include <stdio.h>
#include <TXLib.h>
#include <assert.h>
#include "input.h"



const int RIGHT_INPUT = 3;

//предлагает выбрать режим ввода коэффициентов
void coefficient_input(double *a, double *b, double *c) {
    assert(a);
    assert(b);
    assert(c);

    printf("какой будет ввод? \n");
    printf("(1) с клавиатуры \n");
    printf("(2) из файла \n");

    int number_of_input = 0;
    scanf("%d", &number_of_input);

    switch (number_of_input) {
        case(1):
            getc_coefficient_input(a, b, c, stdin);
            break;
        case(2):
            FILE* input_file;
            input_file = fopen("C:/projects/.vscode/input.txt", "r");
            getc_coefficient_input(a, b, c, input_file);
            break;
        default:
            printf("не выбран режим ввода");
    }

}

//инициализирует a b c, принима€ значени€ из input.txt или с клавиатуры
void getc_coefficient_input(double *a, double *b, double *c, FILE* file_input) {
    assert(a);
    assert(b);
    assert(c);

    double* arr_address[3];
    arr_address[0] = a;
    arr_address[1] = b;
    arr_address[2] = c;
    int count_of_success = 0;
    char arr_str[3][310];

    if (file_input == stdin) {
        printf("введи коэффициенты a b c \n");
    }

    while (count_of_success != 3) {

        read_lines(arr_str, file_input);

        // провер€ет возможность приведени€ строковых представлений a b и c к типу double
        // при наличии такой возможности мен€ет значени€ a b или c, а также увеличивает счЄтчик успешных переназначений
        for(int i = 0; i < 3; i++) {
            if(is_double(arr_str[i], arr_address[i])) {
                count_of_success++;
            }
        }
        // если не все значени€ a b и c были переназначены, число успешных переназначений обнул€етс€, ввод повтор€етс€
        if (count_of_success != 3) {
            count_of_success = 0;
            printf("ввод некорректен, повтори ввод \n");
        }
    }
}

// вводит 3 строки в массив arr_str(строка - последовательность подр€д идущих символов), полностью игнорирует пробелы, переносы строки, табул€ции
// в arr_str:
// в arr_str[0] попадает строковое представление a;
// в arr_str[1] попадает строковое представление b;
// в arr_str[2] попадает строковое представление c;
void read_lines(char arr_str[][310], FILE* file_input) {
    assert(arr_str);
    assert(file_input);

    int attempt =  0;

    while (attempt != 3) {
        int j = 0;
        char ch ='0';

        while ((ch = getc(file_input)) != ' ' && ch != '\n' && ch != '\t') {
            (arr_str[attempt][j]) = ch;
            j++;
        }
        arr_str[attempt][j] = '\0';

        if (j != 0) {
            attempt++;
        }
    }
}

// провер€ет, можно ли строку s привести в тип double, если да, то присваивает €чейке с адресом adress значение этой строки
bool is_double(char* s, double* address) {
    assert(s);
    assert(address);

    char* u = s;
    double d = strtod(s, &u);

    if (*u == '\0') {
        *address = d;
        return true;
    }
    return false;
}
