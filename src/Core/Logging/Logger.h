#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>

#include "LogLevel.h"

namespace Krys
{
  class Logger
  {
  public:
    Logger() = delete;
    Logger(Logger&) = delete;
    ~Logger() = delete;

    static void Log(const char *format, ...);
    static void Log(LogLevel level, const char *format, ...);
    static void SetLogLevel(LogLevel level);
    static LogLevel GetLogLevel();

  private:
    static std::mutex mu;
    static std::ofstream logFile;
    static LogLevel logLevel;

    static const char *FormatLogMessage(const char *message);
    static void Output(const char *message);

    static const char *ToString(LogLevel level);
  };
}