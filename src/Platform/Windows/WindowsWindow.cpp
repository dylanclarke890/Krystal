#include "WindowsWindow.h"

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
    case WM_CLOSE:
    {
      if (MessageBoxA(window, "Are you sure you want to exit?", "Quit?", MB_OKCANCEL) == IDOK)
      {
        DestroyWindow(hWnd);
        // TODO: destroy window??
      }
      break;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
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
      result = DefWindowProcA(window, message, wParam, lParam);
      break;
    }

    return result;
  }

  void WindowsWindow::Show(bool visible)
  {
    ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);
  }
}