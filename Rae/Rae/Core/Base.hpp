#pragma once

#include <cstddef>
#include <cstdint>

#include "Rae/Config/Version.hpp"

// --- Environment Detection ---

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

// --- Compiler Hints & Attributes ---

// forceinline
#if defined(RAE_COMPILER_MSVC)
#define RAE_FORCE_INLINE __forceinline
#elif defined(RAE_COMPILER_CLANG) || defined(RAE_COMPILER_GCC)
#define RAE_FORCE_INLINE inline __attribute__((always_inline))
#else
#define RAE_FORCE_INLINE inline
#endif

// noinline
#if defined(RAE_COMPILER_MSVC)
#define RAE_NO_INLINE __declspec(noinline)
#elif defined(RAE_COMPILER_CLANG) || defined(RAE_COMPILER_GCC)
#define RAE_NO_INLINE __attribute__((noinline))
#else
#define RAE_NO_INLINE
#endif

// Debug break
#if defined(RAE_COMPILER_MSVC)
#define RAE_DEBUGBREAK() __debugbreak()
#elif defined(RAE_COMPILER_CLANG)
#define RAE_DEBUGBREAK() __builtin_debugtrap()
#elif defined(RAE_COMPILER_GCC)
#include <csignal>
#define RAE_DEBUGBREAK() ::std::raise(SIGTRAP)
#else
#define RAE_DEBUGBREAK() ((void)0)
#endif

// no_unique_address
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(no_unique_address)
#define RAE_NO_UNIQUE_ADDRESS [[no_unique_address]]
#elif defined(RAE_COMPILER_MSVC) && __has_cpp_attribute(msvc::no_unique_address)
#define RAE_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#define RAE_NO_UNIQUE_ADDRESS
#endif
#else
#define RAE_NO_UNIQUE_ADDRESS
#endif

// --- Common Type Aliases ---

namespace Rae {
using Int8 = std::int8_t;
using Int16 = std::int16_t;
using Int32 = std::int32_t;
using Int64 = std::int64_t;

using UInt8 = std::uint8_t;
using UInt16 = std::uint16_t;
using UInt32 = std::uint32_t;
using UInt64 = std::uint64_t;

using Byte = std::byte;
} // namespace Rae
