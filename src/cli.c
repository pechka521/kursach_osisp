#include "cli.h"
#include "arithmetic.h"
#include "conversion.h"
#include "fixed_point.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Вывод справки с перечнем доступных команд.
 */
void print_help() {
    printf("\nДоступные команды:\n");
    printf("add <x> <y>    - Сложение\n");
    printf("sub <x> <y>    - Вычитание\n");
    printf("mul <x> <y>    - Умножение\n");
    printf("div <x> <y>    - Деление\n");
    printf("neg <x>        - Отрицание\n");
    printf("abs <x>        - Вычисление модуля\n");
    printf("tof <x>        - Преобразование в float\n");
    printf("toi <x>        - Преобразование в int\n");
    printf("bin <x>        - Двоичное представление\n");
    printf("hex <x>        - Шестнадцатеричное представление\n");
    printf("help           - Показать справку\n");
    printf("exit           - Выход из программы\n\n");
}

/**
 * Преобразование строкового аргумента в число с фиксированной запятой.
 * Если строка начинается с "0x"/"0X", пытается распознать шестнадцатеричный формат;
 * иначе – преобразует значение типа float.
 */
int parse_fixed(const char* str, fixed_point* result) {
    char* endptr;
    
    if (strlen(str) > 2 && str[0] == '0' && tolower(str[1]) == 'x') {
        *result = (fixed_point)strtoul(str, &endptr, 16);
        if (*endptr == '\0')
            return 0;
    }
    
    float fval = strtof(str, &endptr);
    if (endptr != str) {
        *result = float_to_fixed(fval);
        return 0;
    }
    
    return -1;
}

/**
 * Основной цикл интерфейса командной строки.
 * Считывает команду, обрабатывает аргументы и выполняет соответствующую операцию.
 */
void run_cli_interface() {
    printf("Эмулятор арифметических операций с фиксированной запятой (Q16.16)\n");
    print_help();
    
    char line[256];
    char cmd[16];
    fixed_point a = 0, b = 0;
    
    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
            break;
        
        if (sscanf(line, "%15s", cmd) < 1)
            continue;
        
        if (strcmp(cmd, "exit") == 0)
            break;
        if (strcmp(cmd, "help") == 0) {
            print_help();
            continue;
        }
        
        char* token = strtok(line, " \t\n");  // первый токен – команда
        int args_parsed = 0;
        int valid = 1;
        a = 0; b = 0;
        
        token = strtok(NULL, " \t\n");
        while (token != NULL && args_parsed < 2) {
            if (parse_fixed(token, args_parsed == 0 ? &a : &b) < 0) {
                fprintf(stderr, "Ошибка: Некорректный аргумент '%s'\n", token);
                valid = 0;
                break;
            }
            args_parsed++;
            token = strtok(NULL, " \t\n");
        }
        if (!valid)
            continue;
        
        if (strcmp(cmd, "add") == 0 && args_parsed == 2) {
            printf("Результат: %f\n", fixed_to_float(fixed_add(a, b)));
        }
        else if (strcmp(cmd, "sub") == 0 && args_parsed == 2) {
            printf("Результат: %f\n", fixed_to_float(fixed_sub(a, b)));
        }
        else if (strcmp(cmd, "mul") == 0 && args_parsed == 2) {
            printf("Результат: %f\n", fixed_to_float(fixed_mul(a, b)));
        }
        else if (strcmp(cmd, "div") == 0 && args_parsed == 2) {
            printf("Результат: %f\n", fixed_to_float(fixed_div(a, b)));
        }
        else if (strcmp(cmd, "neg") == 0 && args_parsed == 1) {
            printf("Результат: %f\n", fixed_to_float(fixed_neg(a)));
        }
        else if (strcmp(cmd, "abs") == 0 && args_parsed == 1) {
            printf("Результат: %f\n", fixed_to_float(fixed_abs(a)));
        }
        else if (strcmp(cmd, "tof") == 0 && args_parsed == 1) {
            printf("Число с плавающей точкой: %f\n", fixed_to_float(a));
        }
        else if (strcmp(cmd, "toi") == 0 && args_parsed == 1) {
            printf("Целое число: %d\n", fixed_to_int(a));
        }
        else if (strcmp(cmd, "bin") == 0 && args_parsed == 1) {
            print_fixed_binary(a);
        }
        else if (strcmp(cmd, "hex") == 0 && args_parsed == 1) {
            print_fixed_hex(a);
        }
        else {
            fprintf(stderr, "Ошибка: Неверная команда или аргументы\n");
        }
    }
}