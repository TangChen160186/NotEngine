#include "Vector4.h"
#include "math_funcs.h"
#include "core/logger/assert.h"

vector4 vector4_zero(void) {
    return (vector4) { 0.0f, 0.0f, 0.0f, 0.0f };
}

vector4 vector4_one(void) {
    return (vector4) { 1.0f, 1.0f, 1.0f, 1.0f };
}

vector4 vector4_unit_x(void) {
    return (vector4) { 1.0f, 0.0f, 0.0f, 0.0f };
}

vector4 vector4_unit_y(void) {
    return (vector4) { 0.0f, 1.0f, 0.0f, 0.0f };
}

vector4 vector4_unit_z(void) {
    return (vector4) { 0.0f, 0.0f, 1.0f, 0.0f };
}

vector4 vector4_unit_w(void) {
    return (vector4) { 0.0f, 0.0f, 0.0f, 1.0f };
}

vector4 vector4_create(float x, float y, float z, float w) {
    return (vector4) { x, y, z, w };
}

vector4 vector4_create_from_scalar(float value) {
    return (vector4) { value, value, value, value };
}

bool vector4_equals(vector4 v1, vector4 v2) {
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
}

bool vector4_approximate_equals(vector4 v1, vector4 v2) {
    return math_approximate_equals(v1.x, v2.x) &&
        math_approximate_equals(v1.y, v2.y) &&
        math_approximate_equals(v1.z, v2.z) &&
        math_approximate_equals(v1.w, v2.w);
}

vector4 vector4_add(vector4 a, vector4 b) {
    return (vector4) { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

vector4 vector4_subtract(vector4 a, vector4 b) {
    return (vector4) { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

vector4 vector4_negate(vector4 v) {
    return (vector4) { -v.x, -v.y, -v.z, -v.w };
}

vector4 vector4_multiply(vector4 a, vector4 b) {
    return (vector4) { a.x* b.x, a.y* b.y, a.z* b.z, a.w* b.w };
}

vector4 vector4_multiply_scalar(vector4 v, float scalar) {
    return (vector4) { v.x* scalar, v.y* scalar, v.z* scalar, v.w* scalar };
}

vector4 vector4_divide(vector4 a, vector4 b) {
    ASSERT_MSG(b.x != 0 && b.y != 0 && b.z != 0 && b.w != 0,
        "Division by zero in vector4_divide");
    return (vector4) { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
}

vector4 vector4_divide_scalar(vector4 v, float divisor) {
    ASSERT_MSG(divisor != 0, "Division by zero in vector4_divide_scalar");
    return (vector4) { v.x / divisor, v.y / divisor, v.z / divisor, v.w / divisor };
}

float vector4_dot(vector4 a, vector4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

vector4 vector4_normalize(vector4 v) {
    float length = vector4_length(v);
    ASSERT_MSG(length > 0, "Cannot normalize zero vector");
    return vector4_divide_scalar(v, length);
}

bool vector4_is_normalized(vector4 v) {
    return math_is_approximately_zero(1 - (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

float vector4_length(vector4 v) {
    return math_sqrt(vector4_length_squared(v));
}

float vector4_length_squared(vector4 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

vector4 vector4_lerp(vector4 a, vector4 b, float t) {
    ASSERT_MSG(t >= 0.0f && t <= 1.0f, "Interpolation value must be between 0 and 1");
    return (vector4) {
        a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t,
            a.w + (b.w - a.w) * t
    };
}

vector4 vector4_smooth_step(vector4 v1, vector4 v2, float amount)
{
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f,
        "Smooth step amount must be between 0 and 1");
    vector4 result;
    amount = (amount * amount) * (3.0f - (2.0f * amount));
    result.x = v1.x + ((v2.x - v1.x) * amount);
    result.y = v1.y + ((v2.y - v1.y) * amount);
    result.z = v1.z + ((v2.z - v1.z) * amount);
    result.w = v1.w + ((v2.w - v1.w) * amount);
    return result;
}

vector4 vector4_catmull_rom(vector4 v1, vector4 v2, vector4 v3, vector4 v4, float amount)
{
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f,
        "Catmull-Rom interpolation amount must be between 0 and 1");
    vector4 result;
    float t2 = amount * amount;
    float t3 = t2 * amount;
    result.x = 0.5f * ((2.0f * v2.x) + (-v1.x + v3.x) * amount +
        (2.0f * v1.x - 5.0f * v2.x + 4.0f * v3.x - v4.x) * t2 +
        (-v1.x + 3.0f * v2.x - 3.0f * v3.x + v4.x) * t3);
    result.y = 0.5f * ((2.0f * v2.y) + (-v1.y + v3.y) * amount +
        (2.0f * v1.y - 5.0f * v2.y + 4.0f * v3.y - v4.y) * t2 +
        (-v1.y + 3.0f * v2.y - 3.0f * v3.y + v4.y) * t3);
    result.z = 0.5f * ((2.0f * v2.z) + (-v1.z + v3.z) * amount +
        (2.0f * v1.z - 5.0f * v2.z + 4.0f * v3.z - v4.z) * t2 +
        (-v1.z + 3.0f * v2.z - 3.0f * v3.z + v4.z) * t3);   
    result.w = 0.5f * ((2.0f * v2.w) + (-v1.w + v3.w) * amount +
        (2.0f * v1.w - 5.0f * v2.w + 4.0f * v3.w - v4.w) * t2 +
        (-v1.w + 3.0f * v2.w - 3.0f * v3.w + v4.w) * t3);
    return result;
}

vector4 vector4_hermite(vector4 v1, vector4 tangent1, vector4 v2, vector4 tangent2, float amount)
{
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f,
        "Hermite interpolation amount must be between 0 and 1");
    vector4 result;
    float squared = amount * amount;  // t^2
    float cubed = amount * squared;   // t^3

    // Hermite basis functions:
    float a = ((2 * cubed) - (3 * squared)) + 1; // (2t³ - 3t² + 1)
    float b = (-2 * cubed) + (3 * squared);      // (-2t³ + 3t²)
    float c = cubed - (2 * squared) + amount;    // (t³ - 2t² + t)
    float d = cubed - squared;                  // (t³ - t²)

    // Compute the interpolated vector:
    result.x = (v1.x * a) + (v2.x * b) + (tangent1.x * c) + (tangent2.x * d);
    result.y = (v1.y * a) + (v2.y * b) + (tangent1.y * c) + (tangent2.y * d);
    result.z = (v1.z * a) + (v2.z * b) + (tangent1.z * c) + (tangent2.z * d);
    result.w = (v1.w * a) + (v2.w * b) + (tangent1.w * c) + (tangent2.w * d);
    return result;
}
