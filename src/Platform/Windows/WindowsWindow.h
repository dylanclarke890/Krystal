#pragma once
#include <windows.h>

#include "Core/Window.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/KeyEvents.h"

namespace Krys
{
  class WindowsWindow : public Window
  {
  private:
    HWND _window;
    HDC _deviceContext;
    LPSTR _cmdLine;
    int _nShowCmd;

  public:
    WindowsWindow(const string &name, int width, int height, HINSTANCE instance);
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
