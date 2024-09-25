#include "Graphics/Textures/SubTexture2D.h"

#include "GLGraphicsContext.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"
#include "GLShader.h"
#include "Textures/GLTexture2D.h"
#include "Textures/GLTextureCubemap.h"
#include "GLFramebuffer.h"

#include <glad/gl.h>
#include <glad/wgl.h>

namespace Krys
{
#ifdef KRYS_ENABLE_LOGGING
  constexpr uint GL_ERROR_CODE_SHADER_RECOMPILED = 131218;

  void OpenGLMessageCallback(uint source, uint type, uint id, uint severity, int length,
                             const char *message, const void *userParam)
  {
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
      KRYS_CRITICAL(message);
      KRYS_ASSERT(false, "OpenGL Error (HIGH).", 0);
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      KRYS_ERROR(message);
      KRYS_ASSERT(id == GL_ERROR_CODE_SHADER_RECOMPILED, "OpenGL Error (MED).", 0);
      break;
    case GL_DEBUG_SEVERITY_LOW:
      KRYS_WARN(message);
      KRYS_ASSERT(false, "OpenGL Error (LOW).", 0);
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      KRYS_INFO(message);
      break;
    default:
      KRYS_ASSERT(false, "Unknown severity level!", 0);
      break;
    }
  }
