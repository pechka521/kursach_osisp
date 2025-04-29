#ifndef CONVERSION_H
#define CONVERSION_H

#include "fixed_point.h"

// Функции конвертации между фиксированной запятой, float и int, а также печать представлений
fixed_point float_to_fixed(float x);
float fixed_to_float(fixed_point x);
fixed_point int_to_fixed(int x);
int fixed_to_int(fixed_point x);
void print_fixed_binary(fixed_point x);
void print_fixed_hex(fixed_point x);

#endif