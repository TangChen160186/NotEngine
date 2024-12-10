#include "quaternion.h"
#include <stdbool.h>
#include "math_funcs.h"
#include "matrix4x4.h"
#include "Vector4.h"
#include "core/logger/assert.h"

bool quaternion_equals(quaternion q1, quaternion q2) {
    return (q1.i == q2.i) && (q1.j == q2.j) && (q1.k == q2.k) && (q1.u == q2.u);
}

bool quaternion_approximate_equals(quaternion q1, quaternion q2)
{
    return math_approximate_equals(q1.i, q2.i) && 
        math_approximate_equals(q1.j, q2.j) && 
        math_approximate_equals(q1.k, q2.k) &&
        math_approximate_equals(q1.u, q2.u);
}

quaternion quaternion_add(quaternion q1, quaternion q2)
{
    quaternion result;
    result.i = q1.i + q2.i;
    result.j = q1.j + q2.j;
    result.k = q1.k + q2.k;
    result.u = q1.u + q2.u;
    return result;
}

quaternion quaternion_subtract(quaternion q1, quaternion q2)
{
    quaternion result;
    result.i = q1.i - q2.i;
    result.j = q1.j - q2.j;
    result.k = q1.k - q2.k;
    result.u = q1.u - q2.u;
    return result;
}

quaternion quaternion_negate(quaternion q)
{
    quaternion result;
    result.i = -q.i;
    result.j = -q.j;
    result.k = -q.k;
    result.u = -q.u;
    return result;
}

quaternion quaternion_multiply(quaternion q1, quaternion q2)
{
    quaternion result;
    result.i = q1.i * q2.u + q1.u * q2.i + q1.j * q2.k - q1.k * q2.j;
    result.j = q1.u * q2.j - q1.i * q2.k + q1.j * q2.u + q1.k * q2.i;
    result.k = q1.u * q2.k + q1.i * q2.j - q1.j * q2.i + q1.k * q2.u;
    result.u = q1.u * q2.u - q1.i * q2.i - q1.j * q2.j - q1.k * q2.k;
    return result;
}

quaternion quaternion_lerp(quaternion q1, quaternion q2, float amount)
{
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Interpolation amount must be between 0 and 1");
    quaternion result;
    float remaining = 1 - amount;
    result.u = (remaining * q1.u) + (amount * q2.u);
    result.i = (remaining * q1.i) + (amount * q2.i);
    result.j = (remaining * q1.j) + (amount * q2.j);
    result.k = (remaining * q1.k) + (amount * q2.k);
    return result;
}

quaternion quaternion_slerp(quaternion q1, quaternion q2, float amount)
{
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Spherical interpolation amount must be between 0 and 1");
    float dot = quaternion_dot(q1, q2);
    float remaining = 1 - amount;
    if (dot < 0) {
        dot = -dot;
        q1 = quaternion_negate(q1);
    }
    float theta = math_arccos(dot);
    float f = remaining;
    float a = amount;
    if (theta>MATH_EPSILON)
    {
        float x = math_sin(remaining * theta);
        float y = math_sin(amount * theta);
        float z = math_sin(theta);
        f = x / z;
        a = y / z;
    }

    quaternion result;
    result.u = (f * q1.u) + (a * q2.u);
    result.i = (f * q1.i) + (a * q2.i);
    result.j = (f * q1.j) + (a * q2.j);
    result.k = (f * q1.k) + (a * q2.k);
    return result;
}

quaternion quaternion_normalize(quaternion q)
{
    float length = quaternion_length(q);
    ASSERT_MSG(length > 0, "Cannot normalize zero quaternion");
    float inv_length = 1.0f / length;
    quaternion result;
    result.i = q.i * inv_length;
    result.j = q.j * inv_length;
    result.k = q.k * inv_length;
    result.u = q.u * inv_length;
    return result;
}

