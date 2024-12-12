#include "algorithm.h"
#include <string.h>
#include <stdlib.h>

// 辅助函数：交换两个元素
static void swap_elements(Iterator it1, Iterator it2) {
    void* temp = malloc(it1.elem_size);
    iterator_get(it1, temp);
    void* temp2 = malloc(it1.elem_size);
    iterator_get(it2, temp2);
    iterator_set(it1, temp2);
    iterator_set(it2, temp);
    free(temp);
    free(temp2);
}

// 非修改性序列操作
void for_each(Iterator begin, Iterator end, UnaryFunction func) {
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        func(temp);
        begin = iterator_next(begin);
    }
    free(temp);
}

Iterator find_mem(Iterator begin, Iterator end, const void* value) {
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        if (memcmp(temp, value, begin.elem_size) == 0) {
            free(temp);
            return begin;
        }
        begin = iterator_next(begin);
    }
    free(temp);
    return end;
}

Iterator find_if(Iterator begin, Iterator end, UnaryPredicate pred) {
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        if (pred(temp)) {
            free(temp);
            return begin;
        }
        begin = iterator_next(begin);
    }
    free(temp);
    return end;
}

size_t count_if(Iterator begin, Iterator end, UnaryPredicate pred) {
    size_t count = 0;
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        if (pred(temp)) {
            count++;
        }
        begin = iterator_next(begin);
    }
    free(temp);
    return count;
}

bool equal(Iterator first1, Iterator last1, Iterator first2, Compare comp) {
    void* temp1 = malloc(first1.elem_size);
    void* temp2 = malloc(first1.elem_size);

    while (!iterator_equals(first1, last1)) {
        iterator_get(first1, temp1);
        iterator_get(first2, temp2);
        if (comp(temp1, temp2) != 0) {
            free(temp1);
            free(temp2);
            return false;
        }
        first1 = iterator_next(first1);
        first2 = iterator_next(first2);
    }

    free(temp1);
    free(temp2);
    return true;
}

// 修改性序列操作
void copy(Iterator src_begin, Iterator src_end, Iterator dest_begin) {
    void* temp = malloc(src_begin.elem_size);
    while (!iterator_equals(src_begin, src_end)) {
        iterator_get(src_begin, temp);
        iterator_set(dest_begin, temp);
        src_begin = iterator_next(src_begin);
        dest_begin = iterator_next(dest_begin);
    }
    free(temp);
}

void fill(Iterator begin, Iterator end, const void* value) {
    while (!iterator_equals(begin, end)) {
        iterator_set(begin, value);
        begin = iterator_next(begin);
    }
}


void sort(Iterator begin, Iterator end, Compare comp) {
    ptrdiff_t len = iterator_distance(begin, end);
    if (len <= 1) return;

    // 分配连续内存并复制数据
    void* buffer = malloc(len * begin.elem_size);
    if (!buffer) return;

    // 复制到连续内存
    Iterator it = begin;
    char* ptr = buffer;
    while (!iterator_equals(it, end)) {
        iterator_get(it, ptr);
        ptr += begin.elem_size;
        it = iterator_next(it);
    }

    // 使用 qsort 排序
    qsort(buffer, len, begin.elem_size,comp);

    // 复制回原容器
    it = begin;
    ptr = buffer;
    while (!iterator_equals(it, end)) {
        iterator_set(it, ptr);
        ptr += begin.elem_size;
        it = iterator_next(it);
    }

    free(buffer);
}

Iterator lower_bound(Iterator begin, Iterator end, const void* value, Compare comp) {
    ptrdiff_t count = iterator_distance(begin, end);
    void* temp = malloc(begin.elem_size);
    while (count > 0) {
        ptrdiff_t step = count / 2;
        Iterator mid = iterator_advance(begin, step);

        iterator_get(mid, temp);
        if (comp(temp, value) < 0) {
            begin = iterator_next(mid);
            count -= step + 1;
        }
        else {
            count = step;
        }
    }

    free(temp);
    return begin;
}

