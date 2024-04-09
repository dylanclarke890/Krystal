#pragma once
#include <windows.h>
#include "Window.h"
#include "Events/MouseEvent.h"

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
    virtual void BeginFrame() override;
    virtual void EndFrame() override;

  private:
    static LRESULT CALLBACK StaticWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    void GetMouseEventData(MouseEvent *event, WPARAM wParam, LPARAM lParam);
  };
}
