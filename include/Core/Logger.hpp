#pragma once

#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"

namespace Krys
{
  enum class LogLevel
  {
    Debug,
    Info,
    Error,
    Fatal
  };

  NO_DISCARD constexpr inline string ToString(LogLevel level)
  {
    switch (level)
    {
      case LogLevel::Debug: return "[DEBUG]";
      case LogLevel::Info:  return "[INFO ]";
      case LogLevel::Error: return "[ERROR]";
      case LogLevel::Fatal: return "[FATAL]";
      default:              return "[UNDEF]";
    }
  }

  class Logger
  {
  public:
    STATIC_CLASS(Logger)

    template <typename... Args>
    static void Info(const string &message, Args &&...args) noexcept
    {
      Log<LogLevel::Info>(message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Debug(const string &message, Args &&...args) noexcept
    {
      Log<LogLevel::Debug>(message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Error(const string &message, Args &&...args) noexcept
    {
      Log<LogLevel::Error>(message, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Fatal(const string &message, Args &&...args) noexcept
    {
      Log<LogLevel::Fatal>(message, std::forward<Args>(args)...);
    }

  private:
    template <LogLevel level, typename... Args>
    static void Log(const string &fmt, Args &&...args) noexcept
    {
#ifdef KRYS_ENABLE_LOGGING
      string fullMessage = ToString(level) + ": " + std::vformat(fmt, std::make_format_args(args...)) + '\n';
      std::lock_guard<std::mutex> lock(_mu);
      Output(fullMessage);
#endif
    }

    static void Output(const string &message) noexcept;

    static std::mutex _mu;
    static std::ofstream _logFile;
  };
}