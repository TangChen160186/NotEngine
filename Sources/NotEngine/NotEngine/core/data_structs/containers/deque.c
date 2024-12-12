#include <stdio.h>
#include <string.h>
#include "deque.h"

#define BLOCK_SIZE 8
#define INITIAL_MAP_SIZE 8

// 数据块结构
typedef struct {
    void* data;  // 数据块内存
} Block;

// 双端队列结构
struct Deque {
    Block** blocks;       // 块指针数组
    size_t block_count;   // 块数组大小
    size_t front_block;   // 首元素所在块
    size_t front_pos;     // 首元素在块中位置
    size_t back_block;    // 尾元素所在块
    size_t back_pos;      // 尾元素在块中位置
    size_t size;          // 元素个数
    size_t elem_size;     // 元素大小
    Allocator* allocator; // 内存分配器
};

// 创建新的数据块
static Block* create_block(Deque deque) {
    Block* block = deque->allocator->allocate(sizeof(Block));
    block->data = deque->allocator->allocate(BLOCK_SIZE * deque->elem_size);
    return block;
}

// 销毁数据块
static void destroy_block(Deque deque, Block* block) {
    deque->allocator->deallocate(block->data);
    deque->allocator->deallocate(block);
}

// 确保有足够的块空间
static void ensure_capacity(Deque deque) {
    if (deque->back_block - deque->front_block < deque->block_count - 2) {
        return;
    }
     
    size_t new_count = deque->block_count * 2;
    Block** new_blocks = deque->allocator->allocate(new_count * sizeof(Block*));

    // 移动现有块到新数组中间
    size_t new_front = (new_count - (deque->back_block - deque->front_block)) / 2;
    for (size_t i = deque->front_block; i <= deque->back_block; i++) {
        new_blocks[new_front + (i - deque->front_block)] = deque->blocks[i];
    }

    deque->allocator->deallocate(deque->blocks);
    deque->blocks = new_blocks;
    deque->back_block = new_front + (deque->back_block - deque->front_block);
    deque->front_block = new_front;
    deque->block_count = new_count;
}

Deque deque_create(size_t elem_size, Allocator* allocator) {
    if (!allocator) allocator = get_default_allocator();

    Deque deque = allocator->allocate(sizeof(Deque));
    deque->blocks = allocator->allocate(INITIAL_MAP_SIZE * sizeof(Block*));
    deque->block_count = INITIAL_MAP_SIZE;
    deque->elem_size = elem_size;
    deque->allocator = allocator;

    // 初始化为中间位置
    deque->front_block = deque->back_block = INITIAL_MAP_SIZE / 2;
    deque->front_pos = deque->back_pos = BLOCK_SIZE / 2;
    deque->size = 0;

    // 创建初始块
    deque->blocks[deque->front_block] = create_block(deque);
    return deque;
}

void deque_destroy(Deque deque) {
    for (size_t i = deque->front_block; i <= deque->back_block; i++) {
        destroy_block(deque, deque->blocks[i]);
    }
    deque->allocator->deallocate(deque->blocks);
    deque->allocator->deallocate(deque);
}

void deque_push_front(Deque deque, const void* elem) {
    if (deque->front_pos == 0) {
        ensure_capacity(deque);
        deque->front_block--;
        deque->blocks[deque->front_block] = create_block(deque);
        deque->front_pos = BLOCK_SIZE;
    }

    deque->front_pos--;
    memcpy((char*)deque->blocks[deque->front_block]->data +
        deque->front_pos * deque->elem_size, elem, deque->elem_size);
    deque->size++;
}

void deque_push_back(Deque deque, const void* elem) {
    if (deque->back_pos == BLOCK_SIZE) {
        ensure_capacity(deque);
        deque->back_block++;
        deque->blocks[deque->back_block] = create_block(deque);
        deque->back_pos = 0;
    }

    memcpy((char*)deque->blocks[deque->back_block]->data +
        deque->back_pos * deque->elem_size, elem, deque->elem_size);
    deque->back_pos++;
    deque->size++;
}

void deque_pop_front(Deque deque) {
    if (deque->size == 0) return;

    deque->front_pos++;
    if (deque->front_pos == BLOCK_SIZE) {
        destroy_block(deque, deque->blocks[deque->front_block]);
        deque->front_block++;
        deque->front_pos = 0;
    }
    deque->size--;
}

