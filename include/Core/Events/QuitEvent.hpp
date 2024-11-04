#pragma once

#include "Core/Events/Event.hpp"

namespace Krys
{
  class QuitEvent : public Event
  {
  public:
    QuitEvent() noexcept = default;

    KRYS_EVENT_CLASS_TYPE("quit-event")
  };
}