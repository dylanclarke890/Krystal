#pragma once

#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"

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
      KRYS_LOG("[line %d] Error %s: %s", line, where.c_str(), message.c_str());
      // KRYS_ASSERT(false, "Error while running file", 0);
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