void deque_pop_back(Deque deque) {
    if (deque->size == 0) return;

    if (deque->back_pos == 0) {
        destroy_block(deque, deque->blocks[deque->back_block]);
        deque->back_block--;
        deque->back_pos = BLOCK_SIZE;
    }
    deque->back_pos--;
    deque->size--;
}

void deque_front(const Deque deque, void* dest) {
    memcpy(dest,
        (char*)deque->blocks[deque->front_block]->data +
        deque->front_pos * deque->elem_size,
        deque->elem_size);
}

void deque_back(const Deque deque, void* dest) {
    size_t pos = deque->back_pos > 0 ? deque->back_pos - 1 : BLOCK_SIZE - 1;
    memcpy(dest,
        (char*)deque->blocks[deque->back_block]->data +
        pos * deque->elem_size,
        deque->elem_size);
}

size_t deque_size(const Deque deque)
{
    return deque->size;
}

bool deque_empty(const Deque deque)
{
    return deque->size == 0;
}


// 迭代器实现
static void deque_iterator_get(Iterator it, void* dest) {
    memcpy(dest, it.ptr, it.elem_size);
}

static void deque_iterator_set(Iterator it, const void* value) {
    memcpy(it.ptr, value, it.elem_size);
}

static Iterator deque_iterator_next(Iterator it) {
    Deque deque = it.container;
    char* ptr = it.ptr;
    size_t offset = ((char*)ptr - (char*)deque->blocks[deque->front_block]->data) / deque->elem_size;
    size_t block = deque->front_block + offset / BLOCK_SIZE;

    if ((offset + 1) % BLOCK_SIZE == 0) {
        // 移动到下一个块的开始
        ptr = deque->blocks[block + 1]->data;
    }
    else {
        ptr += deque->elem_size;
    }
    it.ptr = ptr;
    return it;
}

static Iterator deque_iterator_prev(Iterator it) {
    Deque deque = it.container;
    char* ptr = it.ptr;
    size_t offset = ((char*)ptr - (char*)deque->blocks[deque->front_block]->data) / deque->elem_size;
    size_t block = deque->front_block + offset / BLOCK_SIZE;

    if (offset % BLOCK_SIZE == 0) {
        // 移动到前一个块的末尾
        ptr = (char*)deque->blocks[block - 1]->data + (BLOCK_SIZE - 1) * deque->elem_size;
    }
    else {
        ptr -= deque->elem_size;
    }
    it.ptr = ptr;
    return it;
}

Iterator deque_begin(Deque deque) {
    return (Iterator) {
        .ptr = (char*)deque->blocks[deque->front_block]->data +
            deque->front_pos * deque->elem_size,
            .container = deque,
            .elem_size = deque->elem_size,
            .next = deque_iterator_next,
            .prev = deque_iterator_prev,
            .get = deque_iterator_get,
            .set = deque_iterator_set
    };
}

Iterator deque_end(Deque deque) {
    return (Iterator) {
        .ptr = (char*)deque->blocks[deque->back_block]->data +
            deque->back_pos * deque->elem_size,
            .container = deque,
            .elem_size = deque->elem_size,
            .next = deque_iterator_next,
            .prev = deque_iterator_prev,
            .get = deque_iterator_get,
            .set = deque_iterator_set
    };
}

Iterator deque_rbegin(Deque deque) {
    size_t pos = deque->back_pos > 0 ? deque->back_pos - 1 : BLOCK_SIZE - 1;
    return (Iterator) {
        .ptr = (char*)deque->blocks[deque->back_block]->data +
            pos * deque->elem_size,
            .container = deque,
            .elem_size = deque->elem_size,
            .next = deque_iterator_prev,  // 反向时交换next和prev
            .prev = deque_iterator_next,
            .get = deque_iterator_get,
            .set = deque_iterator_set
    };
}

Iterator deque_rend(Deque deque) {
    return (Iterator) {
        .ptr = (char*)deque->blocks[deque->front_block]->data +
            deque->front_pos * deque->elem_size,
            .container = deque,
            .elem_size = deque->elem_size,
            .next = deque_iterator_prev,  // 反向时交换next和prev
            .prev = deque_iterator_next,
            .get = deque_iterator_get,
            .set = deque_iterator_set
    };
}
