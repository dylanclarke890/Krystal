#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>

#include "Types.h"

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
    static std::mutex mu;
    static std::ofstream logFile;
    static LogLevel logLevel;

    static string FormatLogMessage(const string &message);
    static void Output(const string &message);

    static string ToString(LogLevel level);
  };
}