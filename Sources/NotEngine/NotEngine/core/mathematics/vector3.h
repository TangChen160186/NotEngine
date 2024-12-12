#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

// 函数声明
API Vector3 vector3_zero(void);
API Vector3 vector3_one(void);
API Vector3 vector3_unit_x(void);
API Vector3 vector3_unit_y(void);
API Vector3 vector3_unit_z(void);

API Vector3 vector3_right(void);
API Vector3 vector3_left(void);
API Vector3 vector3_up(void);
API Vector3 vector3_down(void);
API Vector3 vector3_forward(void);
API Vector3 vector3_backward(void);

API Vector3 vector3_create(float x, float y, float z);
API Vector3 vector3_create_from_scalar(float value);

API bool vector3_equals(Vector3 v1, Vector3 v2);
API bool vector3_approximate_equals(Vector3 v1, Vector3 v2);

API Vector3 vector3_add(Vector3 a, Vector3 b);
API Vector3 vector3_subtract(Vector3 a, Vector3 b);
API Vector3 vector3_negate(Vector3 v);
API Vector3 vector3_multiply(Vector3 a, Vector3 b);
API Vector3 vector3_multiply_scalar(Vector3 v, float scalar);
API Vector3 vector3_divide(Vector3 a, Vector3 b);
API Vector3 vector3_divide_scalar(Vector3 v, float divisor);

API float vector3_distance(Vector3 a, Vector3 b);
API float vector3_distance_squared(Vector3 a, Vector3 b);
API float vector3_dot(Vector3 a, Vector3 b);
API Vector3 vector3_cross(Vector3 a, Vector3 b);

API Vector3 vector3_normalize(Vector3 v);
API bool vector3_is_normalized(Vector3 v);

API float vector3_length(Vector3 v);
API float vector3_length_squared(Vector3 v);

API Vector3 vector3_reflect(Vector3 v, Vector3 normal);

API Vector3 vector3_lerp(Vector3 a, Vector3 b, float t);
API Vector3 vector3_smooth_step(Vector3 v1, Vector3 v2, float amount);
API Vector3 vector3_catmull_rom(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4, float amount);
API Vector3 vector3_hermite(Vector3 v1, Vector3 tangent1, Vector3 v2, Vector3 tangent2, float amount);
