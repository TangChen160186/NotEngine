#pragma once
#include <stdbool.h>
#include "math_types.h"
#include "typedefs.h"

API bool matrix44_equals(Matrix4x4 a, Matrix4x4 b);
API bool matrix44_approximate_equals(Matrix4x4 a, Matrix4x4 b);

API Matrix4x4 matrix44_identity(void);

API Matrix4x4 matrix44_add(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 matrix44_subtract(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 matrix44_negate(Matrix4x4 m);
API Matrix4x4 matrix44_product(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 matrix44_multiply_scalar(Matrix4x4 a, float scalar);
API Matrix4x4 matrix44_transpose(Matrix4x4 m);

API float matrix44_determinant(Matrix4x4 m);
API Matrix4x4 matrix44_invert(Matrix4x4 m);
API void matrix44_decompose(Matrix4x4 m, Vector3* scale, Quaternion* rotation, Vector3* translation);
API Vector3 matrix44_transform_vector3(Matrix4x4 m, Vector3 v);
API Vector4 matrix44_transform_vector4(Matrix4x4 m, Vector4 v);
API Matrix4x4 matrix44_lerp(Matrix4x4 a, Matrix4x4 b, float t);
API Matrix4x4 matrix44_transform_quaternion(Matrix4x4 m, Quaternion q);

API Matrix4x4 matrix44_create_from_quaternion(Quaternion q);
API Matrix4x4 matrix44_create_translation(float x, float y, float z);
API Matrix4x4 matrix44_create_scale(float x, float y, float z);
API Matrix4x4 matrix44_create_rotation_x(float radians);
API Matrix4x4 matrix44_create_rotation_y(float radians);
API Matrix4x4 matrix44_create_rotation_z(float radians);
API Matrix4x4 matrix44_create_from_axis_angle(Vector3 axis, float angle);
API Matrix4x4 matrix44_create_from_cartesian_axes(Vector3 right, Vector3 up, Vector3 backward);
API Matrix4x4 matrix44_create_world(Vector3 position, Vector3 forward, Vector3 up);
API Matrix4x4 matrix44_create_perspective_field_of_view(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 matrix44_create_perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 matrix44_create_perspective_off_center(float left, float right, float bottom, float top,
    float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 matrix44_create_orthographic(float width, float height, float zNearPlane, float zFarPlane);
API Matrix4x4 matrix44_create_orthographic_off_center(float left, float right, float bottom, float top,
    float zNearPlane, float zFarPlane);
API Matrix4x4 matrix44_create_look_at(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);
API bool matrix44_is_rotation(Matrix4x4 m);