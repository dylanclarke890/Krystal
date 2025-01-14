#include "Core/Logger.hpp"

#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Krys
{
  std::mutex Logger::_mu;
  std::ofstream Logger::_logFile("engine-log.txt");

  void Logger::Output(const string &message) noexcept
  {
    ::OutputDebugStringA(message.c_str());
    if (_logFile.is_open())
      _logFile << message;
  }
}