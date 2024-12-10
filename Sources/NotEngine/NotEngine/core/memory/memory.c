//#include "memory.h"
//
//#include <stdbool.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//// 内存块信息结构：用于跟踪每个内存分配的详细信息
//typedef struct MemoryBlock {
//    void* ptr;                  // 分配的内存块指针
//    size_t size;               // 分配的内存大小（字节数）
//    MemoryType type;           // 内存块的类型（字符串、数组等）
//    const char* file;          // 分配发生的源文件名
//    int line;                  // 分配发生的行号
//    struct MemoryBlock* next;  // 指向下一个内存块的指针（链表结构）
//} MemoryBlock;
//
//// 类型统计信息：记录每种类型内存使用的统计数据
//typedef struct {
//    size_t current_used;      // 当前使用的内存量（字节数）
//    size_t total_allocated;   // 累计分配的总内存量（字节数）
//    size_t peak_used;         // 峰值内存使用量（字节数）
//    size_t alloc_count;       // 内存分配次数
//} TypeStats;
//
//// 内存系统状态：管理整个内存系统的全局状态
//typedef struct {
//    bool initialized;          // 内存系统是否已初始化
//    MemoryBlock* blocks;      // 已分配内存块链表的头指针
//    size_t total_allocated;   // 系统总共分配的内存量（字节数）
//    size_t current_used;      // 系统当前使用的内存量（字节数）
//    size_t peak_used;         // 系统峰值内存使用量（字节数）
//    size_t alloc_count;       // 系统总的内存分配次数
//    TypeStats type_stats[MEM_TYPE_COUNT];  // 每种类型的内存使用统计
//    MemoryConfig config;     // 内存系统配置信息
//} MemoryState;
//
//static MemoryState state = { 0 }; 
//     
//static const char* type_names[] = {
//    "Unknown", "String", "Array", "Object", "Buffer"
//};
//
//static void update_type_stats(MemoryType type, size_t size, int is_alloc) {
//    if (type >= MEM_TYPE_COUNT) return;
//
//    TypeStats* stats = &state.type_stats[type];
//    if (is_alloc) {
//        stats->total_allocated += size;
//        stats->current_used += size;
//        stats->alloc_count++;
//        if (stats->current_used > stats->peak_used) {
//            stats->peak_used = stats->current_used;
//        }
//    }
//    else {
//        stats->current_used -= size;
//    }
//}
//
//static void add_block(void* ptr, size_t size, MemoryType type, const char* file, int line) {
//    MemoryBlock* block = malloc(sizeof(MemoryBlock));
//    if (!block) return;
//
//    block->ptr = ptr;
//    block->size = size;
//    block->type = type;
//    block->file = file;
//    block->line = line;
//    block->next = state.blocks;
//    state.blocks = block;
//
//    state.total_allocated += size;
//    state.current_used += size;
//    state.alloc_count++;
//
//    if (state.current_used > state.peak_used) {
//        state.peak_used = state.current_used;
//    }
//
//    update_type_stats(type, size, 1);
//}
//
//static void remove_block(void* ptr) {
//    if (!ptr) return;
//
//    MemoryBlock** curr = &state.blocks;
//    while (*curr) {
//        if ((*curr)->ptr == ptr) {
//            MemoryBlock* block = *curr;
//            *curr = block->next;
//            state.current_used -= block->size;
//            update_type_stats(block->type, block->size, 0);
//            free(block);
//            return;
//        }
//        curr = &(*curr)->next;
//    }
//}
//
//// 公共API实现
//void* memory_alloc(size_t size, MemoryType type, const char* file, int line) {
//    if (!state.initialized) {
//        return malloc(size);
//    }
//
//    if (state.config.max_memory > 0 &&
//        state.current_used + size > state.config.max_memory) {
//        return NULL;
//    }
//
//    void* ptr = malloc(size);
//    if (ptr) {
//        add_block(ptr, size, type, file, line);
//    }
//    return ptr;
//}
//
//void memory_free(void* ptr) {
//    if (!state.initialized) {
//        free(ptr);
//        return;
//    }
//
//    if (ptr) {
//        remove_block(ptr);
//        free(ptr);
//    }
//}
//
//void* memory_set(void* ptr, int value,size_t size)
//{
//    return memset(ptr, value, size);
//}
//
//void* memory_zero(void* ptr, size_t size)
//{
//    return memset(ptr, 0, size);
//}
//
//
//void* memory_copy(void* dest, const void* src, size_t size) {
//    memcpy(dest, src, size);
//    return dest;
//}
//
//void memory_system_init(const MemoryConfig* config) {
//    memset(&state, 0, sizeof(state));
//    if (config) {
//        state.config = *config;
//    }
//    state.initialized = 1;
//}
//void memory_system_shutdown(void) {
//    // 清理跟踪器的内部数据结构
//    while (state.blocks) {
//        MemoryBlock* block = state.blocks;
//        state.blocks = block->next;
//        free(block);
//    }
//}
//
//
//// 字节单位转换辅助函数
//static void format_size(char* buffer, size_t buffer_size, size_t bytes) {
//    const char* units[] = { "B", "KB", "MB", "GB", "TB" };
//    size_t unit_index = 0;
//    double size = bytes;
//
//    while (size >= 1024 && unit_index < 4) {
//        size /= 1024;
//        unit_index++;
//    }
//
//    if (unit_index == 0) {
//        snprintf(buffer, buffer_size, "%zu B", bytes);
//    }
//    else {
//        snprintf(buffer, buffer_size, "%.2f %s", size, units[unit_index]);
//    }
//}
//
//int memory_get_full_stats(char* buffer, size_t size) {
//    char total_size[32], current_size[32], peak_size[32];
//    format_size(total_size, sizeof(total_size), state.total_allocated);
//    format_size(current_size, sizeof(current_size), state.current_used);
//    format_size(peak_size, sizeof(peak_size), state.peak_used);
//
//    const char* format_header =
//        "=== Memory System Statistics ===\n\n"
//        "General Statistics:\n"
//        "+----------------------+----------------------+\n"
//        "| Metric              | Value                 |\n"
//        "+----------------------+----------------------+\n"
//        "| Total Allocated     | %-20s |\n"
//        "| Current Used        | %-20s |\n"
//        "| Peak Usage          | %-20s |\n"
//        "| Allocation Count    | %-20zu |\n"
//        "+----------------------+----------------------+\n\n"
//        "Memory Usage by Type:\n"
//        "+---------------+----------------------+----------------------+----------------------+---------------+\n"
//        "| Type          | Current Used         | Total Allocated     | Peak Usage            | Alloc Count  |\n"
//        "+---------------+----------------------+----------------------+----------------------+---------------+\n";
//
//    const char* format_type =
//        "| %-13s | %-20s | %-20s | %-20s | %11zu  |\n";
//
//
//    int written = snprintf(buffer, buffer ? size : 0, format_header,
//        total_size, current_size, peak_size,
//        state.alloc_count
//    );
//
//    for (int i = 0; i < MEM_TYPE_COUNT; i++) {
//        TypeStats* stats = &state.type_stats[i];
//        if (stats->total_allocated > 0) {
//            char curr_size[32], total_size[32], peak_size[32];
//            format_size(curr_size, sizeof(curr_size), stats->current_used);
//            format_size(total_size, sizeof(total_size), stats->total_allocated);
//            format_size(peak_size, sizeof(peak_size), stats->peak_used);
//
//            written += snprintf(buffer ? buffer + written : NULL,
//                buffer ? size - written : 0,
//                format_type,
//                type_names[i],
//                curr_size,
//                total_size,
//                peak_size,
//                stats->alloc_count);
//        }
//    }
//
//    const char* format_footer =
//        "+---------------+----------------------+----------------------+----------------------+---------------+\n";
//    written += snprintf(buffer ? buffer + written : NULL,
//        buffer ? size - written : 0,
//        format_footer);
//
//    return written + 1;
//}
//
//int memory_get_leaks(char* buffer, size_t size) {
//    const char* format_header =
//        "=== Memory Leaks Report ===\n\n"
//        "+------------------+----------------------+----------------------+---------------+\n"
//        "| Address          | Size                 | Source File         | Line           |\n"
//        "+------------------+----------------------+----------------------+---------------+\n";
//
//    const char* format_row =
//        "| 0x%-14lx | %-20s | %-20s | %11d   |\n";
//
//    const char* format_footer =
//        "+------------------+----------------------+----------------------+---------------+\n";
//
//    const char* format_no_leaks =
//        "=== Memory Leaks Report ===\n\n"
//        "No memory leaks detected.\n";
//
//    if (!state.blocks) {
//        int written = snprintf(buffer, buffer ? size : 0, format_no_leaks);
//        return written + 1;
//    }
//
//    int written = snprintf(buffer, buffer ? size : 0, format_header);
//
//    MemoryBlock* block = state.blocks;
//    while (block) {
//        char size_str[32];
//        format_size(size_str, sizeof(size_str), block->size);
//
//        written += snprintf(buffer ? buffer + written : NULL,
//            buffer ? size - written : 0,
//            format_row,
//            (unsigned long)block->ptr,
//            size_str,
//            block->file,
//            block->line);
//        block = block->next;
//    }
//
//    written += snprintf(buffer ? buffer + written : NULL,
//        buffer ? size - written : 0,
//        format_footer);
//
//    if (state.blocks) {
//        size_t total_leaks = 0;
//        size_t leak_count = 0;
//        block = state.blocks;
//        while (block) {
//            total_leaks += block->size;
//            leak_count++;
//            block = block->next;
//        }
//
//        char total_size[32];
//        format_size(total_size, sizeof(total_size), total_leaks);
//        written += snprintf(buffer ? buffer + written : NULL,
//            buffer ? size - written : 0,
//            "\nTotal leaks: %s in %zu blocks\n",
//            total_size, leak_count);
//    }
//
//    return written + 1;
//}
//
