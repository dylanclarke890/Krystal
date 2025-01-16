#include "Core/Debug/Macros.hpp"
#include "Core/Platform.hpp"
#include "Utils/Lazy.hpp"

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Krys::Platform
{
  void Sleep(uint32 milliseconds) noexcept
  {
    ::Sleep(milliseconds);
  }

  int64 GetTicks() noexcept
  {
    LARGE_INTEGER ticks;
    KRYS_ASSERT_ALWAYS_EVAL(QueryPerformanceCounter(&ticks), "QueryPerformanceCounter failed");
    return ticks.QuadPart;
  }

  int64 GetTickFrequency() noexcept
  {
    static Lazy<uint64> frequency(
      []()
      {
        LARGE_INTEGER freq;
        KRYS_ASSERT_ALWAYS_EVAL(QueryPerformanceFrequency(&freq), "QueryPerformanceFrequency failed");
        return freq.QuadPart;
      });

    return frequency.val();
  }

  uint64 GetCpuCycles() noexcept
  {
    return __rdtsc();
  }

  float TicksToMilliseconds(int64 ticks) noexcept
  {
    float ms = static_cast<float>(ticks) * 1000.0f / static_cast<float>(GetTickFrequency());
    return ms <= 0.0f ? 1.0f : ms;
  }
}