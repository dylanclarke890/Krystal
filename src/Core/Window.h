#pragma once

#include "Utils.h"

namespace Krys
{
  class Window
  {
  private:
    char *name;

  public:
    Window() = delete;
    virtual ~Window() = default;
    Window(char *name) : name(name) {}

    char *GetName() const { return name; }

    virtual void Show(bool visible) = 0;
  };
}