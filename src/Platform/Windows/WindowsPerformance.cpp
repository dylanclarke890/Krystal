#include <windows.h>

#include "Core.h"
#include "Misc/Performance.h"

namespace Krys
{
  bool Performance::PerformanceCounterFrequencyQueried = false;
  int64 Performance::PerformanceCounterFrequency = 0;

  int64 Performance::GetTicks()
  {
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
      // This will never happen on Windows XP and later
      KRYS_CRITICAL("QueryPerformanceCounter failed: %s", GetLastError());

    return ticks.QuadPart;
  }

  int64 Performance::GetTickFrequency()
  {
    if (PerformanceCounterFrequencyQueried)
      return PerformanceCounterFrequency;

    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency))
      // This will never happen on Windows XP and later
      KRYS_CRITICAL("QueryPerformanceFrequency failed: %s", GetLastError());

    PerformanceCounterFrequencyQueried = true;
    PerformanceCounterFrequency = frequency.QuadPart;

    return PerformanceCounterFrequency;
  }

  uint64 Performance::GetCpuCycles()
  {
    return __rdtsc();
  }

  float Performance::TicksToMilliseconds(int64 ticks)
  {
    float ms = static_cast<float>(ticks) * 1000.0f / static_cast<float>(GetTickFrequency());
    return ms <= 0 ? 1 : ms;
  }
}