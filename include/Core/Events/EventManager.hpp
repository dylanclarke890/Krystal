#pragma once

#include "Core/Attributes.hpp"
#include "Core/Defines.hpp"
#include "Core/Events/EventDispatcher.hpp"
#include "Core/Pointers.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  /// @brief Provides basic event queuing and dispatch functionality.
  class EventManager
  {
  public:
    NO_COPY_AND_ASSIGN(EventManager)

    /// @brief Constructs an `EventManager`.
    EventManager() noexcept = default;

    /// @brief Add an event to the queue.
    /// @param event The event to add.
    void Enqueue(Unique<Event> event) noexcept;

    /// @brief Processes all queued events.
    void ProcessEvents() noexcept;

    template <typename TEvent>
    REQUIRES((std::is_base_of_v<Event, TEvent>))
    /// @brief Register an event handler for `TEvent`. The event handler must return true or false depending
    /// on whether the event should propagate to other handlers.
    /// @attention Be careful with adding event handlers that themselves dispatch events.
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
    /// @brief Pending event queue.
    Queue<Unique<Event>> _events;

    /// @brief Dispatches events.
    EventDispatcher _dispatcher;
  };
}