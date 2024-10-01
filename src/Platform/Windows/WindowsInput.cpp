#include "Core.h"

#include <windows.h>

#include "Input/Input.h"
#include "Input/KeyCodes.h"

namespace Krys
{
  static PBYTE PrevKeyState, KeyState;
  static bool *PrevMouseButtonState, *MouseButtonState;
  static List<KeyCode> VirtualKeyMap;
  static List<BYTE> KeyCodeMap;

  static void InitKeyMaps()
  {
    // Character keys
    VirtualKeyMap['A'] = KeyCode::A;
    KeyCodeMap[static_cast<int>(KeyCode::A)] = 'A';

    VirtualKeyMap['B'] = KeyCode::B;
    KeyCodeMap[static_cast<int>(KeyCode::B)] = 'B';

    VirtualKeyMap['C'] = KeyCode::C;
    KeyCodeMap[static_cast<int>(KeyCode::C)] = 'C';

    VirtualKeyMap['D'] = KeyCode::D;
    KeyCodeMap[static_cast<int>(KeyCode::D)] = 'D';

    VirtualKeyMap['E'] = KeyCode::E;
    KeyCodeMap[static_cast<int>(KeyCode::E)] = 'E';

    VirtualKeyMap['F'] = KeyCode::F;
    KeyCodeMap[static_cast<int>(KeyCode::F)] = 'F';

    VirtualKeyMap['G'] = KeyCode::G;
    KeyCodeMap[static_cast<int>(KeyCode::G)] = 'G';

    VirtualKeyMap['H'] = KeyCode::H;
    KeyCodeMap[static_cast<int>(KeyCode::H)] = 'H';

    VirtualKeyMap['I'] = KeyCode::I;
    KeyCodeMap[static_cast<int>(KeyCode::I)] = 'I';

    VirtualKeyMap['J'] = KeyCode::J;
    KeyCodeMap[static_cast<int>(KeyCode::J)] = 'J';

    VirtualKeyMap['K'] = KeyCode::K;
    KeyCodeMap[static_cast<int>(KeyCode::K)] = 'K';

    VirtualKeyMap['L'] = KeyCode::L;
    KeyCodeMap[static_cast<int>(KeyCode::L)] = 'L';

    VirtualKeyMap['M'] = KeyCode::M;
    KeyCodeMap[static_cast<int>(KeyCode::M)] = 'M';

    VirtualKeyMap['N'] = KeyCode::N;
    KeyCodeMap[static_cast<int>(KeyCode::N)] = 'N';

    VirtualKeyMap['O'] = KeyCode::O;
    KeyCodeMap[static_cast<int>(KeyCode::O)] = 'O';

    VirtualKeyMap['P'] = KeyCode::P;
    KeyCodeMap[static_cast<int>(KeyCode::P)] = 'P';

    VirtualKeyMap['Q'] = KeyCode::Q;
    KeyCodeMap[static_cast<int>(KeyCode::Q)] = 'Q';

    VirtualKeyMap['R'] = KeyCode::R;
    KeyCodeMap[static_cast<int>(KeyCode::R)] = 'R';

    VirtualKeyMap['S'] = KeyCode::S;
    KeyCodeMap[static_cast<int>(KeyCode::S)] = 'S';

    VirtualKeyMap['T'] = KeyCode::T;
    KeyCodeMap[static_cast<int>(KeyCode::T)] = 'T';

    VirtualKeyMap['U'] = KeyCode::U;
    KeyCodeMap[static_cast<int>(KeyCode::U)] = 'U';

    VirtualKeyMap['V'] = KeyCode::V;
    KeyCodeMap[static_cast<int>(KeyCode::V)] = 'V';

    VirtualKeyMap['W'] = KeyCode::W;
    KeyCodeMap[static_cast<int>(KeyCode::W)] = 'W';

    VirtualKeyMap['X'] = KeyCode::X;
    KeyCodeMap[static_cast<int>(KeyCode::X)] = 'X';

    VirtualKeyMap['Y'] = KeyCode::Y;
    KeyCodeMap[static_cast<int>(KeyCode::Y)] = 'Y';

    VirtualKeyMap['Z'] = KeyCode::Z;
    KeyCodeMap[static_cast<int>(KeyCode::Z)] = 'Z';

    // Num keys
    VirtualKeyMap['0'] = KeyCode::Num0;
    KeyCodeMap[static_cast<int>(KeyCode::Num0)] = '0';

    VirtualKeyMap['1'] = KeyCode::Num1;
    KeyCodeMap[static_cast<int>(KeyCode::Num1)] = '1';

    VirtualKeyMap['2'] = KeyCode::Num2;
    KeyCodeMap[static_cast<int>(KeyCode::Num2)] = '2';

    VirtualKeyMap['3'] = KeyCode::Num3;
    KeyCodeMap[static_cast<int>(KeyCode::Num3)] = '3';

    VirtualKeyMap['4'] = KeyCode::Num4;
    KeyCodeMap[static_cast<int>(KeyCode::Num4)] = '4';

    VirtualKeyMap['5'] = KeyCode::Num5;
    KeyCodeMap[static_cast<int>(KeyCode::Num5)] = '5';

    VirtualKeyMap['6'] = KeyCode::Num6;
    KeyCodeMap[static_cast<int>(KeyCode::Num6)] = '6';

    VirtualKeyMap['7'] = KeyCode::Num7;
    KeyCodeMap[static_cast<int>(KeyCode::Num7)] = '7';

    VirtualKeyMap['8'] = KeyCode::Num8;
    KeyCodeMap[static_cast<int>(KeyCode::Num8)] = '8';

    VirtualKeyMap['9'] = KeyCode::Num9;
    KeyCodeMap[static_cast<int>(KeyCode::Num9)] = '9';

    // Modifier keys
    VirtualKeyMap[VK_SHIFT] = KeyCode::LeftShift;
    KeyCodeMap[static_cast<int>(KeyCode::LeftShift)] = VK_SHIFT;

    VirtualKeyMap[VK_LSHIFT] = KeyCode::LeftShift;
    KeyCodeMap[static_cast<int>(KeyCode::LeftShift)] = VK_LSHIFT;

    VirtualKeyMap[VK_RSHIFT] = KeyCode::RightShift;
    KeyCodeMap[static_cast<int>(KeyCode::RightShift)] = VK_RSHIFT;

    VirtualKeyMap[VK_CONTROL] = KeyCode::LeftControl;
    KeyCodeMap[static_cast<int>(KeyCode::LeftControl)] = VK_CONTROL;

    VirtualKeyMap[VK_LCONTROL] = KeyCode::LeftControl;
    KeyCodeMap[static_cast<int>(KeyCode::LeftControl)] = VK_LCONTROL;

    VirtualKeyMap[VK_RCONTROL] = KeyCode::RightControl;
    KeyCodeMap[static_cast<int>(KeyCode::RightControl)] = VK_RCONTROL;

    VirtualKeyMap[VK_MENU] = KeyCode::LeftAlt;
    KeyCodeMap[static_cast<int>(KeyCode::LeftAlt)] = VK_MENU;

    VirtualKeyMap[VK_LMENU] = KeyCode::LeftAlt;
    KeyCodeMap[static_cast<int>(KeyCode::LeftAlt)] = VK_LMENU;

    VirtualKeyMap[VK_RMENU] = KeyCode::RightAlt;
    KeyCodeMap[static_cast<int>(KeyCode::RightAlt)] = VK_RMENU;

    // System keys
    VirtualKeyMap[VK_SPACE] = KeyCode::Space;
    KeyCodeMap[static_cast<int>(KeyCode::Space)] = VK_SPACE;

    VirtualKeyMap[VK_RETURN] = KeyCode::Enter;
    KeyCodeMap[static_cast<int>(KeyCode::Enter)] = VK_RETURN;

    VirtualKeyMap[VK_ESCAPE] = KeyCode::Escape;
    KeyCodeMap[static_cast<int>(KeyCode::Escape)] = VK_ESCAPE;

    VirtualKeyMap[VK_BACK] = KeyCode::Backspace;
    KeyCodeMap[static_cast<int>(KeyCode::Backspace)] = VK_BACK;

    VirtualKeyMap[VK_TAB] = KeyCode::Tab;
    KeyCodeMap[static_cast<int>(KeyCode::Tab)] = VK_TAB;

    // Arrow keys
    VirtualKeyMap[VK_LEFT] = KeyCode::LeftArrow;
    KeyCodeMap[static_cast<int>(KeyCode::LeftArrow)] = VK_LEFT;

    VirtualKeyMap[VK_RIGHT] = KeyCode::RightArrow;
    KeyCodeMap[static_cast<int>(KeyCode::RightArrow)] = VK_RIGHT;

    VirtualKeyMap[VK_UP] = KeyCode::UpArrow;
    KeyCodeMap[static_cast<int>(KeyCode::UpArrow)] = VK_UP;

    VirtualKeyMap[VK_DOWN] = KeyCode::DownArrow;
    KeyCodeMap[static_cast<int>(KeyCode::DownArrow)] = VK_DOWN;

    // Function keys
    VirtualKeyMap[VK_F1] = KeyCode::F1;
    KeyCodeMap[static_cast<int>(KeyCode::F1)] = VK_F1;

    VirtualKeyMap[VK_F2] = KeyCode::F2;
    KeyCodeMap[static_cast<int>(KeyCode::F2)] = VK_F2;

    VirtualKeyMap[VK_F3] = KeyCode::F3;
    KeyCodeMap[static_cast<int>(KeyCode::F3)] = VK_F3;

    VirtualKeyMap[VK_F4] = KeyCode::F4;
    KeyCodeMap[static_cast<int>(KeyCode::F4)] = VK_F4;

    VirtualKeyMap[VK_F5] = KeyCode::F5;
    KeyCodeMap[static_cast<int>(KeyCode::F5)] = VK_F5;

    VirtualKeyMap[VK_F6] = KeyCode::F6;
    KeyCodeMap[static_cast<int>(KeyCode::F6)] = VK_F6;

    VirtualKeyMap[VK_F7] = KeyCode::F7;
    KeyCodeMap[static_cast<int>(KeyCode::F7)] = VK_F7;

    VirtualKeyMap[VK_F8] = KeyCode::F8;
    KeyCodeMap[static_cast<int>(KeyCode::F8)] = VK_F8;

    VirtualKeyMap[VK_F9] = KeyCode::F9;
    KeyCodeMap[static_cast<int>(KeyCode::F9)] = VK_F9;

    VirtualKeyMap[VK_F10] = KeyCode::F10;
    KeyCodeMap[static_cast<int>(KeyCode::F10)] = VK_F10;

    VirtualKeyMap[VK_F11] = KeyCode::F11;
    KeyCodeMap[static_cast<int>(KeyCode::F11)] = VK_F11;

    VirtualKeyMap[VK_F12] = KeyCode::F12;
    KeyCodeMap[static_cast<int>(KeyCode::F12)] = VK_F12;
  }

