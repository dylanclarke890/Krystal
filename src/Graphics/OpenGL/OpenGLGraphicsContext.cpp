#include "Graphics/OpenGL/OpenGLGraphicsContext.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Logger.hpp"
#include "Graphics/OpenGL/OpenGLBuffer.hpp"
#include "Graphics/OpenGL/OpenGLPipeline.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"

#include <glad/gl.h>

namespace Krys::Graphics::OpenGL
{
  constexpr GLuint PrimitiveTypeToOpenGL(PrimitiveType type) noexcept
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

  constexpr void OpenGLMessageCallback(uint source, uint type, uint id, uint severity, int length,
                                       const char *message, const void *)
  {
    switch (severity)
    {
      case GL_DEBUG_SEVERITY_HIGH:
        Logger::Fatal(message);
        KRYS_ASSERT(false, "OPENGL: Error (HIGH) - Id: {0}, Source: {1}, Type: {2}, Length {3}", id, source,
                    type, length);
        break;
      case GL_DEBUG_SEVERITY_MEDIUM:
        Logger::Error(message);
        KRYS_ASSERT(false, "OPENGL: Error (MEDIUM) - Id: {0}, Source: {1}, Type: {2}, Length {3}", id, source,
                    type, length);
        break;
      case GL_DEBUG_SEVERITY_LOW:
        Logger::Error(message);
        KRYS_ASSERT(false, "OPENGL: Error (LOW) - Id: {0}, Source: {1}, Type: {2}, Length {3}", id, source,
                    type, length);
        break;
      case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Info(message); break;
      default:                             KRYS_ASSERT(false, "Unknown severity level!", 0); break;
    }
  }

  OpenGLGraphicsContext::OpenGLGraphicsContext() noexcept
  {
  }

  OpenGLGraphicsContext::~OpenGLGraphicsContext() noexcept
  {
  }

  void OpenGLGraphicsContext::Init() noexcept
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
  }

  void OpenGLGraphicsContext::DrawArrays(const PipelineHandle &pipelineHandle,
                                         const VertexBufferHandle &vertexBufferHandle, PrimitiveType type,
                                         uint32 first, uint32 count) noexcept
  {
    auto &pipeline = GetPipeline(pipelineHandle);
    auto &vertexBuffer = GetVertexBuffer(vertexBufferHandle);

    pipeline.Bind();
    vertexBuffer.Bind();

    glDrawArrays(PrimitiveTypeToOpenGL(type), first, count);
  }

  void OpenGLGraphicsContext::SetClearColor(const Vec3 &rgb) noexcept
  {
    glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
    _clearColor = Vec4(rgb.x, rgb.y, rgb.z, 1.0f);
  }

  void OpenGLGraphicsContext::SetClearColor(const Vec4 &rgba) noexcept
  {
    glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
    _clearColor = rgba;
  }

  void OpenGLGraphicsContext::Clear() noexcept
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  VertexBufferHandle OpenGLGraphicsContext::CreateVertexBuffer(uint32 size) noexcept
  {
    auto buffer = CreateUnique<OpenGLVertexBuffer>(size);
    auto handle = buffer->GetHandle();

    buffer->Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(0));

    _vertexBuffers[handle] = std::move(buffer);
    return handle;
  }

  ShaderHandle OpenGLGraphicsContext::CreateShader(const ShaderDescription &description) noexcept
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