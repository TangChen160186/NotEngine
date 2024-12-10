#pragma once
#include "typedefs.h"
#include <stdbool.h>

#include "math_types.h"

// 函数声明
API vector2 vector2_zero(void);
API vector2 vector2_one(void);
API vector2 vector2_unit_x(void);
API vector2 vector2_unit_y(void);
API vector2 vector2_right(void);
API vector2 vector2_left(void);
API vector2 vector2_up(void);
API vector2 vector2_down(void);

API vector2 vector2_create(float x, float y);
API vector2 vector2_create_from_scalar(float value);

API bool vector2_equals(vector2 v1, vector2 v2);
API bool vector2_approximate_equals(vector2 v1, vector2 v2);

API vector2 vector2_add(vector2 a, vector2 b);
API vector2 vector2_subtract(vector2 a, vector2 b);
API vector2 vector2_negate(vector2 v);
API vector2 vector2_multiply(vector2 a, vector2 b);
API vector2 vector2_multiply_scalar(vector2 v, float scalar);
API vector2 vector2_divide(vector2 a, vector2 b);
API vector2 vector2_divide_scalar(vector2 v, float divisor);

API vector2 vector2_min(vector2 a, vector2 b);
API vector2 vector2_max(vector2 a, vector2 b);
API vector2 vector2_clamp(vector2 v, vector2 min, vector2 max);
API vector2 vector2_clamp_scalar(vector2 v, float min, float max);



API float vector2_distance(vector2 a, vector2 b);
API float vector2_distance_squared(vector2 a, vector2 b);
API float vector2_dot(vector2 a, vector2 b);

API vector2 vector2_normalize(vector2 v);
API bool vector2_is_normalized(vector2 v);

API float vector2_length(vector2 v);
API float vector2_length_squared(vector2 v);
API vector2 SquareRoot(vector2 v);

API vector2 vector2_reflect(vector2 v, vector2 normal);


API vector2 vector2_lerp(vector2 a, vector2 b, float t);
API vector2 vector2_smooth_step(vector2 v1, vector2 v2, float amount);
API vector2 vector2_catmull_rom(vector2 v1, vector2 v2, vector2 v3, vector2 v4, float amount);
API vector2 vector2_hermite(vector2 v1, vector2 tangent1, vector2 v2, vector2 tanget2, float amount);
