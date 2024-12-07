#pragma once
#include "typedefs.h"
#include <stdbool.h>

#include "math_types.h"

// 函数声明
API Vector2 vector2_zero(void);
API Vector2 vector2_one(void);
API Vector2 vector2_unit_x(void);
API Vector2 vector2_unit_y(void);
API Vector2 vector2_right(void);
API Vector2 vector2_left(void);
API Vector2 vector2_up(void);
API Vector2 vector2_down(void);

API Vector2 vector2_create(float x, float y);
API Vector2 vector2_create_from_scalar(float value);

API bool vector2_equals(Vector2 v1, Vector2 v2);
API bool vector2_approximate_equals(Vector2 v1, Vector2 v2);

API Vector2 vector2_add(Vector2 a, Vector2 b);
API Vector2 vector2_subtract(Vector2 a, Vector2 b);
API Vector2 vector2_negate(Vector2 v);
API Vector2 vector2_multiply(Vector2 a, Vector2 b);
API Vector2 vector2_multiply_scalar(Vector2 v, float scalar);
API Vector2 vector2_divide(Vector2 a, Vector2 b);
API Vector2 vector2_divide_scalar(Vector2 v, float divisor);

API Vector2 vector2_min(Vector2 a, Vector2 b);
API Vector2 vector2_max(Vector2 a, Vector2 b);
API Vector2 vector2_clamp(Vector2 v, Vector2 min, Vector2 max);
API Vector2 vector2_clamp_scalar(Vector2 v, float min, float max);



API float vector2_distance(Vector2 a, Vector2 b);
API float vector2_distance_squared(Vector2 a, Vector2 b);
API float vector2_dot(Vector2 a, Vector2 b);

API Vector2 vector2_normalize(Vector2 v);
API bool vector2_is_normalized(Vector2 v);

API float vector2_length(Vector2 v);
API float vector2_length_squared(Vector2 v);
API Vector2 SquareRoot(Vector2 v);

API Vector2 vector2_reflect(Vector2 v, Vector2 normal);


API Vector2 vector2_lerp(Vector2 a, Vector2 b, float t);
API Vector2 vector2_smooth_step(Vector2 v1, Vector2 v2, float amount);
API Vector2 vector2_catmull_rom(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, float amount);
API Vector2 vector2_hermite(Vector2 v1, Vector2 tangent1, Vector2 v2, Vector2 tanget2, float amount);