#endif

  static auto EnableFeature = [](GLenum feature, bool enable) -> void
  {
    if (enable)
      glEnable(feature);
    else
      glDisable(feature);
  };

  static auto ToGLBlendFactor = [](BlendFactor factor) -> int
  {
    switch (factor)
    {
    case BlendFactor::One:
      return GL_ONE;
    case BlendFactor::Zero:
      return GL_ZERO;
    case BlendFactor::SourceColor:
      return GL_SRC_COLOR;
    case BlendFactor::OneMinusSourceColor:
      return GL_ONE_MINUS_SRC_COLOR;
    case BlendFactor::DestinationColor:
      return GL_DST_COLOR;
    case BlendFactor::OneMinusDestinationColor:
      return GL_ONE_MINUS_DST_COLOR;
    case BlendFactor::SourceAlpha:
      return GL_SRC_ALPHA;
    case BlendFactor::OneMinusSourceAlpha:
      return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFactor::DestinationAlpha:
      return GL_DST_ALPHA;
    case BlendFactor::OneMinusDestinationAlpha:
      return GL_ONE_MINUS_DST_ALPHA;
    case BlendFactor::ConstantColor:
      return GL_CONSTANT_COLOR;
    case BlendFactor::OneMinusConstantColor:
      return GL_ONE_MINUS_CONSTANT_COLOR;
    case BlendFactor::ConstantAlpha:
      return GL_CONSTANT_ALPHA;
    case BlendFactor::OneMinusConstantAlpha:
      return GL_ONE_MINUS_CONSTANT_ALPHA;
    default:
    {
      KRYS_ASSERT(false, "Unknown blend factor!", 0);
      return 0;
    }
    }
  };

  static auto ToGLDrawMode = [](DrawMode mode) -> int
  {
    switch (mode)
    {
    case DrawMode::Points:
      return GL_POINTS;
    case DrawMode::Triangles:
      return GL_TRIANGLES;
    default:
    {
      KRYS_ASSERT(false, "Unknown draw mode!", 0);
      return 0;
    }
    }
  };

  GLGraphicsContext::GLGraphicsContext(HDC deviceContext, HWND window, HINSTANCE instance)
      : _window(window), _instance(instance), _deviceContext(deviceContext), _context(0), _capabilities([this]()
                                                                                                        { return this->LoadGraphicsCapabilities(); })
  {
  }

  GLGraphicsContext::~GLGraphicsContext()
  {
    wglDeleteContext(_context);
  }

  void GLGraphicsContext::Init() noexcept
  {
    // desired pixel format attributes
    const int32 pixelFormatAttribList[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,       // PFD_DRAW_TO_WINDOW
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,       // PFD_SUPPORT_OPENGL
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,        // PFD_DOUBLEBUFFER
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, // PFD_TYPE_RGBA
        WGL_COLOR_BITS_ARB, 32,                // 32 color bits
        WGL_ALPHA_BITS_ARB, 8,                 // 8 alpha bits
        WGL_DEPTH_BITS_ARB, 24,                // 24 depth bits
        // require that the driver supports the pixel format
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        // MSAA16
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0 // end
    };
    int32 pixelFormatId;
    uint pixelFormatCount;

    BOOL chooseFormatSuccess = wglChoosePixelFormatARB(_deviceContext, pixelFormatAttribList, 0, 1, &pixelFormatId, &pixelFormatCount);
    KRYS_ASSERT(chooseFormatSuccess && pixelFormatId && pixelFormatCount, "Cannot find an appropriate pixel format.", 0);

    // set actual pixel format to device context
    PIXELFORMATDESCRIPTOR pfd{};
    BOOL describeFormatSuccess = DescribePixelFormat(_deviceContext, pixelFormatId, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    KRYS_ASSERT(describeFormatSuccess, "Unable to describe pixel format.", 0);

    BOOL setPixelFormatSuccess = SetPixelFormat(_deviceContext, pixelFormatId, &pfd);
    KRYS_ASSERT(setPixelFormatSuccess, "Unable to set pixel format.", 0);

    const uint32 OPENGL_MAJOR = 3;
    const uint32 OPENGL_MINOR = 3;

    int32 contextAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, OPENGL_MAJOR,
        WGL_CONTEXT_MINOR_VERSION_ARB, OPENGL_MINOR,
        0 // end
    };
    _context = wglCreateContextAttribsARB(_deviceContext, 0, contextAttributes);

    BOOL makeCurrentSucess = wglMakeCurrent(_deviceContext, _context);
    KRYS_ASSERT(makeCurrentSucess, "Failed to make the OpenGL context current.", 0);

    int32 version = gladLoaderLoadGL();
    KRYS_ASSERT(version, "Failed to load OpenGL functions.", 0);

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

  const GraphicsCapabilities &GLGraphicsContext::QueryCapabilities() noexcept
  {
    KRYS_PERFORMANCE_TIMER("QueryCapabilities");
    return _capabilities.val();
  }

  GraphicsCapabilities GLGraphicsContext::LoadGraphicsCapabilities() noexcept
  {
    GraphicsCapabilities capabilities{};

    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &capabilities.MaxDrawBuffers);
    glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &capabilities.MaxInputComponents);
    glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &capabilities.MaxOutputComponents);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &capabilities.MaxTextureImageUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &capabilities.MaxTextureSize);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &capabilities.MaxUniformComponents);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &capabilities.MaxUniformBlocks);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &capabilities.MaxVertexAttributes);

    capabilities.Log();
    return capabilities;
  }

  void GLGraphicsContext::Clear(RenderBuffer flags) noexcept
  {
    if (flags == RenderBuffer::None)
      return;

    int glFlags = 0;
    if (flags & RenderBuffer::Color)
      glFlags |= GL_COLOR_BUFFER_BIT;

    if (flags & RenderBuffer::Depth)
      glFlags |= GL_DEPTH_BUFFER_BIT;

    if (flags & RenderBuffer::Stencil)
      glFlags |= GL_STENCIL_BUFFER_BIT;

    KRYS_ASSERT(glFlags != 0, "Invalid flags!", 0);

    glClear(glFlags);
  }

  void GLGraphicsContext::BindScreenFramebuffer(FramebufferBindType bindType) noexcept
  {
    glBindFramebuffer(ToGLFramebufferBindType(bindType), 0);
  }

  void GLGraphicsContext::SetClearColor(const Vec4 &color) noexcept
  {
    glClearColor(color.x, color.y, color.z, color.a);
  }

  void GLGraphicsContext::SetViewport(int width, int height) noexcept
  {
    glViewport(0, 0, width, height);
  }

  void GLGraphicsContext::SetMultisamplingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_MULTISAMPLE, enable);
  }

  void GLGraphicsContext::SetGammaCorrectionEnabled(bool enable) noexcept
  {
    EnableFeature(GL_FRAMEBUFFER_SRGB, enable);
  }

  void GLGraphicsContext::SetFaceCullingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_CULL_FACE, enable);
  }

  void GLGraphicsContext::SetFaceCulling(CullMode mode) noexcept
  {
    int faceCull = ([&mode]()
                    {
      switch (mode)
      {
      case CullMode::Front:
        return GL_FRONT;
      case CullMode::Back:
        return GL_BACK;
      case CullMode::FrontAndBack:
        return GL_FRONT_AND_BACK;
      default:
      {
        KRYS_ASSERT(false, "Invalid CullMode!", 0);
        return 0;
      }
      } })();

    glCullFace(faceCull);
  }

  void GLGraphicsContext::SetWindingOrder(WindingOrder mode) noexcept
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
      KRYS_ASSERT(false, "Invalid CullMode!", 0);
      break;
    }
  }

  void GLGraphicsContext::SetDepthBufferWritingEnabled(bool enable) noexcept
  {
    glDepthMask(enable);
  }

  void GLGraphicsContext::SetClearDepth(float value) noexcept
  {
    glClearDepth(value);
  }

  void GLGraphicsContext::SetDepthTestingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_DEPTH_TEST, enable);
  }

  void GLGraphicsContext::SetDepthRange(float dNear, float dFar) noexcept
  {
    glDepthRange(dNear, dFar);
  }

  void GLGraphicsContext::SetDepthClampingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_DEPTH_CLAMP, enable);
  }

  void GLGraphicsContext::SetDepthTestFunc(DepthTestFunc func) noexcept
  {
    int glFunc = [&func]()
    {
      switch (func)
      {
      case DepthTestFunc::Never:
        return GL_NEVER;
      case DepthTestFunc::Always:
        return GL_ALWAYS;
      case DepthTestFunc::Less:
        return GL_LESS;
      case DepthTestFunc::EqualOrLess:
        return GL_LEQUAL;
      case DepthTestFunc::EqualOrGreater:
        return GL_GEQUAL;
      case DepthTestFunc::Greater:
        return GL_GREATER;
      default:
        KRYS_ASSERT(false, "Invalid depth func!", 0);
        return 0;
      }
    }();

    glDepthFunc(glFunc);
  }

  void GLGraphicsContext::SetStencilTestFunc(StencilTestFunc func, uint8 ref, uint8 mask) noexcept
  {
    int glFunc = [&func]()
    {
      switch (func)
      {
      case StencilTestFunc::Always:
        return GL_ALWAYS;
      case StencilTestFunc::Never:
        return GL_NEVER;
      case StencilTestFunc::Less:
        return GL_LESS;
      case StencilTestFunc::EqualOrLess:
        return GL_LEQUAL;
      case StencilTestFunc::Equal:
        return GL_EQUAL;
      case StencilTestFunc::NotEqual:
        return GL_NOTEQUAL;
      case StencilTestFunc::EqualOrGreater:
        return GL_GEQUAL;
      case StencilTestFunc::Greater:
        return GL_GREATER;
      default:
        KRYS_ASSERT(false, "Invalid stencil func!", 0);
        return 0;
      }
    }();

    glStencilFunc(glFunc, ref, mask);
  }

  void GLGraphicsContext::SetStencilOperation(StencilOperation fail, StencilOperation zFail, StencilOperation zPass) noexcept
  {
    auto ToOpenGLStencilOp = [](StencilOperation op) -> int
    {
      switch (op)
      {
      case StencilOperation::Keep:
        return GL_KEEP;
      case StencilOperation::Zero:
        return GL_ZERO;
      case StencilOperation::Replace:
        return GL_REPLACE;
      case StencilOperation::Decrement:
        return GL_DECR;
      case StencilOperation::Increment:
        return GL_INCR;
      case StencilOperation::DecrementWithWrap:
        return GL_DECR_WRAP;
      case StencilOperation::IncrementWithWrap:
        return GL_INCR_WRAP;
      case StencilOperation::Invert:
        return GL_INVERT;
      default:
        KRYS_ASSERT(false, "Invalid stencil op!", 0);
        return 0;
      }
    };

    glStencilOp(ToOpenGLStencilOp(fail), ToOpenGLStencilOp(zFail), ToOpenGLStencilOp(zPass));
  }

  void GLGraphicsContext::SetStencilTestingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_STENCIL_TEST, enable);
  }

  void GLGraphicsContext::SetStencilBufferWritingEnabled(bool enable) noexcept
  {
    glStencilMask(enable ? 0xFF : 0x00);
  }

  void GLGraphicsContext::SetStencilBufferBitMask(uint8 mask) noexcept
  {
    glStencilMask(mask);
  }

  void GLGraphicsContext::SetBlendingEnabled(bool enable) noexcept
  {
    EnableFeature(GL_BLEND, enable);
  }

  void GLGraphicsContext::SetBlendFunc(BlendFactor srcFactor, BlendFactor dstFactor) noexcept
  {
    glBlendFunc(ToGLBlendFactor(srcFactor), ToGLBlendFactor(dstFactor));
  }

  void GLGraphicsContext::SetBlendFunc(BlendFactor rgbSrcFactor, BlendFactor rgbDstFactor, BlendFactor alphaSrcFactor, BlendFactor alphaDstFactor) noexcept
  {
    glBlendFuncSeparate(ToGLBlendFactor(rgbSrcFactor), ToGLBlendFactor(rgbDstFactor), ToGLBlendFactor(alphaSrcFactor), ToGLBlendFactor(alphaDstFactor));
  }

  void GLGraphicsContext::SetBlendEquation(BlendEquation equation) noexcept
  {
    int blendEquation = ([&equation]()
                         {
      switch (equation)
      {
      case BlendEquation::Add:
        return GL_FUNC_ADD;
      case BlendEquation::Subtract:
        return GL_FUNC_SUBTRACT;
      case BlendEquation::ReverseSubtract:
        return GL_FUNC_REVERSE_SUBTRACT;
      case BlendEquation::Max:
        return GL_MIN;
      case BlendEquation::Min:
        return GL_MAX;
      default:
      {
        KRYS_ASSERT(false, "Unknown BlendEquation!", 0);
        return 0;
      }
      } })();

    glBlendEquation(blendEquation);
  }

  void GLGraphicsContext::SetBlendColor(Vec4 color) noexcept
  {
    glBlendColor(color.r, color.g, color.b, color.a);
  }

  void GLGraphicsContext::SetWireframeModeEnabled(bool enable) noexcept
  {
    glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
  }

  Ref<IndexBuffer> GLGraphicsContext::CreateIndexBuffer(uint32 count) noexcept
  {
    return CreateRef<GLIndexBuffer>(count);
  }

  Ref<IndexBuffer> GLGraphicsContext::CreateIndexBuffer(const uint32 *indices, uint32 count) noexcept
  {
    return CreateRef<GLIndexBuffer>(indices, count);
  }

  Ref<VertexBuffer> GLGraphicsContext::CreateVertexBuffer(uint32 size) noexcept
  {
    return CreateRef<GLVertexBuffer>(size);
  }

  Ref<VertexBuffer> GLGraphicsContext::CreateVertexBuffer(float *vertices, uint32 size) noexcept
  {
    return CreateRef<GLVertexBuffer>(vertices, size);
  }

  Ref<InstanceArrayBuffer> GLGraphicsContext::CreateInstanceArrayBuffer(uint32 size) noexcept
  {
    return CreateRef<GLInstanceArrayBuffer>(size);
  }

  Ref<InstanceArrayBuffer> GLGraphicsContext::CreateInstanceArrayBuffer(void *data, uint32 size) noexcept
  {
    return CreateRef<GLInstanceArrayBuffer>(data, size);
  }

  Ref<VertexArray> GLGraphicsContext::CreateVertexArray() noexcept
  {
    return CreateRef<GLVertexArray>();
  }

  Ref<Shader> GLGraphicsContext::CreateShader() noexcept
  {
    return CreateRef<GLShader>();
  }

  Ref<UniformBuffer> GLGraphicsContext::CreateUniformBuffer(uint32 size, uint32 binding) noexcept
  {
    return CreateRef<GLUniformBuffer>(size, binding);
  }

  Ref<UniformBuffer> GLGraphicsContext::CreateUniformBuffer(uint32 binding, UniformBufferLayout layout) noexcept
  {
    return CreateRef<GLUniformBuffer>(binding, layout);
  }

  Ref<Shader> GLGraphicsContext::CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath)
  {
    auto shader = CreateRef<GLShader>();
    shader->Load(vertexFilepath, fragmentFilepath);
    shader->Link();

    return shader;
  }

  Ref<Shader> GLGraphicsContext::CreateShader(const stringview &vertexFilepath, const stringview &fragmentFilepath, const stringview &geoFilepath)
  {
    auto shader = CreateRef<GLShader>();
    shader->Load(vertexFilepath, fragmentFilepath);
    shader->Load(ShaderType::Geometry, geoFilepath);
    shader->Link();

    return shader;
  }

  Ref<Texture2D> GLGraphicsContext::CreateTexture2D(const string &filepath) noexcept
  {
    return CreateRef<GLTexture2D>(filepath);
  }

  Ref<SubTexture2D> GLGraphicsContext::CreateSubTexture2D(Ref<Texture2D> texture, Vec2 &coords, Vec2 &cellSize, Vec2 &spriteSize) noexcept
  {
    return CreateRef<SubTexture2D>(texture, coords, cellSize, spriteSize);
  }

  Ref<Framebuffer> GLGraphicsContext::CreateFramebuffer(uint32 width, uint32 height, uint32 samples) noexcept
  {
    return CreateRef<GLFramebuffer>(width, height, samples);
  }

  Ref<TextureCubemap> GLGraphicsContext::CreateTextureCubemap(std::array<string, 6> paths) noexcept
  {
    return CreateRef<GLTextureCubemap>(paths);
  }

  Ref<TextureCubemap> GLGraphicsContext::CreateTextureCubemap(uint width, uint height, TextureInternalFormat format) noexcept
  {
    return CreateRef<GLTextureCubemap>(width, height, format);
  }

  void GLGraphicsContext::DrawVertices(size_t count, DrawMode mode) noexcept
  {
    glDrawArrays(ToGLDrawMode(mode), 0, static_cast<GLsizei>(count));
  }

  void GLGraphicsContext::DrawVerticesInstanced(size_t instanceCount, size_t vertexCount, DrawMode mode) noexcept
  {
    glDrawArraysInstanced(ToGLDrawMode(mode), 0, static_cast<GLsizei>(vertexCount), static_cast<GLsizei>(instanceCount));
  }

  void GLGraphicsContext::DrawIndices(size_t count, DrawMode mode) noexcept
  {
    glDrawElements(ToGLDrawMode(mode), static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
  }

  void GLGraphicsContext::DrawIndicesInstanced(size_t instanceCount, size_t indexCount, DrawMode mode) noexcept
  {
    glDrawElementsInstanced(ToGLDrawMode(mode), static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(instanceCount));
  }
}
