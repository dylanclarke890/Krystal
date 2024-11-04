#include "Core/Events/EventManager.hpp"

namespace Krys
{
  void EventManager::Enqueue(Unique<Event> event) noexcept
  {
    _events.emplace(std::move(event));
  }

  void EventManager::ProcessEvents() noexcept
  {
    while (!_events.empty())
    {
      auto event = std::move(_events.front());
      _events.pop();
      _dispatcher.Dispatch(*event);
    }
  }
}
