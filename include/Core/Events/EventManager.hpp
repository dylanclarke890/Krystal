#pragma once

#include "Core/Attributes.hpp"
#include "Core/Events/EventDispatcher.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager
  {
  public:
    EventManager() noexcept = default;
    NO_COPY_AND_ASSIGN(EventManager)

    void Enqueue(const Unique<Event> &event) noexcept;
    void ProcessEvents() noexcept;

    template <IEvent EventT>
    void RegisterHandler(Func<void(const EventT &)> handler) noexcept
    {
      const auto lambda = [handler](const Event &event)
      {
        handler(static_cast<const EventT &>(event));
      };

      EventType typeId = EventT::GetStaticType();
      _dispatcher._handlers[typeId].push_back(lambda);
    }

  private:
    Queue<Unique<Event>> _events;
    EventDispatcher _dispatcher;
  };
}