#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

API bool quaternion_equals(quaternion q1, quaternion q2);
API bool quaternion_approximate_equals(quaternion q1, quaternion q2);
API quaternion quaternion_add(quaternion q1, quaternion q2);
API quaternion quaternion_subtract(quaternion q1, quaternion q2);
API quaternion quaternion_negate(quaternion q);
API quaternion quaternion_multiply(quaternion q1, quaternion q2);

API quaternion quaternion_lerp(quaternion q1, quaternion q2, float amount);
API quaternion quaternion_slerp(quaternion q1, quaternion q2, float amount);
API quaternion quaternion_normalize(quaternion q);
API quaternion quaternion_conjugate(quaternion q);
API quaternion quaternion_inverse(quaternion q);
API float quaternion_length(quaternion q);
API float quaternion_length_squared(quaternion q);
API float quaternion_dot(quaternion q1, quaternion q2);
API bool quaternion_is_normalized(quaternion q);

API quaternion quaternion_concatenate(quaternion q1, quaternion q2);
API vector3 quaternion_transform_vector3(quaternion q, vector3 v);
API vector4 quaternion_transform_vector4(quaternion q, vector4 v);
API vector3 quaternion_to_yaw_pitch_roll(quaternion q);
API quaternion quaternion_create_from_axis_angle(float x, float y, float z, float angle);
API quaternion quaternion_create_from_yaw_pitch_roll(float yaw, float pitch, float roll);

API quaternion quaternion_create_from_rotation_matrix(matrix_4_4 m);
