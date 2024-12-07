#pragma once
#include <stdbool.h>
#include "math_types.h"
#include "typedefs.h"

API bool Matrix44_Equals(Matrix4x4 a, Matrix4x4 b);
API bool Matrix44_ApproximateEquals(Matrix4x4 a, Matrix4x4 b);

API Matrix4x4 Matrix44_Identity(void);

API Matrix4x4 Matrix44_Add(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 Matrix44_Subtract(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 Matrix44_Negate(Matrix4x4 m);
API Matrix4x4 Matrix44_Product(Matrix4x4 a, Matrix4x4 b);
API Matrix4x4 Matrix44_Multiply_scalar(Matrix4x4 a, float scalar);
API Matrix4x4 Matrix44_Transpose(Matrix4x4 m);

API float Matrix44_Determinant(Matrix4x4 m);
API Matrix4x4 Matrix44_Invert(Matrix4x4 m);
API void Matrix44_Decompose(Matrix4x4 m, Vector3* scale, Quaternion* rotation, Vector3* translation);
API Vector3 Matrix44_TransformVector3(Matrix4x4 m, Vector3 v);
API Vector4 Matrix44_TransformVector4(Matrix4x4 m, Vector4 v);
API Matrix4x4 Matrix44_Lerp(Matrix4x4 a, Matrix4x4 b, float t);
API Matrix4x4 Matrix44_TransformQuaternion(Matrix4x4 m, Quaternion q);

API Matrix4x4 Matrix44_CreateFromQuaternion(Quaternion q);
API Matrix4x4 Matrix44_CreateTranslation(float x, float y, float z);
API Matrix4x4 Matrix44_CreateScale(float x, float y, float z);
API Matrix4x4 Matrix44_CreateRotationX(float radians);
API Matrix4x4 Matrix44_CreateRotationY(float radians);
API Matrix4x4 Matrix44_CreateRotationZ(float radians);
API Matrix4x4 Matrix44_CreateFromAxisAngle(Vector3 axis, float angle);
API Matrix4x4 Matrix44_CreateFromCartesianAxes(Vector3 right, Vector3 up, Vector3 backward);
API Matrix4x4 Matrix44_CreateWorld(Vector3 position, Vector3 forward, Vector3 up);
API Matrix4x4 Matrix44_CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 Matrix44_CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 Matrix44_CreatePerspectiveOffCenter(float left, float right, float bottom, float top,
    float nearPlaneDistance, float farPlaneDistance);
API Matrix4x4 Matrix44_CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
API Matrix4x4 Matrix44_CreateOrthographicOffCenter(float left, float right, float bottom, float top,
    float zNearPlane, float zFarPlane);
API Matrix4x4 Matrix44_CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);
