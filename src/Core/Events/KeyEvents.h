#pragma once

#include "Events.h"
#include "Input/KeyCodes.h"

namespace Krys
{
  class KeyEvent : public Event
  {
  public:
    KeyCode Key;
    bool Ctrl, Shift, Alt;

    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
  };

  class KeyPressedEvent : public KeyEvent
  {
  public:
    bool Repeat;
    KeyPressedEvent() = default;

    EVENT_CLASS_TYPE(KeyPressed)
  };

  class KeyReleasedEvent : public KeyEvent
  {
  public:
    EVENT_CLASS_TYPE(KeyReleased)
  };
}