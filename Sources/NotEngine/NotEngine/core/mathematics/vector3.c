#include "Vector3.h"
#include "math_funcs.h"

Vector3 vector3_zero(void) {
    return (Vector3) { 0.0f, 0.0f, 0.0f };
}

Vector3 vector3_one(void) {
    return (Vector3) { 1.0f, 1.0f, 1.0f };
}

Vector3 vector3_unit_x(void) {
    return (Vector3) { 1.0f, 0.0f, 0.0f };
}

Vector3 vector3_unit_y(void) {
    return (Vector3) { 0.0f, 1.0f, 0.0f };
}

Vector3 vector3_unit_z(void) {
    return (Vector3) { 0.0f, 0.0f, 1.0f };
}

// 向右 (+X) 方向
Vector3 vector3_right(void) {
    return (Vector3) { 1.0f, 0.0f, 0.0f };
}

// 向左 (-X) 方向
Vector3 vector3_left(void) {
    return (Vector3) { -1.0f, 0.0f, 0.0f };
}

// 向上 (+Y) 方向
Vector3 vector3_up(void) {
    return (Vector3) { 0.0f, 1.0f, 0.0f };
}

// 向下 (-Y) 方向
Vector3 vector3_down(void) {
    return (Vector3) { 0.0f, -1.0f, 0.0f };
}

// 向前 (+Z) 方向
Vector3 vector3_forward(void) {
    return (Vector3) { 0.0f, 0.0f, 1.0f };
}

// 向后 (-Z) 方向
Vector3 vector3_backward(void) {
    return (Vector3) { 0.0f, 0.0f, -1.0f };
}


Vector3 vector3_create(float x, float y, float z) {
    return (Vector3) { x, y, z };
}

Vector3 vector3_create_from_scalar(float value) {
    return (Vector3) { value, value, value };
}

bool vector3_equals(Vector3 v1, Vector3 v2) {
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

bool vector3_approximate_equals(Vector3 v1, Vector3 v2) {
    return math_approximate_equals(v1.x, v2.x) &&
        math_approximate_equals(v1.y, v2.y) &&
        math_approximate_equals(v1.z, v2.z);
}

Vector3 vector3_add(Vector3 a, Vector3 b) {
    return (Vector3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 vector3_subtract(Vector3 a, Vector3 b) {
    return (Vector3) { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 vector3_negate(Vector3 v) {
    return (Vector3) { -v.x, -v.y, -v.z };
}

Vector3 vector3_multiply(Vector3 a, Vector3 b) {
    return (Vector3) { a.x* b.x, a.y* b.y, a.z* b.z };
}

Vector3 vector3_multiply_scalar(Vector3 v, float scalar) {
    return (Vector3) { v.x* scalar, v.y* scalar, v.z* scalar };
}

Vector3 vector3_divide(Vector3 a, Vector3 b) {
    return (Vector3) { a.x / b.x, a.y / b.y, a.z / b.z };
}

Vector3 vector3_divide_scalar(Vector3 v, float divisor) {
    return (Vector3) { v.x / divisor, v.y / divisor, v.z / divisor };
}

float vector3_distance(Vector3 a, Vector3 b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return math_sqrt(dx * dx + dy * dy + dz * dz);
}

float vector3_distance_squared(Vector3 a, Vector3 b) {
    float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

float vector3_dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 vector3_cross(Vector3 a, Vector3 b) {
    return (Vector3) {
        a.y* b.z - a.z * b.y,
            a.z* b.x - a.x * b.z,
            a.x* b.y - a.y * b.x
    };
}

Vector3 vector3_normalize(Vector3 v) {
    float length = vector3_length(v);
    return vector3_divide_scalar(v, length);
}

bool vector3_is_normalized(Vector3 v) {
    return math_is_approximately_zero(1 - (v.x * v.x + v.y * v.y + v.z * v.z));
}

float vector3_length(Vector3 v) {
    return math_sqrt(vector3_length_squared(v));
}

float vector3_length_squared(Vector3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

Vector3 vector3_reflect(Vector3 v, Vector3 normal) {
    float dot = vector3_dot(v, normal) * 2.0f;
    return vector3_subtract(v, vector3_multiply_scalar(normal, dot));
}

Vector3 vector3_lerp(Vector3 a, Vector3 b, float t) {
    return (Vector3) {
        a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t
    };
}
// 平滑插值
Vector3 vector3_smooth_step(Vector3 v1, Vector3 v2, float amount) {
    amount = math_clamp(amount, 0, 1);
    Vector3 result;
    amount = (amount * amount) * (3.0f - (2.0f * amount));
    result.x = v1.x + ((v2.x - v1.x) * amount);
    result.y = v1.y + ((v2.y - v1.y) * amount);
    result.z = v1.z + ((v2.z - v1.z) * amount);
    return result;
}

// Catmull-Rom 插值
Vector3 vector3_catmull_rom(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4, float amount) {
    amount = math_clamp(amount, 0, 1);
    Vector3 result;
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
Vector3 vector3_hermite(Vector3 v1, Vector3 tangent1, Vector3 v2, Vector3 tangent2, float amount) {
    amount = math_clamp(amount, 0, 1);
    Vector3 result;
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