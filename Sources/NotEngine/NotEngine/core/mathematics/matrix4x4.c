#include <assert.h>
#include <stdbool.h>
#include "matrix4x4.h"
#include "math_funcs.h"
#include "quaternion.h"
#include "vector3.h"
#include "core/logger/assert.h"
// Function implementations

bool matrix44_equals(Matrix4x4 a, Matrix4x4 b) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a.data[i][j] != b.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool matrix44_approximate_equals(Matrix4x4 a, Matrix4x4 b) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (math_abs(a.data[i][j] - b.data[i][j]) > MATH_EPSILON) {
                return false;
            }
        }
    }
    return true;
}

Matrix4x4 matrix44_identity()
{
    Matrix4x4 result = { {{1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}} };
    return result;
}

Matrix4x4 matrix44_add(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix4x4 matrix44_subtract(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix4x4 matrix44_negate(Matrix4x4 m) {
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = -m.data[i][j];
        }
    }
    return result;
}

Matrix4x4 matrix44_product(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix4x4 matrix44_multiply_scalar(Matrix4x4 a, float scalar)
{
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += a.data[i][k] * scalar;
            }
        }
    }
    return result;
}

Matrix4x4 matrix44_transpose(Matrix4x4 m) {
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = m.data[j][i];
        }
    }
    return result;
}



float matrix44_determinant(Matrix4x4 m) {
    float det;
    det = m.data[0][0] * (m.data[1][1] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) -
        m.data[1][2] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) +
        m.data[1][3] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]));
    det -= m.data[0][1] * (m.data[1][0] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) -
        m.data[1][2] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) +
        m.data[1][3] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]));
    det += m.data[0][2] * (m.data[1][0] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) -
        m.data[1][1] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) +
        m.data[1][3] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    det -= m.data[0][3] * (m.data[1][0] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]) -
        m.data[1][1] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]) +
        m.data[1][2] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    return det;
}

