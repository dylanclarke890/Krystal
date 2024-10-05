#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "Graphics/GraphicsContext.h"

#include <functional>

namespace Krys
{
  using EventCallbackFn = std::function<void(Event &)>;

  // TODO: This doesn't really need to be virtual, platform can only implement one version.
  class Window
  {
  private:
    string Name;

  protected:
    EventCallbackFn eventCallback;
    int Width, Height;
    Ref<GraphicsContext> ctx;

  public:
    Window() = delete;
    Window(const string &name, int width, int height)
        : Name(name), Width(width), Height(height), ctx(nullptr) {}
    virtual ~Window() = default;

    const string &GetName() const { return Name; }
    int GetWidth() const { return Width; }
    int GetHeight() const { return Height; }
    Ref<GraphicsContext> GetGraphicsContext() const { return ctx; }

    virtual void Show(bool visible = true) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(EventCallbackFn callback)
    {
      eventCallback = callback;
    }

    static Ref<Window> Create(const string &name, int width, int height);
  };
}