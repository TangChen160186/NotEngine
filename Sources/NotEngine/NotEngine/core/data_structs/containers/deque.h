#pragma once
#include <stddef.h>
#include "alloctor/allocator.h"
#include "iterator/iterator.h"

typedef struct Deque* Deque;

// 创建deque，element_size为每个元素的字节大小，allocator为可选的分配器
API Deque deque_create(size_t element_size, Allocator* allocator);

// 销毁deque
API void deque_destroy(Deque deque);

// 在头部添加元素
API void deque_push_front(Deque deque, const void* element);

// 在尾部添加元素
API void deque_push_back(Deque deque, const void* element);

// 删除头部元素
API void deque_pop_front(Deque deque);

// 删除尾部元素
API void deque_pop_back(Deque deque);

// 获取头部元素
API void deque_front(const Deque deque,void* dest);

// 获取尾部元素
API void deque_back(const Deque deque,void* dest);

// 设置指定位置的元素
API void deque_set(Deque deque, int index, const void* element);

// 获取当前大小
API size_t deque_size(const Deque deque);

// 检查是否为空
API bool deque_empty(const Deque deque);

// 清空deque
API void deque_clear(Deque deque);
// 迭代器
API Iterator deque_begin(Deque deque);
API Iterator deque_end(Deque deque);
API Iterator deque_rbegin(Deque deque);
API Iterator deque_rend(Deque deque);