Matrix4x4 matrix44_invert(Matrix4x4 m) {
    Matrix4x4 result;
    float det = matrix44_determinant(m);
    ASSERT_MSG(math_abs(det) > MATH_EPSILON, "Matrix is not invertible (determinant is zero)");
    float invDet = 1.0f / det;

    // Calculate the adjugate matrix
    result.data[0][0] = invDet * (m.data[1][1] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) - m.data[1][2] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) + m.data[1][3] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]));
    result.data[0][1] = invDet * -(m.data[0][1] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) - m.data[0][2] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) + m.data[0][3] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]));
    result.data[0][2] = invDet * (m.data[0][1] * (m.data[1][2] * m.data[3][3] - m.data[1][3] * m.data[3][2]) - m.data[0][2] * (m.data[1][1] * m.data[3][3] - m.data[1][3] * m.data[3][1]) + m.data[0][3] * (m.data[1][1] * m.data[3][2] - m.data[1][2] * m.data[3][1]));
    result.data[0][3] = invDet * -(m.data[0][1] * (m.data[1][2] * m.data[2][3] - m.data[1][3] * m.data[2][2]) - m.data[0][2] * (m.data[1][1] * m.data[2][3] - m.data[1][3] * m.data[2][1]) + m.data[0][3] * (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]));

    result.data[1][0] = invDet * -(m.data[1][0] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) - m.data[1][2] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) + m.data[1][3] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]));
    result.data[1][1] = invDet * (m.data[0][0] * (m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2]) - m.data[0][2] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) + m.data[0][3] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]));
    result.data[1][2] = invDet * -(m.data[0][0] * (m.data[1][2] * m.data[3][3] - m.data[1][3] * m.data[3][2]) - m.data[0][2] * (m.data[1][0] * m.data[3][3] - m.data[1][3] * m.data[3][0]) + m.data[0][3] * (m.data[1][0] * m.data[3][2] - m.data[1][2] * m.data[3][0]));
    result.data[1][3] = invDet * (m.data[0][0] * (m.data[1][2] * m.data[2][3] - m.data[1][3] * m.data[2][2]) - m.data[0][2] * (m.data[1][0] * m.data[2][3] - m.data[1][3] * m.data[2][0]) + m.data[0][3] * (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]));

    result.data[2][0] = invDet * (m.data[1][0] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) - m.data[1][1] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) + m.data[1][3] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    result.data[2][1] = invDet * -(m.data[0][0] * (m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1]) - m.data[0][1] * (m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0]) + m.data[0][3] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    result.data[2][2] = invDet * (m.data[0][0] * (m.data[1][1] * m.data[3][3] - m.data[1][3] * m.data[3][1]) - m.data[0][1] * (m.data[1][0] * m.data[3][3] - m.data[1][3] * m.data[3][0]) + m.data[0][3] * (m.data[1][0] * m.data[3][1] - m.data[1][1] * m.data[3][0]));
    result.data[2][3] = invDet * -(m.data[0][0] * (m.data[1][1] * m.data[2][3] - m.data[1][3] * m.data[2][1]) - m.data[0][1] * (m.data[1][0] * m.data[2][3] - m.data[1][3] * m.data[2][0]) + m.data[0][3] * (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]));

    result.data[3][0] = invDet * -(m.data[1][0] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]) - m.data[1][1] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]) + m.data[1][2] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    result.data[3][1] = invDet * (m.data[0][0] * (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1]) - m.data[0][1] * (m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0]) + m.data[0][2] * (m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0]));
    result.data[3][2] = invDet * -(m.data[0][0] * (m.data[1][1] * m.data[3][2] - m.data[1][2] * m.data[3][1]) - m.data[0][1] * (m.data[1][0] * m.data[3][2] - m.data[1][2] * m.data[3][0]) + m.data[0][2] * (m.data[1][0] * m.data[3][1] - m.data[1][1] * m.data[3][0]));
    result.data[3][3] = invDet * (m.data[0][0] * (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) - m.data[0][1] * (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) + m.data[0][2] * (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]));

    return result;
}

void matrix44_decompose(Matrix4x4 m, Vector3* scale, Quaternion* rotation, Vector3* translation) {
    ASSERT_NOT_NULL(scale);
    ASSERT_NOT_NULL(rotation);
    ASSERT_NOT_NULL(translation);
    // Extract translation
    translation->x = m.data[3][0];
    translation->y = m.data[3][1];
    translation->z = m.data[3][2];

    // Extract scale
    scale->x = math_sqrt(m.data[0][0] * m.data[0][0] + m.data[0][1] * m.data[0][1] + m.data[0][2] * m.data[0][2]);
    scale->y = math_sqrt(m.data[1][0] * m.data[1][0] + m.data[1][1] * m.data[1][1] + m.data[1][2] * m.data[1][2]);
    scale->z = math_sqrt(m.data[2][0] * m.data[2][0] + m.data[2][1] * m.data[2][1] + m.data[2][2] * m.data[2][2]);

    // Normalize the rotation matrix
    Matrix4x4 rotationMatrix = m;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            rotationMatrix.data[i][j] /= scale->arr[i];
        }
    }

    // Convert rotation matrix to Quaternion
    // This is a simplified version and may not be fully accurate
    float trace = rotationMatrix.data[0][0] + rotationMatrix.data[1][1] + rotationMatrix.data[2][2];
    if (trace > 0) {
        float s = 0.5f / math_sqrt(trace + 1.0f);
        rotation->u = 0.25f / s;
        rotation->i = -(rotationMatrix.data[2][1] - rotationMatrix.data[1][2]) * s;
        rotation->j = -(rotationMatrix.data[0][2] - rotationMatrix.data[2][0]) * s;
        rotation->k = -(rotationMatrix.data[1][0] - rotationMatrix.data[0][1]) * s;
    }
    else {
        if (rotationMatrix.data[0][0] > rotationMatrix.data[1][1] && rotationMatrix.data[0][0] > rotationMatrix.data[2][2]) {
            float s = 2.0f * math_sqrt(1.0f + rotationMatrix.data[0][0] - rotationMatrix.data[1][1] - rotationMatrix.data[2][2]);
            rotation->u = (rotationMatrix.data[2][1] - rotationMatrix.data[1][2]) / s;
            rotation->i = -0.25f * s;
            rotation->j = -(rotationMatrix.data[0][1] + rotationMatrix.data[1][0]) / s;
            rotation->k = -(rotationMatrix.data[0][2] + rotationMatrix.data[2][0]) / s;
        }
        else if (rotationMatrix.data[1][1] > rotationMatrix.data[2][2]) {
            float s = 2.0f * math_sqrt(1.0f + rotationMatrix.data[1][1] - rotationMatrix.data[0][0] - rotationMatrix.data[2][2]);
            rotation->u = (rotationMatrix.data[0][2] - rotationMatrix.data[2][0]) / s;
            rotation->i = -(rotationMatrix.data[0][1] + rotationMatrix.data[1][0]) / s;
            rotation->j = -0.25f * s;
            rotation->k = -(rotationMatrix.data[1][2] + rotationMatrix.data[2][1]) / s;
        }
        else {
            float s = 2.0f * math_sqrt(1.0f + rotationMatrix.data[2][2] - rotationMatrix.data[0][0] - rotationMatrix.data[1][1]);
            rotation->u = (rotationMatrix.data[1][0] - rotationMatrix.data[0][1]) / s;
            rotation->i = -(rotationMatrix.data[0][2] + rotationMatrix.data[2][0]) / s;
            rotation->j = -(rotationMatrix.data[1][2] + rotationMatrix.data[2][1]) / s;
            rotation->k = -0.25f * s;
        }
    }
}

