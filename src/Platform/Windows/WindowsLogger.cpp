#include <windows.h>
#include "Logging/Logger.h"

namespace Krys
{
  // Static member initialization
  std::mutex Logger::mu;
  std::ofstream Logger::logFile("log.txt"); // Created in cwd

  void Logger::Log(LogLevel level, const std::string &message)
  {
    std::lock_guard<std::mutex> lock(mu);
    auto logMessage = FormatMessage(level, message);
    Output(logMessage);
  }

  std::string Logger::FormatMessage(LogLevel level, const std::string &message)
  {
    std::ostringstream ss;
    ss << ToString(level) << ": " << message << "\n";
    return ss.str();
  }

  void Logger::Output(const std::string &message)
  {
    OutputDebugStringA(message.c_str());
    if (logFile.is_open())
      logFile << message;
  }

  std::string Logger::ToString(LogLevel level)
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