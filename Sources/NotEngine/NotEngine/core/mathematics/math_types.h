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
} vector2;


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
} vector3;

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
} vector4;

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
} quaternion;

typedef struct
{
    float data[4][4];
} matrix_4_4;
