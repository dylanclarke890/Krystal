#pragma once

#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Logger.hpp"
#include "IO/IO.hpp"
#include "Scripting/ErrorReporter.hpp"
#include "Scripting/Scanner.hpp"

namespace Krys::Scripting
{
  class Syrk
  {
  public:
    Syrk() noexcept = default;
    ~Syrk() noexcept = default;

    void Run(const string &source) noexcept
    {
      Scanner scanner(source, _errorReporter);
      auto tokens = scanner.ScanTokens();
      for (const auto &token : tokens)
      {
        Logger::Info("Token: {0}", token.GetLexeme());
      }
    }

    void RunFile(const string &path) noexcept
    {
      string source = IO::ReadFileText(path);
      Run(source);
      KRYS_ASSERT(_errorReporter.Success(), "Error while running file", 0);
    }

  private:
    ErrorReporter _errorReporter;
  };
}