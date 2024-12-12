#include <string.h>
#include "hash_map.h"

#define INITIAL_BUCKET_COUNT 8
#define MAX_LOAD_FACTOR 1.0f

// 哈希表节点
typedef struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;
} HashNode;

struct HashMap {
    HashNode** buckets;     // 桶数组
    size_t bucket_count;    // 桶数量
    size_t size;           // 元素数量
    size_t key_size;       // 键大小
    size_t value_size;     // 值大小
    HashFunc hash_func;    // 哈希函数
    KeyEqual key_equal;    // 键比较函数
    Allocator* allocator;  // 内存分配器
};

// 创建新节点
static HashNode* create_node(HashMap map, const void* key, const void* value) {
    HashNode* node = map->allocator->allocate(sizeof(HashNode));
    node->key = map->allocator->allocate(map->key_size);
    node->value = map->allocator->allocate(map->value_size);
    node->next = NULL;

    memcpy(node->key, key, map->key_size);
    memcpy(node->value, value, map->value_size);
    return node;
}

// 销毁节点
static void destroy_node(HashMap map, HashNode* node) {
    map->allocator->deallocate(node->key);
    map->allocator->deallocate(node->value);
    map->allocator->deallocate(node);
}

// 查找节点
static HashNode** find_node(const HashMap map, const void* key) {
    size_t hash = map->hash_func(key);
    size_t bucket = hash % map->bucket_count;
    HashNode** curr = &map->buckets[bucket];

    while (*curr) {
        if (map->key_equal((*curr)->key, key)) {
            return curr;
        }
        curr = &(*curr)->next;
    }
    return curr;
}

// 重新哈希
static void rehash_internal(HashMap map, size_t new_count) {
    HashNode** new_buckets = map->allocator->allocate(sizeof(HashNode*) * new_count);
    memset(new_buckets, 0, sizeof(HashNode*) * new_count);

    // 重新分配所有节点
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode* curr = map->buckets[i];
        while (curr) {
            HashNode* next = curr->next;
            size_t new_bucket = map->hash_func(curr->key) % new_count;
            curr->next = new_buckets[new_bucket];
            new_buckets[new_bucket] = curr;
            curr = next;
        }
    }

    map->allocator->deallocate(map->buckets);
    map->buckets = new_buckets;
    map->bucket_count = new_count;
}

HashMap hashmap_create(size_t key_size, size_t value_size,
    HashFunc hash_func, KeyEqual key_equal,
    Allocator* allocator) {
    if (!allocator) allocator = get_default_allocator();

    HashMap map = allocator->allocate(sizeof(struct HashMap));
    map->bucket_count = INITIAL_BUCKET_COUNT;
    map->buckets = allocator->allocate(sizeof(HashNode*) * INITIAL_BUCKET_COUNT);
    memset(map->buckets, 0, sizeof(HashNode*) * INITIAL_BUCKET_COUNT);

    map->size = 0;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_func = hash_func;
    map->key_equal = key_equal;
    map->allocator = allocator;

    return map;
}

void hashmap_destroy(HashMap map) {
    hashmap_clear(map);
    map->allocator->deallocate(map->buckets);
    map->allocator->deallocate(map);
}

bool hashmap_insert(HashMap map, const void* key, const void* value) {
    if (hashmap_load_factor(map) >= MAX_LOAD_FACTOR) {
        rehash_internal(map, map->bucket_count * 2);
    }

    HashNode** node = find_node(map, key);
    if (*node) {
        // 更新已存在的值
        memcpy((*node)->value, value, map->value_size);
        return false;
    }

    // 插入新节点
    *node = create_node(map, key, value);
    map->size++;
    return true;
}

bool hashmap_get(const HashMap map, const void* key, void* value_out) {
    HashNode** node = find_node(map, key);
    if (!*node) return false;

    if (value_out) {
        memcpy(value_out, (*node)->value, map->value_size);
    }
    return true;
}

size_t hashmap_erase(HashMap map, const void* key) {
    HashNode** node = find_node(map, key);
    if (!*node) return 0;

    HashNode* temp = *node;
    *node = (*node)->next;
    destroy_node(map, temp);
    map->size--;
    return 1;
}

void hashmap_clear(HashMap map) {
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode* curr = map->buckets[i];
        while (curr) {
            HashNode* next = curr->next;
            destroy_node(map, curr);
            curr = next;
        }
        map->buckets[i] = NULL;
    }
    map->size = 0;
}

size_t hashmap_size(const HashMap map) {
    return map->size;
}

size_t hashmap_bucket_count(const HashMap map) {
    return map->bucket_count;
}

float hashmap_load_factor(const HashMap map) {
    return (float)map->size / map->bucket_count;
}

void hashmap_rehash(HashMap map, size_t bucket_count) {
    if (bucket_count > 0) {
        rehash_internal(map, bucket_count);
    }
}

bool hashmap_empty(const HashMap map) {
    return map->size == 0;
}

bool hashmap_contains(const HashMap map, const void* key) {
    HashNode** node = find_node(map, key);
    return *node != NULL;
}

ArrayList hashmap_keys(HashMap map) {
    ArrayList keys = arraylist_create(map->key_size, map->allocator);

    // 遍历所有桶和链表节点
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode* curr = map->buckets[i];
        while (curr) {
            arraylist_push_back(keys, curr->key);
            curr = curr->next;
        }
    }

    return keys;
}

ArrayList hashmap_values(HashMap map) {
    ArrayList values = arraylist_create(map->value_size, map->allocator);

    // 遍历所有桶和链表节点
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode* curr = map->buckets[i];
        while (curr) {
            arraylist_push_back(values, curr->value);
            curr = curr->next;
        }
    }

    return values;
}
