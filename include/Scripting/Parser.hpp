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
  constexpr uchar Newline = '\r';

  template <IO::IsDataSourceT TSource, IO::IsDataSinkT TSink>
  class Parser
  {
  public:
    explicit constexpr Parser(TSource &source, TSink &sink) noexcept : _source(source), _sink(sink), _next(0)
    {
    }

    ~Parser() noexcept = default;
    constexpr Parser(const Parser &) = delete;
    constexpr Parser &operator=(const Parser &) = delete;

    constexpr void Parse() noexcept
    {
      _source.Open();
      _sink.Open();

      LoadNextChar();
      Assignment();
      if (_next != Newline)
        Expected("Newline");

      _source.Close();
      _sink.Close();
    }

  private:
    constexpr void LoadNextChar() noexcept
    {
      _next = _source.template Read<uchar>();
    }

    constexpr void Match(const uchar c) noexcept
    {
      if (_next == c)
        LoadNextChar();
      else
        Expected(c);
    }

#pragma region Helpers

    constexpr void Expected(const string &msg) const noexcept
    {
      KRYS_ASSERT(false, "Parsing failed - %s expected", msg.c_str());
    }

    constexpr void Expected(const uchar c) const noexcept
    {
      KRYS_ASSERT(false, "Parsing failed - '%c' expected", c);
    }

    NO_DISCARD constexpr bool IsAlpha(uchar c) const noexcept
    {
      return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    NO_DISCARD constexpr bool IsDigit(uchar c) const noexcept
    {
      return c >= '0' && c <= '9';
    }

    NO_DISCARD constexpr bool IsAlphaNumeric(uchar c) const noexcept
    {
      return IsAlpha(c) || IsDigit(c);
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
      if (!IsAlpha(_next))
        Expected("Name");

      uchar c = ToUpper(_next);
      LoadNextChar();

      return c;
    }

    NO_DISCARD constexpr uchar GetNum() noexcept
    {
      if (!IsDigit(_next))
        Expected("Integer");

      uchar c = _next;
      LoadNextChar();

      return c;
    }

#pragma endregion Helpers

#pragma region Operations

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

#pragma endregion Operations

#pragma region Expressions

    void Identifier() noexcept
    {
      auto name = GetName();
      if (_next == '(')
      {
        Match('(');
        Match(')');
        EmitLn(Format("BSR {:c}", name));
      }
      else
        EmitLn(Format("MOVE {:c}(PC), D0", name));
    }

    void Factor() noexcept
    {
      if (_next == '(')
      {
        Match('(');
        Expression();
        Match(')');
      }
      else if (IsAlpha(_next))
        Identifier();
      else
        EmitLn(Format("MOVE #{:c}, D0", GetNum()));
    }

    void Term() noexcept
    {
      Factor();
      while (IsMulop(_next))
      {
        EmitLn("MOVE D0, D1");
        switch (_next)
        {
          case '*': Multiply(); break;
          case '/': Divide(); break;
          default:  Expected("mulop"); break; // can't be reached
        }
      }
    }

    void Expression() noexcept
    {
      if (IsAddop(_next))
        EmitLn("CLR D0");
      else
        Term();
      EmitLn("MOVE D0, -(SP)");
      while (IsAddop(_next))
      {
        switch (_next)
        {
          case '+': Add(); break;
          case '-': Subtract(); break;
          default:  Expected("addop"); break; // can't be reached
        }
      }
    }

    void Assignment() noexcept
    {
      uchar name = GetName();
      Match('=');
      Expression();
      EmitLn(Format("LEA {:c}(PC), A0", name));
      EmitLn("MOVE D0, (A0)");
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

    /// @brief Lookahead character.
    uchar _next;
  };
}