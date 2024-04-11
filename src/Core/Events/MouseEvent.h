#pragma once

#include "Events/Events.h"

class MouseEvent : public Event
{
public:
  int X, Y;
  bool Ctrl, Shift;
  uint32 Buttons;

  MouseEvent() = default;

  EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  EVENT_CLASS_TYPE(Mouse)
};

class MouseDownEvent : public MouseEvent
{
public:
  EVENT_CLASS_TYPE(MouseDown)
};

class MouseUpEvent : public MouseEvent
{
public:
  EVENT_CLASS_TYPE(MouseUp)
};
