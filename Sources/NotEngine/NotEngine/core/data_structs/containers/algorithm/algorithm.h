#pragma once
#include "core/data_structs/iterator/iterator.h"
#include <stdbool.h>
// 函数类型定义
typedef void (*UnaryFunction)(void* elem);
typedef bool (*UnaryPredicate)(const void* elem);
typedef int (*Compare)(const void* a, const void* b);
typedef void (*BinaryFunction)(const void* a, const void* b, void* result);

// 非修改性序列操作
API void for_each(Iterator begin, Iterator end, UnaryFunction func);
API Iterator find_mem(Iterator begin, Iterator end, const void* value);
API Iterator find_if(Iterator begin, Iterator end, UnaryPredicate pred);
API size_t count_if(Iterator begin, Iterator end, UnaryPredicate pred);
API bool equal(Iterator first1, Iterator last1, Iterator first2, Compare comp);
API bool all_of(Iterator begin, Iterator end, UnaryPredicate pred);
API bool any_of(Iterator begin, Iterator end, UnaryPredicate pred);
API bool none_of(Iterator begin, Iterator end, UnaryPredicate pred);

// 修改性序列操作
API void copy(Iterator src_begin, Iterator src_end, Iterator dest_begin);
API void copy_n(Iterator src_begin, size_t n, Iterator dest_begin);
API void copy_if(Iterator src_begin, Iterator src_end, Iterator dest_begin, UnaryPredicate pred);
API void fill(Iterator begin, Iterator end, const void* value);
API void fill_n(Iterator begin, size_t n, const void* value);
API void replace(Iterator begin, Iterator end, const void* old_value, const void* new_value);
API void replace_if(Iterator begin, Iterator end, UnaryPredicate pred, const void* new_value);
API void swap_ranges(Iterator first1, Iterator last1, Iterator first2);
API void reverse(Iterator begin, Iterator end);
API Iterator rotate(Iterator begin, Iterator middle, Iterator end);
API void transform(Iterator src_begin, Iterator src_end, Iterator dest_begin, UnaryFunction op);
API void transform_binary(Iterator src1_begin, Iterator src1_end, Iterator src2_begin,
    Iterator dest_begin, BinaryFunction binary_op);

// 排序和相关操作
API void sort(Iterator begin, Iterator end, Compare comp);
API void partial_sort(Iterator begin, Iterator middle, Iterator end, Compare comp);
API bool is_sorted(Iterator begin, Iterator end, Compare comp);
API void merge(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp);
API Iterator lower_bound(Iterator begin, Iterator end, const void* value, Compare comp);
API Iterator upper_bound(Iterator begin, Iterator end, const void* value, Compare comp);
API bool binary_search(Iterator begin, Iterator end, const void* value, Compare comp);
API Iterator partition(Iterator begin, Iterator end, UnaryPredicate pred);
API bool is_partitioned(Iterator begin, Iterator end, UnaryPredicate pred);

// 最值操作
API Iterator min_element(Iterator begin, Iterator end, Compare comp);
API Iterator max_element(Iterator begin, Iterator end, Compare comp);
API void minmax_element(Iterator begin, Iterator end, Compare comp,
    Iterator* min_result, Iterator* max_result);

// 堆操作
API void make_heap(Iterator begin, Iterator end, Compare comp);
API void push_heap(Iterator begin, Iterator end, Compare comp);
API void pop_heap(Iterator begin, Iterator end, Compare comp);
API bool is_heap(Iterator begin, Iterator end, Compare comp);

// 集合操作
API bool includes(Iterator first1, Iterator last1, Iterator first2, Iterator last2, Compare comp);
API void set_union(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp);
API void set_intersection(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp);
API void set_difference(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp);

