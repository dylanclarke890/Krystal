#pragma once

#include "Base/Types.hpp"
#include "Scripting/ErrorReporter.hpp"
#include "Scripting/Token.hpp"

namespace Krys::Scripting
{
  class Parser
  {
  public:
    Parser(const List<Token> &tokens, const ErrorReporter &errorReporter) noexcept
        : _tokens(tokens), _current(0), _errorReporter(errorReporter)
    {
    }

    void Parse() noexcept
    {
    }

  private:
    List<Token> _tokens;
    uint32 _current;
    const ErrorReporter &_errorReporter;
  };
}