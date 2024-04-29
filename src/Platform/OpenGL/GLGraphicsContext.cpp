#include "GLGraphicsContext.h"
#include "OpenGL/GLGraphicsContext.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShader.h"

namespace Krys
{
  GLGraphicsContext::GLGraphicsContext(HDC deviceContext, HWND window)
      : hWnd(window), dc(deviceContext), openGLContext(0) {}

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
      KRYS_ASSERT(false, "Failed to initialize OpenGL context");

    KRYS_INFO("OPENGL - initialised:");

    int minorVersion, majorVersion;
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    KRYS_INFO("- Version: %d.%d", majorVersion, minorVersion);

    KRYS_INFO("- Vendor: %s", glGetString(GL_VENDOR));
    KRYS_INFO("- Renderer: %s", glGetString(GL_RENDERER));
    KRYS_INFO("- Primary GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  }

  void GLGraphicsContext::Clear(ClearFlags flags)
  {
    if (flags == ClearFlags::None)
      return;

    int glFlags = 0;
    if (flags & ClearFlags::Color)
      glFlags |= GL_COLOR_BUFFER_BIT;

    if (flags & ClearFlags::Depth)
      glFlags |= GL_DEPTH_BUFFER_BIT;

    if (flags & ClearFlags::Stencil)
      glFlags |= GL_STENCIL_BUFFER_BIT;

    KRYS_ASSERT(glFlags != 0, "Invalid flags!");

    glClear(glFlags);
  }

  // TODO: pass a vector of floats instead?
  void GLGraphicsContext::SetClearColor(float x, float y, float z, float a)
  {
    glClearColor(x, y, z, a);
  }

  void GLGraphicsContext::SetViewport(int width, int height)
  {
    glViewport(0, 0, width, height);
  }

  void GLGraphicsContext::SetFaceCulling(CullMode mode)
  {
    switch (mode)
    {
    case CullMode::None:
    {
      glDisable(GL_CULL_FACE);
      break;
    }
    case CullMode::Front:
    {
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      break;
    }
    case CullMode::Back:
    {
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      break;
    }
    case CullMode::FrontAndBack:
    {
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT_AND_BACK);
      break;
    }
    default:
      KRYS_ASSERT(false, "Invalid CullMode!");
      break;
    }
  }

  void GLGraphicsContext::SetWindingOrder(WindingOrder mode)
  {
    switch (mode)
    {
    case WindingOrder::Clockwise:
      glFrontFace(GL_CW);
      break;
    case WindingOrder::CounterClockwise:
      glFrontFace(GL_CCW);
      break;
    default:
      KRYS_ASSERT(false, "Invalid CullMode!");
      break;
    }
  }

  void GLGraphicsContext::SetClearDepth(float value)
  {
    glClearDepth(value);
  }

  void GLGraphicsContext::SetDepthTestingEnabled(bool enable)
  {
    if (enable)
      glEnable(GL_DEPTH_TEST);
    else
      glDisable(GL_DEPTH_TEST);
  }

  void GLGraphicsContext::SetDepthRange(float dNear, float dFar)
  {
    glDepthRange(dNear, dFar);
  }

  void GLGraphicsContext::SetDepthTestFunc(DepthTestFunc func)
  {
    int glFunc = [&]()
    {
      switch (func)
      {
      case DepthTestFunc::Always:
        return GL_ALWAYS;
      case DepthTestFunc::EqualOrGreater:
        return GL_GEQUAL;
      case DepthTestFunc::Greater:
        return GL_GREATER;
      case DepthTestFunc::EqualOrLess:
        return GL_LEQUAL;
      case DepthTestFunc::Less:
        return GL_LESS;
      case DepthTestFunc::Never:
        return GL_NEVER;
      default:
        KRYS_ASSERT(false, "Invalid depth func!");
        return 0;
      }
    }();

    glDepthFunc(glFunc);
  }

  Ref<IndexBuffer> GLGraphicsContext::CreateIndexBuffer(uint32 *indices, uint32 count)
  {
    return CreateRef<GLIndexBuffer>(indices, count);
  }

  Ref<VertexBuffer> GLGraphicsContext::CreateVertexBuffer(uint32 size)
  {
    return CreateRef<GLVertexBuffer>(size);
  }

  Ref<VertexBuffer> GLGraphicsContext::CreateVertexBuffer(float *vertices, uint32 size)
  {
    return CreateRef<GLVertexBuffer>(vertices, size);
  }

  Ref<VertexArray> GLGraphicsContext::CreateVertexArray()
  {
    return CreateRef<GLVertexArray>();
  }

  Ref<Shader> GLGraphicsContext::CreateShader()
  {
    return CreateRef<GLShader>();
  }
}
