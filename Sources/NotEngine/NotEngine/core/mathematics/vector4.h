#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

// 函数声明
API Vector4 vector4_zero(void);
API Vector4 vector4_one(void);
API Vector4 vector4_unit_x(void);
API Vector4 vector4_unit_y(void);
API Vector4 vector4_unit_z(void);
API Vector4 vector4_unit_w(void);

API Vector4 vector4_create(float x, float y, float z, float w);
API Vector4 vector4_create_from_scalar(float value);

API bool vector4_equals(Vector4 v1, Vector4 v2);
API bool vector4_approximate_equals(Vector4 v1, Vector4 v2);

API Vector4 vector4_add(Vector4 a, Vector4 b);
API Vector4 vector4_subtract(Vector4 a, Vector4 b);
API Vector4 vector4_negate(Vector4 v);
API Vector4 vector4_multiply(Vector4 a, Vector4 b);
API Vector4 vector4_multiply_scalar(Vector4 v, float scalar);
API Vector4 vector4_divide(Vector4 a, Vector4 b);
API Vector4 vector4_divide_scalar(Vector4 v, float divisor);

API float vector4_dot(Vector4 a, Vector4 b);

API Vector4 vector4_normalize(Vector4 v);
API bool vector4_is_normalized(Vector4 v);

API float vector4_length(Vector4 v);    
API float vector4_length_squared(Vector4 v);

API Vector4 vector4_lerp(Vector4 a, Vector4 b, float t);
API Vector4 vector4_smooth_step(Vector4 v1, Vector4 v2, float amount);
API Vector4 vector4_catmull_rom(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4, float amount);
API Vector4 vector4_hermite(Vector4 v1, Vector4 tangent1, Vector4 v2, Vector4 tangent2, float amount);
