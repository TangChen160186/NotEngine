#pragma once

typedef struct
{
    union
    {
        struct
        {
            float x, y;
        };

        struct
        {
            float arr[2];
        };
    };
} Vector2;


typedef struct
{
    union
    {
        struct
        {
            float x, y, z;
        };

        struct
        {
            float arr[3];
        };
    };
} Vector3;

typedef struct
{
    union
    {
        struct
        {
            float x, y, z, w;
        };

        struct
        {
            float arr[4];
        };
    };
} Vector4;

typedef struct
{
    union
    {
        struct
        {
            float i, j, k, u;
        };

        struct
        {
            float arr[4];
        };
    };
} Quaternion;

typedef struct
{
    float data[4][4];
} Matrix4x4;