Vector3 matrix44_transform_vector3(Matrix4x4 m, Vector3 v) {
    Vector3 result;
    result.x = m.data[0][0] * v.x + m.data[1][0] * v.y + m.data[2][0] * v.z + m.data[3][0];
    result.y = m.data[0][1] * v.x + m.data[1][1] * v.y + m.data[2][1] * v.z + m.data[3][1];
    result.z = m.data[0][2] * v.x + m.data[1][2] * v.y + m.data[2][2] * v.z + m.data[3][2];
    return result;
}

Vector4 matrix44_transform_vector4(Matrix4x4 m, Vector4 v) {
    Vector4 result;
    result.x = m.data[0][0] * v.x + m.data[1][0] * v.y + m.data[2][0] * v.z + m.data[3][0] * v.w;
    result.y = m.data[0][1] * v.x + m.data[1][1] * v.y + m.data[2][1] * v.z + m.data[3][1] * v.w;
    result.z = m.data[0][2] * v.x + m.data[1][2] * v.y + m.data[2][2] * v.z + m.data[3][2] * v.w;
    result.w = m.data[0][3] * v.x + m.data[1][3] * v.y + m.data[2][3] * v.z + m.data[3][3] * v.w;
    return result;
}

Matrix4x4 matrix44_lerp(Matrix4x4 a, Matrix4x4 b, float t)
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = a.data[i][j] * (1 - t) + b.data[i][j] * t;
        }
    }
    return result;
}

