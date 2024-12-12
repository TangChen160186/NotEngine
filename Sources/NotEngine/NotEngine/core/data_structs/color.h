#pragma once
#pragma once

#include "typedefs.h"

// 基本颜色结构体
typedef struct {
    float r;    // 红色分量 (0.0-1.0)
    float g;    // 绿色分量 (0.0-1.0)
    float b;    // 蓝色分量 (0.0-1.0)
    float a;    // 透明度 (0.0-1.0)
} Color;

// 常用颜色常量
static const Color COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
static const Color COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
static const Color COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f };
static const Color COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
static const Color COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
static const Color COLOR_YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
static const Color COLOR_MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
static const Color COLOR_CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
static const Color COLOR_TRANSPARENT = { 0.0f, 0.0f, 0.0f, 0.0f };

// 创建颜色
API Color color_create(float r, float g, float b, float a);
API Color color_from_rgb(float r, float g, float b);


