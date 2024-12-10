#pragma once
#include <stdbool.h>
#include "math_types.h"
#include "typedefs.h"

API bool matrix44_equals(matrix_4_4 a, matrix_4_4 b);
API bool matrix44_approximate_equals(matrix_4_4 a, matrix_4_4 b);

API matrix_4_4 matrix44_identity(void);

API matrix_4_4 matrix44_add(matrix_4_4 a, matrix_4_4 b);
API matrix_4_4 matrix44_subtract(matrix_4_4 a, matrix_4_4 b);
API matrix_4_4 matrix44_negate(matrix_4_4 m);
API matrix_4_4 matrix44_product(matrix_4_4 a, matrix_4_4 b);
API matrix_4_4 matrix44_multiply_scalar(matrix_4_4 a, float scalar);
API matrix_4_4 matrix44_transpose(matrix_4_4 m);

API float matrix44_determinant(matrix_4_4 m);
API matrix_4_4 matrix44_invert(matrix_4_4 m);
API void matrix44_decompose(matrix_4_4 m, vector3* scale, quaternion* rotation, vector3* translation);
API vector3 matrix44_transform_vector3(matrix_4_4 m, vector3 v);
API vector4 matrix44_transform_vector4(matrix_4_4 m, vector4 v);
API matrix_4_4 matrix44_lerp(matrix_4_4 a, matrix_4_4 b, float t);
API matrix_4_4 matrix44_transform_quaternion(matrix_4_4 m, quaternion q);

API matrix_4_4 matrix44_create_from_quaternion(quaternion q);
API matrix_4_4 matrix44_create_translation(float x, float y, float z);
API matrix_4_4 matrix44_create_scale(float x, float y, float z);
API matrix_4_4 matrix44_create_rotation_x(float radians);
API matrix_4_4 matrix44_create_rotation_y(float radians);
API matrix_4_4 matrix44_create_rotation_z(float radians);
API matrix_4_4 matrix44_create_from_axis_angle(vector3 axis, float angle);
API matrix_4_4 matrix44_create_from_cartesian_axes(vector3 right, vector3 up, vector3 backward);
API matrix_4_4 matrix44_create_world(vector3 position, vector3 forward, vector3 up);
API matrix_4_4 matrix44_create_perspective_field_of_view(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
API matrix_4_4 matrix44_create_perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
API matrix_4_4 matrix44_create_perspective_off_center(float left, float right, float bottom, float top,
    float nearPlaneDistance, float farPlaneDistance);
API matrix_4_4 matrix44_create_orthographic(float width, float height, float zNearPlane, float zFarPlane);
API matrix_4_4 matrix44_create_orthographic_off_center(float left, float right, float bottom, float top,
    float zNearPlane, float zFarPlane);
API matrix_4_4 matrix44_create_look_at(vector3 cameraPosition, vector3 cameraTarget, vector3 cameraUpVector);
API bool matrix44_is_rotation(matrix_4_4 m);