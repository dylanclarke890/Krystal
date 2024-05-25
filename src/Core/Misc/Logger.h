#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <mutex>

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

    static void Log(const char *format, ...);
    static void Log(LogLevel level, const char *format, ...);
    static void SetLogLevel(LogLevel level);
    static LogLevel GetLogLevel();

  private:
    static std::mutex mu;
    static std::ofstream logFile;
    static LogLevel logLevel;

    static std::string FormatLogMessage(const char *message);
    static void Output(std::string message);

    static const char *ToString(LogLevel level);
  };
}