  void Input::Init()
  {
    PrevKeyState = new BYTE[256]{};
    KeyState = new BYTE[256]{};
    PrevMouseButtonState = new bool[5];
    MouseButtonState = new bool[5];
    VirtualKeyMap = List<KeyCode>(256, KeyCode::None);
    KeyCodeMap = List<BYTE>(256, 0);

    GetKeyboardState(KeyState);
    InitKeyMaps();
  }

  void Input::Shutdown()
  {
    delete PrevKeyState;
    delete KeyState;
    delete PrevMouseButtonState;
    delete MouseButtonState;
  }

  void Input::BeginFrame()
  {
    if (!GetKeyboardState(KeyState))
      KRYS_CRITICAL("Failed to get keyboard state: %s", GetLastError());

    MouseButtonState[0] = GetAsyncKeyState(VK_LBUTTON);
    MouseButtonState[1] = GetAsyncKeyState(VK_RBUTTON);
    MouseButtonState[2] = GetAsyncKeyState(VK_MBUTTON);
    MouseButtonState[3] = GetAsyncKeyState(VK_XBUTTON1);
    MouseButtonState[4] = GetAsyncKeyState(VK_XBUTTON2);
  }

  void Input::EndFrame()
  {
    for (uint16 i = 0; i < 256; i++)
      PrevKeyState[i] = KeyState[i];

    for (uint8 i = 0; i < 5; i++)
      PrevMouseButtonState[i] = MouseButtonState[i];
  }

