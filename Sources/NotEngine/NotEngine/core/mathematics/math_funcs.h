#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "typedefs.h"
#define MATH_EPSILON 0.000001f
#define MATH_E 2.71828182845904523536028747135f
#define MATH_HALF 0.5f
#define MATH_QUARTER 0.25f
#define MATH_LOG10E 0.43429448190325182765112891892f
#define MATH_LOG2E 1.44269504088896340735992468100f
#define MATH_PI 3.14159265358979323846264338328f
#define MATH_HALFPi 1.57079632679489661923132169164f
#define MATH_QUARTERPi 0.78539816339744830961566084582f
#define MATH_ROOT2 1.41421356237309504880168872421f
#define MATH_ROOT3 1.73205080756887729352744634151f
#define MATH_TAU 6.28318530717958647692528676656f
#define MATH_DEG2RAD 0.01745329251994329576923690768f
#define MATH_RAD2DEG 57.29577951308232087679815481409f
#define MATH_ZERO 0.0f
#define MATH_ONE 1.0f

// 函数声明（小写，使用下划线分隔）
API float math_sqrt(float v);
API float math_abs(float v);
API float math_sin(float v);
API float math_cos(float v);
API float math_tan(float v);
API float math_arccos(float v);
API float math_arcsin(float v);
API float math_arctan(float v);
API float math_arctan2(float y, float x);
API float math_to_radians(float input);
API float math_to_degrees(float input);
API float math_from_fraction(int32_t numerator, int32_t denominator);
API float math_from_fraction_int64(int64_t numerator, int64_t denominator);
API float math_min(float a, float b);
API float math_max(float a, float b);
API float math_clamp(float value, float min, float max);
API float math_lerp(float a, float b, float t);
API bool math_is_approximately_zero(float value);
API bool math_approximate_equals(float a, float b);
API int math_sign(float value);
API float math_copy_sign(float x, float y);
API float math_from_string(const char* str);


