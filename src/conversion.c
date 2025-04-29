#include "conversion.h"
#include "fixed_point.h"
#include <stdio.h>

/**
 * Преобразование числа с плавающей точкой в число с фиксированной запятой.
 */
fixed_point float_to_fixed(float x) {
    return (fixed_point)(x * FIXED_SCALE);
}

/**
 * Преобразование числа с фиксированной запятой в число с плавающей точкой.
 */
float fixed_to_float(fixed_point x) {
    return (float)x / FIXED_SCALE;
}

/**
 * Преобразование целого числа в число с фиксированной запятой.
 */
fixed_point int_to_fixed(int x) {
    return x << FIXED_SHIFT;
}

/**
 * Преобразование числа с фиксированной запятой в целое число с округлением.
 */
int fixed_to_int(fixed_point x) {
    return (x + (1 << (FIXED_SHIFT - 1))) >> FIXED_SHIFT;
}

/**
 * Вывод двоичного представления числа с фиксированной запятой.
 */
void print_fixed_binary(fixed_point x) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if (i == FIXED_SHIFT)
            printf(".");
    }
    printf("\n");
}

/**
 * Вывод шестнадцатеричного представления числа с фиксированной запятой.
 */
void print_fixed_hex(fixed_point x) {
    printf("0x%08X\n", (unsigned int)x);
}
