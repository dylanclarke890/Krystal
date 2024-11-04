#include "Core/Events/QuitEvent.hpp"

namespace Krys
{
  QuitEvent::QuitEvent() noexcept : Event(EVENT_TYPE("quit-event"))
  {
  }
}