Iterator upper_bound(Iterator begin, Iterator end, const void* value, Compare comp) {
    ptrdiff_t count = iterator_distance(begin, end);
    void* temp = malloc(begin.elem_size);

    while (count > 0) {
        ptrdiff_t step = count / 2;
        Iterator mid = iterator_advance(begin, step);

        iterator_get(mid, temp);
        if (comp(value, temp) >= 0) {
            begin = iterator_next(mid);
            count -= step + 1;
        }
        else {
            count = step;
        }
    }

    free(temp);
    return begin;
}

void replace(Iterator begin, Iterator end, const void* old_value, const void* new_value) {
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        if (memcmp(temp, old_value, begin.elem_size) == 0) {
            iterator_set(begin, new_value);
        }
        begin = iterator_next(begin);
    }
    free(temp);
}

void replace_if(Iterator begin, Iterator end, UnaryPredicate pred, const void* new_value) {
    void* temp = malloc(begin.elem_size);
    while (!iterator_equals(begin, end)) {
        iterator_get(begin, temp);
        if (pred(temp)) {
            iterator_set(begin, new_value);
        }
        begin = iterator_next(begin);
    }
    free(temp);
}

void copy_n(Iterator src_begin, size_t n, Iterator dest_begin) {
    void* temp = malloc(src_begin.elem_size);
    for (size_t i = 0; i < n; i++) {
        iterator_get(src_begin, temp);
        iterator_set(dest_begin, temp);
        src_begin = iterator_next(src_begin);
        dest_begin = iterator_next(dest_begin);
    }
    free(temp);
}

void copy_if(Iterator src_begin, Iterator src_end, Iterator dest_begin, UnaryPredicate pred) {
    void* temp = malloc(src_begin.elem_size);
    while (!iterator_equals(src_begin, src_end)) {
        iterator_get(src_begin, temp);
        if (pred(temp)) {
            iterator_set(dest_begin, temp);
            dest_begin = iterator_next(dest_begin);
        }
        src_begin = iterator_next(src_begin);
    }
    free(temp);
}

void fill_n(Iterator begin, size_t n, const void* value) {
    for (size_t i = 0; i < n; i++) {
        iterator_set(begin, value);
        begin = iterator_next(begin);
    }
}

void transform(Iterator src_begin, Iterator src_end, Iterator dest_begin, UnaryFunction op) {
    void* temp = malloc(src_begin.elem_size);
    while (!iterator_equals(src_begin, src_end)) {
        iterator_get(src_begin, temp);
        op(temp);  // 修改temp的值
        iterator_set(dest_begin, temp);
        src_begin = iterator_next(src_begin);
        dest_begin = iterator_next(dest_begin);
    }
    free(temp);
}

void transform_binary(Iterator src1_begin, Iterator src1_end, Iterator src2_begin,
    Iterator dest_begin, BinaryFunction binary_op) {
    void* temp1 = malloc(src1_begin.elem_size);
    void* temp2 = malloc(src1_begin.elem_size);
    void* result = malloc(dest_begin.elem_size);

    while (!iterator_equals(src1_begin, src1_end)) {
        iterator_get(src1_begin, temp1);
        iterator_get(src2_begin, temp2);
        binary_op(temp1, temp2, result);
        iterator_set(dest_begin, result);

        src1_begin = iterator_next(src1_begin);
        src2_begin = iterator_next(src2_begin);
        dest_begin = iterator_next(dest_begin);
    }

    free(temp1);
    free(temp2);
    free(result);
}

Iterator min_element(Iterator begin, Iterator end, Compare comp) {
    if (iterator_equals(begin, end)) return end;

    Iterator min_it = begin;
    Iterator current = iterator_next(begin);

    void* min_val = malloc(begin.elem_size);
    void* curr_val = malloc(begin.elem_size);

    iterator_get(min_it, min_val);

    while (!iterator_equals(current, end)) {
        iterator_get(current, curr_val);
        if (comp(curr_val, min_val) < 0) {
            min_it = current;
            memcpy(min_val, curr_val, begin.elem_size);
        }
        current = iterator_next(current);
    }

    free(min_val);
    free(curr_val);
    return min_it;
}

