#pragma once

#include "Krystal.h"
#include "Events/Events.h"
#include <functional>

namespace Krys
{
  // TODO: can we do something similar without std::function?
  using EventCallbackFn = std::function<void(Event &)>;

  class Window
  {
  private:
    char *name;

  protected:
    void *ctx = nullptr;
    EventCallbackFn eventCallback;

  public:
    Window() = delete;
    virtual ~Window() = default;
    Window(char *name) : name(name) {}

    char *GetName() const { return name; }

    virtual void Show(bool visible) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(EventCallbackFn callback)
    {
      eventCallback = callback;
    }
  };
}