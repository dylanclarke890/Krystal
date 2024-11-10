#include "Core/Debug/ScopedProfiler.hpp"
#include "Base/Lazy.hpp"
#include "Core/Debug/Macros.hpp"

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Krys::Debug
{
  uint64 GetPerformanceFrequency() noexcept;
  static Lazy<uint64> PerformanceCounterFrequency([]() { return GetPerformanceFrequency(); });

  ScopedProfiler::ScopedProfiler(const string &name) noexcept : _start(0), _name(name)
  {
    LARGE_INTEGER start;
    QueryPerformanceCounter(&start);
    _start = static_cast<uint64>(start.QuadPart);
  }

  ScopedProfiler::~ScopedProfiler() noexcept
  {
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);

    const uint64 difference = static_cast<uint64>(end.QuadPart) - _start;
    const uint64 frequency = PerformanceCounterFrequency.val();
    const double elapsedMs = static_cast<double>(difference) / static_cast<double>(frequency) * 1000.0f;

    KRYS_LOG("%s took %.3f ms.", _name.c_str(), elapsedMs);
  }

  uint64 GetPerformanceFrequency() noexcept
  {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return static_cast<uint64>(freq.QuadPart);
  }
}