#include "Log.h"
#include <stdarg.h>
static Logger* engine_logger;
bool init_log_system(void)
{
    const LogConfig log_config = {
        .logger_name = "EngineLog",
        false,
    };
    engine_logger = logger_create(&log_config);
    if (!engine_logger) return false;

    // console log
    SinkConfig sink_config = {
        .min_level = LOG_TRACE,
        .use_color = true,
        .format = NULL };
    LogSink* console_sink = console_sink_create(&sink_config);
    if (!console_sink) return false;
    logger_add_sink(engine_logger, console_sink);
    
    // other log


    return true;
}


void shutdown_log_system()
{
    logger_destroy(engine_logger);
}

void output(LogLevel level, const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    logger_log_va_list(engine_logger, level, file, line, fmt, args);
    va_end(args);
}