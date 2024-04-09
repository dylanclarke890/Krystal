#pragma once

#include "Window.h"
#include "Events/Events.h"

namespace Krys
{
  class Application
  {
  private:
    Window *window;
    bool isRunning;

  public:
    Application(Window *window);
    void Run();
    bool OnEvent(Event &event);
  };
}
