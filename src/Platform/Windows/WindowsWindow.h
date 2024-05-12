#pragma once
#include <windows.h>

#include "Window.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvents.h"

namespace Krys
{
  class WindowsWindow : public Window
  {
  private:
    HWND hWnd;
    HDC dc;
    LPSTR cmdLine;
    int nShowCmd;

  public:
    WindowsWindow(const char *name, int width, int height, HINSTANCE instance);
    virtual void Show(bool visible) override;
    virtual void BeginFrame() override;
    virtual void EndFrame() override;

  private:
    static LRESULT CALLBACK StaticWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

    static void GetMouseEventData(MouseEvent *event, WPARAM wParam, LPARAM lParam);
    void GetKeyEventData(KeyEvent *event, WORD vkCode);
  };
}
