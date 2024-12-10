#pragma once

typedef struct {
    void* items;       // 使用void指针存储数据缓冲区
    int size;          // 当前元素个数
    int capacity;      // 当前容量
    int element_size;  // 每个元素的字节大小
    Allocator* allocator;  // 添加allocator成员
} ArrayList;

// 创建和销毁
ArrayList* array_list_create(int initial_capacity, int element_size, Allocator* allocator);
void array_list_destroy(ArrayList* list);

// 基本操作
int array_list_add(ArrayList* list, const void* item);
void* array_list_get(ArrayList* list, int index);
int array_list_remove(ArrayList* list, int index);
void array_list_clear(ArrayList* list);
int array_list_size(ArrayList* list);

// 容量相关
void array_list_ensure_capacity(ArrayList* list, int min_capacity);
void array_list_trim_to_size(ArrayList* list);
