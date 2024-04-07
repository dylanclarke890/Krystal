#include <windows.h>

static bool IsRunning;

static void Win_ProcessMessages()
{
  MSG msg = {};
  while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
  {
    if (msg.message == WM_QUIT)
      IsRunning = false;

    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
}

static LRESULT CALLBACK
Win_MainWindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch (message)
  {
  case WM_CLOSE:
  {
    if (MessageBoxA(window, "Are you sure you want to exit?", "Quit?", MB_OKCANCEL) == IDOK)
    {
      // TODO: destroy window??
      IsRunning = false;
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

int CALLBACK
WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCode)
{
  WNDCLASSA windowClass = {};
  windowClass.style = 0; // CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  windowClass.lpfnWndProc = Win_MainWindowCallback;
  windowClass.hInstance = instance;
  windowClass.lpszClassName = "Krystal Platform";

  RegisterClassA(&windowClass);

  HWND window = CreateWindowExA(
      0,                                                          // optional window styles
      windowClass.lpszClassName,                                  // window class
      "Krystal",                                                  // window name
      WS_BORDER,                                                  // window style
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // size/position
      0,                                                          // parent window
      0,                                                          // menu
      instance,                                                   // instance handle
      0);                                                         // additional application data

  if (!window)
  {
    // TODO: logging
    return 0;
  }

  ShowWindow(window, showCode);
  IsRunning = true;
  while (IsRunning)
  {
    Win_ProcessMessages();
  }

  return 1;
}
