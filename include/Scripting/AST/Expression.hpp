#pragma once

#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Scripting/Token.hpp"

namespace Krys::Scripting
{
  class Binary;
  class Grouping;
  class Literal;
  class Unary;

  class Visitor
  {
  public:
    virtual ~Visitor() noexcept = default;

    virtual void VisitBinary(const Binary &binary) const noexcept = 0;
    virtual void VisitGrouping(const Grouping &grouping) const noexcept = 0;
    virtual void VisitLiteral(const Literal &literal) const noexcept = 0;
    virtual void VisitUnary(const Unary &unary) const noexcept = 0;
  };

  class Expression
  {
  public:
    virtual ~Expression() noexcept = default;

    virtual void Accept(const Visitor &visitor) const noexcept = 0;
  };

  class Binary : public Expression
  {
  public:
    Binary(Unique<Expression> left, Token op, Unique<Expression> right) noexcept
        : _left(std::move(left)), _operator(std::move(op)), _right(std::move(right))
    {
    }

    void Accept(const Visitor &visitor) const noexcept override
    {
      visitor.VisitBinary(*this);
    }

  private:
    Unique<Expression> _left;
    Token _operator;
    Unique<Expression> _right;
  };

  class Grouping : public Expression
  {
  public:
    Grouping(Unique<Expression> expression) noexcept : _expression(std::move(expression))
    {
    }

    void Accept(const Visitor &visitor) const noexcept override
    {
      visitor.VisitGrouping(*this);
    }

  private:
    Unique<Expression> _expression;
  };

  class Literal : public Expression
  {
  public:
    Literal(Token value) noexcept : _value(std::move(value))
    {
    }

    void Accept(const Visitor &visitor) const noexcept override
    {
      visitor.VisitLiteral(*this);
    }

  private:
    Token _value;
  };

  class Unary : public Expression
  {
  public:
    Unary(Token op, Unique<Expression> right) noexcept : _operator(std::move(op)), _right(std::move(right))
    {
    }

    void Accept(const Visitor &visitor) const noexcept override
    {
      visitor.VisitUnary(*this);
    }

  private:
    Token _operator;
    Unique<Expression> _right;
  };
}