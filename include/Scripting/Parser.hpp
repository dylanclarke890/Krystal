#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Macros.hpp"
#include "IO/Concepts.hpp"

#include <format>

namespace Krys::Lang
{
  template <IO::IsDataSourceT TSource, IO::IsDataSinkT TSink>
  class Parser
  {
  public:
    explicit constexpr Parser(TSource &source, TSink &sink) noexcept
        : _source(source), _sink(sink), _lookAhead(0)
    {
    }

    ~Parser() noexcept = default;
    constexpr Parser(const Parser &) = delete;
    constexpr Parser &operator=(const Parser &) = delete;

    constexpr void Parse() noexcept
    {
      _source.Open();
      _sink.Open();

      NextChar();
      Expression();

      _source.Close();
      _sink.Close();
    }

  private:
#pragma region Helpers
    constexpr void Expected(const string &msg) noexcept
    {
      KRYS_ASSERT(false, "Parsing failed - %s expected", msg.c_str());
    }

    constexpr void Expected(const uchar c) noexcept
    {
      KRYS_ASSERT(false, "Parsing failed - '%c' expected", c);
    }

    constexpr void NextChar() noexcept
    {
      _lookAhead = _source.template Read<uchar>();
    }

    constexpr void Match(const uchar c) noexcept
    {
      if (_lookAhead == c)
        NextChar();
      else
        Expected(c);
    }

    NO_DISCARD constexpr bool IsAlpha() const noexcept
    {
      return (_lookAhead >= 'a' && _lookAhead <= 'z') || (_lookAhead >= 'A' && _lookAhead <= 'Z');
    }

    NO_DISCARD constexpr bool IsDigit() const noexcept
    {
      return _lookAhead >= '0' && _lookAhead <= '9';
    }

    NO_DISCARD constexpr bool IsAddop(const uchar c) const noexcept
    {
      return c == '+' || c == '-';
    }

    NO_DISCARD constexpr bool IsMulop(const uchar c) const noexcept
    {
      return c == '*' || c == '/';
    }

    NO_DISCARD constexpr uchar ToUpper(const uchar c) const noexcept
    {
      return c >= 'a' && c <= 'z' ? c - 32 : c;
    }

    NO_DISCARD constexpr uchar GetName() noexcept
    {
      if (!IsAlpha())
        Expected("Name");

      auto c = ToUpper(_lookAhead);
      NextChar();

      return c;
    }

    NO_DISCARD constexpr uchar GetNum() noexcept
    {
      if (!IsDigit())
        Expected("Integer");

      auto c = _lookAhead;
      NextChar();

      return c;
    }

#pragma endregion Helpers

#pragma region Expressions
    void Add() noexcept
    {
      Match('+');
      Term();
      EmitLn("ADD D1, (SP)+");
    }

    void Subtract() noexcept
    {
      Match('-');
      Term();
      EmitLn("SUB D1, (SP)+");
      EmitLn("NEG D0");
    }

    void Multiply() noexcept
    {
      Match('*');
      Factor();
      EmitLn("MULS (SP)+, D0");
    }

    void Divide() noexcept
    {
      Match('/');
      Factor();
      EmitLn("MOVE (SP)+, D1");
      EmitLn("DIVS D1, D0");
    }

    void Factor() noexcept
    {
      if (_lookAhead == '(')
      {
        Match('(');
        Expression();
        Match(')');
      }
      else
      {
        EmitLn(Format("MOVE #{:c}, D0", GetNum()));
      }
    }

    void Term() noexcept
    {
      Factor();
      while (_lookAhead == '*' || _lookAhead == '/')
      {
        EmitLn("MOVE D0, D1");
        switch (_lookAhead)
        {
          case '*': Multiply(); break;
          case '/': Divide(); break;
          default:  Expected("mulop"); break;
        }
      }
    }

    void Expression() noexcept
    {
      if (IsAddop(_lookAhead))
        EmitLn("CLR D0");
      else
        Term();
      EmitLn("MOVE D0, -(SP)");
      while (IsAddop(_lookAhead))
      {
        switch (_lookAhead)
        {
          case '+': Add(); break;
          case '-': Subtract(); break;
          default:  Expected("addop"); break;
        }
      }
    }

#pragma endregion Expressions

#pragma region Output

    constexpr void Emit(uchar c) noexcept
    {
      _sink.template Write<uchar>(c);
    }

    constexpr void EmitLn(uchar c) noexcept
    {
      Emit(c);
      Emit('\n');
    }

    constexpr void Emit(const string &str) noexcept
    {
      _sink.Write(str);
    }

    constexpr void EmitLn(const string &str) noexcept
    {
      Emit(str);
      Emit('\n');
    }

    template <typename... Args>
    string Format(stringview fmt, Args &&...args)
    {
      return std::vformat(fmt, std::make_format_args(args...));
    }

#pragma endregion Output

  private:
    TSource &_source;
    TSink &_sink;
    uchar _lookAhead;
  };
}