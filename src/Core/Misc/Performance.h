#pragma once

#include "Core.h"

namespace Krys
{
  class Performance
  {
  private:
    static bool PerformanceCounterFrequencyQueried;
    static int64 PerformanceCounterFrequency;

  public:
    static int64 GetTicks();
    static int64 GetTickFrequency();
    static uint64 GetCpuCycles();
    static float TicksToMilliseconds(int64 ticks);
  };

  class PerformanceTimer
  {
  private:
    const char *name;
    int64 startCounter;

  public:
    PerformanceTimer(const char *name)
        : name(name), startCounter(Performance::GetTicks()) {}
    ~PerformanceTimer()
    {
      int64 endCounter = Performance::GetTicks();
      int64 tickFrequency = Performance::GetTickFrequency();

      int64 counterElapsed = endCounter - startCounter;
      if (counterElapsed <= 0)
        counterElapsed = 1;

      float64 ms = (((1000.0f * (float64)counterElapsed) / (float64)tickFrequency));

      KRYS_INFO("%s took %.02fms.", name, ms);
    }
  };
}