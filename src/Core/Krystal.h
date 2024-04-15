#pragma once

#include "Misc/PlatformDetection.h"

// --------- TYPES ----------
#include <stdint.h>
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;
// --------- TYPES ----------

// ------ DEBUG BREAK -------
#ifdef KRYS_ENABLE_DEBUG_BREAK
#if defined(KRYS_PLATFORM_WINDOWS)
#define KRYS_DEBUG_BREAK() __debugbreak()
#elif defined(KRYS_PLATFORM_LINUX)
#include <signal.h>
#define KRYS_DEBUG_BREAK() raise(SIGTRAP)
#else
#error "KRYS_DEBUG_BREAK is not supported for your platform!"
#endif
#else
#define KRYS_DEBUG_BREAK()
#endif
// ------ DEBUG BREAK -------

// ------- FUNC NAME --------
// Resolve the best macro for a function signature, based on the compiler being used.
// Note: only gets resolved during preprocessing so your code editor may highlight the wrong one (i.e the 'else' branch) but should still work.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
#define KRYS_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define KRYS_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define KRYS_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define KRYS_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define KRYS_FUNC_SIG __func__
#else
#error "KRYS_FUNC_SIG unknown!"
#endif
// ------- FUNC NAME --------

// -------- LOGGING ---------
#ifdef KRYS_ENABLE_LOGGING
#include "Logging/Logger.h"
#define KRYS_LOG(message, ...) Logger::Log(message VA_ARGS(__VA_ARGS__))
#define KRYS_DEBUG(message, ...) Logger::Log(LogLevel::Debug, message VA_ARGS(__VA_ARGS__))
#define KRYS_INFO(message, ...) Logger::Log(LogLevel::Info, message VA_ARGS(__VA_ARGS__))
#define KRYS_WARN(message, ...) Logger::Log(LogLevel::Warning, message VA_ARGS(__VA_ARGS__))
#define KRYS_ERROR(message, ...) Logger::Log(LogLevel::Error, message VA_ARGS(__VA_ARGS__))
#define KRYS_CRITICAL(message, ...) Logger::Log(LogLevel::Fatal, message VA_ARGS(__VA_ARGS__))
#else
#define KRYS_LOG(message, ...)
#define KRYS_DEBUG(message, ...)
#define KRYS_INFO(message, ...)
#define KRYS_WARN(message, ...)
#define KRYS_ERROR(message, ...)
#define KRYS_CRITICAL(message, ...)
#endif
// -------- LOGGING ---------

// -------- ASSERTS ---------
#ifdef KRYS_ENABLE_ASSERTS
#define KRYS_ASSERT(condition, format, ...)    \
  do                                           \
  {                                            \
    if (!(condition))                          \
    {                                          \
      KRYS_ERROR(format VA_ARGS(__VA_ARGS__)); \
      KRYS_DEBUG_BREAK();                      \
    }                                          \
  } while (false)
#else
#define KRYS_ASSERT(condition, format, ...)
#endif
// -------- ASSERTS ---------

// ------- MISC/UTILS -------
#define VA_ARGS(...) , ##__VA_ARGS__
#define BIT(x) (1 << x)
#define Kilobytes(value) ((value) * 1024)
#define Megabytes(value) (Kilobytes(value) * 1024)
#define Gigabytes(value) (Megabytes(value) * 1024)
#define KRYS_BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// ------- MISC/UTILS -------