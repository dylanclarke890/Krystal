#include <windows.h>

LRESULT MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch (message)
  {
  case WM_SIZE:
  {
    OutputDebugStringA("WM_SIZE\n");
  }
  break;
  case WM_DESTROY:
  {
    OutputDebugStringA("WM_DESTROY\n");
  }
  break;
  case WM_CLOSE:
  {
    OutputDebugStringA("WM_CLOSE\n");
  }
  break;
  case WM_ACTIVATEAPP:
  {
    OutputDebugStringA("WM_ACTIVATEAPP\n");
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT paint;

    HDC deviceContext = BeginPaint(window, &paint);

    static DWORD operation = WHITENESS;

    PatBlt(
        deviceContext,
        paint.rcPaint.left,
        paint.rcPaint.top,
        paint.rcPaint.bottom - paint.rcPaint.top,
        paint.rcPaint.right - paint.rcPaint.left,
        operation);

    if (operation == WHITENESS)
      operation = BLACKNESS;
    else
      operation = WHITENESS;

    EndPaint(window, &paint);
  }
  break;
  default:
  {
    result = DefWindowProc(window, message, wParam, lParam);
  }
  break;
  }

  return result;
}

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int showCode)
{
  WNDCLASSA windowClass = {};

  // TODO: check if these flags still matter
  windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

  windowClass.lpfnWndProc = MainWindowCallback;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = "HandmadeHeroWindowClass";

  if (RegisterClassA(&windowClass))
  {
    HWND windowHandle = CreateWindowExA(
        0,
        windowClass.lpszClassName,
        "Handmade Hero",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        instance,
        0);

    if (windowHandle)
    {
      MSG message;
      for (;;)
      {
        BOOL messageResult = GetMessageA(&message, 0, 0, 0);
        if (messageResult > 0)
        {
          TranslateMessage(&message);
          DispatchMessageA(&message);
        }
        else
        {
          break;
        }
      }
    }
    else
    {
      // TODO: logging
    }
  }
  else
  {
    // TODO: logging
  }
  return 0;
}