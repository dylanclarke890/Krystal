#include <glad/gl.h>
#include <glad/wgl.h>
#include <hidusage.h>

#include "Core/Debug/Macros.hpp"
#include "IO/Logger.hpp"
#include "Platform/Win32/Win32OpenGLWindow.hpp"

namespace Krys::Platform
{
  Win32OpenGLWindow::Win32OpenGLWindow(const ApplicationSettings &settings, Ptr<EventManager> eventManager,
                                       Ptr<InputManager> inputManager) noexcept
      : Win32Window(std::forward<const ApplicationSettings &>(settings), eventManager, inputManager)
  {
    const auto instance = ::GetModuleHandleA(NULL);

    WNDCLASSA windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = &Win32Window::StaticWindowProc;
    windowClass.cbWndExtra = sizeof(Win32Window *);
    windowClass.lpszClassName = "KrystalOpenGLWindowClass";

    if (!::RegisterClassA(&windowClass))
      Logger::Fatal("Unable to register class: {0}", GetLastErrorAsString());

    RECT windowDimensions = {0, 0, static_cast<LONG>(_width), static_cast<LONG>(_height)};
    int windowStyles = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    // TODO: account for dpi?

    if (!::AdjustWindowRect(&windowDimensions, windowStyles, 0))
      KRYS_ASSERT(false, "Error adjusting window rect {0}", GetLastErrorAsString());

    // Calculate the total width and height of the window
    int totalWidth = windowDimensions.right - windowDimensions.left;
    int totalHeight = windowDimensions.bottom - windowDimensions.top;
    Logger::Info("Creating window with dimensions: {0} x {1}", _width, _height);
    Logger::Info("Adjusted window dimensions: {0} x {1}", totalWidth, totalHeight);

    InitOpenGLExtensions(instance);

    _windowHandle = ::CreateWindowExA(0,                         // optional window styles
                                      windowClass.lpszClassName, // window class
                                      _title.c_str(),            // window name
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
      Logger::Fatal("Unable to create window: {0}", GetLastErrorAsString());

    ::SetWindowLongPtrA(_windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    TIMECAPS timeCaps;
    if (::timeGetDevCaps(&timeCaps, sizeof(timeCaps)) == TIMERR_NOCANDO)
      Logger::Fatal("timeGetDevCaps failed");

    Logger::Info("Timer precision range - min: {0}ms, max: {1}ms", timeCaps.wPeriodMin, timeCaps.wPeriodMax);

    if (::timeBeginPeriod(timeCaps.wPeriodMin) == TIMERR_NOCANDO)
      Logger::Fatal("timeBeginPeriod failed");

    _deviceContext = ::GetDC(_windowHandle);

    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;

    int pfdID = ::ChoosePixelFormat(_deviceContext, &pfd);
    KRYS_ASSERT(pfdID != 0, "ChoosePixelFormat() failed: {0}", GetLastErrorAsString());

    KRYS_ASSERT_ALWAYS_EVAL(::SetPixelFormat(_deviceContext, pfdID, &pfd), "Failed to set the pixel format");

    HGLRC renderContext = ::wglCreateContext(_deviceContext);
    KRYS_ASSERT(renderContext, "Failed to create OpenGL context");
    KRYS_ASSERT_ALWAYS_EVAL(::wglMakeCurrent(_deviceContext, renderContext),
                            "Failed to make OpenGL context current");
    KRYS_ASSERT_ALWAYS_EVAL(::gladLoaderLoadGL(), "Failed to load OpenGL functions");

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

  void Win32OpenGLWindow::SetVSync(bool enabled) noexcept
  {
    ::wglSwapIntervalEXT(enabled ? 1 : 0);
    _vsyncEnabled = enabled;
    Logger::Info("VSync is {0}", enabled ? "enabled" : "disabled");
  }

  void Win32OpenGLWindow::InitOpenGLExtensions(HINSTANCE instance) const noexcept
  {
    static bool EXTENSIONS_INITIALISED = false;
    if (EXTENSIONS_INITIALISED)
    {
      Logger::Error("OpenGL extensions already initialised.");
      return;
    }
    EXTENSIONS_INITIALISED = true;

    // register window class class
    WNDCLASSA wc {};
    wc.lpfnWndProc = ::DefWindowProcA;
    wc.hInstance = instance;
    wc.lpszClassName = "wgl_extension_loader_class";

    KRYS_ASSERT(::RegisterClassA(&wc), "unable to register temporary window class {0}",
                GetLastErrorAsString());

    HWND fakeWND = ::CreateWindowA(wc.lpszClassName, "Fake Window",   // window class, title
                                   WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
                                   0, 0,                              // position x & y
                                   1, 1,                              // width & height
                                   NULL, NULL,                        // parent window, menu
                                   instance, NULL);                   // instance, param

    HDC fakeDC = ::GetDC(fakeWND);
    KRYS_ASSERT(fakeDC, "Device context was not valid: {0}", GetLastErrorAsString());

    // specify an arbitrary PFD with OpenGL capabilities
    PIXELFORMATDESCRIPTOR fakePFD = {0};
    fakePFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    fakePFD.nVersion = 1;
    fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    fakePFD.iPixelType = PFD_TYPE_RGBA;
    fakePFD.cColorBits = 32;
    fakePFD.cAlphaBits = 8;
    fakePFD.cDepthBits = 24;
    fakePFD.cStencilBits = 8;

    int fakePFDID = ::ChoosePixelFormat(fakeDC, &fakePFD);
    KRYS_ASSERT(fakePFDID != 0, "ChoosePixelFormat() failed: {0}", GetLastErrorAsString());

    KRYS_ASSERT_ALWAYS_EVAL(::SetPixelFormat(fakeDC, fakePFDID, &fakePFD), "Failed to set the pixel format",
                            0);

    // TODO: DescribePixelFormat?

    HGLRC fakeRC = ::wglCreateContext(fakeDC);
    KRYS_ASSERT(fakeRC, "Failed to create OpenGL context");

    KRYS_ASSERT_ALWAYS_EVAL(::wglMakeCurrent(fakeDC, fakeRC), "Failed to make OpenGL context current");
    KRYS_ASSERT_ALWAYS_EVAL(::gladLoaderLoadWGL(fakeDC), "glad WGL loader failed.");

    ::wglMakeCurrent(NULL, NULL);
    ::wglDeleteContext(fakeRC);
    ::ReleaseDC(fakeWND, fakeDC);
    ::DestroyWindow(fakeWND);
  }
}
