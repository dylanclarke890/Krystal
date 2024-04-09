#pragma once

#include "Events.h"

namespace Krys
{
  class ShutdownEvent : public Event
  {
    EVENT_CLASS_TYPE(Shutdown)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };
}