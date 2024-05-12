#pragma once

#include "Krystal.h"
#include "Events/Events.h"
#include "Graphics/GraphicsContext.h"
#include <functional>

namespace Krys
{
  using EventCallbackFn = std::function<void(Event &)>;

  class Window
  {
  private:
    const char *Name;

  protected:
    EventCallbackFn eventCallback;
    int Width, Height;
    Ref<GraphicsContext> ctx;

  public:
    Window() = delete;
    Window(const char *name, int width, int height)
        : Name(name), Width(width), Height(height), ctx(nullptr) {}
    virtual ~Window() = default;

    const char *GetName() const { return Name; }
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
  };
}