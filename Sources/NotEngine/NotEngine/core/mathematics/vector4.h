#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

// 函数声明
API vector4 vector4_zero(void);
API vector4 vector4_one(void);
API vector4 vector4_unit_x(void);
API vector4 vector4_unit_y(void);
API vector4 vector4_unit_z(void);
API vector4 vector4_unit_w(void);

API vector4 vector4_create(float x, float y, float z, float w);
API vector4 vector4_create_from_scalar(float value);

API bool vector4_equals(vector4 v1, vector4 v2);
API bool vector4_approximate_equals(vector4 v1, vector4 v2);

API vector4 vector4_add(vector4 a, vector4 b);
API vector4 vector4_subtract(vector4 a, vector4 b);
API vector4 vector4_negate(vector4 v);
API vector4 vector4_multiply(vector4 a, vector4 b);
API vector4 vector4_multiply_scalar(vector4 v, float scalar);
API vector4 vector4_divide(vector4 a, vector4 b);
API vector4 vector4_divide_scalar(vector4 v, float divisor);

API float vector4_dot(vector4 a, vector4 b);

API vector4 vector4_normalize(vector4 v);
API bool vector4_is_normalized(vector4 v);

API float vector4_length(vector4 v);    
API float vector4_length_squared(vector4 v);

API vector4 vector4_lerp(vector4 a, vector4 b, float t);
API vector4 vector4_smooth_step(vector4 v1, vector4 v2, float amount);
API vector4 vector4_catmull_rom(vector4 v1, vector4 v2, vector4 v3, vector4 v4, float amount);
API vector4 vector4_hermite(vector4 v1, vector4 tangent1, vector4 v2, vector4 tangent2, float amount);
