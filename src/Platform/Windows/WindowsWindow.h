#pragma once
#include <windows.h>

#include "Window.h"
#include "WindowsInput.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Krys
{
  class WindowsWindow : public Window
  {
  private:
    HWND hWnd;
    HDC dc;
    LPSTR cmdLine;
    int nShowCmd;
    Ref<WindowsInput> input;

  public:
    WindowsWindow(const char *name, int width, int height, HINSTANCE instance, LPSTR cmdLine, int nShowCmd, Ref<WindowsInput> input);
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
