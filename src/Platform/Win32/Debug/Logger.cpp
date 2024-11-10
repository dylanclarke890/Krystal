#include "Core/Debug/Logger.hpp"
#include <cstdarg>
#include <cstdio>
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Krys::Debug
{
  std::mutex Logger::_mu;
  std::ofstream Logger::_logFile("engine-log.txt");

  void Logger::Log(LogLevel level, const char *message, ...) noexcept
  {
    char buffer[1'024];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);
    string fullMessage = ToString(level) + ": " + string(buffer) + "\n";

    std::lock_guard<std::mutex> lock(_mu);

    ::OutputDebugStringA(fullMessage.c_str());
    if (_logFile.is_open())
      _logFile << fullMessage;
  }
}