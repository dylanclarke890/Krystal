#pragma once

#include "Base/Detection.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "IO/Logger.hpp"

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

#ifdef KRYS_ENABLE_ASSERTS
  #define KRYS_ASSERT(condition, format, ...)                                                                \
    do                                                                                                       \
    {                                                                                                        \
      if (!(condition))                                                                                      \
      {                                                                                                      \
        Krys::Logger::Error(format VA_ARGS(__VA_ARGS__));                                                             \
        KRYS_DEBUG_BREAK();                                                                                  \
      }                                                                                                      \
    } while (false)
  #define KRYS_ASSERT_ALWAYS_EVAL(condition, format, ...)                                                    \
    do                                                                                                       \
    {                                                                                                        \
      if (!(condition))                                                                                      \
      {                                                                                                      \
        Krys::Logger::Error(format VA_ARGS(__VA_ARGS__));                                                             \
        KRYS_DEBUG_BREAK();                                                                                  \
      }                                                                                                      \
    } while (false)
#else
  #define KRYS_ASSERT(condition, format, ...)
  #define KRYS_ASSERT_ALWAYS_EVAL(condition, format, ...) (condition)
#endif
