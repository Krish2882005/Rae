#pragma once

#include "Rae/Config/Version.hpp"

// Platform Detection
#if defined(_WIN32)
#define RAE_PLATFORM_WINDOWS
#elif defined(__linux__)
#define RAE_PLATFORM_LINUX
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if defined(TARGET_OS_OSX) && TARGET_OS_OSX
#define RAE_PLATFORM_MACOS
#else
#error "Rae: Only macOS is supported on Apple platforms"
#endif
#else
#error "Rae: Unsupported platform! Supported: Windows, Linux, macOS"
#endif

// Compiler Detection
#if defined(__clang__)
#define RAE_COMPILER_CLANG
#define RAE_COMPILER_VERSION                                                                       \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(_MSC_VER)
#define RAE_COMPILER_MSVC
#define RAE_COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
#define RAE_COMPILER_GCC
#define RAE_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "Rae: Unsupported compiler! Supported: MSVC, Clang, GCC"
#endif

// C++23 version check
#if defined(RAE_COMPILER_MSVC)
#if !((defined(__cplusplus) && __cplusplus >= 202302L) ||                                          \
      (defined(_MSVC_LANG) && _MSVC_LANG >= 202302L))
#error "Rae: Requires C++23 or later"
#endif
#else
#if !defined(__cplusplus) || __cplusplus < 202302L
#error "Rae: Requires C++23 or later"
#endif
#endif

// Build Configuration
#if defined(NDEBUG)
#define RAE_RELEASE
#else
#define RAE_DEBUG
#endif
