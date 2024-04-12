#include "Application.h"
#include "WindowsWindow.h"

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
  Krys::Window *window = new Krys::WindowsWindow("Krystal Platform", instance, cmdLine, nCmdShow);
  // TODO: this should be the actual game that inherits from 'Application'
  Krys::Application *app = new Krys::Application(window);

  app->Run();

  delete app;
  delete window;

  return 1;
}
