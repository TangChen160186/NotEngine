#pragma once
#include "array_list.h"
#include "typedefs.h"
#include "alloctor/allocator.h"
#include "iterator/iterator.h"

typedef struct HashMap* HashMap;
typedef size_t(*HashFunc)(const void* key);
typedef bool (*KeyEqual)(const void* key1, const void* key2);

// 添加键值对结构
typedef struct {
    void* key;
    void* value;
} HashMapPair;

// 创建HashMap
API HashMap hashmap_create(size_t key_size, size_t value_size,
    HashFunc hash_func, KeyEqual key_equal,
    Allocator* allocator);

// 销毁HashMap
API void hashmap_destroy(HashMap map);

// 插入键值对，返回是否为新插入
API bool hashmap_insert(HashMap map, const void* key, const void* value);

// 查找值
API bool hashmap_get(const HashMap map, const void* key, void* value_out);

// 删除键值对，返回删除的数量
API size_t hashmap_erase(HashMap map, const void* key);

// 清空HashMap
API void hashmap_clear(HashMap map);

// 获取大小
API size_t hashmap_size(const HashMap map);

// 获取桶数量
API size_t hashmap_bucket_count(const HashMap map);

// 获取负载因子
API float hashmap_load_factor(const HashMap map);

// 重新设置桶数量
API void hashmap_rehash(HashMap map, size_t bucket_count);

// 检查是否为空
API bool hashmap_empty(const HashMap map);

// 检查键是否存在
API bool hashmap_contains(const HashMap map, const void* key);
API void hashmap_get_pair(Iterator it, void* key,void* value);  // 新增：获取键值对


// 获取所有keys或values
API ArrayList hashmap_keys(HashMap map);
API ArrayList hashmap_values(HashMap map);