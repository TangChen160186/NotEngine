#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Logger结构体
static struct {
    void (*callbacks[10])(LogLevel level, const char* message, const char* file, int line);
    int callback_count;
} engine_logger = {
    .callback_count = 0
};


// 日志级别名称
static const char* level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

// 日志级别颜色
static const char* level_colors[] = {
    "\x1b[94m",  // TRACE: 亮蓝色
    "\x1b[36m",  // DEBUG: 青色
    "\x1b[32m",  // INFO:  绿色
    "\x1b[33m",  // WARN:  黄色
    "\x1b[31m",  // ERROR: 红色
    "\x1b[35m"   // FATAL: 紫色
};

// 重置颜色
static const char* color_reset = "\x1b[0m";

static void console_callback(LogLevel level, const char* message, const char* file, int line) {
    char time_buf[32];
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);


    printf("[%s] [%s%s]%s %s:%d: %s\n",
        time_buf,
        level_colors[level],
        level_names[level],
        color_reset,
        file,
        line,
        message);
}


// 添加回调函数
void logger_add_callback(void (*callback)(LogLevel level, const char* message, const char* file, int line)) {
    if (engine_logger.callback_count < 10) {
        engine_logger.callbacks[engine_logger.callback_count++] = callback;
    }
}

void logger_add_console_callback(void)
{
    logger_add_callback(console_callback);
}

// 写日志
void logger_log(LogLevel level, const char* file, int line, const char* fmt, ...) {
    char message[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    // 调用所有注册的回调函数
    for (int i = 0; i < engine_logger.callback_count; i++) {
        engine_logger.callbacks[i](level, message, file, line);
    }
}

