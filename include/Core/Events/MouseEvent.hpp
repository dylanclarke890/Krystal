#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/Event.hpp"

namespace Krys
{
  class MouseEvent : public Event
  {
  public:
    MouseEvent(const float deltaX, const float deltaY) noexcept;

    KRYS_EVENT_CLASS_TYPE("mouse-event")

    /// @brief Get the amount the cursor has moved along the x-axis since the last event.
    NO_DISCARD float DeltaX() const noexcept;

    /// @brief Get the amount the cursor has moved along the y-axis since the last event.
    NO_DISCARD float DeltaY() const noexcept;

  private:
    float _deltaX, _deltaY;
  };
}