#pragma once

#include "Window.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Krys
{
  class Application
  {
  private:
    Window *window;
    Input *input;
    bool IsRunning;

  public:
    Application(Window *window, Input *input);
    void Run();

  private:
    void OnEvent(Event &event);
    bool OnMouseButtonEvent(MouseButtonEvent &event);
    bool OnKeyEvent(KeyEvent &event);
    bool OnShutdownEvent(ShutdownEvent &event);
  };
}