Iterator max_element(Iterator begin, Iterator end, Compare comp) {
    if (iterator_equals(begin, end)) return end;

    Iterator max_it = begin;
    Iterator current = iterator_next(begin);

    void* max_val = malloc(begin.elem_size);
    void* curr_val = malloc(begin.elem_size);

    iterator_get(max_it, max_val);

    while (!iterator_equals(current, end)) {
        iterator_get(current, curr_val);
        if (comp(max_val, curr_val) < 0) {
            max_it = current;
            memcpy(max_val, curr_val, begin.elem_size);
        }
        current = iterator_next(current);
    }

    free(max_val);
    free(curr_val);
    return max_it;
}

void minmax_element(Iterator begin, Iterator end, Compare comp,
    Iterator* min_result, Iterator* max_result) {
    if (iterator_equals(begin, end)) {
        *min_result = begin;
        *max_result = begin;
        return;
    }

    *min_result = begin;
    *max_result = begin;
    Iterator current = iterator_next(begin);

    void* min_val = malloc(begin.elem_size);
    void* max_val = malloc(begin.elem_size);
    void* curr_val = malloc(begin.elem_size);

    iterator_get(*min_result, min_val);
    iterator_get(*max_result, max_val);

    while (!iterator_equals(current, end)) {
        iterator_get(current, curr_val);
        if (comp(curr_val, min_val) < 0) {
            *min_result = current;
            memcpy(min_val, curr_val, begin.elem_size);
        }
        if (comp(max_val, curr_val) < 0) {
            *max_result = current;
            memcpy(max_val, curr_val, begin.elem_size);
        }
        current = iterator_next(current);
    }

    free(min_val);
    free(max_val);
    free(curr_val);
}

// 堆操作辅助函数
static void sift_down(Iterator begin, size_t start, size_t end, Compare comp) {
    size_t root = start;
    void* root_val = malloc(begin.elem_size);
    void* child_val = malloc(begin.elem_size);

    while (root * 2 + 1 < end) {
        size_t child = root * 2 + 1;
        Iterator root_it = iterator_advance(begin, root);
        Iterator child_it = iterator_advance(begin, child);
        Iterator child_plus_it = iterator_advance(begin, child + 1);

        iterator_get(root_it, root_val);
        iterator_get(child_it, child_val);

        if (child + 1 < end) {
            void* child_plus_val = malloc(begin.elem_size);
            iterator_get(child_plus_it, child_plus_val);
            if (comp(child_val, child_plus_val) < 0) {
                child++;
                child_it = child_plus_it;
                memcpy(child_val, child_plus_val, begin.elem_size);
            }
            free(child_plus_val);
        }

        if (comp(root_val, child_val) < 0) {
            swap_elements(root_it, child_it);
            root = child;
        }
        else {
            break;
        }
    }

    free(root_val);
    free(child_val);
}

void make_heap(Iterator begin, Iterator end, Compare comp) {
    size_t len = iterator_distance(begin, end);
    for (size_t start = len / 2; start > 0; start--) {
        sift_down(begin, start - 1, len, comp);
    }
}

void push_heap(Iterator begin, Iterator end, Compare comp) {
    ptrdiff_t count = iterator_distance(begin, end) - 1;
    if (count <= 0) return;

    void* temp = malloc(begin.elem_size);
    void* parent_val = malloc(begin.elem_size);

    while (count > 0) {
        ptrdiff_t parent = (count - 1) / 2;
        Iterator current = iterator_advance(begin, count);
        Iterator parent_it = iterator_advance(begin, parent);

        iterator_get(current, temp);
        iterator_get(parent_it, parent_val);

        if (comp(parent_val, temp) < 0) {
            swap_elements(current, parent_it);
            count = parent;
        }
        else {
            break;
        }
    }

    free(temp);
    free(parent_val);
}

void pop_heap(Iterator begin, Iterator end, Compare comp) {
    if (iterator_equals(begin, end)) return;
    end = iterator_prev(end);
    swap_elements(begin, end);
    sift_down(begin, 0, iterator_distance(begin, end), comp);
}

