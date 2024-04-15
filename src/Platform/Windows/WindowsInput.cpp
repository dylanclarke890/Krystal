#include "Krystal.h"
#include "WindowsInput.h"

namespace Krys
{
  WindowsInput::WindowsInput()
      : PrevKeyState(new BYTE[256]{}), KeyState(new BYTE[256]{}),
        PrevMouseButtonState(new bool[5]), MouseButtonState(new bool[5]),
        VirtualKeyMap(256, KeyCode::None), KeyCodeMap(256, 0)
  {
    GetKeyboardState(KeyState);
    InitKeyMaps();
  }

  WindowsInput::~WindowsInput()
  {
    delete PrevKeyState;
    delete KeyState;
    delete PrevMouseButtonState;
    delete MouseButtonState;
  }

  void WindowsInput::InitKeyMaps()
  {
    // Character keys
    VirtualKeyMap['A'] = KeyCode::A;
    KeyCodeMap[(int)KeyCode::A] = 'A';

    VirtualKeyMap['B'] = KeyCode::B;
    KeyCodeMap[(int)KeyCode::B] = 'B';

    VirtualKeyMap['C'] = KeyCode::C;
    KeyCodeMap[(int)KeyCode::B] = 'C';

    VirtualKeyMap['D'] = KeyCode::D;
    KeyCodeMap[(int)KeyCode::B] = 'D';

    VirtualKeyMap['E'] = KeyCode::E;
    KeyCodeMap[(int)KeyCode::B] = 'E';

    VirtualKeyMap['F'] = KeyCode::F;
    KeyCodeMap[(int)KeyCode::B] = 'F';

    VirtualKeyMap['G'] = KeyCode::G;
    KeyCodeMap[(int)KeyCode::B] = 'G';

    VirtualKeyMap['H'] = KeyCode::H;
    KeyCodeMap[(int)KeyCode::B] = 'H';

    VirtualKeyMap['I'] = KeyCode::I;
    KeyCodeMap[(int)KeyCode::B] = 'I';

    VirtualKeyMap['J'] = KeyCode::J;
    KeyCodeMap[(int)KeyCode::B] = 'J';

    VirtualKeyMap['K'] = KeyCode::K;
    KeyCodeMap[(int)KeyCode::B] = 'K';

    VirtualKeyMap['L'] = KeyCode::L;
    KeyCodeMap[(int)KeyCode::B] = 'L';

    VirtualKeyMap['M'] = KeyCode::M;
    KeyCodeMap[(int)KeyCode::B] = 'M';

    VirtualKeyMap['N'] = KeyCode::N;
    KeyCodeMap[(int)KeyCode::B] = 'N';

    VirtualKeyMap['O'] = KeyCode::O;
    KeyCodeMap[(int)KeyCode::B] = 'O';

    VirtualKeyMap['P'] = KeyCode::P;
    KeyCodeMap[(int)KeyCode::B] = 'P';

    VirtualKeyMap['Q'] = KeyCode::Q;
    KeyCodeMap[(int)KeyCode::B] = 'Q';

    VirtualKeyMap['R'] = KeyCode::R;
    KeyCodeMap[(int)KeyCode::B] = 'R';

    VirtualKeyMap['S'] = KeyCode::S;
    KeyCodeMap[(int)KeyCode::B] = 'S';

    VirtualKeyMap['T'] = KeyCode::T;
    KeyCodeMap[(int)KeyCode::B] = 'T';

    VirtualKeyMap['U'] = KeyCode::U;
    KeyCodeMap[(int)KeyCode::B] = 'U';

    VirtualKeyMap['V'] = KeyCode::V;
    KeyCodeMap[(int)KeyCode::B] = 'V';

    VirtualKeyMap['W'] = KeyCode::W;
    KeyCodeMap[(int)KeyCode::B] = 'W';

    VirtualKeyMap['X'] = KeyCode::X;
    KeyCodeMap[(int)KeyCode::B] = 'X';

    VirtualKeyMap['Y'] = KeyCode::Y;
    KeyCodeMap[(int)KeyCode::B] = 'Y';

    VirtualKeyMap['Z'] = KeyCode::Z;
    KeyCodeMap[(int)KeyCode::B] = 'Z';

    // Num keys
    VirtualKeyMap['0'] = KeyCode::Num0;
    KeyCodeMap[(int)KeyCode::B] = '0';

    VirtualKeyMap['1'] = KeyCode::Num1;
    KeyCodeMap[(int)KeyCode::B] = '1';

    VirtualKeyMap['2'] = KeyCode::Num2;
    KeyCodeMap[(int)KeyCode::B] = '2';

    VirtualKeyMap['3'] = KeyCode::Num3;
    KeyCodeMap[(int)KeyCode::B] = '3';

    VirtualKeyMap['4'] = KeyCode::Num4;
    KeyCodeMap[(int)KeyCode::B] = '4';

    VirtualKeyMap['5'] = KeyCode::Num5;
    KeyCodeMap[(int)KeyCode::B] = '5';

    VirtualKeyMap['6'] = KeyCode::Num6;
    KeyCodeMap[(int)KeyCode::B] = '6';

    VirtualKeyMap['7'] = KeyCode::Num7;
    KeyCodeMap[(int)KeyCode::B] = '7';

    VirtualKeyMap['8'] = KeyCode::Num8;
    KeyCodeMap[(int)KeyCode::B] = '8';

    VirtualKeyMap['9'] = KeyCode::Num9;
    KeyCodeMap[(int)KeyCode::B] = '9';

    // Modifier keys
    VirtualKeyMap[VK_SHIFT] = KeyCode::LeftShift;
    KeyCodeMap[(int)KeyCode::B] = VK_SHIFT;

    VirtualKeyMap[VK_LSHIFT] = KeyCode::LeftShift;
    KeyCodeMap[(int)KeyCode::B] = VK_LSHIFT;

    VirtualKeyMap[VK_RSHIFT] = KeyCode::RightShift;
    KeyCodeMap[(int)KeyCode::B] = VK_RSHIFT;

    VirtualKeyMap[VK_CONTROL] = KeyCode::LeftControl;
    KeyCodeMap[(int)KeyCode::B] = VK_CONTROL;

    VirtualKeyMap[VK_LCONTROL] = KeyCode::LeftControl;
    KeyCodeMap[(int)KeyCode::B] = VK_LCONTROL;

    VirtualKeyMap[VK_RCONTROL] = KeyCode::RightControl;
    KeyCodeMap[(int)KeyCode::B] = VK_RCONTROL;

    VirtualKeyMap[VK_MENU] = KeyCode::LeftAlt;
    KeyCodeMap[(int)KeyCode::B] = VK_MENU;

    VirtualKeyMap[VK_LMENU] = KeyCode::LeftAlt;
    KeyCodeMap[(int)KeyCode::B] = VK_LMENU;

    VirtualKeyMap[VK_RMENU] = KeyCode::RightAlt;
    KeyCodeMap[(int)KeyCode::B] = VK_RMENU;

    // System keys
    VirtualKeyMap[VK_SPACE] = KeyCode::Space;
    KeyCodeMap[(int)KeyCode::B] = VK_SPACE;

    VirtualKeyMap[VK_RETURN] = KeyCode::Enter;
    KeyCodeMap[(int)KeyCode::B] = VK_RETURN;

    VirtualKeyMap[VK_ESCAPE] = KeyCode::Escape;
    KeyCodeMap[(int)KeyCode::B] = VK_ESCAPE;

    VirtualKeyMap[VK_BACK] = KeyCode::Backspace;
    KeyCodeMap[(int)KeyCode::B] = VK_BACK;

    VirtualKeyMap[VK_TAB] = KeyCode::Tab;
    KeyCodeMap[(int)KeyCode::B] = VK_TAB;

    // Arrow keys
    VirtualKeyMap[VK_LEFT] = KeyCode::LeftArrow;
    KeyCodeMap[(int)KeyCode::B] = VK_LEFT;

    VirtualKeyMap[VK_RIGHT] = KeyCode::RightArrow;
    KeyCodeMap[(int)KeyCode::B] = VK_RIGHT;

    VirtualKeyMap[VK_UP] = KeyCode::UpArrow;
    KeyCodeMap[(int)KeyCode::B] = VK_UP;

    VirtualKeyMap[VK_DOWN] = KeyCode::DownArrow;
    KeyCodeMap[(int)KeyCode::B] = VK_DOWN;

    // Function keys
    VirtualKeyMap[VK_F1] = KeyCode::F1;
    KeyCodeMap[(int)KeyCode::B] = VK_F1;

    VirtualKeyMap[VK_F2] = KeyCode::F2;
    KeyCodeMap[(int)KeyCode::B] = VK_F2;

    VirtualKeyMap[VK_F3] = KeyCode::F3;
    KeyCodeMap[(int)KeyCode::B] = VK_F3;

    VirtualKeyMap[VK_F4] = KeyCode::F4;
    KeyCodeMap[(int)KeyCode::B] = VK_F4;

    VirtualKeyMap[VK_F5] = KeyCode::F5;
    KeyCodeMap[(int)KeyCode::B] = VK_F5;

    VirtualKeyMap[VK_F6] = KeyCode::F6;
    KeyCodeMap[(int)KeyCode::B] = VK_F6;

    VirtualKeyMap[VK_F7] = KeyCode::F7;
    KeyCodeMap[(int)KeyCode::B] = VK_F7;

    VirtualKeyMap[VK_F8] = KeyCode::F8;
    KeyCodeMap[(int)KeyCode::B] = VK_F8;

    VirtualKeyMap[VK_F9] = KeyCode::F9;
    KeyCodeMap[(int)KeyCode::B] = VK_F9;

    VirtualKeyMap[VK_F10] = KeyCode::F10;
    KeyCodeMap[(int)KeyCode::B] = VK_F10;

    VirtualKeyMap[VK_F11] = KeyCode::F11;
    KeyCodeMap[(int)KeyCode::B] = VK_F11;

    VirtualKeyMap[VK_F12] = KeyCode::F12;
    KeyCodeMap[(int)KeyCode::B] = VK_F12;
  }

