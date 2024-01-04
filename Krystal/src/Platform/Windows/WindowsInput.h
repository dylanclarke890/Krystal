#pragma once

#include "Krystal/Core/Input.h"
#include "Krystal/Core/KeyCodes.h"
#include "Krystal/Core/MouseCodes.h"

namespace Krys {
  class WindowsInput : public Input
  {
  protected: 
    virtual bool IsKeyPressedImpl(KeyCode keycode) override;
    virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;
    virtual std::pair<float, float> GetMousePositionImpl() override;
  };
}