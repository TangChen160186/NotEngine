#pragma once
#include "log.h"
#ifdef  DEBUG
#define ASSERT_ENABLE
#endif


// 断言宏
#ifdef ASSERT_ENABLE
#define ASSERT(condition) \
        do { \
            if (!(condition)) { \
                LOG_FATAL("Assertion failed: %s,Message: ", #condition); \
            } \
        } while(0)

#define ASSERT_MSG(condition, msg) \
        do { \
            if (!(condition)) { \
                LOG_FATAL("Assertion failed: %s\n" msg, #condition); \
            } \
        } while(0)

#define ASSERT_NOT_NULL(ptr) \
        do { \
            if ((ptr) == NULL) { \
                LOG_FATAL("Assertion failed: %s is NULL", #ptr); \
            } \
        } while(0)

#define ASSERT_FAIL(msg) \
        LOG_FATAL("Assertion failed: " msg)

#else
    // Release模式下断言被禁用
#define ASSERT(condition, ...) ((void)0)
#define ASSERT_MSG(condition, msg, ...) ((void)0)
#define ASSERT_NOT_NULL(ptr) ((void)0)
#define ASSERT_FAIL(msg, ...) ((void)0)
#endif
