#pragma once

#include "Core/Events/Event.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;

  class EventDispatcher
  {
    friend class EventManager;

  public:
    EventDispatcher() noexcept = default;
    NO_COPY_AND_ASSIGN(EventDispatcher)

    void Dispatch(const Event &event) const noexcept;

  private:
    Map<EventType, List<Func<bool(const Event &)>>, StringIdHasher> _handlers;
  };
}