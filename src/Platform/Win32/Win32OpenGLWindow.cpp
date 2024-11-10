#include <glad/wgl.h>
#include <hidusage.h>

#include "Core/Debug/Macros.hpp"
#include "Platform/Win32/Win32OpenGLWindow.hpp"

namespace Krys::Platform
{
  Win32OpenGLWindow::Win32OpenGLWindow(uint32 width, uint32 height, Ptr<EventManager> eventManager,
                                       Ptr<InputManager> inputManager) noexcept
      : Win32Window(width, height, eventManager, inputManager)
  {
    const auto instance = ::GetModuleHandleA(NULL);

    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = &Win32Window::StaticWindowProc;
    windowClass.cbWndExtra = sizeof(Win32Window *);
    windowClass.lpszClassName = "KrystalOpenGLWindowClass";

    if (!::RegisterClassA(&windowClass))
      KRYS_FATAL("Unable to register class: %s", ::GetLastError());

    RECT windowDimensions = {0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
    int windowStyles = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    // TODO: account for dpi?

    if (!::AdjustWindowRect(&windowDimensions, windowStyles, 0))
      KRYS_ASSERT(false, "Error adjusting window rect %s", ::GetLastError());

    // Calculate the total width and height of the window
    int totalWidth = windowDimensions.right - windowDimensions.left;
    int totalHeight = windowDimensions.bottom - windowDimensions.top;
    KRYS_INFO("Creating window with dimensions: %d x %d", width, height);
    KRYS_INFO("Adjusted window dimensions: %d x %d", totalWidth, totalHeight);

    InitOpenGLExtensions(instance);

    _windowHandle = ::CreateWindowExA(0,                         // optional window styles
                                      windowClass.lpszClassName, // window class
                                      "Krystal",                 // window name
                                      windowStyles,              // window style
                                      CW_USEDEFAULT,             // initial x position
                                      CW_USEDEFAULT,             // initial y position
                                      totalWidth,                // width
                                      totalHeight,               // height
                                      0,                         // parent window
                                      0,                         // menu
                                      instance,                  // instance handle
                                      0);                        // additional application data;

    if (!_windowHandle)
      KRYS_FATAL("Unable to create window: %s", ::GetLastError());

    ::SetWindowLongPtrA(_windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    TIMECAPS timeCaps;
    if (::timeGetDevCaps(&timeCaps, sizeof(timeCaps)) == TIMERR_NOCANDO)
      KRYS_FATAL("timeGetDevCaps failed");

    KRYS_INFO("Timer precision range - min: %dms, max: %dms", timeCaps.wPeriodMin, timeCaps.wPeriodMax);

    if (::timeBeginPeriod(timeCaps.wPeriodMin) == TIMERR_NOCANDO)
      KRYS_FATAL("timeBeginPeriod failed");

    _deviceContext = ::GetDC(_windowHandle);

    // register for raw mouse events
    RAWINPUTDEVICE rid;
    rid.usUsagePage = HID_USAGE_PAGE_GENERIC;
    rid.usUsage = HID_USAGE_GENERIC_MOUSE;
    rid.dwFlags = RIDEV_INPUTSINK;
    rid.hwndTarget = _windowHandle;

    ::RegisterRawInputDevices(&rid, 1, sizeof(rid));

    // optional: confine cursor to window
    // ::ClipCursor(&GET_WINDOW_DIMENSIONS);

    // ensure mouse visibility reference count is 0 (mouse is hidden)
    while (::ShowCursor(FALSE) >= 0)
    {
    }

    ::ShowWindow(_windowHandle, SW_SHOW);
    ::UpdateWindow(_windowHandle);
  }

  void Win32OpenGLWindow::InitOpenGLExtensions(HINSTANCE instance) const noexcept
  {
    static bool EXTENSIONS_INITIALISED = false;
    if (EXTENSIONS_INITIALISED)
      return;
    EXTENSIONS_INITIALISED = true;

    // register window class class
    WNDCLASSA wc {};
    wc.lpfnWndProc = ::DefWindowProcA;
    wc.hInstance = instance;
    wc.lpszClassName = "wgl_extension_loader_class";

    auto registerSuccess = ::RegisterClassA(&wc);
    KRYS_ASSERT(registerSuccess, "unable to register temporary window class", 0);

    HWND fakeWND = ::CreateWindowA(wc.lpszClassName, "Fake Window",   // window class, title
                                   WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
                                   0, 0,                              // position x & y
                                   1, 1,                              // width & height
                                   NULL, NULL,                        // parent window, menu
                                   instance, NULL);                   // instance, param

    HDC fakeDC = ::GetDC(fakeWND);
    KRYS_ASSERT(fakeDC, "Device context was not valid", 0);

    // specify an arbitrary PFD with OpenGL capabilities
    PIXELFORMATDESCRIPTOR fakePFD = {0};
    fakePFD.nSize = sizeof(PIXELFORMATDESCRIPTOR); // size of structure
    fakePFD.nVersion = 1;                          // default version
    fakePFD.dwFlags = PFD_SUPPORT_OPENGL;          // OpenGL support

    int fakePFDID = ::ChoosePixelFormat(fakeDC, &fakePFD);
    KRYS_ASSERT(fakePFDID != 0, "ChoosePixelFormat() failed.", 0);

    BOOL setPixelFormatSuccess = ::SetPixelFormat(fakeDC, fakePFDID, &fakePFD);
    KRYS_ASSERT(setPixelFormatSuccess, "Failed to set the pixel format", 0);

    // TODO: DescribePixelFormat?

    HGLRC fakeRC = ::wglCreateContext(fakeDC);
    KRYS_ASSERT(fakeRC, "Failed to create OpenGL context", 0);

    BOOL makeCurrentSuccess = ::wglMakeCurrent(fakeDC, fakeRC);
    KRYS_ASSERT(makeCurrentSuccess, "Failed to make OpenGL context current", 0);

    int32 wglVersion = ::gladLoaderLoadWGL(fakeDC);
    KRYS_ASSERT(wglVersion, "glad WGL loader failed.", 0);

    ::wglMakeCurrent(NULL, NULL);
    ::wglDeleteContext(fakeRC);
    ::ReleaseDC(fakeWND, fakeDC);
    ::DestroyWindow(fakeWND);
  }
}
