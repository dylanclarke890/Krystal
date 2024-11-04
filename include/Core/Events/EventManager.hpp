#pragma once

#include "Core/Attributes.hpp"
#include "Core/Defines.hpp"
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

    void Enqueue(Unique<Event> event) noexcept;
    void ProcessEvents() noexcept;

    template <typename TEvent>
    REQUIRES((std::is_base_of_v<Event, TEvent>))
    void RegisterHandler(Func<bool(const TEvent &)> handler) noexcept
    {
      const auto lambda = [handler](const Event &event) -> bool
      {
        return handler(static_cast<const TEvent &>(event));
      };

      EventType typeId = TEvent::GetStaticType();
      _dispatcher._handlers[typeId].push_back(lambda);
    }

  private:
    Queue<Unique<Event>> _events;
    EventDispatcher _dispatcher;
  };
}