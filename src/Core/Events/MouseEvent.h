#pragma once

#include "Events/Events.h"

namespace Krys
{
  class MouseEvent : public Event
  {
  public:
    int X, Y;
    bool Ctrl, Shift, Alt;
    uint32 Buttons;

    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  };

  class MouseMoveEvent : public MouseEvent
  {
  public:
    MouseMoveEvent() = default;
    EVENT_CLASS_TYPE(MouseMoved)
  };

  class MouseButtonEvent : public MouseEvent
  {
  public:
    MouseButtonEvent(MouseButton button) : Button(button) {}
    int Button;
  };

  class MouseButtonPressedEvent : public MouseButtonEvent
  {
  public:
    MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MousePressed)
  };

  class MouseButtonReleasedEvent : public MouseButtonEvent
  {
  public:
    MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MouseReleased)
  };
}
