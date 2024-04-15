#include <windows.h>

#include "WindowsWindow.h"
#include "WindowsInput.h"
#include "Application.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
  Krys::WindowsInput *input = new Krys::WindowsInput();
  Krys::WindowsWindow *window = new Krys::WindowsWindow("Krystal Platform", instance, cmdLine, nCmdShow, input);

  // TODO: this should be the actual game that inherits from 'Application'
  Krys::Application *app = new Krys::Application(60.0f, window, input);
  app->Run();

  delete app;
  delete window;
  delete input;

  return 1;
}
