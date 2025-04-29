#include "arithmetic.h"
#include "fixed_point.h"
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>  // Для llabs

/**
 * Функция сложения двух чисел с фиксированной запятой.
 * При переполнении выводится предупреждение.
 */
fixed_point fixed_add(fixed_point a, fixed_point b) {
    fixed_point result = a + b;
    if ((b > 0 && a > FIXED_MAX - b) || (b < 0 && a < FIXED_MIN - b)) {
        fprintf(stderr, "Предупреждение: Возможное переполнение при сложении\n");
    }
    return result;
}

/**
 * Функция вычитания двух чисел с фиксированной запятой.
 * При переполнении выводится предупреждение.
 */
fixed_point fixed_sub(fixed_point a, fixed_point b) {
    fixed_point result = a - b;
    if ((b > 0 && a < FIXED_MIN + b) || (b < 0 && a > FIXED_MAX + b)) {
        fprintf(stderr, "Предупреждение: Возможное переполнение при вычитании\n");
    }
    return result;
}

/**
 * Функция умножения двух чисел с фиксированной запятой.
 * Выполняется корректное округление с учетом знака аргументов.
 * При переполнении выводится сообщение об ошибке и возвращается предел.
 */
fixed_point fixed_mul(fixed_point a, fixed_point b) {
    int64_t temp = (int64_t)a * b;
    
    if (temp >= 0)
        temp += 1LL << (FIXED_SHIFT - 1);
    else
        temp -= 1LL << (FIXED_SHIFT - 1);
    
    temp >>= FIXED_SHIFT;
    
    if (temp > FIXED_MAX || temp < FIXED_MIN) {
        fprintf(stderr, "Ошибка: Переполнение при умножении\n");
        return (a ^ b) < 0 ? FIXED_MIN : FIXED_MAX;
    }
    return (fixed_point)temp;
}

/**
 * Функция деления двух чисел с фиксированной запятой.
 * Выполняется округление с учетом знака, а также проверка деления на ноль.
 */
fixed_point fixed_div(fixed_point a, fixed_point b) {
    if (b == 0) {
        fprintf(stderr, "Ошибка: Деление на ноль\n");
        return (a < 0) ? FIXED_MIN : FIXED_MAX;
    }
    
    int64_t temp = ((int64_t)a << FIXED_SHIFT);
    int64_t offset = llabs(b) / 2;
    if ((temp >= 0 && b > 0) || (temp < 0 && b < 0))
        temp += offset;
    else
        temp -= offset;
    
    return (fixed_point)(temp / b);
}

/**
 * Функция вычисления отрицания числа.
 * Обрабатывается ситуация переполнения.
 */
fixed_point fixed_neg(fixed_point x) {
    if (x == FIXED_MIN) {
        fprintf(stderr, "Ошибка: Переполнение при отрицании\n");
        return FIXED_MAX;
    }
    return -x;
}

/**
 * Функция вычисления модуля числа.
 * Обрабатывается ситуация переполнения.
 */
fixed_point fixed_abs(fixed_point x) {
    if (x == FIXED_MIN) {
        fprintf(stderr, "Ошибка: Переполнение при вычислении модуля\n");
        return FIXED_MAX;
    }
    return x < 0 ? -x : x;
}
