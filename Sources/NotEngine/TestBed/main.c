#include <stdio.h>
#include <stdlib.h>
#include "core/logger/log.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string.h>


int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    logger_add_console_callback();
    return EXIT_SUCCESS;
}
