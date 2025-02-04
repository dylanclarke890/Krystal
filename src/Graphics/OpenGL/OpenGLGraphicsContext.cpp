#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Debug/Macros.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "IO/Logger.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  constexpr GLuint ToOpenGLEnum(PrimitiveType type) noexcept
  {
    switch (type)
    {
      case PrimitiveType::Points:        return GL_POINTS;
      case PrimitiveType::Lines:         return GL_LINES;
      case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
      case PrimitiveType::LineLoop:      return GL_LINE_LOOP;
      case PrimitiveType::Triangles:     return GL_TRIANGLES;
      case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
      case PrimitiveType::TriangleFan:   return GL_TRIANGLE_FAN;
      default:                           return 0;
    }
  }

  static void OpenGLMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei,
                                    const char *msg, const void *)
  {
    switch (severity)
    {
      case GL_DEBUG_SEVERITY_HIGH:         Logger::Fatal("OPENGL ({0}): {1}", id, msg); break;
      case GL_DEBUG_SEVERITY_MEDIUM:       Logger::Error("OPENGL ({0}): {1}", id, msg); break;
      case GL_DEBUG_SEVERITY_LOW:          Logger::Error("OPENGL ({0}): {1}", id, msg); break;
      case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Info("OPENGL ({0}): {1}", id, msg); break;
      default:                             KRYS_ASSERT(false, "Unknown enum value: OpenGL severity level"); break;
    }

    Logger::Write(" - Type: ");
    switch (type)
    {
      case GL_DEBUG_TYPE_ERROR:               Logger::Write("Error"); break;
      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: Logger::Write("Deprecated Behavior"); break;
      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  Logger::Write("Undefined Behavior"); break;
      case GL_DEBUG_TYPE_PORTABILITY:         Logger::Write("Portability"); break;
      case GL_DEBUG_TYPE_PERFORMANCE:         Logger::Write("Performance"); break;
      case GL_DEBUG_TYPE_MARKER:              Logger::Write("Marker"); break;
      case GL_DEBUG_TYPE_PUSH_GROUP:          Logger::Write("Push Group"); break;
      case GL_DEBUG_TYPE_POP_GROUP:           Logger::Write("Pop Group"); break;
      case GL_DEBUG_TYPE_OTHER:               Logger::Write("Other"); break;
      default:                                KRYS_ASSERT(false, "Unknown enum value: OpenGL message type"); break;
    }
    Logger::NewLine();

    Logger::Write(" - Source: ");
    switch (source)
    {
      case GL_DEBUG_SOURCE_API:             Logger::Write("API"); break;
      case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   Logger::Write("Window System"); break;
      case GL_DEBUG_SOURCE_SHADER_COMPILER: Logger::Write("Shader Compiler"); break;
      case GL_DEBUG_SOURCE_THIRD_PARTY:     Logger::Write("Third Party"); break;
      case GL_DEBUG_SOURCE_APPLICATION:     Logger::Write("Application"); break;
      case GL_DEBUG_SOURCE_OTHER:           Logger::Write("Other"); break;
      default:                              KRYS_ASSERT(false, "Unknown enum value: OpenGL source type"); break;
    }
    Logger::NewLine();

    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
      KRYS_ASSERT(false, "OpenGL error");
  }

  static void LoadDeviceCapabilities(DeviceCapabilities &deviceCapabilities) noexcept
  {
    ::glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &deviceCapabilities.MaxShaderStorageBlockSize);
  }

  OpenGLGraphicsContext::OpenGLGraphicsContext() noexcept
  {
  }

  OpenGLGraphicsContext::~OpenGLGraphicsContext() noexcept
  {
  }

  void OpenGLGraphicsContext::Init() noexcept
  {
    ::glEnable(GL_DEBUG_OUTPUT);
    ::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    ::glDebugMessageCallback(OpenGLMessageCallback, nullptr);

    LoadDeviceCapabilities(_deviceCapabilities);

    ::glEnable(GL_DEPTH_TEST);
  }

  void OpenGLGraphicsContext::SetViewport(const Vec4ui &viewport) noexcept
  {
    ::glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
  }

  void OpenGLGraphicsContext::DrawArrays(PrimitiveType type, uint32 count) noexcept
  {
    ::glDrawArrays(ToOpenGLEnum(type), 0, count);
  }

  void OpenGLGraphicsContext::DrawElements(PrimitiveType type, uint32 count) noexcept
  {
    ::glDrawElements(ToOpenGLEnum(type), count, GL_UNSIGNED_INT, nullptr);
  }

  void OpenGLGraphicsContext::SetClearColour(const Colour &colour) noexcept
  {
    if (_clearColour == colour)
      return;

    ::glClearColor(colour.r, colour.g, colour.b, colour.a);
    _clearColour = colour;
  }

  void OpenGLGraphicsContext::Clear(ClearBuffer flags) noexcept
  {
    GLint mask = 0;

    if ((flags & ClearBuffer::Colour) == ClearBuffer::Colour)
      mask |= GL_COLOR_BUFFER_BIT;

    if ((flags & ClearBuffer::Depth) == ClearBuffer::Depth)
      mask |= GL_DEPTH_BUFFER_BIT;

    if ((flags & ClearBuffer::Stencil) == ClearBuffer::Stencil)
      mask |= GL_STENCIL_BUFFER_BIT;

    ::glClear(mask);
  }

  Unique<Program> OpenGLGraphicsContext::CreateProgramImpl(ProgramHandle handle, ShaderHandle vertexShader,
                                                           ShaderHandle fragmentShader) noexcept
  {
    auto &vertex = *static_cast<OpenGLShader *>(GetShader(vertexShader));
    auto &fragment = *static_cast<OpenGLShader *>(GetShader(fragmentShader));
    return CreateUnique<OpenGLProgram>(handle, vertex, fragment);
  }

  Unique<Shader> OpenGLGraphicsContext::CreateShaderImpl(ShaderHandle handle, ShaderStage stage,
                                                         const string &source) noexcept
  {
    return CreateUnique<OpenGLShader>(handle, stage, source);
  }

  Unique<VertexBuffer> OpenGLGraphicsContext::CreateVertexBufferImpl(VertexBufferHandle handle,
                                                                     uint32 size) noexcept
  {
    return CreateUnique<OpenGLVertexBuffer>(handle, size);
  }

  Unique<IndexBuffer> OpenGLGraphicsContext::CreateIndexBufferImpl(IndexBufferHandle handle,
                                                                   uint32 size) noexcept
  {
    return CreateUnique<OpenGLIndexBuffer>(handle, size);
  }

  Unique<UniformBuffer> OpenGLGraphicsContext::CreateUniformBufferImpl(UniformBufferHandle handle,
                                                                       uint32 size) noexcept
  {
    return CreateUnique<OpenGLUniformBuffer>(handle, size);
  }

  Unique<ShaderStorageBuffer>
    OpenGLGraphicsContext::CreateShaderStorageBufferImpl(ShaderStorageBufferHandle handle,
                                                         uint32 size) noexcept
  {
    return CreateUnique<OpenGLShaderStorageBuffer>(handle, size);
  }
}