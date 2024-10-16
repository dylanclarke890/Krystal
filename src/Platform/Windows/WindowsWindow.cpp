#include <windowsx.h>

#include <glad/wgl.h>

#include "Core.h"

#include "Core/Events/ApplicationEvents.h"
#include "Core/Input/Input.h"
#include "Core/Input/MouseButtons.h"
#include "Core/Input/KeyCodes.h"

#include "Windows/WindowsWindow.h"
#include "OpenGL/GLGraphicsContext.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT (reinterpret_cast<HINSTANCE>(&__ImageBase))

namespace Krys
{
  static void InitARBExtensions(HINSTANCE instance)
  {
    // register window class class
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = instance;
    wc.lpszClassName = "wgl_extension_loader_class";

    auto registerSuccess = RegisterClassA(&wc);
    KRYS_ASSERT(registerSuccess, "unable to register temporary window class", 0);

    HWND fakeWND = CreateWindowA(
        wc.lpszClassName, "Fake Window",   // window class, title
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
        0, 0,                              // position x, y
        1, 1,                              // width, height
        NULL, NULL,                        // parent window, menu
        instance, NULL);                   // instance, param

    HDC fakeDC = GetDC(fakeWND); // Device Context
    KRYS_ASSERT(fakeDC, "Device context was not valid", 0);

    // specifiy an arbitray PFD with OpenGL capabilities
    PIXELFORMATDESCRIPTOR fakePFD = {0};
    fakePFD.nSize = sizeof(PIXELFORMATDESCRIPTOR); // size of structure
    fakePFD.nVersion = 1;                          // default version
    fakePFD.dwFlags = PFD_SUPPORT_OPENGL;          // OpenGL support

    int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
    KRYS_ASSERT(fakePFDID != 0, "ChoosePixelFormat() failed.", 0);

    BOOL setPixelFormatSuccess = SetPixelFormat(fakeDC, fakePFDID, &fakePFD);
    KRYS_ASSERT(setPixelFormatSuccess, "Failed to set the pixel format", 0);

    // TODO: DescribePixelFormat?

    HGLRC fakeRC = wglCreateContext(fakeDC);
    KRYS_ASSERT(fakeRC, "Failed to create OpenGL context", 0);

    BOOL makeCurrentSuccess = wglMakeCurrent(fakeDC, fakeRC);
    KRYS_ASSERT(makeCurrentSuccess, "Failed to make OpenGL context current", 0);

    int32 wglVersion = gladLoaderLoadWGL(fakeDC);
    KRYS_ASSERT(wglVersion, "glad WGL loader failed.", 0);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(fakeRC);
    ReleaseDC(fakeWND, fakeDC);
    DestroyWindow(fakeWND);
  }

  Ref<Window> Window::Create(const string &name, int width, int height)
  {
    return CreateRef<WindowsWindow>(name, width, height, HINST_THISCOMPONENT);
  }

