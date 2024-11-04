#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/Event.hpp"

namespace Krys
{
  class ScrollWheelEvent : public Event
  {
  public:
    ScrollWheelEvent(const float delta) noexcept;

    KRYS_EVENT_CLASS_TYPE("scroll-wheel-event")

    /// @brief Get the amount the scroll wheel has moved since the last event.
    NO_DISCARD float Delta() const noexcept;

  private:
    float _delta;
  };

}