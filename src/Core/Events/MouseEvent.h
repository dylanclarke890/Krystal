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
    // TODO: deltaX and deltaY?
  public:
    MouseMoveEvent() = default;
    EVENT_CLASS_TYPE(MouseMoved)
  };

  class MouseButtonEvent : public MouseEvent
  {
    // TODO: double click?
  public:
    MouseButtonEvent(MouseButton button) : Button(button) {}
    MouseButton Button;
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

  class MouseScrollEvent : public MouseEvent
  {
  public:
    int DeltaZ;
    EVENT_CLASS_TYPE(MouseScrolled)
  };
}
