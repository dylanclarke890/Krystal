#pragma once

#include "Window.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Camera/Perspective.h"

namespace Krys
{

  class Application
  {
  private:
    float TargetFrameTimeMs;
    bool IsRunning;

  protected:
    Ref<Window> Window;
    Ref<GraphicsContext> Context;

  public:
    Application(const string &name, int width, int height, float targetFps);
    virtual ~Application() = default;

    virtual void Startup();
    virtual void Run();
    virtual void BeginFrame();
    virtual void Update(float dt) = 0;
    virtual void EndFrame();

    void Stop() noexcept
    {
      IsRunning = false;
    }

    virtual void Shutdown();
    virtual void OnEvent(Event &event);

  private:
    bool OnResizeEvent(ResizeEvent &event);
    bool OnShutdownEvent(ShutdownEvent &event);
  };
}
