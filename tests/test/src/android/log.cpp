// System Dependencies
#include <android/log.h>

// Module Dependencies
#include "../../include/log.h"

namespace native
{
    namespace test
    {
        void log(const char* format, ...)
        {
            va_list args;

            va_start(args, format);
            __android_log_vprint(ANDROID_LOG_INFO, "native-test", format, args);
            va_end(args);
        }
    }
}

