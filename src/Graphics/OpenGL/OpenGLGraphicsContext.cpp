#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Logger.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLPipeline.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"

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

  void OpenGLMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei,
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

  void OpenGLGraphicsContext::Clear() noexcept
  {
    ::glClear(GL_COLOR_BUFFER_BIT);
  }

  VertexBufferHandle OpenGLGraphicsContext::CreateVertexBuffer(uint32 size) noexcept
  {
    auto buffer = CreateUnique<OpenGLVertexBuffer>(size);
    auto handle = buffer->GetHandle();

    buffer->Bind();
    _vertexBuffers[handle] = std::move(buffer);
    return handle;
  }

  IndexBufferHandle OpenGLGraphicsContext::CreateIndexBuffer(uint32 size) noexcept
  {
    auto buffer = CreateUnique<OpenGLIndexBuffer>(size);
    auto handle = buffer->GetHandle();

    _indexBuffers[handle] = std::move(buffer);
    return handle;
  }

  ShaderHandle OpenGLGraphicsContext::CreateShader(const ShaderDescriptor &description) noexcept
  {
    auto shader = CreateUnique<OpenGLShader>(description);
    auto handle = shader->GetHandle();

    _shaders[handle] = std::move(shader);
    return handle;
  }

  PipelineHandle OpenGLGraphicsContext::CreatePipeline() noexcept
  {
    auto pipeline = CreateUnique<OpenGLPipeline>();
    auto handle = pipeline->GetHandle();

    _pipelines[handle] = std::move(pipeline);
    return handle;
  }
}