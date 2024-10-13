#include <windows.h>

#include "Core.h"
#include "Core/Misc/Performance.h"

namespace Krys
{
  bool Performance::_performanceCounterFrequencyQueried = false;
  int64 Performance::_performanceCounterFrequency = 0;

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
    if (_performanceCounterFrequencyQueried)
      return _performanceCounterFrequency;

    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency))
      // This will never happen on Windows XP and later
      KRYS_CRITICAL("QueryPerformanceFrequency failed: %s", GetLastError());

    _performanceCounterFrequencyQueried = true;
    _performanceCounterFrequency = frequency.QuadPart;

    return _performanceCounterFrequency;
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