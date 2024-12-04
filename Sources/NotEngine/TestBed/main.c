﻿#include "log.h"
#include <stdio.h>
#include <stdlib.h>

#include "log_internal.h"

int main(void) {

    union {
        struct {
            float x;
            float y;
            float z;
        };
        float coord[3] = { 0 }; // 默认初始化
    };
  
    // 创建日志格式
    LogFormatElement elements[] = {
        {LOG_FMT_TEXT, "[JGFA8HFAIUHFAIU]", NULL},
        {LOG_FMT_TIME, NULL, "[%Y-%m-%d %H:%M:%S]"},
        {LOG_FMT_TEXT, " [", NULL},
        {LOG_FMT_LOGGER_NAME, NULL, NULL},
        {LOG_FMT_TEXT, "] [", NULL},
        {LOG_FMT_LEVEL, NULL, NULL},
        {LOG_FMT_TEXT, "] ", NULL},
        {LOG_FMT_MESSAGE, NULL, NULL}
    };
    LogFormat* format = log_format_create(elements, sizeof(elements) / sizeof(elements[0]));

    // 创建日志配置
    LogConfig config = {
        .logger_name = "MyLogger",
        .async = true,
        .format = format
    };

    // 创建Logger
    Logger* logger = logger_create(&config);
    if (!logger) {
        fprintf(stderr, "Failed to create logger\n");
        return EXIT_FAILURE;
    }
    ColorConfig myColorConfig = {
        .trace_color = "#5F9EA0",  // 浅蓝色
        .debug_color = "rgb(0,255,255)",  // 青色
        .info_color = "\x1b[32m",   // 绿色 (ANSI)
        .warn_color = "#FFD700",    // 金色
        .error_color = "rgb(255,0,0)",  // 红色
        .fatal_color = "\x1b[35m"   // 紫色 (ANSI)
    };
    // 创建控制台Sink
    SinkConfig console_config = {
        .min_level = LOG_DEBUG,
        .use_color = true,
        .color_config = &myColorConfig,
        .format = NULL,  // 使用全局格式
    };
    LogSink* console_sink = console_sink_create(&console_config);
    if (!console_sink) {
        fprintf(stderr, "Failed to create console sink\n");
        logger_destroy(logger);
        return EXIT_FAILURE;
    }
    logger_add_sink(logger, console_sink);

    // 创建文件Sink
    SinkConfig file_config = {
        .min_level = LOG_INFO,
        .use_color = false,
        .format = NULL  // 使用全局格式
    };
    LogSink* file_sink = file_sink_create("logfile.log", &file_config);
    if (!file_sink) {
        fprintf(stderr, "Failed to create file sink\n");
        logger_destroy(logger);
        return EXIT_FAILURE;
    }
    logger_add_sink(logger, file_sink);

    // 创建滚动文件Sink
    RollConfig roll_config = {
        .strategy = ROLL_BY_SIZE,
        .max_file_size = 1024 * 1024,  // 1MB
        .max_files = 5,
        .time_unit = TIME_UNIT_DAY,
        .time_interval = 1,
        .filename_pattern = "%f_%i.log"
    };
    LogSink* rolling_sink = rolling_file_sink_create("rolling_log", &file_config, &roll_config);
    if (!rolling_sink) {
        fprintf(stderr, "Failed to create rolling file sink\n");
        logger_destroy(logger);
        return EXIT_FAILURE;
    }
    logger_add_sink(logger, rolling_sink);

    // 记录不同级别的日志
    LOG_TRACE(logger, "This is a trace message,%d", 100);
    LOG_DEBUG(logger, "This is a debug message");
    LOG_INFO(logger, "This is an info message");
    LOG_WARN(logger, "This is a warning message");
    LOG_ERROR(logger, "This is an error message");
    LOG_FATAL(logger, "This is a fatal message");

    // 销毁Logger
    logger_destroy(logger);
    return EXIT_SUCCESS;
}
