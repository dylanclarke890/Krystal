#pragma once

#include "Core.h"
#include "Events/Events.h"
#include "Graphics/GraphicsContext.h"

#include <functional>

namespace Krys
{
  using EventCallbackFn = std::function<void(Event &)>;

  class Window
  {
  protected:
    string Name;
    EventCallbackFn EventCallback;
    int Width, Height;
    Ref<GraphicsContext> Context;

  public:
    Window() = delete;
    Window(const string &name, int width, int height)
        : Name(name), Width(width), Height(height), Context(nullptr) {}

    virtual ~Window() = default;

    const string &GetName() const { return Name; }
    int GetWidth() const { return Width; }
    int GetHeight() const { return Height; }
    Ref<GraphicsContext> GetGraphicsContext() const { return Context; }

    virtual void Show(bool visible = true) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(EventCallbackFn callback)
    {
      EventCallback = callback;
    }

    static Ref<Window> Create(const string &name, int width, int height);
  };
}