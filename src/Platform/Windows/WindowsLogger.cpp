#include <windows.h> // For OutputDebugStringA
#include <cstdarg>   // For va_list and related operations
#include <cstdio>    // For vsnprintf
#include "Logging/Logger.h"

namespace Krys
{
  // Static member initialization
  std::mutex Logger::mu;
  std::ofstream Logger::logFile("log.txt"); // Created in cwd
  LogLevel Logger::logLevel = LogLevel::Info;
  
  // TODO: consider an overload that's templated for formatting strings at some point.
  void Logger::Log(const char *format, ...)
  {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::lock_guard<std::mutex> lock(mu);
    auto logMessage = FormatLogMessage(buffer);
    Output(logMessage);
  }

  void Logger::SetLogLevel(LogLevel level)
  {
    logLevel = level;
  }

  LogLevel Logger::GetLogLevel()
  {
    return logLevel;
  }

  const char *Logger::FormatLogMessage(const char *message)
  {
    std::ostringstream ss;
    ss << ToString(logLevel) << ": " << message << "\n";
    return ss.str().c_str();
  }

  void Logger::Output(const char *message)
  {
    OutputDebugStringA(message);
    if (logFile.is_open())
      logFile << message;
  }

  const char *Logger::ToString(LogLevel level)
  {
    switch (level)
    {
    case LogLevel::Debug:
      return "[DEBUG]";
    case LogLevel::Info:
      return "[INFO]";
    case LogLevel::Warning:
      return "[WARNING]";
    case LogLevel::Error:
      return "[ERROR]";
    case LogLevel::Fatal:
      return "[FATAL]";
    default:
      return "[UNKNOWN]";
    }
  }
}