#include <stdio.h>
#include "stack.h"
#include "deque.h"
struct Stack {
    Deque deque;  // 使用deque作为底层容器
    Allocator* allocator;  // 保存创建时使用的分配器
};

Stack stack_create(size_t element_size, Allocator* allocator) {
    if (!allocator) allocator = get_default_allocator();
    Stack stack = allocator->allocate(sizeof(Stack));
    stack->allocator = allocator;
    stack->deque = deque_create(element_size, allocator);
    return stack;
}

void stack_destroy(Stack stack) {
    deque_destroy(stack->deque);
    stack->allocator->deallocate(stack);
}

bool stack_empty(const Stack stack) {
    return deque_empty(stack->deque);
}

size_t stack_size(const Stack stack) {
    return deque_size(stack->deque);
}

void stack_top(const Stack stack, void* out) {
    deque_back(stack->deque, out);
}

void stack_push(Stack stack, const void* element) {
    deque_push_back(stack->deque, element);
}

void stack_pop(Stack stack) {
    deque_pop_back(stack->deque);
}

Iterator stack_begin(Stack stack) {
    // 从栈顶开始，即 deque 的末尾
    return deque_rbegin(stack->deque);
}

Iterator stack_end(Stack stack) {
    // 栈的结束位置是 deque 的开始
    return deque_rend(stack->deque);
}

Iterator stack_rbegin(Stack stack) {
    // 从栈底开始，即 deque 的开始
    return deque_begin(stack->deque);
}

Iterator stack_rend(Stack stack) {
    // 栈的反向结束位置是 deque 的末尾
    return deque_end(stack->deque);
}