  void WindowsInput::BeginFrame()
  {
    if (!GetKeyboardState(KeyState))
      KRYS_CRITICAL("Failed to get keyboard state: %s", GetLastError());

    MouseButtonState[0] = GetAsyncKeyState(VK_LBUTTON);
    MouseButtonState[1] = GetAsyncKeyState(VK_RBUTTON);
    MouseButtonState[2] = GetAsyncKeyState(VK_MBUTTON);
    MouseButtonState[3] = GetAsyncKeyState(VK_XBUTTON1);
    MouseButtonState[4] = GetAsyncKeyState(VK_XBUTTON2);
  }

  void WindowsInput::EndFrame()
  {
    for (uint16 i = 0; i < 256; i++)
      PrevKeyState[i] = KeyState[i];

    for (uint8 i = 0; i < 5; i++)
      PrevMouseButtonState[i] = MouseButtonState[i];
  }

  bool WindowsInput::IsKeyPressed(KeyCode key) const
  {
    WORD vkCode = MapKeyCodeToVirtualKey(key);
    return KeyState[vkCode] & 0x80;
  }

  bool WindowsInput::WasKeyReleased(KeyCode key) const
  {
    WORD vkCode = MapKeyCodeToVirtualKey(key);
    return (PrevKeyState[vkCode] & 0x80) && !(KeyState[vkCode] & 0x80);
  }

