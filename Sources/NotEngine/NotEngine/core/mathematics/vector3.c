#include "Vector3.h"
#include "math_funcs.h"
#include "core/logger/assert.h"

vector3 vector3_zero(void) {
    return (vector3) { 0.0f, 0.0f, 0.0f };
}

vector3 vector3_one(void) {
    return (vector3) { 1.0f, 1.0f, 1.0f };
}

vector3 vector3_unit_x(void) {
    return (vector3) { 1.0f, 0.0f, 0.0f };
}

vector3 vector3_unit_y(void) {
    return (vector3) { 0.0f, 1.0f, 0.0f };
}

vector3 vector3_unit_z(void) {
    return (vector3) { 0.0f, 0.0f, 1.0f };
}

// 向右 (+X) 方向
vector3 vector3_right(void) {
    return (vector3) { 1.0f, 0.0f, 0.0f };
}

// 向左 (-X) 方向
vector3 vector3_left(void) {
    return (vector3) { -1.0f, 0.0f, 0.0f };
}

// 向上 (+Y) 方向
vector3 vector3_up(void) {
    return (vector3) { 0.0f, 1.0f, 0.0f };
}

// 向下 (-Y) 方向
vector3 vector3_down(void) {
    return (vector3) { 0.0f, -1.0f, 0.0f };
}

// 向前 (+Z) 方向
vector3 vector3_forward(void) {
    return (vector3) { 0.0f, 0.0f, 1.0f };
}

// 向后 (-Z) 方向
vector3 vector3_backward(void) {
    return (vector3) { 0.0f, 0.0f, -1.0f };
}


vector3 vector3_create(float x, float y, float z) {
    return (vector3) { x, y, z };
}

vector3 vector3_create_from_scalar(float value) {
    return (vector3) { value, value, value };
}

bool vector3_equals(vector3 v1, vector3 v2) {
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

bool vector3_approximate_equals(vector3 v1, vector3 v2) {
    return math_approximate_equals(v1.x, v2.x) &&
        math_approximate_equals(v1.y, v2.y) &&
        math_approximate_equals(v1.z, v2.z);
}

vector3 vector3_add(vector3 a, vector3 b) {
    return (vector3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

vector3 vector3_subtract(vector3 a, vector3 b) {
    return (vector3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

vector3 vector3_negate(vector3 v) {
    return (vector3) { -v.x, -v.y, -v.z };
}

vector3 vector3_multiply(vector3 a, vector3 b) {
    return (vector3) { a.x* b.x, a.y* b.y, a.z* b.z };
}

vector3 vector3_multiply_scalar(vector3 v, float scalar) {
    return (vector3) { v.x* scalar, v.y* scalar, v.z* scalar };
}

vector3 vector3_divide(vector3 a, vector3 b) {
    ASSERT_MSG(b.x != 0 && b.y != 0 && b.z != 0, "Division by zero in vector3_divide");
    return (vector3) { a.x / b.x, a.y / b.y, a.z / b.z };
}

vector3 vector3_divide_scalar(vector3 v, float divisor) {
    ASSERT_MSG(divisor != 0, "Division by zero in vector3_divide_scalar");
    return (vector3) { v.x / divisor, v.y / divisor, v.z / divisor };
}

float vector3_distance(vector3 a, vector3 b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return math_sqrt(dx * dx + dy * dy + dz * dz);
}

float vector3_distance_squared(vector3 a, vector3 b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

float vector3_dot(vector3 a, vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vector3 vector3_cross(vector3 a, vector3 b) {
    ASSERT_MSG(vector3_length_squared(a) > 0 && vector3_length_squared(b) > 0,
        "Cross product with zero vector is undefined");
    return (vector3) {
        a.y* b.z - a.z * b.y,
            a.z* b.x - a.x * b.z,
            a.x* b.y - a.y * b.x
    };
}

vector3 vector3_normalize(vector3 v) {
    float length = vector3_length(v);
    ASSERT_MSG(length > 0, "Cannot normalize zero vector");
    return vector3_divide_scalar(v, length);
}

bool vector3_is_normalized(vector3 v) {
    return math_is_approximately_zero(1 - (v.x * v.x + v.y * v.y + v.z * v.z));
}

float vector3_length(vector3 v) {
    return math_sqrt(vector3_length_squared(v));
}

float vector3_length_squared(vector3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

vector3 vector3_reflect(vector3 v, vector3 normal) {
    ASSERT_MSG(vector3_is_normalized(normal), "Reflection normal must be normalized");
    float dot = vector3_dot(v, normal) * 2.0f;
    return vector3_subtract(v, vector3_multiply_scalar(normal, dot));
}

vector3 vector3_lerp(vector3 a, vector3 b, float t) {
    ASSERT_MSG(t >= 0.0f && t <= 1.0f, "Interpolation value must be between 0 and 1");
    return (vector3) {
        a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t
    };
}
// 平滑插值
vector3 vector3_smooth_step(vector3 v1, vector3 v2, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Smooth-Step interpolation amount must be between 0 and 1");
    vector3 result;
    amount = (amount * amount) * (3.0f - (2.0f * amount));
    result.x = v1.x + ((v2.x - v1.x) * amount);
    result.y = v1.y + ((v2.y - v1.y) * amount);
    result.z = v1.z + ((v2.z - v1.z) * amount);
    return result;
}

// Catmull-Rom 插值
vector3 vector3_catmull_rom(vector3 v1, vector3 v2, vector3 v3, vector3 v4, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Catmull-Rom interpolation amount must be between 0 and 1");
    vector3 result;
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
    return result;
}

// Hermite 插值
vector3 vector3_hermite(vector3 v1, vector3 tangent1, vector3 v2, vector3 tangent2, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Hermite interpolation amount must be between 0 and 1");
    vector3 result;
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
    return result;
}