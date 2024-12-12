#pragma once
#include "typedefs.h"
#include <stdbool.h>
#include <stddef.h> 
// 迭代器结构
typedef struct Iterator {
    void* ptr;           // 当前位置指针
    void* container;     // 指向容器的指针
    size_t elem_size;    // 元素大小

    // 迭代器操作函数指针
    struct Iterator(*next)(struct Iterator);  // ++it
    struct Iterator(*prev)(struct Iterator);  // --it
    void (*get)(struct Iterator,void*);           // *it
    void (*set)(struct Iterator, const void*); // *it = value
} Iterator;

// 迭代器基本操作
API Iterator iterator_next(Iterator it);
API Iterator iterator_prev(Iterator it);
API Iterator iterator_advance(Iterator it, int n);
API void iterator_get(Iterator it,void* dest);
API void iterator_set(Iterator it, const void* value);
API bool iterator_equals(Iterator it1, Iterator it2);
API ptrdiff_t iterator_distance(Iterator first, Iterator last);