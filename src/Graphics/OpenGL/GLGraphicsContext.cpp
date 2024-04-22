#include "GLGraphicsContext.h"
#pragma warning(push)
#pragma warning(disable : 4005)
#include <glad.h>
#include <stdio.h>
#pragma warning(pop)

namespace Krys
{
  GLGraphicsContext::~GLGraphicsContext()
  {
    wglDeleteContext(openGLContext);
  }

  void GLGraphicsContext::Init()
  {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
        32,                                                         // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, // Number of bits for the depthbuffer
        8,  // Number of bits for the stencilbuffer
        0,  // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0};

    // TODO: static BAD!
    KRYS_ASSERT(dc, "Device context was not valid");

    int pixelFormat = ChoosePixelFormat(dc, &pfd);
    KRYS_ASSERT(pixelFormat != 0, "Failed to choose a pixel format");

    BOOL setPixelFormatSuccess = SetPixelFormat(dc, pixelFormat, &pfd);
    KRYS_ASSERT(setPixelFormatSuccess, "Failed to set the pixel format");

    openGLContext = wglCreateContext(dc);
    KRYS_ASSERT(openGLContext, "Failed to create OpenGL context");

    BOOL makeCurrentSuccess = wglMakeCurrent(dc, openGLContext);
    KRYS_ASSERT(makeCurrentSuccess, "Failed to make OpenGL context current");

    if (!gladLoadGL())
    {
      KRYS_ASSERT(false, "Failed to initialize OpenGL context");
      // TODO: exit early
    }

    KRYS_INFO("OPENGL - initialised:");

    int minorVersion, majorVersion;
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    KRYS_INFO("- Version: %d.%d", majorVersion, minorVersion);

    KRYS_INFO("- Vendor: %s", glGetString(GL_VENDOR));
    KRYS_INFO("- Renderer: %s", glGetString(GL_RENDERER));
    KRYS_INFO("- Primary GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
  }

  void GLGraphicsContext::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  // TODO: pass a vector of floats instead
  void GLGraphicsContext::SetClearColor(float x, float y, float z, float a)
  {
    glClearColor(x, y, z, a);
  }

  void GLGraphicsContext::OnResize(int width, int height)
  {
    glViewport(0, 0, width, height);
  }
}