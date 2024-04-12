#include <windowsx.h>
#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"

namespace Krys
{
  WindowsWindow::WindowsWindow(char *name, HINSTANCE instance, LPSTR cmdLine, int nShowCmd)
      : Window(name), cmdLine(cmdLine), nShowCmd(nShowCmd)
  {
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
    LRESULT result = 0;
    switch (message)
    {
    // #region Input
    // TODO: Do we need to differentiate the button that initiated the click??
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
    {
      MouseDownEvent event;
      GetMouseEventData(&event, wParam, lParam);
      if (eventCallback)
        eventCallback(event);
      break;
    }
    // TODO: Do we need to differentiate the button that initiated the click??
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP:
    {
      MouseUpEvent event;
      GetMouseEventData(&event, wParam, lParam);
      if (eventCallback)
        eventCallback(event);
      break;
    }
    // TODO: does windows send a double click event if two separate x buttons are clicked?
    // TODO: double click event
    // TODO: Do we need to differentiate the button that initiated the click??
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDBLCLK:
    {
      // TODO: double click event
      MouseDownEvent event;
      GetMouseEventData(&event, wParam, lParam);
      if (eventCallback)
        eventCallback(event);
      break;
    }
      // #endregion Input

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

    default: return DefWindowProcA(window, message, wParam, lParam);
    }

    return result;
  }

  void WindowsWindow::GetMouseEventData(MouseEvent *event, WPARAM wParam, LPARAM lParam)
  {
    event->Shift = wParam & MK_SHIFT;
    event->Ctrl = wParam & MK_CONTROL;

    uint32 buttons = 0;
    if (wParam & MK_LBUTTON)
      buttons |= MouseButton::Primary;
    if (wParam & MK_RBUTTON)
      buttons |= MouseButton::Secondary;
    if (wParam & MK_MBUTTON)
      buttons |= MouseButton::Auxiliary;
    if (wParam & MK_XBUTTON1)
      buttons |= MouseButton::Fourth;
    if (wParam & MK_XBUTTON2)
      buttons |= MouseButton::Fifth;
    event->Buttons = buttons;

    event->X = GET_X_LPARAM(lParam);
    event->Y = GET_Y_LPARAM(lParam);

    // TODO: deltaX and deltaY?
  }

  void WindowsWindow::Show(bool visible)
  {
    ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);
  }

  void WindowsWindow::BeginFrame()
  {
    MSG msg = {};
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