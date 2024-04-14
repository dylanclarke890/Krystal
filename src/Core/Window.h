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
    const char *name;

  protected:
    EventCallbackFn eventCallback;

  public:
    Window() = delete;
    Window(const char *name) : name(name) {}
    virtual ~Window() = default;

    const char *GetName() const { return name; }

    virtual void Show(bool visible) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(EventCallbackFn callback)
    {
      eventCallback = callback;
    }
  };
}