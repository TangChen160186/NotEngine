#pragma once
#include "typedefs.h"
#include "stdbool.h"
#include "Internal/logger.h"

API bool init_log_system(void);
API void shutdown_log_system(void);
API void output(LogLevel level, const char* file, int line, const char* fmt, ...);
#define LOG_TRACE(...) output(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)  
#define LOG_DEBUG(...) output(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  output(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  output(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) output(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) output(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
