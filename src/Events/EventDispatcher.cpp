#include "Events/EventDispatcher.hpp"

namespace Krys
{
  void EventDispatcher::Dispatch(const Event &event) const noexcept
  {
    auto it = _handlers.find(event.GetEventType());
    if (it != _handlers.end())
    {
      for (const auto &func : it->second)
      {
        const bool handled = func(event);
        if (handled)
          break;
      }
    }
  }
}