quaternion quaternion_conjugate(quaternion q)
{
    quaternion result;
    result.i = -q.i;
    result.j = -q.j;
    result.k = -q.k;
    result.u = q.u;
    return result;
}
float quaternion_length(quaternion q)
{
    return math_sqrt(quaternion_length_squared(q));
}

float quaternion_length_squared(quaternion q)
{
    return  (q.i * q.i) + (q.j * q.j) + (q.k * q.k) + (q.u * q.u);
}

float quaternion_dot(quaternion q1, quaternion q2)
{
    return (q1.i * q2.i) + (q1.j * q2.j) + (q1.k * q2.k) + (q1.u * q2.u);
}

quaternion quaternion_inverse(quaternion q)
{
    quaternion result = quaternion_conjugate(q);
    float length_squared = quaternion_length_squared(q);
    float inv_length_squared = 1.0f / length_squared;
    result.i *= inv_length_squared;
    result.j *= inv_length_squared;
    result.k *= inv_length_squared;
    result.u *= inv_length_squared;
    return result;
}


bool quaternion_is_normalized(quaternion q)
{
    return math_is_approximately_zero(1 - q.i * q.i - q.j * q.j - q.k * q.k - q.u * q.u);
}

quaternion quaternion_concatenate(quaternion q1, quaternion q2)
{
    return quaternion_multiply(q1, q2);
}

vector3 quaternion_transform_vector3(quaternion q, vector3 v)
{
    ASSERT_MSG(quaternion_is_normalized(q),
        "Quaternion must be normalized for vector transformation");
    vector3 result;
    float ii = q.i * q.i, jj = q.j * q.j, kk = q.k * q.k;
    float ui = q.u * q.i, uj = q.u * q.j, uk = q.u * q.k;
    float ij = q.i * q.j, ik = q.i * q.k, jk = q.j * q.k;
    result.x = v.x - 2 * (jj + kk) * v.x + 2 * (ij - uk) * v.y + 2 * (ik + uj) * v.z;
    result.y = v.y + 2 * (ij + uk) * v.x - 2 * (ii + kk) * v.y + 2 * (jk - ui) * v.z;
    result.z = v.z + 2 * (ik - uj) * v.x + 2 * (jk + ui) * v.y - 2 * (ii + jj) * v.z;
    return result;
}

vector4 quaternion_transform_vector4(quaternion q, vector4 v)
{
    ASSERT_MSG(quaternion_is_normalized(q),
        "Quaternion must be normalized for vector transformation");
    vector4 result;
    float ii = q.i * q.i, jj = q.j * q.j, kk = q.k * q.k;
    float ui = q.u * q.i, uj = q.u * q.j, uk = q.u * q.k;
    float ij = q.i * q.j, ik = q.i * q.k, jk = q.j * q.k;
    result.x = v.x - 2 * (jj + kk) * v.x + 2 * (ij - uk) * v.y + 2 * (ik + uj) * v.z;
    result.y = v.y + 2 * (ij + uk) * v.x - 2 * (ii + kk) * v.y + 2 * (jk - ui) * v.z;
    result.z = v.z + 2 * (ik - uj) * v.x + 2 * (jk + ui) * v.y - 2 * (ii + jj) * v.z;
    result.w = v.w;
    return result;
}

vector3 quaternion_to_yaw_pitch_roll(quaternion q)
{
    ASSERT_MSG(quaternion_is_normalized(q),
        "Quaternion must be normalized for Euler angle conversion");
    vector3 result;
    // roll (x-axis rotation)
    float sinr_cosp = 2 * (q.u * q.k + q.i * q.j);
    float cosr_cosp = 1 - 2 * (q.k * q.k + q.i * q.i);
    result.z = math_arctan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    float sinp = 2 * (q.u * q.i - q.j * q.k);
    if (math_abs(sinp) >= 1)
        result.y = math_copy_sign(MATH_HALFPi, sinp); // use 90 degrees if out of range
    else
        result.y = math_sin(sinp);

    // yaw (z-axis rotation)
    float siny_cosp = 2 * (q.u * q.j + q.k * q.i);
    float cosy_cosp = 1 - 2 * (q.i * q.i + q.j * q.j);
    result.x = math_arctan2(siny_cosp, cosy_cosp);

    return result;
}

