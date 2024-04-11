#pragma once

#include "Window.h"
#include "Events/Events.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

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

  private:
    void OnEvent(Event &event);
    bool OnMouseEvent(MouseEvent &event);
    bool OnShutdownEvent(ShutdownEvent &event);
  };
}
