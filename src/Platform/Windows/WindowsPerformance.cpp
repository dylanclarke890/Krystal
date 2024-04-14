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
      Logger::Log(LogLevel::Fatal, "QueryPerformanceCounter failed: %s", GetLastError());

    return ticks.QuadPart;
  }
}