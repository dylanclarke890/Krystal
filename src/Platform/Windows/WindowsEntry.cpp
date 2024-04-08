#include "WindowsWindow.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
  Krys::WindowsWindow *window = new Krys::WindowsWindow("Krystal Platform", instance, cmdLine, nCmdShow);
  window->Show(true);

  MSG msg = {};
  bool isRunning = true;
  while (isRunning)
  {
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
      if (msg.message == WM_QUIT)
        isRunning = false;

      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }
  }

  delete window;

  return 1;
}
