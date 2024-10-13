#pragma once

#include "Core.h"

namespace Krys
{
  class Performance
  {
  private:
    static bool _performanceCounterFrequencyQueried;
    static int64 _performanceCounterFrequency;

  public:
    static int64 GetTicks();
    static int64 GetTickFrequency();
    static uint64 GetCpuCycles();
    static float TicksToMilliseconds(int64 ticks);
  };

#ifdef KRYS_ENABLE_PERFORMANCE_CHECKS
  class PerformanceTimer
  {
  private:
    string _name;
    int64 _startCounter;

  public:
    PerformanceTimer(const string &name)
        : _name(name), _startCounter(Performance::GetTicks()) {}
    ~PerformanceTimer()
    {
      int64 endCounter = Performance::GetTicks();
      int64 tickFrequency = Performance::GetTickFrequency();

      int64 counterElapsed = endCounter - _startCounter;
      if (counterElapsed <= 0)
        counterElapsed = 1;

      float64 ms = (((1000.0f * (float64)counterElapsed) / (float64)tickFrequency));

      KRYS_INFO("%s took %.02fms.", _name.c_str(), ms);
    }
  };
  #endif
}