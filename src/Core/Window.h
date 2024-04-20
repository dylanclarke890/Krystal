#pragma once

#include "Krystal.h"
#include "Events/Events.h"
#include "GraphicsContext.h"
#include <functional>

namespace Krys
{
  // TODO: can we do something similar without std::function?
  using EventCallbackFn = std::function<void(Event &)>;

  class Window
  {
  private:
    const char *Name;

  protected:
    EventCallbackFn eventCallback;
    int Width, Height;
    GraphicsContext *ctx;

  public:
    Window() = delete;
    Window(const char *name, int width, int height)
        : Name(name), Width(width), Height(height), ctx(nullptr) {}
    virtual ~Window() = default;

    const char *GetName() const { return Name; }
    int GetWidth() const { return Width; }
    int GetHeight() const { return Height; }
    GraphicsContext *GetGraphicsContext() const { return ctx; }

    virtual void Show(bool visible) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(EventCallbackFn callback)
    {
      eventCallback = callback;
    }
  };
}