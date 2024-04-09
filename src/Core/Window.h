#pragma once

#include "Krystal.h"
#include "Events/Events.h"

namespace Krys
{
  typedef bool (*WindowEventCallback)(void *, Event &);

  class Window
  {
  private:
    char *name;

  protected:
    void *ctx = nullptr;
    WindowEventCallback eventCallback;

  public:
    Window() = delete;
    virtual ~Window() = default;
    Window(char *name) : name(name) {}

    char *GetName() const { return name; }

    virtual void Show(bool visible) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    void SetEventCallback(void *context, WindowEventCallback callback)
    {
      ctx = context;
      eventCallback = callback;
    }
  };
}