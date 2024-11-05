#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/Event.hpp"

namespace Krys
{
  /// @brief Represents a user interaction with a mouse scroll wheel.
  class ScrollWheelEvent : public Event
  {
  public:
    KRYS_EVENT_CLASS_TYPE("scroll-wheel-event")

    /// @brief Constructs a `ScrollWheelEvent`.
    /// @param delta The amount the scroll wheel has moved since the last event. Positive values MUST indicate
    /// scrolling forward and negative values MUST indicate scrolling backwards.
    ScrollWheelEvent(const float delta) noexcept;

    /// @brief Gets the scroll delta since the last event. Positive values indicate scrolling forward (away
    /// from the user), and negative values indicate scrolling backward (toward the user).
    NO_DISCARD float Delta() const noexcept;

  private:
    float _delta;
  };
}