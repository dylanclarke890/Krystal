#pragma once

#include <windows.h>
#include <vector> // TODO: implement own map or vector class
#include "Input/Input.h"
#include "Input/KeyCodes.h"

namespace Krys
{
  class WindowsInput : public Input
  {
    friend class WindowsWindow;

  private:
    PBYTE PrevKeyState, KeyState;
    bool *PrevMouseButtonState, *MouseButtonState;
    std::vector<KeyCode> VirtualKeyMap;
    std::vector<BYTE> KeyCodeMap;

  public:
    WindowsInput();
    virtual ~WindowsInput() override;

    virtual void BeginFrame() override;
    virtual void EndFrame() override;

    // Keyboard
    virtual bool IsKeyPressed(KeyCode key) const override;
    virtual bool WasKeyReleased(KeyCode key) const override;

    // Mouse
    virtual bool IsMouseButtonPressed(MouseButton button) const override;
    virtual bool WasMouseButtonReleased(MouseButton button) const override;
    virtual std::pair<int, int> GetMousePosition() const override;
    virtual int GetMouseX() const override;
    virtual int GetMouseY() const override;

  private:
    void InitKeyMaps();
    KeyCode MapVirtualKeyToKeyCode(WORD vkCode) const;
    WORD MapKeyCodeToVirtualKey(KeyCode keyCode) const;
    WORD MapMouseButtonToVirtualKey(MouseButton button) const;
  };
}