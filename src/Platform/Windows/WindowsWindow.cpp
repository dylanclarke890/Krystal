#include <vector> // TODO: implement own map or vector class
#include <windowsx.h>

#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Input/MouseButtons.h"
#include "Input/KeyCodes.h"
namespace Krys
{
  static std::vector<KeyCode> keyMap(256, KeyCode::None);

  static void InitKeyCodes()
  {
    // Character keys
    keyMap['A'] = KeyCode::A;
    keyMap['B'] = KeyCode::B;
    keyMap['C'] = KeyCode::C;
    keyMap['D'] = KeyCode::D;
    keyMap['E'] = KeyCode::E;
    keyMap['F'] = KeyCode::F;
    keyMap['G'] = KeyCode::G;
    keyMap['H'] = KeyCode::H;
    keyMap['I'] = KeyCode::I;
    keyMap['J'] = KeyCode::J;
    keyMap['K'] = KeyCode::K;
    keyMap['L'] = KeyCode::L;
    keyMap['M'] = KeyCode::M;
    keyMap['N'] = KeyCode::N;
    keyMap['O'] = KeyCode::O;
    keyMap['P'] = KeyCode::P;
    keyMap['Q'] = KeyCode::Q;
    keyMap['R'] = KeyCode::R;
    keyMap['S'] = KeyCode::S;
    keyMap['T'] = KeyCode::T;
    keyMap['U'] = KeyCode::U;
    keyMap['V'] = KeyCode::V;
    keyMap['W'] = KeyCode::W;
    keyMap['X'] = KeyCode::X;
    keyMap['Y'] = KeyCode::Y;
    keyMap['Z'] = KeyCode::Z;

    // Num keys
    keyMap['0'] = KeyCode::Num0;
    keyMap['1'] = KeyCode::Num1;
    keyMap['2'] = KeyCode::Num2;
    keyMap['3'] = KeyCode::Num3;
    keyMap['4'] = KeyCode::Num4;
    keyMap['5'] = KeyCode::Num5;
    keyMap['6'] = KeyCode::Num6;
    keyMap['7'] = KeyCode::Num7;
    keyMap['8'] = KeyCode::Num8;
    keyMap['9'] = KeyCode::Num9;

    // Modifier keys
    keyMap[VK_SHIFT] = KeyCode::LeftShift;
    keyMap[VK_LSHIFT] = KeyCode::LeftShift;
    keyMap[VK_RSHIFT] = KeyCode::RightShift;
    keyMap[VK_CONTROL] = KeyCode::LeftControl;
    keyMap[VK_LCONTROL] = KeyCode::LeftControl;
    keyMap[VK_RCONTROL] = KeyCode::RightControl;
    keyMap[VK_MENU] = KeyCode::LeftAlt;
    keyMap[VK_LMENU] = KeyCode::LeftAlt;
    keyMap[VK_RMENU] = KeyCode::RightAlt;

    // System keys
    keyMap[VK_SPACE] = KeyCode::Space;
    keyMap[VK_RETURN] = KeyCode::Enter;
    keyMap[VK_ESCAPE] = KeyCode::Escape;
    keyMap[VK_BACK] = KeyCode::Backspace;
    keyMap[VK_TAB] = KeyCode::Tab;

    // Arrow keys
    keyMap[VK_LEFT] = KeyCode::LeftArrow;
    keyMap[VK_RIGHT] = KeyCode::RightArrow;
    keyMap[VK_UP] = KeyCode::UpArrow;
    keyMap[VK_DOWN] = KeyCode::DownArrow;

    // Function keys
    keyMap[VK_F1] = KeyCode::F1;
    keyMap[VK_F2] = KeyCode::F2;
    keyMap[VK_F3] = KeyCode::F3;
    keyMap[VK_F4] = KeyCode::F4;
    keyMap[VK_F5] = KeyCode::F5;
    keyMap[VK_F6] = KeyCode::F6;
    keyMap[VK_F7] = KeyCode::F7;
    keyMap[VK_F8] = KeyCode::F8;
    keyMap[VK_F9] = KeyCode::F9;
    keyMap[VK_F10] = KeyCode::F10;
    keyMap[VK_F11] = KeyCode::F11;
    keyMap[VK_F12] = KeyCode::F12;
  }

