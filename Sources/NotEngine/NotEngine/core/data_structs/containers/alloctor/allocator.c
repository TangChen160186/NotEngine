#include <stdlib.h>
#include "allocator.h"

// 默认的内存分配函数
static void* default_allocate(size_t size) {
    return malloc(size);
}

// 默认的内存释放函数
static void default_deallocate(void* ptr) {
    free(ptr);
}

// 默认分配器实例
static Allocator default_allocator = {
    .allocate = default_allocate,
    .deallocate = default_deallocate
};

// 当前使用的分配器，初始为默认分配器
static Allocator* current_allocator = &default_allocator;

Allocator* get_default_allocator(void) {
    return current_allocator;
}

void set_default_allocator(Allocator* allocator) {
    current_allocator = allocator ? allocator : &default_allocator;
}