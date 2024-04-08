#include "WindowsWindow.h"

static bool Win_ProcessMessages()
{
  MSG msg = {};
  while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
  {
    if (msg.message == WM_QUIT)
      return false;

    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }

  return true;
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
  Krys::WindowsWindow *window = new Krys::WindowsWindow("Krystal Platform", instance, cmdLine, nCmdShow);
  window->Show(true);

  while (Win_ProcessMessages())
  {
  }

  delete window;

  return 1;
}
