#include "GLGraphicsContext.h"
#include "OpenGL/GLGraphicsContext.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShader.h"
#include "GLTexture2D.h"
#include "Graphics/SubTexture2D.h"

#include <glad/gl.h>
#include <glad/wgl.h>

namespace Krys
{
#ifdef KRYS_ENABLE_LOGGING
  void OpenGLMessageCallback(uint source, uint type, uint id, uint severity, int length,
                             const char *message, const void *userParam)
  {
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
      KRYS_CRITICAL(message);
      return;
    case GL_DEBUG_SEVERITY_MEDIUM:
      KRYS_ERROR(message);
      return;
    case GL_DEBUG_SEVERITY_LOW:
      KRYS_WARN(message);
      return;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      KRYS_INFO(message);
      return;
    }

    KRYS_ASSERT(false, "Unknown severity level!");
  }
#endif

  GLGraphicsContext::GLGraphicsContext(HDC deviceContext, HWND window, HINSTANCE instance)
      : hWnd(window), instance(instance), dc(deviceContext), openGLContext(0) {}

  GLGraphicsContext::~GLGraphicsContext()
  {
    wglDeleteContext(openGLContext);
  }

  void GLGraphicsContext::Init()
  {
    // TODO: check we have the settings that we want.

    // desired pixel format attributes
    const int32 i_pixel_format_attrib_list[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,       // PFD_DRAW_TO_WINDOW
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,       // PFD_SUPPORT_OPENGL
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,        // PFD_DOUBLEBUFFER
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, // PFD_TYPE_RGBA
        WGL_COLOR_BITS_ARB, 32,                // 32 color bits
        WGL_DEPTH_BITS_ARB, 24,                // 24 depth bits
        // require that the driver supports the pixel format
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        // MSAA16
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 16,
        0 // end
    };

    int32 pixel_format_idx;
    uint pixel_format_count;

    auto chooseFormatSuccess = wglChoosePixelFormatARB(
        dc, i_pixel_format_attrib_list, 0, 1, &pixel_format_idx,
        &pixel_format_count);

    KRYS_ASSERT(chooseFormatSuccess && pixel_format_count && pixel_format_count,
                "Cannot find an appropriate pixel format.");

    // set actual pixel format to device context
    PIXELFORMATDESCRIPTOR pfd{};
    auto describeFormatSuccess = DescribePixelFormat(
        dc, pixel_format_idx, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    KRYS_ASSERT(describeFormatSuccess, "Unable to describe pixel format.");

    auto setPixelFormatSuccess = SetPixelFormat(dc, pixel_format_idx, &pfd);
    KRYS_ASSERT(setPixelFormatSuccess, "Unable to set pixel format.");

    const uint32 OPENGL_MAJOR = 3;
    const uint32 OPENGL_MINOR = 3;

    int32 attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, OPENGL_MAJOR,
        WGL_CONTEXT_MINOR_VERSION_ARB, OPENGL_MINOR,
        0 // end
    };

    openGLContext = wglCreateContextAttribsARB(dc, 0, attributes);

    auto makeCurrentSucess = wglMakeCurrent(dc, openGLContext);
    KRYS_ASSERT(makeCurrentSucess, "Failed to make the OpenGL context current.");

    int32 version = gladLoaderLoadGL();
    KRYS_ASSERT(version, "Failed to load OpenGL functions.");

    KRYS_INFO("OPENGL - initialised:");

    int minorVersion, majorVersion;
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    KRYS_INFO("- Version: %d.%d", majorVersion, minorVersion);

    KRYS_INFO("- Vendor: %s", glGetString(GL_VENDOR));
    KRYS_INFO("- Renderer: %s", glGetString(GL_RENDERER));
    KRYS_INFO("- Primary GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

#ifdef KRYS_ENABLE_LOGGING
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
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

  void GLGraphicsContext::SetClearColor(Vec4 &color)
  {
    glClearColor(color.x, color.y, color.z, color.a);
  }

  void GLGraphicsContext::SetClearColor(Vec4 color)
  {
    glClearColor(color.x, color.y, color.z, color.a);
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

  void GLGraphicsContext::SetDepthBufferWritingEnabled(bool enable)
  {
    glDepthMask(enable);
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

  void GLGraphicsContext::SetDepthClampingEnabled(bool enable)
  {
    if (enable)
      glEnable(GL_DEPTH_CLAMP);
    else
      glDisable(GL_DEPTH_CLAMP);
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

  void GLGraphicsContext::SetWireframeModeEnabled(bool enable)
  {
    glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
  }

  Ref<IndexBuffer> GLGraphicsContext::CreateIndexBuffer(uint32 count)
  {
    return CreateRef<GLIndexBuffer>(count);
  }

  Ref<IndexBuffer> GLGraphicsContext::CreateIndexBuffer(const uint32 *indices, uint32 count)
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

  Ref<Texture2D> GLGraphicsContext::CreateTexture2D(const char *filepath)
  {
    return CreateRef<GLTexture2D>(filepath);
  }

  Ref<SubTexture2D> GLGraphicsContext::CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize)
  {
    return CreateRef<SubTexture2D>(texture, coords, cellSize, spriteSize);
  }
}