  bool Input::IsKeyPressed(KeyCode key)
  {
    WORD vkCode = static_cast<WORD>(KeyCodeToNativeKey(key));
    return KeyState[vkCode] & 0x80;
  }

  bool Input::WasKeyReleased(KeyCode key)
  {
    WORD vkCode = static_cast<WORD>(KeyCodeToNativeKey(key));
    return (PrevKeyState[vkCode] & 0x80) && !(KeyState[vkCode] & 0x80);
  }

  bool Input::IsMouseButtonPressed(MouseButton button)
  {
    WORD vkCode = static_cast<WORD>(MouseButtonToNativeKey(button));
    return (KeyState[vkCode] & 0x80);
  }

  bool Input::WasMouseButtonReleased(MouseButton button)
  {
    WORD vkCode = static_cast<WORD>(MouseButtonToNativeKey(button));
    return (PrevKeyState[vkCode] & 0x80) && !(KeyState[vkCode] & 0x80);
  }

  Vec2i Input::GetMousePosition()
  {
    POINT point;
    if (GetCursorPos(&point))
    {
      return Vec2i(point.x, point.y);
    }
    return Vec2i(0, 0);
  }

  int Input::GetMouseX()
  {
    return GetMousePosition().x;
  }

  int Input::GetMouseY()
  {
    return GetMousePosition().y;
  }

  KeyCode Input::NativeKeyToKeyCode(uint vkCode)
  {
    return VirtualKeyMap[vkCode];
  }

  uint Input::KeyCodeToNativeKey(KeyCode keyCode)
  {
    return static_cast<uint>(KeyCodeMap[static_cast<int>(keyCode)]);
  }

  uint Input::MouseButtonToNativeKey(MouseButton button)
  {
    auto keyCode = [&]()
    { switch (button)
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
      KRYS_ASSERT(false, "Unknown mouse button: %d", static_cast<int>(button));
      return 0;
    } }();

    return static_cast<uint>(keyCode);
  }

  MouseButton Input::NativeKeyToMouseButton(uint keyCode)
  {
    switch (keyCode)
    {
    case VK_LBUTTON:
      return MouseButton::Left;
    case VK_RBUTTON:
      return MouseButton::Right;
    case VK_MBUTTON:
      return MouseButton::Middle;
    case VK_XBUTTON1:
      return MouseButton::Thumb1;
    case VK_XBUTTON2:
      return MouseButton::Thumb2;
    default:
      return MouseButton::MouseButtonNone;
    }
  }
}