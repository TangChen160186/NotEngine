#include <stdio.h>
#include <string.h>
#include "linked_list.h"

#include <crtdbg.h>
#include <stdlib.h>

// 链表节点结构
typedef struct Node {
    struct Node* prev;    // 前一个节点
    struct Node* next;    // 后一个节点
    void* data;          // 数据指针
} Node;

struct LinkedList {
    Node* head;          // 头节点
    Node* tail;          // 尾节点
    size_t element_size; // 元素大小
    size_t size;           // 当前元素个数
    Allocator* allocator;// 内存分配器
};

// 创建新节点
static Node* create_node(LinkedList list, const void* element) {
    Node* node = list->allocator->allocate(sizeof(Node));
    node->data = list->allocator->allocate(list->element_size);
    if (element) {
        memcpy(node->data, element, list->element_size);
    }
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// 销毁节点
static void destroy_node(LinkedList list, Node* node) {
    list->allocator->deallocate(node->data);
    list->allocator->deallocate(node);
}

LinkedList linkedlist_create(size_t element_size, Allocator* allocator) {
    if (allocator == NULL) {
        allocator = get_default_allocator();
    }

    LinkedList list = allocator->allocate(sizeof(LinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->element_size = element_size;
    list->size = 0;
    list->allocator = allocator;
    return list;
}

void linkedlist_destroy(LinkedList list) {
    linkedlist_clear(list);
    list->allocator->deallocate(list);
}

void linkedlist_push_front(LinkedList list, const void* element) {
    Node* node = create_node(list, element);

    if (list->head == NULL) {
        list->head = list->tail = node;
    }
    else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}

void linkedlist_push_back(LinkedList list, const void* element) {
    Node* node = create_node(list, element);

    if (list->tail == NULL) {
        list->head = list->tail = node;
    }
    else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void linkedlist_pop_front(LinkedList list,void* dest) {
    if (list->head == NULL) return;
    if (dest)
    {
        memcpy(dest, list->head->data, list->element_size);
    }

    Node* old_head = list->head;
    list->head = old_head->next;

    if (list->head == NULL) {
        list->tail = NULL;
    }
    else {
        list->head->prev = NULL;
    }

    destroy_node(list, old_head);
    list->size--;
}

void linkedlist_pop_back(LinkedList list,void* dest) {
    if (list->tail == NULL) return;
    if (dest)
    {
        memcpy(dest, list->tail->data, list->element_size);
    }
    Node* old_tail = list->tail;
    list->tail = old_tail->prev;

    if (list->tail == NULL) {
        list->head = NULL;
    }
    else {
        list->tail->next = NULL;
    }

    destroy_node(list, old_tail);
    list->size--;
}


void linkedlist_front(const LinkedList list, void* out) {
    memcpy(out, list->head->data, list->element_size);
}

void linkedlist_back(const LinkedList list, void* out) {
    memcpy(out, list->tail->data, list->element_size);
}

size_t linkedlist_size(const LinkedList list) {
    return (size_t)list->size;
}

bool linkedlist_empty(const LinkedList list) {
    return list->size == 0;
}

void linkedlist_clear(LinkedList list) {
    while (!linkedlist_empty(list)) {
        linkedlist_pop_front(list,NULL);
    }
}

// LinkedList的迭代器操作
static Iterator list_iterator_next(Iterator it) {
    Node* node = it.ptr;
    if (node) {
        it.ptr = node->next;
    }
    return it;
}

static Iterator list_iterator_prev(Iterator it) {
    Node* node = it.ptr;
    if (node) {
        it.ptr = node->prev;
    }
    return it;
}

static void list_iterator_get(Iterator it, void* dest) {
    Node* node = it.ptr;
    if (node && node->data) {
        memcpy(dest, node->data, it.elem_size);
    }
}

static void list_iterator_set(Iterator it, const void* value) {
    Node* node = it.ptr;
    if (node && node->data) {
        memcpy(node->data, value, it.elem_size);
    }
}

Iterator linkedlist_begin(LinkedList list) {
    return (Iterator) {
        .ptr = list->head,
            .container = list,
            .elem_size = list->element_size,
            .next = list_iterator_next,
            .prev = list_iterator_prev,
            .get = list_iterator_get,
            .set = list_iterator_set
    };
}

Iterator linkedlist_end(LinkedList list) {
    return (Iterator) {
        .ptr = NULL,
            .container = list,
            .elem_size = list->element_size,
            .next = list_iterator_next,
            .prev = list_iterator_prev,
            .get = list_iterator_get,
            .set = list_iterator_set
    };
}

// 反向迭代器实现
static Iterator reverse_iterator_next(Iterator it) {
    Node* node = it.ptr;
    if (node) {
        it.ptr = node->prev;
    }
    return it;
}

static Iterator reverse_iterator_prev(Iterator it) {
    Node* node = it.ptr;
    if (node) {
        it.ptr = node->next;
    }
    return it;
}

Iterator linkedlist_rbegin(LinkedList list) {
    return (Iterator) {
        .ptr = list->tail,
            .container = list,
            .elem_size = list->element_size,
            .next = reverse_iterator_next,
            .prev = reverse_iterator_prev,
            .get = list_iterator_get,
            .set = list_iterator_set
    };
}

Iterator linkedlist_rend(LinkedList list) {
    return (Iterator) {
        .ptr = NULL,
            .container = list,
            .elem_size = list->element_size,
            .next = reverse_iterator_next,
            .prev = reverse_iterator_prev,
            .get = list_iterator_get,
            .set = list_iterator_set
    };
}

Iterator linkedlist_insert(LinkedList list, Iterator pos, const void* element) {
    Node* new_node = create_node(list, element);
    Node* pos_node = pos.ptr;

    if (pos_node == NULL) {
        // 插入到末尾
        if (list->tail) {
            new_node->prev = list->tail;
            list->tail->next = new_node;
            list->tail = new_node;
        }
        else {
            list->head = list->tail = new_node;
        }
    }
    else {
        new_node->next = pos_node;
        new_node->prev = pos_node->prev;

        if (pos_node->prev) {
            pos_node->prev->next = new_node;
        }
        else {
            list->head = new_node;
        }
        pos_node->prev = new_node;
    }

    list->size++;
    return (Iterator) {
        .ptr = new_node,
            .container = list,
            .elem_size = list->element_size,
            .next = list_iterator_next,
            .prev = list_iterator_prev,
            .get = list_iterator_get,
            .set = list_iterator_set
    };
}

Iterator linkedlist_erase(LinkedList list, Iterator pos) {
    Node* node = pos.ptr;
    if (!node) return pos;

    Iterator next = list_iterator_next(pos);

    if (node->prev) {
        node->prev->next = node->next;
    }
    else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }
    else {
        list->tail = node->prev;
    }

    destroy_node(list, node);
    list->size--;
    return next;
}

void linkedlist_remove(LinkedList list, const void* value) {
    Iterator it = linkedlist_begin(list);
    void* temp = malloc(list->element_size);

    while (!iterator_equals(it, linkedlist_end(list))) {
        iterator_get(it, temp);
        if (memcmp(temp, value, list->element_size) == 0) {
            it = linkedlist_erase(list, it);
        }
        else {
            it = iterator_next(it);
        }
    }

    free(temp);
}

void linkedlist_remove_if(LinkedList list, bool (*pred)(const void*)) {
    Iterator it = linkedlist_begin(list);
    void* temp = malloc(list->element_size);

    while (!iterator_equals(it, linkedlist_end(list))) {
        iterator_get(it, temp);
        if (pred(temp)) {
            it = linkedlist_erase(list, it);
        }
        else {
            it = iterator_next(it);
        }
    }

    free(temp);
}

void linkedlist_splice(LinkedList list, Iterator pos, LinkedList other) {
    if (other->size == 0) return;

    Node* pos_node = pos.ptr;

    // 调整other的前后节点连接
    if (other->head->prev) {
        other->head->prev->next = other->tail->next;
    }
    if (other->tail->next) {
        other->tail->next->prev = other->head->prev;
    }

    // 插入到pos位置
    if (pos_node == NULL) {
        // 插入到末尾
        if (list->tail) {
            list->tail->next = other->head;
            other->head->prev = list->tail;
            list->tail = other->tail;
        }
        else {
            list->head = other->head;
            list->tail = other->tail;
        }
    }
    else {
        other->head->prev = pos_node->prev;
        other->tail->next = pos_node;

        if (pos_node->prev) {
            pos_node->prev->next = other->head;
        }
        else {
            list->head = other->head;
        }
        pos_node->prev = other->tail;
    }

    list->size += other->size;

    // 清空other
    other->head = other->tail = NULL;
    other->size = 0;
}

void linkedlist_merge(LinkedList list, LinkedList other, int (*comp)(const void*, const void*)) {
    if (other->size == 0) return;

    Iterator it1 = linkedlist_begin(list);
    Iterator it2 = linkedlist_begin(other);
    void* val1 = malloc(list->element_size);
    void* val2 = malloc(list->element_size);

    while (!iterator_equals(it1, linkedlist_end(list)) &&
        !iterator_equals(it2, linkedlist_end(other))) {
        iterator_get(it1, val1);
        iterator_get(it2, val2);

        if (comp(val2, val1) <= 0) {
            Iterator next = iterator_next(it2);
            linkedlist_splice(list, it1, other);
            it2 = next;
        }
        else {
            it1 = iterator_next(it1);
        }
    }

    if (!iterator_equals(it2, linkedlist_end(other))) {
        linkedlist_splice(list, linkedlist_end(list), other);
    }

    free(val1);
    free(val2);
}

void linkedlist_sort(LinkedList list, int (*comp)(const void*, const void*)) {
    if (list->size <= 1) return;

    // 使用归并排序
    LinkedList left = linkedlist_create(list->element_size, list->allocator);
    LinkedList right = linkedlist_create(list->element_size, list->allocator);

    // 分割链表
    size_t mid = list->size / 2;
    Iterator it = linkedlist_begin(list);

    for (size_t i = 0; i < mid; i++) {
        void* temp = malloc(list->element_size);
        iterator_get(it, temp);
        linkedlist_push_back(left, temp);
        it = iterator_next(it);
        free(temp);
    }

    while (!iterator_equals(it, linkedlist_end(list))) {
        void* temp = malloc(list->element_size);
        iterator_get(it, temp);
        linkedlist_push_back(right, temp);
        it = iterator_next(it);
        free(temp);
    }

    // 递归排序
    linkedlist_sort(left, comp);
    linkedlist_sort(right, comp);

    // 清空原链表
    linkedlist_clear(list);

    // 合并
    linkedlist_merge(list, left, comp);
    linkedlist_merge(list, right, comp);

    linkedlist_destroy(left);
    linkedlist_destroy(right);
}

void linkedlist_unique(LinkedList list, int (*comp)(const void*, const void*)) {
    if (list->size <= 1) return;

    Iterator it = linkedlist_begin(list);
    void* prev_val = malloc(list->element_size);
    void* curr_val = malloc(list->element_size);

    iterator_get(it, prev_val);
    it = iterator_next(it);

    while (!iterator_equals(it, linkedlist_end(list))) {
        iterator_get(it, curr_val);
        if (comp(prev_val, curr_val) == 0) {
            it = linkedlist_erase(list, it);
        }
        else {
            memcpy(prev_val, curr_val, list->element_size);
            it = iterator_next(it);
        }
    }

    free(prev_val);
    free(curr_val);
}

void linkedlist_reverse(LinkedList list) {
    if (list->size <= 1) return;

    Node* current = list->head;
    Node* temp = NULL;

    // 交换所有节点的prev和next指针
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // 交换head和tail
    temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}