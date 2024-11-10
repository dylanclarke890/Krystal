#pragma once

#include "Base/Defines.hpp"
#include "Base/Macros.hpp"

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

#ifdef KRYS_ENABLE_PROFILING
  #include "Core/Debug/ScopedProfiler.hpp"
  #define UNIQUE_PROFILER_NAME(prefix) CONCATENATE(prefix, __LINE__)
  #define KRYS_SCOPED_PROFILER(name) Krys::Debug::ScopedProfiler UNIQUE_PROFILER_NAME(profiler_)(name)
#else
  #define KRYS_SCOPED_PROFILER(name)
#endif

#ifdef KRYS_ENABLE_LOGGING
  #include "Core/Debug/Logger.hpp"
  #define KRYS_LOG(message, ...)                                                                             \
    Krys::Debug::Logger::Log(Krys::Debug::LogLevel::Info, message VA_ARGS(__VA_ARGS__))
  #define KRYS_DEBUG(message, ...)                                                                           \
    Krys::Debug::Logger::Log(Krys::Debug::LogLevel::Debug, message VA_ARGS(__VA_ARGS__))
  #define KRYS_INFO(message, ...)                                                                            \
    Krys::Debug::Logger::Log(Krys::Debug::LogLevel::Info, message VA_ARGS(__VA_ARGS__))
  #define KRYS_ERROR(message, ...)                                                                           \
    Krys::Debug::Logger::Log(Krys::Debug::LogLevel::Error, message VA_ARGS(__VA_ARGS__))
  #define KRYS_FATAL(message, ...)                                                                           \
    Krys::Debug::Logger::Log(Krys::Debug::LogLevel::Fatal, message VA_ARGS(__VA_ARGS__))
#else
  #define KRYS_LOG(message, ...)
  #define KRYS_DEBUG(message, ...)
  #define KRYS_INFO(message, ...)
  #define KRYS_ERROR(message, ...)
  #define KRYS_CRITICAL(message, ...)
#endif

#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(condition, format, ...)                                                                \
    do                                                                                                       \
    {                                                                                                        \
      if (!(condition))                                                                                      \
      {                                                                                                      \
        KRYS_ERROR(format VA_ARGS(__VA_ARGS__));                                                             \
        KRYS_DEBUG_BREAK();                                                                                  \
      }                                                                                                      \
    } while (false)
#else
  #define KRYS_ASSERT(condition, format, ...)
#endif
