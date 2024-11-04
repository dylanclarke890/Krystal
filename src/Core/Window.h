#pragma once

#include "Core.h"
#include "Graphics/GraphicsContext.h"

namespace Krys
{
  using namespace Krys::Graphics;

  class Window
  {
  protected:
    string _name;
    int _width, _height;
    Ref<GraphicsContext> _context;

  public:
    Window() = delete;
    Window(const string &name, int width, int height) : _name(name), _width(width), _height(height), _context(nullptr)
    {
    }

    virtual ~Window() = default;

    const string &GetName() const
    {
      return _name;
    }

    int GetWidth() const
    {
      return _width;
    }

    int GetHeight() const
    {
      return _height;
    }

    Ref<GraphicsContext> GetGraphicsContext() const
    {
      return _context;
    }

    virtual void Show(bool visible = true) = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    static Ref<Window> Create(const string &name, int width, int height);
  };
}