Matrix4x4 matrix44_transform_quaternion(Matrix4x4 m, Quaternion q)
{
    ASSERT_MSG(quaternion_is_normalized(q), "Quaternion must be normalized");
    // Compute rotation matrix elements
    float twoI = q.i + q.i, twoJ = q.j + q.j, twoK = q.k + q.k;
    float twoUI = q.u * twoI, twoUJ = q.u * twoJ, twoUK = q.u * twoK;
    float twoII = q.i * twoI, twoIJ = q.i * twoJ, twoIK = q.i * twoK;
    float twoJJ = q.j * twoJ, twoJK = q.j * twoK, twoKK = q.k * twoK;

    float tR0C0 = 1.0f - twoJJ - twoKK;
    float tR1C0 = twoIJ - twoUK;
    float tR2C0 = twoIK + twoUJ;

    float tR0C1 = twoIJ + twoUK;
    float tR1C1 = 1.0f - twoII - twoKK;
    float tR2C1 = twoJK - twoUI;

    float tR0C2 = twoIK - twoUJ;
    float tR1C2 = twoJK + twoUI;
    float tR2C2 = 1.0f - twoII - twoJJ;

    // Compute the transformed matrix
    Matrix4x4 result;

    // First row
    result.data[0][0] = m.data[0][0] * tR0C0 + m.data[0][1] * tR1C0 + m.data[0][2] * tR2C0;
    result.data[0][1] = m.data[0][0] * tR0C1 + m.data[0][1] * tR1C1 + m.data[0][2] * tR2C1;
    result.data[0][2] = m.data[0][0] * tR0C2 + m.data[0][1] * tR1C2 + m.data[0][2] * tR2C2;
    result.data[0][3] = m.data[0][3];

    // Second row
    result.data[1][0] = m.data[1][0] * tR0C0 + m.data[1][1] * tR1C0 + m.data[1][2] * tR2C0;
    result.data[1][1] = m.data[1][0] * tR0C1 + m.data[1][1] * tR1C1 + m.data[1][2] * tR2C1;
    result.data[1][2] = m.data[1][0] * tR0C2 + m.data[1][1] * tR1C2 + m.data[1][2] * tR2C2;
    result.data[1][3] = m.data[1][3];

    // Third row
    result.data[2][0] = m.data[2][0] * tR0C0 + m.data[2][1] * tR1C0 + m.data[2][2] * tR2C0;
    result.data[2][1] = m.data[2][0] * tR0C1 + m.data[2][1] * tR1C1 + m.data[2][2] * tR2C1;
    result.data[2][2] = m.data[2][0] * tR0C2 + m.data[2][1] * tR1C2 + m.data[2][2] * tR2C2;
    result.data[2][3] = m.data[2][3];

    // Fourth row
    result.data[3][0] = m.data[3][0] * tR0C0 + m.data[3][1] * tR1C0 + m.data[3][2] * tR2C0;
    result.data[3][1] = m.data[3][0] * tR0C1 + m.data[3][1] * tR1C1 + m.data[3][2] * tR2C1;
    result.data[3][2] = m.data[3][0] * tR0C2 + m.data[3][1] * tR1C2 + m.data[3][2] * tR2C2;
    result.data[3][3] = m.data[3][3];

    return result;
}



Matrix4x4 matrix44_create_from_quaternion(Quaternion q) {
    ASSERT_MSG(quaternion_is_normalized(q),
        "Quaternion must be normalized for matrix creation");
    Matrix4x4 result;
    float twoI = q.i + q.i, twoJ = q.j + q.j, twoK = q.k + q.k;
    float twoUI = q.u * twoI, twoUJ = q.u * twoJ, twoUK = q.u * twoK;
    float twoII = q.i * twoI, twoIJ = q.i * twoJ, twoIK = q.i * twoK;
    float twoJJ = q.j * twoJ, twoJK = q.j * twoK, twoKK = q.k * twoK;

    result.data[0][0] = 1 - twoJJ - twoKK;
    result.data[1][0] = twoIJ - twoUK;
    result.data[2][0] = twoIK + twoUJ;
    result.data[3][0] = 0;

    result.data[0][1] = twoIJ + twoUK;
    result.data[1][1] = 1 - twoII - twoKK;
    result.data[2][1] = twoJK - twoUI;
    result.data[3][1] = 0;

    result.data[0][2] = twoIK - twoUJ;
    result.data[1][2] = twoJK + twoUI;
    result.data[2][2] = 1 - twoII - twoJJ;
    result.data[3][2] = 0;

    result.data[0][3] = 0;
    result.data[1][3] = 0;
    result.data[2][3] = 0;
    result.data[3][3] = 1;

    return result;
}

