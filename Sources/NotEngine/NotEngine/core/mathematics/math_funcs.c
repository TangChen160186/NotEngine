#include <math.h>
#include <stdio.h>
#include "math_funcs.h"
// 函数实现（小写，使用下划线分隔）
float math_sqrt(float v) {
    return sqrtf(v);
}

float math_abs(float v) {
    return fabsf(v);
}

float math_sin(float v) {
    return sinf(v);
}

float math_cos(float v) {
    return cosf(v);
}

float math_tan(float v) {
    return tanf(v);
}

float math_arccos(float v) {
    return acosf(v);
}

float math_arcsin(float v) {
    return asinf(v);
}

float math_arctan(float v) {
    return atanf(v);
}

float math_arctan2(float y, float x) {
    return atan2f(y, x);
}

float math_to_radians(float input) {
    return input * MATH_DEG2RAD;
}

float math_to_degrees(float input) {
    return input * MATH_RAD2DEG;
}

float math_from_fraction(int32_t numerator, int32_t denominator) {
    return (float)numerator / (float)denominator;
}

float math_from_fraction_int64(int64_t numerator, int64_t denominator) {
    return (float)numerator / (float)denominator;
}

float math_min(float a, float b) {
    return a < b ? a : b;
}

float math_max(float a, float b) {
    return a > b ? a : b;
}

float math_clamp(float value, float min, float max) {
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

float math_lerp(float a, float b, float t) {
    return a + ((b - a) * t);
}

bool math_is_approximately_zero(float value) {
    return math_abs(value) < MATH_EPSILON;
}

bool math_approximate_equals(float a, float b) {
    float num = a - b;
    return (-MATH_EPSILON <= num) && (num <= MATH_EPSILON);
}

int math_sign(float value) {
    if (value > 0) return 1;
    else if (value < 0) return -1;
    return 0;
}

float math_copy_sign(float x, float y) {
    return ((x >= 0 && y >= 0) || (x <= 0 && y <= 0)) ? x : -x;
}

float math_from_string(const char* str) {
    float result = MATH_ZERO;
    if (sscanf(str, "%f", &result) == 1) {
        return result;
    }
    return MATH_ZERO;
}