bool is_heap(Iterator begin, Iterator end, Compare comp) {
    size_t len = iterator_distance(begin, end);
    void* parent_val = malloc(begin.elem_size);
    void* child_val = malloc(begin.elem_size);

    for (size_t i = 1; i < len; i++) {
        Iterator parent = iterator_advance(begin, (i - 1) / 2);
        Iterator child = iterator_advance(begin, i);

        iterator_get(parent, parent_val);
        iterator_get(child, child_val);

        if (comp(parent_val, child_val) < 0) {
            free(parent_val);
            free(child_val);
            return false;
        }
    }

    free(parent_val);
    free(child_val);
    return true;
}

// 集合操作
bool includes(Iterator first1, Iterator last1, Iterator first2, Iterator last2, Compare comp) {
    void* val1 = malloc(first1.elem_size);
    void* val2 = malloc(first2.elem_size);

    while (!iterator_equals(first2, last2)) {
        if (iterator_equals(first1, last1)) {
            free(val1);
            free(val2);
            return false;
        }

        iterator_get(first1, val1);
        iterator_get(first2, val2);

        if (comp(val2, val1) < 0) {
            free(val1);
            free(val2);
            return false;
        }

        if (comp(val1, val2) == 0) {
            first2 = iterator_next(first2);
        }
        first1 = iterator_next(first1);
    }

    free(val1);
    free(val2);
    return true;
}

void set_union(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp) {
    void* val1 = malloc(first1.elem_size);
    void* val2 = malloc(first2.elem_size);

    while (!iterator_equals(first1, last1) && !iterator_equals(first2, last2)) {
        iterator_get(first1, val1);
        iterator_get(first2, val2);

        if (comp(val1, val2) < 0) {
            iterator_set(result, val1);
            first1 = iterator_next(first1);
        }
        else if (comp(val2, val1) < 0) {
            iterator_set(result, val2);
            first2 = iterator_next(first2);
        }
        else {
            iterator_set(result, val1);
            first1 = iterator_next(first1);
            first2 = iterator_next(first2);
        }
        result = iterator_next(result);
    }

    // 复制剩余元素
    while (!iterator_equals(first1, last1)) {
        iterator_get(first1, val1);
        iterator_set(result, val1);
        first1 = iterator_next(first1);
        result = iterator_next(result);
    }

    while (!iterator_equals(first2, last2)) {
        iterator_get(first2, val2);
        iterator_set(result, val2);
        first2 = iterator_next(first2);
        result = iterator_next(result);
    }

    free(val1);
    free(val2);
}

void set_intersection(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp) {
    void* val1 = malloc(first1.elem_size);
    void* val2 = malloc(first2.elem_size);

    while (!iterator_equals(first1, last1) && !iterator_equals(first2, last2)) {
        iterator_get(first1, val1);
        iterator_get(first2, val2);

        if (comp(val1, val2) < 0) {
            first1 = iterator_next(first1);
        }
        else if (comp(val2, val1) < 0) {
            first2 = iterator_next(first2);
        }
        else {
            iterator_set(result, val1);
            result = iterator_next(result);
            first1 = iterator_next(first1);
            first2 = iterator_next(first2);
        }
    }

    free(val1);
    free(val2);
}

void set_difference(Iterator first1, Iterator last1, Iterator first2, Iterator last2,
    Iterator result, Compare comp) {
    void* val1 = malloc(first1.elem_size);
    void* val2 = malloc(first2.elem_size);

    while (!iterator_equals(first1, last1) && !iterator_equals(first2, last2)) {
        iterator_get(first1, val1);
        iterator_get(first2, val2);

        if (comp(val1, val2) < 0) {
            iterator_set(result, val1);
            result = iterator_next(result);
            first1 = iterator_next(first1);
        }
        else if (comp(val2, val1) < 0) {
            first2 = iterator_next(first2);
        }
        else {
            first1 = iterator_next(first1);
            first2 = iterator_next(first2);
        }
    }

    while (!iterator_equals(first1, last1)) {
        iterator_get(first1, val1);
        iterator_set(result, val1);
        first1 = iterator_next(first1);
        result = iterator_next(result);
    }

    free(val1);
    free(val2);
}


