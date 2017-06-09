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

// Processor Architecture
#if defined(_WIN64) || defined(__x86_64__) || defined(__amd64__)
# define NATIVE_ARCH_X64 1
#elif defined(_WIN32) || defined(__i386__) || defined(_M_X86) || defined(__i686__)
# define NATIVE_ARCH_X86 1
#elif defined(__ARM_EABI__) || defined(_M_ARM) || defined(__arm__)
# define NATIVE_ARCH_ARM 1
#elif defined(__aarch64__)
# define NATIVE_ARCH_ARM64 1
#elif defined(__mips__) && (__mips__ < 5)
# define NATIVE_ARCH_MIPS 1
#else
# error No supported processor architecture detected.
#endif // NATIVE_ARCH_*

// Pointer Bit Size
#if defined(NATIVE_ARCH_X64) || defined(NATIVE_ARCH_ARM64)
# define NATIVE_BIT_WIDTH 64
#else
# define NATIVE_BIT_WIDTH 32
#endif // NATIVE_BIT_WIDTH

// Form-Factors
#if defined(NATIVE_PLATFORM_WIN32)
# define NATIVE_FORM_DESKTOP 1
#elif defined(NATIVE_PLATFORM_ANDROID)
# define NATIVE_FORM_MOBILE 1
#else
# error Form-factor for current platform not defined.
#endif

#endif // _NATIVE_CORE_PLATFORM_H_

