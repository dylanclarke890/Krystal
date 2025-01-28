#pragma once

#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Core/Events/Event.hpp"

namespace Krys
{
  class EventManager;

  /// @brief Dispatches events to registered handlers.
  class EventDispatcher
  {
    friend class EventManager;

  public:
    NO_COPY(EventDispatcher)

    /// @brief Constructs an `EventDispatcher`.
    EventDispatcher() noexcept = default;

    /// @brief Dispatches an event to all registered handlers for the event's type.
    /// @param event The event to dispatch.
    void Dispatch(const Event &event) const noexcept;

  private:
    Map<EventType, List<Func<bool(const Event &)>>, EventTypeHasher> _handlers;
  };
}