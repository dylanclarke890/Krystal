#pragma once

#include "Window.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  class Application
  {
  private:
    Ref<Window> window;
    Ref<GraphicsContext> ctx;
    bool IsRunning;
    float TargetFrameTimeMs;

  public:
    Application(float targetFps, Ref<Window> window);
    void Run();
    void Shutdown();

  private:
    void OnEvent(Event &event);
    bool OnMouseButtonEvent(MouseButtonEvent &event);
    bool OnKeyEvent(KeyEvent &event);
    bool OnResizeEvent(ResizeEvent &event);
    bool OnShutdownEvent(ShutdownEvent &event);
  };
}
