#pragma once

#include "Core/Events/Event.hpp"
#include "Core/Types.hpp"

namespace Krys
{
  class EventManager;

  /// @brief Dispatches events to registered handlers.
  class EventDispatcher
  {
    friend class EventManager;

  public:
    NO_COPY_AND_ASSIGN(EventDispatcher)

    /// @brief Constructs an `EventDispatcher`.
    EventDispatcher() noexcept = default;

    /// @brief Dispatches an event to all registered handlers for the event's type.
    /// @param event The event to dispatch.
    void Dispatch(const Event &event) const noexcept;

  private:
    Map<EventType, List<Func<bool(const Event &)>>, EventTypeHasher> _handlers;
  };
}