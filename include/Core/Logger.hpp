#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

#include "Base/Types.hpp"

namespace Krys
{
  enum class LogLevel
  {
    Debug,
    Info,
    Warning,
    Error,
    Fatal
  };

  class Logger
  {
  public:
    Logger() = delete;
    Logger(Logger &) = delete;
    ~Logger() = delete;

    static void Log(const char *formatformat, ...);
    static void Log(LogLevel level, const char *formatformat, ...);
    static void SetLogLevel(LogLevel level);
    static LogLevel GetLogLevel();

  private:
    static std::mutex _mu;
    static std::ofstream _logFile;
    static LogLevel _logLevel;

    static string FormatLogMessage(const string &message);
    static void Output(const string &message);
    static string ToString(LogLevel level);
  };
}