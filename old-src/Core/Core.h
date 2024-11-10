#pragma once

#include "Misc/PlatformDetection.h"
#include "Types.h"

// ------- MISC/UTILS -------
#define VA_ARGS(...) , ##__VA_ARGS__
#define BIT(x) (1 << x)
#define Kilobytes(value) ((value) * 1'024)
#define Megabytes(value) (Kilobytes(value) * 1'024)
#define Gigabytes(value) (Megabytes(value) * 1'024)
#define KRYS_BIND_EVENT_FN(fn)                                                                               \
  [this](auto &&...args) -> decltype(auto)                                                                   \
  {                                                                                                          \
    return this->fn(std::forward<decltype(args)>(args)...);                                                  \
  }

// ------- PERFORMANCE ------
#ifdef KRYS_ENABLE_PERFORMANCE_CHECKS
  #include "Misc/Performance.h"
  #define KRYS_PERFORMANCE_TIMER(name) PerformanceTimer perfTimer##__LINE__(name)
#else
  #define KRYS_PERFORMANCE_TIMER(name)
#endif
// ------- PERFORMANCE ------
