#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

// 函数声明
API vector3 vector3_zero(void);
API vector3 vector3_one(void);
API vector3 vector3_unit_x(void);
API vector3 vector3_unit_y(void);
API vector3 vector3_unit_z(void);

API vector3 vector3_right(void);
API vector3 vector3_left(void);
API vector3 vector3_up(void);
API vector3 vector3_down(void);
API vector3 vector3_forward(void);
API vector3 vector3_backward(void);

API vector3 vector3_create(float x, float y, float z);
API vector3 vector3_create_from_scalar(float value);

API bool vector3_equals(vector3 v1, vector3 v2);
API bool vector3_approximate_equals(vector3 v1, vector3 v2);

API vector3 vector3_add(vector3 a, vector3 b);
API vector3 vector3_subtract(vector3 a, vector3 b);
API vector3 vector3_negate(vector3 v);
API vector3 vector3_multiply(vector3 a, vector3 b);
API vector3 vector3_multiply_scalar(vector3 v, float scalar);
API vector3 vector3_divide(vector3 a, vector3 b);
API vector3 vector3_divide_scalar(vector3 v, float divisor);

API float vector3_distance(vector3 a, vector3 b);
API float vector3_distance_squared(vector3 a, vector3 b);
API float vector3_dot(vector3 a, vector3 b);
API vector3 vector3_cross(vector3 a, vector3 b);

API vector3 vector3_normalize(vector3 v);
API bool vector3_is_normalized(vector3 v);

API float vector3_length(vector3 v);
API float vector3_length_squared(vector3 v);

API vector3 vector3_reflect(vector3 v, vector3 normal);

API vector3 vector3_lerp(vector3 a, vector3 b, float t);
API vector3 vector3_smooth_step(vector3 v1, vector3 v2, float amount);
API vector3 vector3_catmull_rom(vector3 v1, vector3 v2, vector3 v3, vector3 v4, float amount);
API vector3 vector3_hermite(vector3 v1, vector3 tangent1, vector3 v2, vector3 tangent2, float amount);
