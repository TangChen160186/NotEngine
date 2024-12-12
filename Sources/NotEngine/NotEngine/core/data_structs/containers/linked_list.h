#pragma once
#include <stddef.h>

#include "core/data_structs/alloctor/allocator.h"
#include "core/data_structs/iterator/iterator.h"

typedef struct LinkedList* LinkedList;

// 创建和销毁
API LinkedList linkedlist_create(size_t element_size, Allocator* allocator);
API void linkedlist_destroy(LinkedList list);

// 容量相关
API bool linkedlist_empty(const LinkedList list);
API size_t linkedlist_size(const LinkedList list);
API void linkedlist_clear(LinkedList list);

// 元素访问
API void linkedlist_front(const LinkedList list, void* out);
API void linkedlist_back(const LinkedList list, void* out);

// 修改器
API void linkedlist_push_front(LinkedList list, const void* element);
API void linkedlist_push_back(LinkedList list, const void* element);
API void linkedlist_pop_front(LinkedList list,void* dest);
API void linkedlist_pop_back(LinkedList list, void* dest);

// 插入和删除
API Iterator linkedlist_insert(LinkedList list, Iterator pos, const void* element);
API Iterator linkedlist_erase(LinkedList list, Iterator pos);
API void linkedlist_remove(LinkedList list, const void* value);
API void linkedlist_remove_if(LinkedList list, bool (*pred)(const void*));

// 操作
API void linkedlist_splice(LinkedList list, Iterator pos, LinkedList other);
API void linkedlist_merge(LinkedList list, LinkedList other, int (*comp)(const void*, const void*));
API void linkedlist_sort(LinkedList list, int (*comp)(const void*, const void*));
API void linkedlist_unique(LinkedList list, int (*comp)(const void*, const void*));
API void linkedlist_reverse(LinkedList list);

// 迭代器
API Iterator linkedlist_begin(LinkedList list);
API Iterator linkedlist_end(LinkedList list);
API Iterator linkedlist_rbegin(LinkedList list);
API Iterator linkedlist_rend(LinkedList list);