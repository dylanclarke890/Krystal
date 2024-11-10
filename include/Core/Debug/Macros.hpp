#pragma once

#include "Base/Defines.hpp"

#ifdef KRYS_ENABLE_PROFILING
  #include "Core/Debug/ScopedProfiler.hpp"
  #define UNIQUE_PROFILER_NAME(prefix) CONCATENATE(prefix, __LINE__)
  #define KRYS_SCOPED_PROFILER(name) Krys::Debug::ScopedProfiler UNIQUE_PROFILER_NAME(profiler_)(name)
#else
  #define KRYS_SCOPED_PROFILER(name)
#endif