  WindowsWindow::WindowsWindow(const string &name, int width, int height, HINSTANCE instance)
      : Window(name, width, height), _deviceContext(NULL)
  {
    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = &WindowsWindow::StaticWindowProc;
    windowClass.hInstance = instance;
    windowClass.lpszClassName = name.c_str();
    windowClass.cbWndExtra = sizeof(WindowsWindow *);

    if (!RegisterClassA(&windowClass))
      KRYS_CRITICAL("Unable to register class: %s", GetLastError());

    RECT windowDimensions = {};
    windowDimensions.right = width;
    windowDimensions.bottom = height;

    int windowStyles = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    if (!AdjustWindowRect(&windowDimensions, windowStyles, 0))
      KRYS_ASSERT(false, "Error adjusting window rect %s", GetLastError());

    // Calculate the total width and height of the window
    int totalWidth = windowDimensions.right - windowDimensions.left;
    int totalHeight = windowDimensions.bottom - windowDimensions.top;
    KRYS_INFO("Creating window with dimensions: %d x %d", width, height);
    KRYS_INFO("Adjusted window dimensions: %d x %d", totalWidth, totalHeight);

    InitARBExtensions(instance);

    _window = CreateWindowExA(
        0,                         // optional window styles
        windowClass.lpszClassName, // window class
        "Krystal",                 // window name
        windowStyles,              // window style
        CW_USEDEFAULT,             // initial x position
        CW_USEDEFAULT,             // initial y position
        totalWidth,                // width
        totalHeight,               // height
        0,                         // parent window
        0,                         // menu
        instance,                  // instance handle
        0);                        // additional application data;

    if (!_window)
      KRYS_CRITICAL("Unable to create window: %s", GetLastError());

    SetWindowLongPtr(_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    TIMECAPS timeCaps;
    if (timeGetDevCaps(&timeCaps, sizeof(timeCaps)) == TIMERR_NOCANDO)
      KRYS_CRITICAL("timeGetDevCaps failed");

    KRYS_INFO("Timer precision range - min: %dms, max: %dms", timeCaps.wPeriodMin, timeCaps.wPeriodMax);

    if (timeBeginPeriod(timeCaps.wPeriodMin) == TIMERR_NOCANDO)
      KRYS_CRITICAL("timeBeginPeriod failed");

    _deviceContext = GetDC(_window);
    _context = CreateRef<OpenGL::GLGraphicsContext>(_deviceContext, _window, instance);
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
      pThis = reinterpret_cast<WindowsWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (pThis)
      return pThis->WindowProc(hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  LRESULT CALLBACK WindowsWindow::WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
  {
#define KRYS_EVENT_CALLBACK() \
  if (_eventCallback)         \
  _eventCallback(event)

    LRESULT result = 0;
    switch (message)
    {
#pragma region Mouse input
    case WM_MOUSEMOVE:
    {
      MouseMoveEvent event;
      GetMouseEventData(&event, wParam, lParam);
      KRYS_EVENT_CALLBACK();
      break;
    }
    // TODO: should we always capture mouse on mouse down until mouse up? we currently don't.
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
      return DefWindowProc(window, message, wParam, lParam);
    case WM_MOUSEWHEEL:
    {
      MouseScrollEvent event;
      event.DeltaZ = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
      GetMouseEventData(&event, wParam, lParam);

      // Mouse position is in screen coordinates for this message, convert.
      POINT pt{};
      pt.x = event.X;
      pt.y = event.Y;
      ScreenToClient(window, &pt);
      event.X = pt.x;
      event.Y = pt.y;

      KRYS_EVENT_CALLBACK();
      break;
    }
#pragma endregion Mouse input

#pragma region Keyboard input
    case WM_KEYUP:
    case WM_KEYDOWN:
    case WM_SYSKEYUP:
    case WM_SYSKEYDOWN:
    {
      // Unused data:
      // KF_DLGMODE -  Dialog mode flag, indicates whether a dialog box is active.
      // KF_MENUMODE - Menu mode flag, indicates whether a menu is active.
      // WORD repeatCount = LOWORD(lParam); // repeat count, > 0 if several keydown messages were combined into one message
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
#pragma endregion Keyboard input

#pragma region Quitting
    case WM_CLOSE:
    {
      if (MessageBoxA(window, "Are you sure you want to exit?", "Quit?", MB_OKCANCEL) == IDOK)
        DestroyWindow(window);
      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
#pragma endregion Quitting

    case WM_SIZE:
    {
      int width = static_cast<int>(LOWORD(lParam));
      int height = static_cast<int>(HIWORD(lParam));

      ResizeEvent event;
      event.Width = width;
      event.Height = height;
      _width = width;
      _height = height;

      KRYS_EVENT_CALLBACK();

      return DefWindowProcA(window, message, wParam, lParam);
    }
    case WM_PAINT:
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
    event->Key = Input::NativeKeyToKeyCode(static_cast<uint>(vkCode));
  }

  void WindowsWindow::Show(bool visible)
  {
    ShowWindow(_window, visible ? SW_SHOW : SW_HIDE);
  }

  void WindowsWindow::BeginFrame()
  {
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);

      if (msg.message == WM_QUIT && _eventCallback)
      {
        ShutdownEvent event;
        _eventCallback(event);
      }
    }
  }

  void WindowsWindow::EndFrame()
  {
    SwapBuffers(_deviceContext);
  }
}