  WindowsWindow::WindowsWindow(char *name, HINSTANCE instance, LPSTR cmdLine, int nShowCmd)
      : Window(name), cmdLine(cmdLine), nShowCmd(nShowCmd)
  {
    InitKeyCodes();
    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = &WindowsWindow::StaticWindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = name;
    windowClass.cbWndExtra = sizeof(WindowsWindow *);

    if (!RegisterClassA(&windowClass))
    {
      // TODO: Handle error
    }

    hWnd = CreateWindowExA(
        0,                                                          // optional window styles
        windowClass.lpszClassName,                                  // window class
        "Krystal",                                                  // window name
        WS_BORDER,                                                  // window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // size/position
        0,                                                          // parent window
        0,                                                          // menu
        instance,                                                   // instance handle
        0);                                                         // additional application data;

    if (!hWnd)
    {
      // TODO: Handle error
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
  }

  LRESULT CALLBACK WindowsWindow::StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    WindowsWindow *pThis = nullptr;
    if (message == WM_NCCREATE)
    {
      CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
      pThis = static_cast<WindowsWindow *>(pCreate->lpCreateParams);
      SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
      pThis = reinterpret_cast<WindowsWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
      return pThis->WindowProc(hWnd, message, wParam, lParam);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  LRESULT CALLBACK WindowsWindow::WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
  {
#define KRYS_EVENT_CALLBACK() \
  if (eventCallback)          \
  eventCallback(event)

    LRESULT result = 0;
    switch (message)
    {
    // TODO: should we always capture mouse on mouse down until mouse up? we currently don't.
    // #region Mouse input
    case WM_LBUTTONDOWN:
    {
      MouseButtonPressedEvent event(MouseButton::Left);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_LBUTTONUP:
    {
      MouseButtonReleasedEvent event(MouseButton::Left);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_RBUTTONDOWN:
    {
      MouseButtonPressedEvent event(MouseButton::Right);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_RBUTTONUP:
    {
      MouseButtonReleasedEvent event(MouseButton::Right);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_MBUTTONDOWN:
    {
      MouseButtonPressedEvent event(MouseButton::Middle);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_MBUTTONUP:
    {
      MouseButtonReleasedEvent event(MouseButton::Middle);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_XBUTTONDOWN:
    {
      MouseButton button = GET_XBUTTON_WPARAM(wParam) & XBUTTON1
                               ? MouseButton::Thumb1
                               : MouseButton::Thumb2;
      MouseButtonPressedEvent event(button);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_XBUTTONUP:
    {
      MouseButton button = GET_XBUTTON_WPARAM(wParam) & XBUTTON1
                               ? MouseButton::Thumb1
                               : MouseButton::Thumb2;
      MouseButtonReleasedEvent event(button);
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDBLCLK:
    {
      return DefWindowProc(window, message, wParam, lParam);
    }
      // #endregion  Mouse input

    // #region Keyboard input
    case WM_KEYUP:
    case WM_KEYDOWN:
    case WM_SYSKEYUP:
    case WM_SYSKEYDOWN:
    {
      // Unused data:
      // KF_DLGMODE -  Dialog mode flag, indicates whether a dialog box is active.
      // KF_MENUMODE - Menu mode flag, indicates whether a menu is active.
      // WORD repeatCount = LOWORD(lParam); // repeat count, > 0 if several keydown messages was combined into one message
      WORD keyFlags = HIWORD(lParam);
      bool isSysKeyMessage = (keyFlags & KF_ALTDOWN);

      bool isExtendedKey = (keyFlags & KF_EXTENDED); // extended-key flag, 1 if scancode has 0xE0 prefix
      WORD scanCode = LOBYTE(keyFlags);
      if (isExtendedKey)
        scanCode = MAKEWORD(scanCode, 0xE0);
      WORD vkCode = LOWORD(wParam);
      switch (vkCode)
      {
      case VK_SHIFT:   // converts to VK_LSHIFT or VK_RSHIFT
      case VK_CONTROL: // converts to VK_LCONTROL or VK_RCONTROL
      case VK_MENU:    // converts to VK_LMENU or VK_RMENU
        vkCode = LOWORD(MapVirtualKeyA(scanCode, MAPVK_VSC_TO_VK_EX));
        break;
      default:
        break;
      }

      bool isKeyUpMessage = (keyFlags & KF_UP);
      if (isKeyUpMessage)
      {
        KeyReleasedEvent event;
        event.Alt = isSysKeyMessage;
        GetKeyEventData(&event, vkCode);
        KRYS_EVENT_CALLBACK();
      }
      else
      {
        KeyPressedEvent event;
        event.Alt = isSysKeyMessage;
        event.Repeat = (keyFlags & KF_REPEAT); // previous key-state flag, 1 on autorepeat
        GetKeyEventData(&event, vkCode);
        KRYS_EVENT_CALLBACK();
      }

      if (isSysKeyMessage) // OS also needs to process, otherwise cmds like ALT+TAB won't work
        return DefWindowProcA(window, message, wParam, lParam);
      break;
    }
    // #endregion Keyboard input

    // #region Quitting
    case WM_CLOSE:
    {
      if (MessageBoxA(window, "Are you sure you want to exit?", "Quit?", MB_OKCANCEL) == IDOK)
        DestroyWindow(hWnd);
      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
      // #endregion Quitting

    case WM_SIZE:
    {
      // int width = LOWORD(lParam);
      // int height = HIWORD(lParam);
      //  TODO: Replace this with the actual resize handling
      result = DefWindowProcA(window, message, wParam, lParam);
      break;
    }
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(window, &ps);

      // TODO: test code
      HBRUSH brush = CreateSolidBrush(RGB(50, 151, 151));
      FillRect(hdc, &ps.rcPaint, brush);
      DeleteObject(brush);

      EndPaint(window, &ps);
      break;
    }

    default:
      return DefWindowProcA(window, message, wParam, lParam);
    }

    return result;
  }

  void WindowsWindow::GetMouseEventData(MouseEvent *event, WPARAM wParam, LPARAM lParam)
  {
    event->X = GET_X_LPARAM(lParam);
    event->Y = GET_Y_LPARAM(lParam);

    WORD keysDown = GET_KEYSTATE_WPARAM(wParam);
    event->Shift = keysDown & MK_SHIFT;
    event->Ctrl = keysDown & MK_CONTROL;
    event->Alt = GetKeyState(VK_MENU) < 0;

    uint32 buttons = MouseButton::MouseButtonNone;
    if (keysDown & MK_LBUTTON)
      buttons |= MouseButton::Left;
    if (keysDown & MK_RBUTTON)
      buttons |= MouseButton::Right;
    if (keysDown & MK_MBUTTON)
      buttons |= MouseButton::Middle;
    if (keysDown & MK_XBUTTON1)
      buttons |= MouseButton::Thumb1;
    if (keysDown & MK_XBUTTON2)
      buttons |= MouseButton::Thumb2;
    event->Buttons = buttons;
  }

  void WindowsWindow::GetKeyEventData(KeyEvent *event, WORD vkCode)
  {
    event->Shift = GetKeyState(VK_SHIFT) < 0;
    event->Ctrl = GetKeyState(VK_CONTROL) < 0;
    event->Key = keyMap[vkCode];
  }

  void WindowsWindow::Show(bool visible)
  {
    ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);
  }

  void WindowsWindow::BeginFrame()
  {
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);

      if (msg.message == WM_QUIT && eventCallback)
      {
        ShutdownEvent event;
        eventCallback(event);
      }
    }
  }

  void WindowsWindow::EndFrame()
  {
  }
}