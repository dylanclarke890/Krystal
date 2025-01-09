#pragma once

#include "Base/Types.hpp"
#include "Scripting/ErrorReporter.hpp"
#include "Scripting/Token.hpp"
#include "Scripting/Utils.hpp"

namespace Krys::Scripting
{
  class Scanner
  {
  public:
    Scanner(const string &source, const ErrorReporter &errorReporter) noexcept
        : _source(source), _start(0), _current(0), _line(1), _errorReporter(errorReporter)
    {
    }

    List<Token> ScanTokens() noexcept
    {
      while (!IsAtEnd())
      {
        _start = _current;
        ScanToken();
      }

      _tokens.push_back(Token(TokenType::Eof, "[EOF-MARKER]", _line));
      return _tokens;
    }

  private:
    void ScanToken() noexcept
    {
      char c = Advance();

      switch (c)
      {
        case '(': _tokens.push_back(Token(TokenType::LeftParen, "(", _line)); break;
        case ')': _tokens.push_back(Token(TokenType::RightParen, ")", _line)); break;
        case '{': _tokens.push_back(Token(TokenType::LeftBrace, "{", _line)); break;
        case '}': _tokens.push_back(Token(TokenType::RightBrace, "}", _line)); break;
        case ',': _tokens.push_back(Token(TokenType::Comma, ",", _line)); break;
        case '.': _tokens.push_back(Token(TokenType::Dot, ".", _line)); break;
        case '-': _tokens.push_back(Token(TokenType::Minus, "-", _line)); break;
        case '+': _tokens.push_back(Token(TokenType::Plus, "+", _line)); break;
        case ';': _tokens.push_back(Token(TokenType::Semicolon, ";", _line)); break;
        case '*': _tokens.push_back(Token(TokenType::Star, "*", _line)); break;
        case '!':
          _tokens.push_back(Match('=') ? Token(TokenType::BangEqual, "!=", _line)
                                       : Token(TokenType::Bang, "!", _line));
          break;
        case '=':
          _tokens.push_back(Match('=') ? Token(TokenType::EqualEqual, "==", _line)
                                       : Token(TokenType::Equal, "=", _line));
          break;
        case '<':
          _tokens.push_back(Match('=') ? Token(TokenType::LessEqual, "<=", _line)
                                       : Token(TokenType::Less, "<", _line));
          break;
        case '>':
          _tokens.push_back(Match('=') ? Token(TokenType::GreaterEqual, ">=", _line)
                                       : Token(TokenType::Greater, ">", _line));
          break;
        case '/':  Slash(); break;

        case ' ':
        case '\r':
        case '\t': break;
        case '\n': _line++; break;

        case '"':  String(); break;
        default:
          if (IsIdentifierPrefix(c))
            Identifier();
          else if (IsDigit(c))
            Number();
          else
            _errorReporter.Error(_line, "Unexpected character.");
          break;
      }
    }

    void Identifier() noexcept
    {
      while (IsIdentifier(Peek()))
        Advance();

      const string text = _source.substr(_start, _current - _start);
      if (_keywords.contains(text))
        _tokens.push_back(Token(_keywords[text], text, _line));
      else
        _tokens.push_back(Token(TokenType::Identifier, text, _line));
    }

    void Number() noexcept
    {
      while (IsDigit(Peek()))
        Advance();

      if (Peek() == '.' && IsDigit(PeekNext()))
      {
        Advance();
        while (IsDigit(Peek()))
          Advance();
      }

      _tokens.push_back(Token(TokenType::Number, _source.substr(_start, _current - _start), _line));
    }

    void String() noexcept
    {
      while (Peek() != '"' && !IsAtEnd())
      {
        if (Peek() == '\n')
          _line++;
        Advance();
      }

      if (IsAtEnd())
      {
        _errorReporter.Error(_line, "Unterminated string.");
        return;
      }

      Advance();

      const string value = _source.substr(_start + 1, _current - _start - 2);
      _tokens.push_back(Token(TokenType::String, value, _line));
    }

    void Slash() noexcept
    {
      if (Match('/'))
        while (Peek() != '\n' && !IsAtEnd())
          Advance();
      else
        _tokens.push_back(Token(TokenType::Slash, "/", _line));
    }

#pragma region Helpers

    char Advance() noexcept
    {
      return _source[_current++];
    }

    char Peek() const noexcept
    {
      return _source[_current];
    }

    char PeekNext() const noexcept
    {
      if (_current + 1 >= _source.size())
        return '\0';
      return _source[_current + 1];
    }

    bool Match(const char expected) noexcept
    {
      if (IsAtEnd())
        return false;

      if (Peek() != expected)
        return false;

      _current++;
      return true;
    }

    bool IsAtEnd() const noexcept
    {
      return _current >= _source.size();
    }

#pragma endregion Helpers

  private:
    string _source;
    const ErrorReporter &_errorReporter;

    uint32 _start;
    uint32 _current;
    uint32 _line;
    List<Token> _tokens;
    Map<string, TokenType> _keywords {
      {"and", TokenType::And},     {"class", TokenType::Class},   {"else", TokenType::Else},
      {"false", TokenType::False}, {"for", TokenType::For},       {"func", TokenType::Func},
      {"if", TokenType::If},       {"null", TokenType::Null},     {"or", TokenType::Or},
      {"print", TokenType::Print}, {"return", TokenType::Return}, {"super", TokenType::Super},
      {"this", TokenType::This},   {"true", TokenType::True},     {"var", TokenType::Var},
      {"while", TokenType::While}};
  };
}