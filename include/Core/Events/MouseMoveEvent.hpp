#pragma once

#include "Base/Attributes.hpp"
#include "Core/Events/Event.hpp"

namespace Krys
{
  /// @brief Represents a mouse movement.
  class MouseMoveEvent : public Event
  {
  public:
    KRYS_EVENT_CLASS_TYPE("mouse-move-event")

    /// @brief Constructs a `MouseMoveEvent`.
    /// @param deltaX The amount the cursor moved along the x-axis since the last event.
    /// @param deltaY The amount the cursor moved along the y-axis since the last event.
    MouseMoveEvent(const float deltaX, const float deltaY) noexcept;

    /// @brief Gets the amount the cursor has moved along the x-axis since the last event.
    NO_DISCARD float DeltaX() const noexcept;

    /// @brief Gets the amount the cursor has moved along the y-axis since the last event.
    NO_DISCARD float DeltaY() const noexcept;

  private:
    float _deltaX, _deltaY;
  };
}