Matrix4x4 matrix44_create_translation(float x, float y, float z) {
    Matrix4x4 result = { {{1, 0, 0, 0},
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {x, y, z, 1}} };
    return result;
}

Matrix4x4 matrix44_create_scale(float x, float y, float z) {
    Matrix4x4 result = { {{x, 0, 0, 0},
                        {0, y, 0, 0},
                        {0, 0, z, 0},
                        {0, 0, 0, 1}} };
    return result;
}

Matrix4x4 matrix44_create_rotation_x(float radians) {
    float c = math_cos(radians);
    float s = math_sin(radians);
    Matrix4x4 result = { {{1, 0, 0, 0},
                        {0, c, s, 0},
                        {0, -s, c, 0},
                        {0, 0, 0, 1}} };
    return result;
}

Matrix4x4 matrix44_create_rotation_y(float radians) {
    float c = math_cos(radians);
    float s = math_sin(radians);
    Matrix4x4 result = { {{c, 0, -s, 0},
                        {0, 1, 0, 0},
                        {s, 0, c, 0},
                        {0, 0, 0, 1}} };
    return result;
}

Matrix4x4 matrix44_create_rotation_z(float radians) {
    float c = math_cos(radians);
    float s = math_sin(radians);
    Matrix4x4 result = { {{c, s, 0, 0},
                        {-s, c, 0, 0},
                        {0, 0, 1, 0},
                        {0, 0, 0, 1}} };
    return result;
}
Matrix4x4 matrix44_create_from_axis_angle(Vector3 axis, float angle) {
    ASSERT_MSG(vector3_is_normalized(axis),
        "Rotation axis must be normalized");
    Matrix4x4 result;
    float x = axis.x, y = axis.y, z = axis.z;
    float sin = math_sin(angle), cos = math_cos(angle);
    float xx = x * x, yy = y * y, zz = z * z;
    float xy = x * y, xz = x * z, yz = y * z;

    result.data[0][0] = xx + (cos * (1 - xx));
    result.data[0][1] = xy - (cos * xy) + (sin * z);
    result.data[0][2] = xz - (cos * xz) - (sin * y);
    result.data[0][3] = 0;

    result.data[1][0] = xy - (cos * xy) - (sin * z);
    result.data[1][1] = yy + (cos * (1 - yy));
    result.data[1][2] = yz - (cos * yz) + (sin * x);
    result.data[1][3] = 0;

    result.data[2][0] = xz - (cos * xz) + (sin * y);
    result.data[2][1] = yz - (cos * yz) - (sin * x);
    result.data[2][2] = zz + (cos * (1 - zz));
    result.data[2][3] = 0;

    result.data[3][0] = 0;
    result.data[3][1] = 0;
    result.data[3][2] = 0;
    result.data[3][3] = 1;

    return result;
}

Matrix4x4 matrix44_create_from_cartesian_axes(Vector3 right, Vector3 up, Vector3 backward) {
    ASSERT_MSG(vector3_is_normalized(right) &&
        vector3_is_normalized(up) &&
        vector3_is_normalized(backward),
        "All axes must be normalized");
    ASSERT_MSG(math_abs(vector3_dot(right, up)) < MATH_EPSILON &&
        math_abs(vector3_dot(up, backward)) < MATH_EPSILON &&
        math_abs(vector3_dot(backward, right)) < MATH_EPSILON,
        "Axes must be orthogonal");
    // 轴必须两两垂直且为单位长度
    Matrix4x4 result;
    result.data[0][0] = right.x;
    result.data[0][1] = right.y;
    result.data[0][2] = right.z;
    result.data[0][3] = 0;

    result.data[1][0] = up.x;
    result.data[1][1] = up.y;
    result.data[1][2] = up.z;
    result.data[1][3] = 0;

    result.data[2][0] = backward.x;
    result.data[2][1] = backward.y;
    result.data[2][2] = backward.z;
    result.data[2][3] = 0;

    result.data[3][0] = 0;
    result.data[3][1] = 0;
    result.data[3][2] = 0;
    result.data[3][3] = 1;

    return result;
}

