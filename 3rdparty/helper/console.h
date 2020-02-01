#pragma once

#include "rang.h"

#ifdef WIN32
    void open_console();
    void close_console();
#else
#   define open_console
#   define close_console
#endif // OS_WIN