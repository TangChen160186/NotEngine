#pragma once
#include "typedefs.h"

// 日志级别
typedef enum LogLevel {
    LOG_TRACE = 0,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

// 断点宏
#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#else
#define DEBUG_BREAK() raise(SIGTRAP)
#endif

// 日志级别控制宏
#ifdef _DEBUG
    // Debug构建：启用所有日志
#define LOG_LEVEL_TRACE 1  // 追踪详细的执行流程
#define LOG_LEVEL_DEBUG 1  // 调试信息
#define LOG_LEVEL_INFO  1  // 一般信息
#define LOG_LEVEL_WARN  1  // 警告信息
#define LOG_LEVEL_ERROR 1  // 错误信息
#else
    // Release构建：只保留重要日志
#define LOG_LEVEL_TRACE 0  // 关闭
#define LOG_LEVEL_DEBUG 0  // 关闭
#define LOG_LEVEL_INFO  0  // 关闭
#define LOG_LEVEL_WARN  1  // 保留警告
#define LOG_LEVEL_ERROR 1  // 保留错误
#endif

// 日志宏
#if LOG_LEVEL_TRACE
#define LOG_TRACE(...) logger_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_TRACE(...) ((void)0)
#endif

#if LOG_LEVEL_DEBUG
#define LOG_DEBUG(...) logger_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_DEBUG(...) ((void)0)
#endif

#if LOG_LEVEL_INFO
#define LOG_INFO(...) logger_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_INFO(...) ((void)0)
#endif

#if LOG_LEVEL_WARN
#define LOG_WARN(...) logger_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_WARN(...) ((void)0)
#endif

#if LOG_LEVEL_ERROR
#define LOG_ERROR(...) logger_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_ERROR(...) ((void)0)
#endif

#define LOG_FATAL(...) do{ \
        logger_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__); \
        DEBUG_BREAK(); \
    } while(0)
 

// API函数
API void logger_log(LogLevel level, const char* file, int line, const char* fmt, ...);
API void logger_add_callback(void (*callback)(LogLevel level, const char* message, const char* file, int line));
API void logger_add_console_callback(void);
API void logger_set_level(LogLevel level);
