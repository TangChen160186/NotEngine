#include <string.h>
#include "array_list.h"
#define INITIAL_CAPACITY 4
#define GROW_FACTOR 2

struct ArrayList
{
    void* data; // 数据数组
    size_t element_size; // 每个元素的字节大小
    size_t size; // 当前元素个数
    size_t capacity; // 当前容量
    Allocator* allocator; // 内存分配器
};

static void expand_capacity(ArrayList list)
{
    int new_capacity = list->capacity * GROW_FACTOR;
    void* new_data = list->allocator->allocate(new_capacity * list->element_size);
    // 复制旧数据到新内存
    memcpy(new_data, list->data, list->size * list->element_size);

    // 释放旧内存
    list->allocator->deallocate(list->data);

    list->data = new_data;
    list->capacity = new_capacity;
}

ArrayList arraylist_create(size_t element_size, Allocator* allocator)
{
    if (allocator == NULL)
    {
        allocator = get_default_allocator();
    }

    ArrayList list = allocator->allocate(sizeof(ArrayList));
    list->data = allocator->allocate(INITIAL_CAPACITY * element_size);

    list->element_size = element_size;
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->allocator = allocator;
    return list;
}

void arraylist_destroy(ArrayList list)
{
    list->allocator->deallocate(list->data);
    list->allocator->deallocate(list);
    list->data = NULL;
}

void arraylist_push_back(ArrayList list, const void* element)
{
    if (list->size == list->capacity)
    {
        expand_capacity(list);
    }

    // 计算新元素的存储位置并复制数据
    void* dest = (char*)list->data + list->size * list->element_size;
    memcpy(dest, element, list->element_size);
    list->size++;
}

void arraylist_pop_back(ArrayList list, void* dest)
{
    if (dest)
    {
        arraylist_get(list, list->size, dest);
    }
    if (list->size > 0)
    {
        list->size--;
    }
}

void arraylist_get(const ArrayList list, int index, void* dest)
{
    memcpy(dest, (char*)list->data + index * list->element_size, list->element_size);
}

void arraylist_set(ArrayList list, int index, const void* element)
{
    void* dest = (char*)list->data + index * list->element_size;
    memcpy(dest, element, list->element_size);
}

void arraylist_insert(ArrayList list, int index, const void* element)
{
    if (list->size == list->capacity)
    {
        expand_capacity(list);
    }

    // 将index及之后的元素后移一位
    void* src = (char*)list->data + index * list->element_size;
    void* dest = (char*)src + list->element_size;
    size_t bytes_to_move = (list->size - index) * list->element_size;
    memmove(dest, src, bytes_to_move);

    // 插入新元素
    memcpy(src, element, list->element_size);
    list->size++;
}

void arraylist_erase(ArrayList list, int index)
{
    // 将index之后的元素前移一位
    void* dest = (char*)list->data + index * list->element_size;
    void* src = (char*)dest + list->element_size;
    size_t bytes_to_move = (list->size - index - 1) * list->element_size;
    memmove(dest, src, bytes_to_move);

    list->size--;
}

size_t arraylist_size(const ArrayList list)
{
    return list->size;
}

size_t arraylist_capacity(const ArrayList list)
{
    return list->capacity;
}

bool arraylist_empty(const ArrayList list)
{
    return list->size == 0;
}

void arraylist_clear(ArrayList list)
{
    list->size = 0;
}

//迭代器操作
static Iterator array_iterator_next(Iterator it)
{
    it.ptr = (char*)it.ptr + it.elem_size;
    return it;
}

static Iterator array_iterator_prev(Iterator it)
{
    it.ptr = (char*)it.ptr - it.elem_size;
    return it;
}

static void array_iterator_get(Iterator it, void* dest)
{
    memcpy(dest, it.ptr, it.elem_size);
}

static void array_iterator_set(Iterator it, const void* value)
{
    memcpy(it.ptr, value, it.elem_size);
}

Iterator arraylist_begin(ArrayList list)
{
    Iterator it = {
        .ptr = list->data,
        .container = list,
        .elem_size = list->element_size,
        .next = array_iterator_next,
        .prev = array_iterator_prev,
        .get = array_iterator_get,
        .set = array_iterator_set
    };
    return it;
}

Iterator arraylist_end(ArrayList list)
{
    Iterator it = {
        .ptr = (char*)list->data + list->size * list->element_size,
        .container = list,
        .elem_size = list->element_size
    };
    return it;
}

// 反向迭代器操作
static Iterator array_reverse_iterator_next(Iterator it)
{
    it.ptr = (char*)it.ptr - it.elem_size; // 反向时next是向前移动
    return it;
}

static Iterator array_reverse_iterator_prev(Iterator it)
{
    it.ptr = (char*)it.ptr + it.elem_size; // 反向时prev是向后移动
    return it;
}

Iterator arraylist_rbegin(ArrayList list)
{
    Iterator it = {
        .ptr = (char*)list->data + (list->size - 1) * list->element_size,
        .container = list,
        .elem_size = list->element_size,
        .next = array_reverse_iterator_next,
        .prev = array_reverse_iterator_prev,
        .get = array_iterator_get,
        .set = array_iterator_set
    };
    return it;
}

Iterator arraylist_rend(ArrayList list)
{
    Iterator it = {
        .ptr = (char*)list->data - list->element_size,
        .container = list,
        .elem_size = list->element_size,
        .next = array_reverse_iterator_next,
        .prev = array_reverse_iterator_prev,
        .get = array_iterator_get,
        .set = array_iterator_set
    };
    return it;
}
