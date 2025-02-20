#pragma once

#include "Base/Types.hpp"

#include <format>

namespace Krys
{
  /// @brief The state of a key during an interaction.
  enum class KeyState : uint8
  {
    Pressed,
    Held,
    Released
  };

  /// @brief Supported keyboard keys.
  enum class Key : uint32
  {
    UNKNOWN,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    EQUAL,
    MINUS,
    RIGHT_BRACKET,
    LEFT_BRACKET,
    QUOTE,
    SEMI_COLON,
    BACKSLASH,
    COMMA,
    SLASH,
    PERIOD,
    GRAVE,
    KEYPAD_DECIMAL,
    KEYPAD_MULTIPLY,
    KEYPAD_PLUS,
    KEYPAD_CLEAR,
    KEYPAD_DIVIDE,
    KEYPAD_ENTER,
    KEYPAD_MINUS,
    KEYPAD_EQUALS,
    KEYPAD_0,
    KEYPAD_1,
    KEYPAD_2,
    KEYPAD_3,
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_6,
    KEYPAD_7,
    KEYPAD_8,
    KEYPAD_9,
    RETURN,
    TAB,
    SPACE,
    DEL,
    ESCAPE,
    COMMAND,
    SHIFT,
    CAPS_LOCK,
    OPTION,
    CONTROL,
    RIGHT_SHIFT,
    RIGHT_OPTION,
    RIGHT_CONTROL,
    FUNCTION,
    VOLUME_UP,
    VOLUME_DOWN,
    MUTE,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    HELP,
    HOME,
    FORWARD_DELETE,
    END,
    PAGE_UP,
    PAGE_DOWN,
    LEFT_ARROW,
    RIGHT_ARROW,
    DOWN_ARROW,
    UP_ARROW,
  };
}

template <>
struct std::formatter<Krys::Key>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(const Krys::Key &key, std::format_context &ctx) const
  {
    return std::format_to(ctx.out(), "{}", static_cast<Krys::uint32>(key));
  }
};

template <>
struct std::formatter<Krys::KeyState>
{
  constexpr auto parse(std::format_parse_context &ctx)
  {
    return ctx.begin();
  }

  auto format(const Krys::KeyState &state, std::format_context &ctx) const
  {
    return std::format_to(ctx.out(), "{}", static_cast<Krys::uint32>(state));
  }
};