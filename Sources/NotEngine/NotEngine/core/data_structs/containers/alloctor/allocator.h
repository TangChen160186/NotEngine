#pragma once
#include "typedefs.h"

typedef struct {
    // 分配内存的函数指针
    void* (*allocate)(size_t size);
    // 释放内存的函数指针
    void (*deallocate)(void* ptr);
} Allocator;

// 获取默认分配器
API Allocator* get_default_allocator(void);

// 设置默认分配器
API void set_default_allocator(Allocator* allocator);