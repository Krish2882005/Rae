#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <print>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <utility>

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

// --- Assertion System ---

namespace Rae::Internal {
[[noreturn]] inline void FatalAssertHandler(std::string_view expression, std::string_view message,
                                            const std::source_location& location) noexcept {
    std::println(stderr, "\n{}\n  {} failed\n  {}:{} in {}", message, expression,
                 location.file_name(), location.line(), location.function_name());

    std::fflush(stderr);
    RAE_DEBUGBREAK();
    std::abort();
}
} // namespace Rae::Internal

#define RAE_ASSERT(expr, msg)                                                                      \
    do {                                                                                           \
        if (!(expr)) [[unlikely]] {                                                                \
            auto loc = std::source_location::current();                                            \
            ::Rae::Internal::FatalAssertHandler(RAE_STRINGIFY(expr), msg, loc);                    \
        }                                                                                          \
    } while (false)

#ifdef RAE_DEBUG
#define RAE_DEBUG_ASSERT(expr, msg) RAE_ASSERT(expr, msg)
#else
#define RAE_DEBUG_ASSERT(expr, msg) static_cast<void>(0)
#endif

#ifdef RAE_DEBUG
#define RAE_VERIFY(expr) RAE_ASSERT(expr, "Verification failed")
#else
#define RAE_VERIFY(expr) static_cast<void>(expr)
#endif

// --- Fundamental Type Aliases ---

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

// --- Smart Pointer Aliases & Factories ---

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T, typename... Args>
[[nodiscard]] constexpr auto CreateScope(Args&&... args) -> Scope<T> {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
[[nodiscard]] auto CreateRef(Args&&... args) -> Ref<T> {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

// --- Bit Manipulation Utilities ---

template <typename T>
    requires std::is_enum_v<T>
[[nodiscard]] constexpr auto BitSet(T value, T flag) noexcept -> T {
    auto v = std::to_underlying(value);
    auto f = std::to_underlying(flag);
    return static_cast<T>(v | f);
}

template <typename T>
    requires std::is_enum_v<T>
[[nodiscard]] constexpr auto BitClear(T value, T flag) noexcept -> T {
    auto v = std::to_underlying(value);
    auto f = std::to_underlying(flag);
    return static_cast<T>(v & ~f);
}

template <typename T>
    requires std::is_enum_v<T>
[[nodiscard]] constexpr auto BitTest(T value, T flag) noexcept -> bool {
    auto v = std::to_underlying(value);
    auto f = std::to_underlying(flag);
    return (v & f) != 0;
}
} // namespace Rae
