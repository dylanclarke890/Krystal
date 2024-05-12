#pragma once

#include "Window.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera/Perspective.h"

namespace Krys
{
  class Application
  {
  private:
    Ref<Window> window;
    Ref<GraphicsContext> ctx;
    bool IsRunning;
    float TargetFrameTimeMs;
    Ref<Camera> Camera;

  public:
    Application(float targetFps, Ref<Window> window);
    void Run();
    void Shutdown();

  private:
    void OnEvent(Event &event);
    bool OnMouseButtonEvent(MouseButtonEvent &event);
    bool OnKeyEvent(KeyEvent &event);
    bool OnMouseScrollEvent(MouseScrollEvent &event);
    bool OnResizeEvent(ResizeEvent &event);
    bool OnShutdownEvent(ShutdownEvent &event);
    bool OnMouseMove(Event &event);
  };
}
