#pragma once
#include "deque.h"

typedef struct Stack* Stack;

// 创建和销毁
API Stack stack_create(size_t element_size, Allocator* allocator);
API void stack_destroy(Stack stack);

// 容量相关
API bool stack_empty(const Stack stack);
API size_t stack_size(const Stack stack);

// 元素访问
API void stack_top(const Stack stack, void* out);

// 修改器
API void stack_push(Stack stack, const void* element);
API void stack_pop(Stack stack);

// 迭代器
API Iterator stack_begin(Stack stack);
API Iterator stack_end(Stack stack);
API Iterator stack_rbegin(Stack stack);
API Iterator stack_rend(Stack stack);
