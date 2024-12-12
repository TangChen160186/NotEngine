#pragma once
#include <stddef.h>
#include "deque.h"
typedef struct Queue* Queue;

// 创建和销毁
API Queue queue_create(size_t element_size, Allocator* allocator);
API void queue_destroy(Queue queue);

// 容量相关
API bool queue_empty(const Queue queue);
API size_t queue_size(const Queue queue);

// 元素访问
API void queue_front(const Queue queue, void* out);
API void queue_back(const Queue queue, void* out);

// 修改器
API void queue_push(Queue queue, const void* element);
API void queue_pop(Queue queue);

// 迭代器
API Iterator queue_begin(Queue queue);
API Iterator queue_end(Queue queue);
API Iterator queue_rbegin(Queue queue);
API Iterator queue_rend(Queue queue);