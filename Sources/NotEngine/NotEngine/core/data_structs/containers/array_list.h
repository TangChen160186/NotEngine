#pragma once
#include "typedefs.h"
#include "core/data_structs/iterator/iterator.h"
#include "core/data_structs/alloctor/allocator.h"

typedef struct ArrayList* ArrayList;

// 创建新的ArrayList，可选指定分配器（NULL表示使用默认分配器）
API ArrayList arraylist_create(size_t element_size, Allocator* allocator);

// 销毁ArrayList
API void arraylist_destroy(ArrayList list);

// 在末尾添加元素
API void arraylist_push_back(ArrayList list, const void* element);

// 删除末尾元素
API void arraylist_pop_back(ArrayList list,void* dest);

// 获取指定位置的元素
API void arraylist_get(const ArrayList list, int index,void* dest);

// 设置指定位置的元素
API void arraylist_set(ArrayList list, int index, const void* element);

// 在指定位置插入元素
API void arraylist_insert(ArrayList list, int index, const void* element);

// 删除指定位置的元素
API void arraylist_erase(ArrayList list, int index);

// 获取当前大小
API size_t arraylist_size(const ArrayList list);

// 获取当前容量
API size_t arraylist_capacity(const ArrayList list);

// 检查是否为空
API bool arraylist_empty(const ArrayList list);

// 清空列表
API void arraylist_clear(ArrayList list);

// 获取开始迭代器
API Iterator arraylist_begin(ArrayList list);

// 获取结束迭代器
API Iterator arraylist_end(ArrayList list);

API Iterator arraylist_rbegin(ArrayList list);  // 添加反向迭代器

API Iterator arraylist_rend(ArrayList list);    // 添加反向迭代器
