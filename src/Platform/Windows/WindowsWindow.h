#pragma once
#include <windows.h>
#include "Window.h"

namespace Krys
{
  class WindowsWindow : public Window
  {
  private:
    HWND hWnd;
    LPSTR cmdLine;
    int nShowCmd;

  public:
    WindowsWindow(char *name, HINSTANCE instance, LPSTR cmdLine, int nShowCmd);
    virtual void Show(bool visible) override;

  private:
    static LRESULT CALLBACK StaticWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
  };
}
