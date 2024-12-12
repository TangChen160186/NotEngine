#include <stdio.h>
#include "queue.h"

struct Queue {
    Deque deque;  // 使用deque作为底层容器
    Allocator* allocator;
};

Queue queue_create(size_t element_size, Allocator* allocator) {
    if (!allocator) allocator = get_default_allocator();

    Queue queue = allocator->allocate(sizeof(struct Queue));
    queue->deque = deque_create(element_size, allocator);
    queue->allocator = allocator;
    return queue;
}

void queue_destroy(Queue queue) {
    deque_destroy(queue->deque);
    queue->allocator->deallocate(queue);
}

bool queue_empty(const Queue queue) {
    return deque_empty(queue->deque);
}

size_t queue_size(const Queue queue) {
    return deque_size(queue->deque);
}

void queue_front(const Queue queue, void* out) {
    deque_front(queue->deque, out);
}

void queue_back(const Queue queue, void* out) {
    deque_back(queue->deque, out);
}

void queue_push(Queue queue, const void* element) {
    deque_push_back(queue->deque, element);
}

void queue_pop(Queue queue) {
    deque_pop_front(queue->deque);
}

Iterator queue_begin(Queue queue) {
    return deque_begin(queue->deque);
}

Iterator queue_end(Queue queue) {
    return deque_end(queue->deque);
}

Iterator queue_rbegin(Queue queue) {
    return deque_rbegin(queue->deque);
}

Iterator queue_rend(Queue queue) {
    return deque_rend(queue->deque);
}