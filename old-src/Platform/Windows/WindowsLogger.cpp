#include "Core/Misc/Logger.h"
#include <cstdarg>   // For va_list and related operations
#include <cstdio>    // For vsnprintf
#include <windows.h> // For OutputDebugStringA

namespace Krys
{
  std::mutex Logger::_mu;
  std::ofstream Logger::_logFile("log.txt");
  LogLevel Logger::_logLevel = LogLevel::Info;

  void Logger::Log(const char *format, ...)
  {
    char buffer[1'024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::lock_guard<std::mutex> lock(_mu);
    auto logMessage = FormatLogMessage(buffer);
    Output(logMessage);
  }

  // TODO: combine this with the above
  void Logger::Log(LogLevel level, const char *format, ...)
  {
    auto currentLevel = Logger::GetLogLevel();
    Logger::SetLogLevel(level);
    {
      char buffer[1'024];
      va_list args;
      va_start(args, format);
      vsnprintf(buffer, sizeof(buffer), format, args);
      va_end(args);

      std::lock_guard<std::mutex> lock(_mu);
      auto logMessage = FormatLogMessage(buffer);
      Output(logMessage);
    }
    Logger::SetLogLevel(currentLevel);
  }

  void Logger::SetLogLevel(LogLevel level)
  {
    _logLevel = level;
  }

  LogLevel Logger::GetLogLevel()
  {
    return _logLevel;
  }

  string Logger::FormatLogMessage(const string &message)
  {
    std::ostringstream ss;
    ss << ToString(_logLevel) << ": " << message << "\n";
    return ss.str();
  }

  void Logger::Output(const string &message)
  {
    OutputDebugStringA(message.c_str());
    if (_logFile.is_open())
      _logFile << message;
  }

  string Logger::ToString(LogLevel level)
  {
    switch (level)
    {
      case LogLevel::Debug:   return "[DEBUG]";
      case LogLevel::Info:    return "[INFO]";
      case LogLevel::Warning: return "[WARNING]";
      case LogLevel::Error:   return "[ERROR]";
      case LogLevel::Fatal:   return "[FATAL]";
      default:                return "[UNKNOWN]";
    }
  }
}