#ifndef _NATIVE_CORE_PLATFORM_H_
#define _NATIVE_CORE_PLATFORM_H_ 1

// Platform Detection
#if defined(_WIN32) || defined(_WIN64)
# define NATIVE_PLATFORM_WIN32 1
#elif defined(__ANDROID__)
# define NATIVE_PLATFORM_ANDROID 1
#else
# error No supported platform detected.
#endif // NATIVE_PLATFORM_*

#endif // _NATIVE_CORE_PLATFORM_H_