  bool WindowsInput::IsMouseButtonPressed(MouseButton button) const
  {
    WORD vkCode = MapMouseButtonToVirtualKey(button);
    return (KeyState[vkCode] & 0x80);
  }

  bool WindowsInput::WasMouseButtonReleased(MouseButton button) const
  {
    WORD vkCode = MapMouseButtonToVirtualKey(button);
    return (PrevKeyState[vkCode] & 0x80) && !(KeyState[vkCode] & 0x80);
  }

  Vector2D<int> WindowsInput::GetMousePosition() const
  {
    POINT point;
    if (GetCursorPos(&point))
    {
      return Vector2D<int>(point.x, point.y);
    }
    return Vector2D<int>(0, 0);
  }

  int WindowsInput::GetMouseX() const
  {
    return GetMousePosition().X;
  }

  int WindowsInput::GetMouseY() const
  {
    return GetMousePosition().Y;
  }

  KeyCode WindowsInput::MapVirtualKeyToKeyCode(WORD vkCode) const
  {
    return VirtualKeyMap[vkCode];
  }

  WORD WindowsInput::MapKeyCodeToVirtualKey(KeyCode keyCode) const
  {
    return KeyCodeMap[(int)keyCode];
  }

  WORD WindowsInput::MapMouseButtonToVirtualKey(MouseButton button) const
  {
    switch (button)
    {
    case MouseButton::Left:
      return VK_LBUTTON;
    case MouseButton::Right:
      return VK_RBUTTON;
    case MouseButton::Middle:
      return VK_MBUTTON;
    case MouseButton::Thumb1:
      return VK_XBUTTON1;
    case MouseButton::Thumb2:
      return VK_XBUTTON2;
    default:
      return 0;
    }
  }
}