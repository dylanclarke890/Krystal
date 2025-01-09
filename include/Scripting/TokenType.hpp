#pragma once

namespace Krys::Scripting
{
  enum class TokenType
  {
    // Single-character tokens.
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Minus,
    Plus,
    Semicolon,
    Slash,
    Star,

    // One or two character tokens.
    Bang,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,

    // Literals.
    Identifier,
    String,
    Number,

    // Keywords.
    And,
    Class,
    If,
    Else,
    True,
    False,
    Func,
    For,
    Null,
    Or,
    Print,
    Return,
    Super,
    This,
    Var,
    While,

    Eof
  };
}