Matrix4x4 matrix44_create_world(Vector3 position, Vector3 forward, Vector3 up) {
    Matrix4x4 result;
    Vector3 backward = vector3_negate(forward);
    backward = vector3_normalize(backward);

    Vector3 right = vector3_cross(up, backward);
    right = vector3_normalize(right);

    Vector3 final_up = vector3_cross(right, backward);
    final_up = vector3_normalize(final_up);

    result.data[0][0] = right.x;
    result.data[0][1] = right.y;
    result.data[0][2] = right.z;
    result.data[0][3] = 0;

    result.data[1][0] = final_up.x;
    result.data[1][1] = final_up.y;
    result.data[1][2] = final_up.z;
    result.data[1][3] = 0;

    result.data[2][0] = backward.x;
    result.data[2][1] = backward.y;
    result.data[2][2] = backward.z;
    result.data[2][3] = 0;

    result.data[3][0] = position.x;
    result.data[3][1] = position.y;
    result.data[3][2] = position.z;
    result.data[3][3] = 1;

    return result;
}


Matrix4x4 matrix44_create_perspective_field_of_view(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {
    ASSERT_MSG(fieldOfView > 0 && fieldOfView < MATH_PI,
        "Field of view must be between 0 and PI");
    ASSERT_MSG(aspectRatio > 0, "Aspect ratio must be positive");
    ASSERT_MSG(nearPlaneDistance > 0, "Near plane distance must be positive");
    ASSERT_MSG(farPlaneDistance > nearPlaneDistance,
        "Far plane must be further than near plane");

    Matrix4x4 result = { 0 };
    float yScale = 1.0f / math_tan(fieldOfView * 0.5f);
    float xScale = yScale / aspectRatio;
    float f1 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    float f2 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);

    result.data[0][0] = xScale;
    result.data[1][1] = yScale;
    result.data[2][2] = f1;
    result.data[2][3] = -1.0f;
    result.data[3][2] = f2;

    return result;
}

Matrix4x4 matrix44_create_perspective(float width, float height, float nearPlaneDistance, float farPlaneDistance) {
    assert(nearPlaneDistance > 0);
    assert(farPlaneDistance > 0);
    assert(nearPlaneDistance < farPlaneDistance);

    Matrix4x4 result = { 0 };
    result.data[0][0] = (nearPlaneDistance * 2.0f) / width;
    result.data[1][1] = (nearPlaneDistance * 2.0f) / height;
    result.data[2][2] = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    result.data[2][3] = -1.0f;
    result.data[3][2] = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);

    return result;
}

Matrix4x4 matrix44_create_perspective_off_center(float left, float right, float bottom, float top,
    float nearPlaneDistance, float farPlaneDistance) {
    assert(nearPlaneDistance > 0);
    assert(farPlaneDistance > 0);
    assert(nearPlaneDistance < farPlaneDistance);

    Matrix4x4 result = { 0 };
    result.data[0][0] = (nearPlaneDistance * 2.0f) / (right - left);
    result.data[1][1] = (nearPlaneDistance * 2.0f) / (top - bottom);
    result.data[2][0] = (left + right) / (right - left);
    result.data[2][1] = (top + bottom) / (top - bottom);
    result.data[2][2] = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
    result.data[2][3] = -1.0f;
    result.data[3][2] = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);

    return result;
}

Matrix4x4 matrix44_create_orthographic(float width, float height, float zNearPlane, float zFarPlane) {
    Matrix4x4 result = { 0 };
    result.data[0][0] = 2.0f / width;
    result.data[1][1] = 2.0f / height;
    result.data[2][2] = 1.0f / (zNearPlane - zFarPlane);
    result.data[3][2] = zNearPlane / (zNearPlane - zFarPlane);
    result.data[3][3] = 1.0f;

    return result;
}

