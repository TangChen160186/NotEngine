#include "Vector2.h"
#include "math_funcs.h"
#include <stdlib.h>

// 实现函数
Vector2 vector2_zero(void) {
    return (Vector2) { 0.0f, 0.0f };
}

Vector2 vector2_one(void) {
    return (Vector2) { 1.0f, 1.0f };
}

Vector2 vector2_unit_x(void) {
    return (Vector2) { 1.0f, 0.0f };
}

Vector2 vector2_unit_y(void) {
    return (Vector2) { 0.0f, 1.0f };
}

Vector2 vector2_right(void) {
    return (Vector2) { 1.0f, 0.0f };
}

Vector2 vector2_left(void) {
    return (Vector2) { -1.0f, 0.0f };
}

Vector2 vector2_up(void) {
    return (Vector2) { 0.0f, 1.0f };
}

Vector2 vector2_down(void) {
    return (Vector2) { 0.0f, -1.0f };
}

Vector2 vector2_create(float x, float y) {
    return (Vector2)  { x, y };
}

Vector2 vector2_create_from_scalar(float value) {
    Vector2 v = { value, value };
    return v;
}


bool vector2_equals(Vector2 v1, Vector2 v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

bool vector2_approximate_equals(Vector2 v1, Vector2 v2) {
    return math_approximate_equals(v1.x, v1.x) && math_approximate_equals(v1.y, v1.y);

}



Vector2 vector2_add(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vector2 vector2_subtract(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vector2 vector2_negate(Vector2 v) {
    Vector2 result;
    result.x = -v.x;
    result.y = -v.y;
    return result;
}

Vector2 vector2_multiply(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

Vector2 vector2_multiply_scalar(Vector2 v, float scalar) {
    Vector2 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    return result;
}

Vector2 vector2_divide(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

Vector2 vector2_divide_scalar(Vector2 v, float divisor) {
    Vector2 result;
    result.x = v.x / divisor;
    result.y = v.y / divisor;
    return result;
}


Vector2 vector2_min(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = (a.x < b.x) ? a.x : b.x;
    result.y = (a.y < b.y) ? a.y : b.y;
    return result;
}

Vector2 vector2_max(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = (a.x > b.x) ? a.x : b.x;
    result.y = (a.y > b.y) ? a.y : b.y;
    return result;
}

Vector2 vector2_clamp(Vector2 v, Vector2 min, Vector2 max) {
    return vector2_min(vector2_max(v, min), max);
}

Vector2 vector2_clamp_scalar(Vector2 v, float min, float max)
{
    Vector2 result = v;
    result.x = (result.x < min) ? min : (result.x > max) ? max : result.x;
    result.y = (result.y < min) ? min : (result.y > max) ? max : result.y;
    return result;
}


float vector2_distance(Vector2 a,Vector2 b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    float length_squared = (dx * dx) + (dy * dy);
    return math_sqrt(length_squared);
}

float vector2_distance_squared(Vector2 a, Vector2 b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    return  (dx * dx) + (dy * dy);
}

float vector2_dot(Vector2 a,Vector2 b)
{
    return a.x * b.x + a.y * b.y;
}


Vector2 vector2_normalize(Vector2 v)
{
    return vector2_divide_scalar(v,vector2_length(v));
}
bool vector2_is_normalized(Vector2 v)
{
    return math_is_approximately_zero(1 - v.x * v.x - v.y * v.y);
}


float vector2_length_squared(Vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

float vector2_length(Vector2 v)
{
    return math_sqrt(vector2_length_squared(v));
}

Vector2 SquareRoot(Vector2 v)
{
    return (Vector2) { math_sqrt(v.x), math_sqrt(v.y) };
}

Vector2 vector2_reflect(Vector2 v, Vector2 normal)
{
    float dot = vector2_dot(v, normal);
    float two_dot = dot * 2;
    Vector2 m = vector2_multiply_scalar(normal, two_dot);
    return vector2_subtract(v, m);
}

Vector2 vector2_lerp(Vector2 a, Vector2 b, float t) {
    Vector2 result;
    result.x = a.x + (b.x - a.x) * t;
    result.y = a.y + (b.y - a.y) * t;
    return result;
}
Vector2 vector2_smooth_step(Vector2 v1, Vector2 v2, float amount) {
    amount = math_clamp(amount, 0, 1);
    Vector2 result;
    amount = (amount * amount) * (3.0f - (2.0f * amount));
    result.x = v1.x + ((v2.x - v1.x) * amount);
    result.y = v1.y + ((v2.y - v1.y) * amount);
    return result;

}
Vector2 vector2_catmull_rom(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, float amount) {
    amount = math_clamp(amount, 0, 1);
    Vector2 result;
    float t2 = amount * amount;
    float t3 = t2 * amount;
    result.x = 0.5f * ((2.0f * v2.x) + (-v1.x + v3.x) * amount + (2.0f * v1.x - 5.0f * v2.x + 4.0f * v3.x - v4.x) * t2 + (-v1.x + 3.0f * v2.x - 3.0f * v3.x + v4.x) * t3);
    result.y = 0.5f * ((2.0f * v2.y) + (-v1.y + v3.y) * amount + (2.0f * v1.y - 5.0f * v2.y + 4.0f * v3.y - v4.y) * t2 + (-v1.y + 3.0f * v2.y - 3.0f * v3.y + v4.y) * t3);
    return result;
}
Vector2 vector2_hermite(Vector2 v1, Vector2 tangent1, Vector2 v2, Vector2 tangent2, float amount) {

    amount = math_clamp(amount, 0, 1);
    Vector2 result;
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