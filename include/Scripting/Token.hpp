#pragma once

#include "Base/Types.hpp"
#include "Scripting/TokenType.hpp"

namespace Krys::Scripting
{
  class Token
  {
  public:
    Token(TokenType type, const string &lexeme, uint32 line) noexcept
        : _type(type), _lexeme(lexeme), _line(line)
    {
    }

    TokenType GetType() const noexcept
    {
      return _type;
    }

    const string &GetLexeme() const noexcept
    {
      return _lexeme;
    }

    uint32 GetLine() const noexcept
    {
      return _line;
    }

  private:
    TokenType _type;
    string _lexeme;
    uint32 _line;
  };
}