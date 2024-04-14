#pragma once

#include "KeyCodes.h"
#include "MouseButtons.h"
#include "Maths/Vector.h"

// TODO: consider implementing this in the same way we implemented the logger.
namespace Krys
{
  class Input
  {
  public:
    virtual ~Input() = default;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    // Keyboard
    virtual bool IsKeyPressed(KeyCode key) const = 0;
    virtual bool WasKeyReleased(KeyCode key) const = 0;

    // Mouse
    virtual bool IsMouseButtonPressed(MouseButton button) const = 0;
    virtual bool WasMouseButtonReleased(MouseButton button) const = 0;
    virtual Vector2D<int> GetMousePosition() const = 0;
    virtual int GetMouseX() const = 0;
    virtual int GetMouseY() const = 0;
    // TODO: virtual float GetMouseScrollDelta() const = 0;
  };
}