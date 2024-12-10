//#pragma once
//
//#include "typedefs.h"
//#include <stddef.h>
//
//// 内存分配类型枚举
//typedef enum {
//    MEM_TYPE_UNKNOWN = 0,
//    MEM_TYPE_STRING,
//    MEM_TYPE_ARRAY_LIST,
//    MEM_TYPE_OBJECT,
//    MEM_TYPE_BUFFER,
//    MEM_TYPE_COUNT
//} MemoryType;
//
//// 内存系统配置
//typedef struct {
//    size_t max_memory;        // 最大内存限制（0表示无限制）
//} MemoryConfig;
//
//// 核心API
//API void memory_system_init(const MemoryConfig* config);
//API void memory_system_shutdown(void);
//
//// 内存分配函数
//API void* memory_alloc(size_t size, MemoryType type, const char* file, int line);
//API void* memory_copy(void* dest, const void* src, size_t size);
//API void memory_free(void* ptr);
//API void* memory_set(void* ptr, int value, size_t size);
//API void* memory_zero(void* ptr,size_t size);
//// 内存统计和诊断
//API int memory_get_full_stats(char* buffer, size_t size);         // 获取完整的内存统计信息（包括总体和类型统计）
//API int memory_get_leaks(char* buffer, size_t size);              // 获取内存泄漏信息
//
//
//#define MEM_MALLOC(size,type) memory_alloc(size,type, __FILE__, __LINE__)
//#define MEM_FREE(ptr) memory_free(ptr)
//#define MEM_COPY(dest,src,size) memory_copy(dest,src,size)
//#define MEM_SET(ptr,value,size) memory_set(ptr,value,size)
//#define MEM_ZERO(ptr,size) memory_zero(ptr,size)
//
//
//
//
//
//
//
//
//
