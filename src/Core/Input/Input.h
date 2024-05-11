#pragma once

#include "KeyCodes.h"
#include "MouseButtons.h"
#include "Maths/Maths.h"

namespace Krys
{
  class Input
  {
  public:
    Input() = delete;

    static void Init();
    static void Shutdown();

    static void BeginFrame();
    static void EndFrame();

    // Keyboard
    static uint KeyCodeToNativeKey(KeyCode key);
    static KeyCode NativeKeyToKeyCode(uint keyCode);
    static bool IsKeyPressed(KeyCode key);
    static bool WasKeyReleased(KeyCode key);

    // Mouse
    static uint MouseButtonToNativeKey(MouseButton button);
    static MouseButton NativeKeyToMouseButton(uint button);
    static bool IsMouseButtonPressed(MouseButton button);
    static bool WasMouseButtonReleased(MouseButton button);
    static Vec2i GetMousePosition();
    static int GetMouseX();
    static int GetMouseY();
    // TODO: virtual float GetMouseScrollDelta() const = 0;
  };
}