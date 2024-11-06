#include "Platform/Win32/Win32Window.hpp"
#include "Core/Events/EventManager.hpp"
#include "Core/Events/QuitEvent.hpp"
#include "Platform/Win32/Input/Win32InputManager.hpp"

namespace Krys::Platform
{
  Win32Window::Win32Window(uint32 width, uint32 height, Ptr<EventManager> eventManager,
                           Ptr<InputManager> inputManager) noexcept
      : Window(width, height, eventManager, inputManager), _deviceContext(NULL), _windowHandle(NULL)
  {
  }

  HDC Win32Window::GetDeviceContext() const noexcept
  {
    return _deviceContext;
  }

  HWND Win32Window::GetWindowHandle() const noexcept
  {
    return _windowHandle;
  }

  LRESULT Win32Window::StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
  {
    Win32Window *pThis = nullptr;
    if (message == WM_NCCREATE)
    {
      CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
      pThis = static_cast<Win32Window *>(pCreate->lpCreateParams);
      ::SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
      pThis = reinterpret_cast<Win32Window *>(::GetWindowLongPtrA(hWnd, GWLP_USERDATA));
    }

    if (pThis)
      return pThis->WindowProc(hWnd, message, wParam, lParam);
    return ::DefWindowProcA(hWnd, message, wParam, lParam);
  }

  LRESULT Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
  {
    LRESULT result = 0;
    switch (message)
    {
      case WM_CLOSE:     _eventManager->Enqueue(CreateUnique<QuitEvent>()); break;
      case WM_SETFOCUS:
      case WM_KILLFOCUS:
      case WM_CHAR:
      case WM_PAINT:
      case WM_CREATE:
      case WM_SIZE:
      case WM_MOVE:
      case WM_QUIT:      result = ::DefWindowProcA(hWnd, message, wParam, lParam); break;
      default:
      {
        bool handled =
          static_cast<Win32InputManager *>(_inputManager)->HandleWindowsMessage(message, wParam, lParam);

        if (!handled)
          result = ::DefWindowProcA(hWnd, message, wParam, lParam);
      }
      break;
    }

    return result;
  }

  void Win32Window::Poll() noexcept
  {
    MSG message = {0};
    while (::PeekMessageA(&message, NULL, 0, 0, PM_REMOVE) != 0)
    {
      ::TranslateMessage(&message);
      ::DispatchMessageA(&message);
    }
  }
}
