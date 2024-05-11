#include <windows.h>

#include "WindowsWindow.h"
#include "Application.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
  using namespace Krys;

  Ref<WindowsWindow> window = CreateRef<WindowsWindow>(
      "Krystal Platform", 1280, 720, instance, cmdLine, nCmdShow);

  // TODO: this should be the actual game that inherits from 'Application'
  Unique<Application> app = CreateUnique<Application>(60.0f, window);
  app->Run();

  return 1;
}
