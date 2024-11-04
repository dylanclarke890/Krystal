#pragma once

#include "Events/Events.h"

namespace Krys
{
  class Controller
  {
  public:
    virtual void OnEvent(Event &event) noexcept = 0;
    virtual void OnUpdate(float dt) noexcept = 0;
  };
}