Matrix4x4 matrix44_create_orthographic_off_center(float left, float right, float bottom, float top,
    float zNearPlane, float zFarPlane) {
    ASSERT_MSG(right != left, "Left and right planes cannot be equal");
    ASSERT_MSG(top != bottom, "Top and bottom planes cannot be equal");
    ASSERT_MSG(zFarPlane != zNearPlane, "Near and far planes cannot be equal");
    Matrix4x4 result = { 0 };
    result.data[0][0] = 2.0f / (right - left);
    result.data[1][1] = 2.0f / (top - bottom);
    result.data[2][2] = 1.0f / (zNearPlane - zFarPlane);
    result.data[3][0] = (left + right) / (left - right);
    result.data[3][1] = (top + bottom) / (bottom - top);
    result.data[3][2] = zNearPlane / (zNearPlane - zFarPlane);
    result.data[3][3] = 1.0f;

    return result;
}

Matrix4x4 matrix44_create_look_at(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector) {
    ASSERT_MSG(!vector3_equals(cameraPosition, cameraTarget),
        "Camera position cannot be equal to target");
    ASSERT_MSG(vector3_length_squared(cameraUpVector) > 0,
        "Up vector cannot be zero");
    Vector3 forward = vector3_subtract(cameraPosition, cameraTarget);
    forward = vector3_normalize(forward);

    Vector3 right = vector3_cross(cameraUpVector, forward);
    right = vector3_normalize(right);

    Vector3 up = vector3_cross(forward, right);
    up = vector3_normalize(up);

    float a = vector3_dot(right, cameraPosition);
    float b = vector3_dot(up, cameraPosition);
    float c = vector3_dot(forward, cameraPosition);

    Matrix4x4 result = { 0 };
    result.data[0][0] = right.x;
    result.data[0][1] = up.x;
    result.data[0][2] = forward.x;
    result.data[1][0] = right.y;
    result.data[1][1] = up.y;
    result.data[1][2] = forward.y;
    result.data[2][0] = right.z;
    result.data[2][1] = up.z;
    result.data[2][2] = forward.z;
    result.data[3][0] = -a;
    result.data[3][1] = -b;
    result.data[3][2] = -c;
    result.data[3][3] = 1.0f;

    return result;
}


bool matrix44_is_rotation(Matrix4x4 m) {
    // 1. 检查每行是否为单位向量
    Vector3 row1 = { m.data[0][0], m.data[0][1], m.data[0][2] };
    Vector3 row2 = { m.data[1][0], m.data[1][1], m.data[1][2] };
    Vector3 row3 = { m.data[2][0], m.data[2][1], m.data[2][2] };

    // 检查每行是否为单位向量
    if (!math_approximate_equals(vector3_length_squared(row1), 1.0f) ||
        !math_approximate_equals(vector3_length_squared(row2), 1.0f) ||
        !math_approximate_equals(vector3_length_squared(row3), 1.0f)) {
        return false;
    }

    // 2. 检查行向量是否互相垂直
    if (!math_is_approximately_zero(vector3_dot(row1, row2)) ||
        !math_is_approximately_zero(vector3_dot(row2, row3)) ||
        !math_is_approximately_zero(vector3_dot(row3, row1))) {
        return false;
    }

    // 3. 检查行列式是否为1（保持右手坐标系）
    float det = matrix44_determinant(m);
    if (!math_approximate_equals(det, 1.0f)) {
        return false;
    }

    // 4. 检查第四行和第四列是否符合旋转矩阵的形式
    if (!math_is_approximately_zero(m.data[3][0]) ||
        !math_is_approximately_zero(m.data[3][1]) ||
        !math_is_approximately_zero(m.data[3][2]) ||
        !math_approximate_equals(m.data[3][3], 1.0f)) {
        return false;
    }

    return true;
}