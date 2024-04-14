#pragma once

#include "Krystal.h"
#include "Logging/Logger.h"

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
    static float ToMilliseconds(int64 ticks);
  };

  class PerformanceTimer
  {
  private:
    const char *name;
    int64 startCycle;
    int64 startCounter;

  public:
    PerformanceTimer(const char *name)
        : name(name), startCycle(Performance::GetCpuCycles()), startCounter(Performance::GetTicks()) {}
    ~PerformanceTimer()
    {
      int64 endCycle = Performance::GetCpuCycles();
      int64 endCounter = Performance::GetTicks();
      int64 tickFrequency = Performance::GetTickFrequency();

      int64 cyclesElapsed = endCycle - startCycle;
      int64 counterElapsed = endCounter - startCounter;
      if (counterElapsed <= 0)
        counterElapsed = 1;

      float64 msPerFrame = (((1000.0f * (float64)counterElapsed) / (float64)tickFrequency));
      float64 fps = (float64)tickFrequency / (float64)counterElapsed;
      float64 megaCyclesPerFrame = ((float64)cyclesElapsed / (1000.0f * 1000.0f));

      Logger::Log(LogLevel::Info, "%s: %.02fms/f,  %.02ff/s,  %.02fmc/f\n",
                  name, msPerFrame, fps, megaCyclesPerFrame);
    }
  };
}