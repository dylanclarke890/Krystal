#pragma once

#include "Krystal/Core/Core.h"

#include "Krystal/Core/KeyCodes.h"
#include "Krystal/Core/MouseCodes.h"

namespace Krys
{
  class Input
  {
  public:
    inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
    inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
    inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
    inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
    
    static Scope<Input> Create();
  protected:
    virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
    virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

  private:
    static Scope<Input> s_Instance;

  // Enforce Singleton usage.
  public:
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
  protected:
    Input() = default;
  };
}