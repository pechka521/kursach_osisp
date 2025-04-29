#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>
#include <limits.h>

#define FIXED_SHIFT 16
#define FIXED_SCALE (1 << FIXED_SHIFT)
#define FIXED_MAX INT32_MAX
#define FIXED_MIN INT32_MIN

typedef int32_t fixed_point;

#endif