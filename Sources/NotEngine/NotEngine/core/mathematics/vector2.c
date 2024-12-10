#include "Vector2.h"
#include "math_funcs.h"
#include <stdlib.h>

#include "core/logger/assert.h"

// 实现函数
vector2 vector2_zero(void) {
    return (vector2) { 0.0f, 0.0f };
}

vector2 vector2_one(void) {
    return (vector2) { 1.0f, 1.0f };
}

vector2 vector2_unit_x(void) {
    return (vector2) { 1.0f, 0.0f };
}

vector2 vector2_unit_y(void) {
    return (vector2) { 0.0f, 1.0f };
}

vector2 vector2_right(void) {
    return (vector2) { 1.0f, 0.0f };
}

vector2 vector2_left(void) {
    return (vector2) { -1.0f, 0.0f };
}

vector2 vector2_up(void) {
    return (vector2) { 0.0f, 1.0f };
}

vector2 vector2_down(void) {
    return (vector2) { 0.0f, -1.0f };
}

vector2 vector2_create(float x, float y) {
    return (vector2)  { x, y };
}

vector2 vector2_create_from_scalar(float value) {
    vector2 v = { value, value };
    return v;
}


bool vector2_equals(vector2 v1, vector2 v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

bool vector2_approximate_equals(vector2 v1, vector2 v2) {
    return math_approximate_equals(v1.x, v1.x) && math_approximate_equals(v1.y, v1.y);
}



vector2 vector2_add(vector2 a, vector2 b) {
    vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

vector2 vector2_subtract(vector2 a, vector2 b) {
    vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

vector2 vector2_negate(vector2 v) {
    vector2 result;
    result.x = -v.x;
    result.y = -v.y;
    return result;
}

vector2 vector2_multiply(vector2 a, vector2 b) {
    vector2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

vector2 vector2_multiply_scalar(vector2 v, float scalar) {
    vector2 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    return result;
}

vector2 vector2_divide(vector2 a, vector2 b) {
    ASSERT_MSG(b.x != 0 && b.y!=0, "divisor can't be zero!");
    vector2 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

vector2 vector2_divide_scalar(vector2 v, float divisor) {
    ASSERT_MSG(divisor != 0, "divisor can't be zero!");
    vector2 result;
    result.x = v.x / divisor;
    result.y = v.y / divisor;
    return result;
}


vector2 vector2_min(vector2 a, vector2 b) {
    vector2 result;
    result.x = (a.x < b.x) ? a.x : b.x;
    result.y = (a.y < b.y) ? a.y : b.y;
    return result;
}

vector2 vector2_max(vector2 a, vector2 b) {
    vector2 result;
    result.x = (a.x > b.x) ? a.x : b.x;
    result.y = (a.y > b.y) ? a.y : b.y;
    return result;
}

vector2 vector2_clamp(vector2 v, vector2 min, vector2 max) {
    return vector2_min(vector2_max(v, min), max);
}

vector2 vector2_clamp_scalar(vector2 v, float min, float max)
{
    vector2 result = v;
    result.x = (result.x < min) ? min : (result.x > max) ? max : result.x;
    result.y = (result.y < min) ? min : (result.y > max) ? max : result.y;
    return result;
}


float vector2_distance(vector2 a,vector2 b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    float length_squared = (dx * dx) + (dy * dy);
    return math_sqrt(length_squared);
}

float vector2_distance_squared(vector2 a, vector2 b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    return  (dx * dx) + (dy * dy);
}

float vector2_dot(vector2 a,vector2 b)
{
    return a.x * b.x + a.y * b.y;
}


vector2 vector2_normalize(vector2 v)
{
    float length = vector2_length(v);
    ASSERT_MSG(length > 0, "Cannot normalize zero vector");
    return vector2_divide_scalar(v, length);
}
bool vector2_is_normalized(vector2 v)
{
    return math_is_approximately_zero(1 - v.x * v.x - v.y * v.y);
}


float vector2_length_squared(vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

float vector2_length(vector2 v)
{
    return math_sqrt(vector2_length_squared(v));
}

vector2 SquareRoot(vector2 v)
{
    ASSERT_MSG(v.x >= 0.0f && v.y >= 0.0f, "Cannot calculate square root of negative values");
    return (vector2) { math_sqrt(v.x), math_sqrt(v.y) };
}

vector2 vector2_reflect(vector2 v, vector2 normal)
{
    ASSERT_MSG(vector2_is_normalized(normal), "Normal vector must be normalized");
    float dot = vector2_dot(v, normal);
    float two_dot = dot * 2;
    vector2 m = vector2_multiply_scalar(normal, two_dot);
    return vector2_subtract(v, m);
}

vector2 vector2_lerp(vector2 a, vector2 b, float t) {
    ASSERT_MSG(t >= 0.0f && t <= 1.0f, "Interpolation value must be between 0 and 1");
    vector2 result;
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    return result;
}
vector2 vector2_smooth_step(vector2 v1, vector2 v2, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Amount must be between 0 and 1");
    vector2 result;
    amount = (amount * amount) * (3.0f - (2.0f * amount));
    result.x = v1.x + ((v2.x - v1.x) * amount);
    result.y = v1.y + ((v2.y - v1.y) * amount);
    return result;

}
vector2 vector2_catmull_rom(vector2 v1, vector2 v2, vector2 v3, vector2 v4, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Amount must be between 0 and 1");
    vector2 result;
    float t2 = amount * amount;
    float t3 = t2 * amount;
    result.x = 0.5f * ((2.0f * v2.x) + (-v1.x + v3.x) * amount + (2.0f * v1.x - 5.0f * v2.x + 4.0f * v3.x - v4.x) * t2 + (-v1.x + 3.0f * v2.x - 3.0f * v3.x + v4.x) * t3);
    result.y = 0.5f * ((2.0f * v2.y) + (-v1.y + v3.y) * amount + (2.0f * v1.y - 5.0f * v2.y + 4.0f * v3.y - v4.y) * t2 + (-v1.y + 3.0f * v2.y - 3.0f * v3.y + v4.y) * t3);
    return result;
}
vector2 vector2_hermite(vector2 v1, vector2 tangent1, vector2 v2, vector2 tangent2, float amount) {
    ASSERT_MSG(amount >= 0.0f && amount <= 1.0f, "Amount must be between 0 and 1");
    ASSERT_MSG(vector2_is_normalized(tangent1) && vector2_is_normalized(tangent2), "Tangent must be between 0 and 1");
    vector2 result;
    float squared = amount * amount; // t^2
    float cubed = amount * squared; // t^3

    // Hermite basis functions:
    float a = ((2 * cubed) - (3 * squared)) + 1; // (2t³ - 3t² + 1)
    float b = (-2 * cubed) + (3 * squared); // (-2t³ + 3t²)
    float c = cubed - (2 * squared) + amount; // (t³ - 2t² + t)
    float d = cubed - squared; // (t³ - t²)

    // Compute the interpolated vector.
    result.x = (v1.x * a) + (v2.x * b) + (tangent1.x * c) + (tangent2.x * d);
    result.y = (v1.y * a) + (v2.y * b) + (tangent1.y * c) + (tangent2.y * d);
    return result;
}