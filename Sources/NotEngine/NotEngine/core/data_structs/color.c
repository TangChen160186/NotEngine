#include "color.h"

// 常用颜色定义
static const Color COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
static const Color COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
static const Color COLOR_RED = { 1.0f, 0.0f, 0.0f, 1.0f };
static const Color COLOR_GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
static const Color COLOR_BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
static const Color COLOR_YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };
static const Color COLOR_MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };
static const Color COLOR_CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };
static const Color COLOR_TRANSPARENT = { 0.0f, 0.0f, 0.0f, 0.0f };

Color color_create(float r, float g, float b, float a) {
    return (Color) { r, g, b, a };
}

Color color_from_rgb(float r, float g, float b) {
    return (Color) { r, g, b, 1.0f };
}
