#include <windows.h>

#include "Krystal.h"
#include "Logging/Logger.h"
#include "Misc/Performance.h"

namespace Krys
{
  int64 Performance::GetTicks()
  {
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
      auto currentLevel = Logger::GetLogLevel();
      Logger::SetLogLevel(LogLevel::Fatal);
      Logger::Log("QueryPerformanceCounter failed: %s", GetLastError());
      Logger::SetLogLevel(currentLevel);
    }

    return ticks.QuadPart;
  }
}