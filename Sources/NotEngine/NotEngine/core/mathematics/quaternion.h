#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include "math_types.h"

API bool quaternion_equals(Quaternion q1, Quaternion q2);
API bool quaternion_approximate_equals(Quaternion q1, Quaternion q2);
API Quaternion quaternion_add(Quaternion q1, Quaternion q2);
API Quaternion quaternion_subtract(Quaternion q1, Quaternion q2);
API Quaternion quaternion_negate(Quaternion q);
API Quaternion quaternion_multiply(Quaternion q1, Quaternion q2);

API Quaternion quaternion_lerp(Quaternion q1, Quaternion q2, float amount);
API Quaternion quaternion_slerp(Quaternion q1, Quaternion q2, float amount);
API Quaternion quaternion_normalize(Quaternion q);
API Quaternion quaternion_conjugate(Quaternion q);
API Quaternion quaternion_inverse(Quaternion q);
API float quaternion_length(Quaternion q);
API float quaternion_length_squared(Quaternion q);
API float quaternion_dot(Quaternion q1, Quaternion q2);
API bool quaternion_is_normalized(Quaternion q);

API Quaternion quaternion_concatenate(Quaternion q1, Quaternion q2);
API Vector3 quaternion_transform_vector3(Quaternion q, Vector3 v);
API Vector4 quaternion_transform_vector4(Quaternion q, Vector4 v);
API Vector3 quaternion_to_yaw_pitch_roll(Quaternion q);
API Quaternion quaternion_create_from_axis_angle(float x, float y, float z, float angle);
API Quaternion quaternion_create_from_yaw_pitch_roll(float yaw, float pitch, float roll);

API Quaternion quaternion_create_from_rotation_matrix(Matrix4x4 m);
