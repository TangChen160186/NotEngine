#include <stdio.h>
#include <stdlib.h>
#include "core/logger/log.h"
#include "core/memory/memory.h"
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

#include "core/logger/assert.h"
#include "core/mathematics/math_funcs.h"
#include "core/mathematics/vector2.h"
#include "core/mathematics/matrix4x4.h"
#include "core/mathematics/quaternion.h"

int main(void)
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    logger_add_console_callback(); 
    char leaks[1024];
    bool a1 = matrix44_is_rotation(matrix44_create_from_quaternion(quaternion_create_from_yaw_pitch_roll(1.2,1.3,1.3)));
    vector2 v={};
    vector2 v1 = { 1,3 };
    vector2 a =vector2_divide(v1,v);
    float d = math_sqrt(-1);
    LOG_TRACE("%s", "fafa");
    LOG_DEBUG("%s", "fafa");
    LOG_INFO("%s", "fafa");
    LOG_WARN("%s", "fafa");
    LOG_ERROR("%s", "fafa");

    return EXIT_SUCCESS;
}
