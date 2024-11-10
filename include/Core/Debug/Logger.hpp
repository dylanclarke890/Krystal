#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

#include "Base/Macros.hpp"
#include "Base/Types.hpp"

namespace Krys::Debug
{
  enum class LogLevel
  {
    Debug,
    Info,
    Error,
    Fatal
  };

  inline string ToString(LogLevel level)
  {
    switch (level)
    {
      case LogLevel::Debug: return "[DEBUG]";
      case LogLevel::Info:  return "[INFO_]";
      case LogLevel::Error: return "[ERROR]";
      case LogLevel::Fatal: return "[FATAL]";
      default:              return "[UNDEF]";
    }
  }

  class Logger
  {
  public:
    STATIC_CLASS(Logger)

    static void Log(LogLevel level, const char *message, ...) noexcept;

  private:
    static std::mutex _mu;
    static std::ofstream _logFile;
  };
}