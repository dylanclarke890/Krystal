#pragma once

#include "Base/Detection.hpp"

// TODO: fix these
#define KRYS_ENABLE_ASSERTS 1
#define KRYS_ENABLE_LOGGING 1
#define KRYS_ENABLE_DEBUG_BREAK 1
#define KRYS_ENABLE_PERFORMANCE_CHECKS 1

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

// Resolve the best macro for a function signature, based on the compiler being used.
// Note: only gets resolved during preprocessing so your code editor may highlight the wrong one (i.e the 'else' branch)
// but should still work.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))         \
  || defined(__ghs__)
  #define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
  #define KRYS_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__) || defined(_MSC_VER)
  #define KRYS_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
  #define KRYS_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
  #define KRYS_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199'901)
  #define KRYS_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201'103)
  #define KRYS_FUNC_SIG __func__
#else
  #error "KRYS_FUNC_SIG unknown!"
#endif

#define VA_ARGS(...) , ##__VA_ARGS__
#ifdef KRYS_ENABLE_LOGGING
  #include "Core/Logger.hpp"
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

#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(condition, format, ...)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
      if (!(condition))                                                                                                \
      {                                                                                                                \
        KRYS_ERROR(format VA_ARGS(__VA_ARGS__));                                                                       \
        KRYS_DEBUG_BREAK();                                                                                            \
      }                                                                                                                \
    } while (false)
#else
  #define KRYS_ASSERT(condition, format, ...)
#endif

// Compiler-specific macros for disabling and restoring warnings
#if defined(_MSC_VER) // Microsoft Visual C++
  #define KRYS_DISABLE_WARNING_PUSH() __pragma(warning(push))
  #define KRYS_DISABLE_WARNING_POP() __pragma(warning(pop))
  #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName) __pragma(warning(disable : msvcWarningCode))
#elif defined(__GNUC__) || defined(__clang__) // GCC or Clang
  #define KRYS_DISABLE_WARNING_PUSH() _Pragma("GCC diagnostic push")
  #define KRYS_DISABLE_WARNING_POP() _Pragma("GCC diagnostic pop")
  #if defined(__clang__)
    #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)                                            \
      _Pragma("clang diagnostic ignored \"" gccWarningName "\"")
  #else
    #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)                                            \
      _Pragma("GCC diagnostic ignored \"" gccWarningName "\"")
  #endif
#else
  #define KRYS_DISABLE_WARNING_PUSH()
  #define KRYS_DISABLE_WARNING_POP()
  #define KRYS_DISABLE_WARNING(msvcWarningCode, gccWarningName)
#endif

#ifdef __INTELLISENSE__
  /// @brief Intellisense sometimes loses when parsing code with require statements.
  /// This macro hides them from intellisense while ensuring they are included when actually compiling.
  #define REQUIRES(x)
#else
  #define REQUIRES(x) requires(x)
#endif
