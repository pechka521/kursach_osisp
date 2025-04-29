#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "fixed_point.h"

// Арифметические операции для фиксированной запятой (Q16.16)
fixed_point fixed_add(fixed_point a, fixed_point b);
fixed_point fixed_sub(fixed_point a, fixed_point b);
fixed_point fixed_mul(fixed_point a, fixed_point b);
fixed_point fixed_div(fixed_point a, fixed_point b);
fixed_point fixed_neg(fixed_point x);
fixed_point fixed_abs(fixed_point x);

#endif