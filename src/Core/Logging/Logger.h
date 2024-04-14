#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <fstream>

#include "LogLevel.h"

namespace Krys
{
  class Logger
  {
  public:
    Logger() = default;
    ~Logger() = default;

    static void Log(LogLevel level, const std::string &message);

  private:
    static std::mutex mu;
    static std::ofstream logFile;

    static std::string FormatMessage(LogLevel level, const std::string &message);
    static void Output(const std::string &message);

    static std::string ToString(LogLevel level);
  };
}