quaternion quaternion_create_from_axis_angle(float x, float y, float z, float angle)
{
    ASSERT_MSG(math_abs(x*x + y*y + z*z - 1.0f) < MATH_EPSILON, 
               "Rotation axis must be normalized");
    float halfAngle = angle * 0.5f;
    float sinHalfAngle = math_sin(halfAngle);
    quaternion result;
    result.i = x * sinHalfAngle;
    result.j = y * sinHalfAngle;
    result.k = z * sinHalfAngle;
    result.u = math_cos(halfAngle);
    return result;
}

quaternion quaternion_create_from_yaw_pitch_roll(float yaw, float pitch, float roll)
{
    ASSERT_MSG(pitch > -MATH_HALFPi && pitch < MATH_HALFPi,
        "Pitch angle must be between -90 and 90 degrees");
    float halfYaw = yaw * 0.5f;
    float halfPitch = pitch * 0.5f;
    float halfRoll = roll * 0.5f;
    float sinYaw = math_sin(halfYaw);
    float cosYaw = math_cos(halfYaw);
    float sinPitch = math_sin(halfPitch);
    float cosPitch = math_cos(halfPitch);
    float sinRoll = math_sin(halfRoll);
    float cosRoll = math_cos(halfRoll);

    quaternion result;
    result.i = cosYaw * sinPitch * cosRoll + sinYaw * cosPitch * sinRoll;
    result.j = sinYaw * cosPitch * cosRoll - cosYaw * sinPitch * sinRoll;
    result.k = cosYaw * cosPitch * sinRoll - sinYaw * sinPitch * cosRoll;
    result.u = cosYaw * cosPitch * cosRoll + sinYaw * sinPitch * sinRoll;
    return result;
}

quaternion quaternion_create_from_rotation_matrix(matrix_4_4 m)
{
    ASSERT_MSG(matrix44_is_rotation(m), "Matrix must be a valid rotation matrix");
    quaternion result;
    float tr = m.data[0][0] + m.data[1][1] + m.data[2][2];

    if (tr > 0) {
        float s = math_sqrt(tr + 1.0f) * 2.0f;
        result.u = 0.25f * s;
        result.i = (m.data[1][2] - m.data[2][1]) / s;
        result.j = (m.data[2][0] - m.data[0][2]) / s;
        result.k = (m.data[0][1] - m.data[1][0]) / s;
    }
    else if ((m.data[0][0] >= m.data[1][1]) && (m.data[0][0] >= m.data[2][2])) {
        float s = math_sqrt(1.0f + m.data[0][0] - m.data[1][1] - m.data[2][2]) * 2.0f;
        result.u = (m.data[1][2] - m.data[2][1]) / s;
        result.i = 0.25f * s;
        result.j = (m.data[0][1] + m.data[1][0]) / s;
        result.k = (m.data[0][2] + m.data[2][0]) / s;
    }
    else if (m.data[1][1] > m.data[2][2]) {
        float s = math_sqrt(1.0f + m.data[1][1] - m.data[0][0] - m.data[2][2]) * 2.0f;
        result.u = (m.data[2][0] - m.data[0][2]) / s;
        result.i = (m.data[1][0] + m.data[0][1]) / s;
        result.j = 0.25f * s;
        result.k = (m.data[2][1] + m.data[1][2]) / s;
    }
    else {
        float s = math_sqrt(1.0f + m.data[2][2] - m.data[0][0] - m.data[1][1]) * 2.0f;
        result.u = (m.data[0][1] - m.data[1][0]) / s;
        result.i = (m.data[2][0] + m.data[0][2]) / s;
        result.j = (m.data[2][1] + m.data[1][2]) / s;
        result.k = 0.25f * s;
    }

    return result;
}