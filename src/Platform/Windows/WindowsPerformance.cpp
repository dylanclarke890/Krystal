#include <windows.h>

#include "Krystal.h"
#include "Logging/Logger.h"
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
      Logger::Log(LogLevel::Fatal, "QueryPerformanceCounter failed: %s", GetLastError());

    return ticks.QuadPart;
  }

  int64 Performance::GetTickFrequency()
  {
    if (PerformanceCounterFrequencyQueried)
      return PerformanceCounterFrequency;

    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency))
      // This will never happen on Windows XP and later
      Logger::Log(LogLevel::Fatal, "QueryPerformanceFrequency failed: %s", GetLastError());

    PerformanceCounterFrequencyQueried = true;
    PerformanceCounterFrequency = frequency.QuadPart;

    return PerformanceCounterFrequency;
  }

  uint64 Performance::GetCpuCycles()
  {
    return __rdtsc();
  }
}