#pragma once

#include "Base/Types.hpp"
#include "Core/Logger.hpp"

namespace Krys::Scripting
{
  class ErrorReporter
  {
  public:
    void Error(uint32 line, const string &message) const noexcept
    {
      Report(line, "", message);
    }

    void Report(uint32 line, const string &where, const string &message) const noexcept
    {
      Logger::Info("[line {0}] Error {1}: {2}", line, where, message);
      // KRYS_ASSERT(false, "Error while running file");
      _hadError = true;
    }

    bool Success() const noexcept
    {
      return !_hadError;
    }

  private:
    mutable bool _hadError {false};
  };
}