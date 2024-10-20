#pragma once

#include "Window.h"
#include "Input/Input.h"
#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/Scene/SceneManager.h"

namespace Krys
{
  using namespace Krys::Graphics;

  class Application
  {
  protected:
    Ref<Window> _window;
    Ref<GraphicsContext> _context;
    Ref<Renderer> _renderer;
    SceneManager _sceneManager;

  private:
    float _targetFrameTimeMs;
    bool _isRunning;

  public:
    Application(const string &name, int width, int height, float targetFps) noexcept;
    virtual ~Application() noexcept = default;

    virtual void Startup() noexcept;
    virtual void Run() noexcept;
    virtual void Stop() noexcept;
    virtual void Shutdown() noexcept;

    virtual void BeginFrame() noexcept;
    virtual void Update(float dt) noexcept;
    virtual void EndFrame() noexcept;

    virtual void OnEvent(Event &event) noexcept;

  private:
    bool OnResizeEvent(ResizeEvent &event) noexcept;
    bool OnShutdownEvent(ShutdownEvent &event) noexcept;
  };
}
