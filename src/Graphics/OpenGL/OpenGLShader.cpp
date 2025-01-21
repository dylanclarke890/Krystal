#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Logger.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  constexpr GLenum ShaderStageToOpenGL(ShaderStage stage) noexcept
  {
    switch (stage)
    {
      case ShaderStage::Vertex:   return GL_VERTEX_SHADER; break;
      case ShaderStage::Fragment: return GL_FRAGMENT_SHADER; break;
      default:                    return 0; break;
    }
  }

  OpenGLShader::OpenGLShader(const ShaderDescriptor &description) noexcept : Shader(description), _id(0u)
  {
    GLenum stage = ShaderStageToOpenGL(description.Stage);
    _id = ::glCreateShader(stage);

    KRYS_ASSERT(_id != 0, "Failed to create shader");
    _handle = ShaderHandle(static_cast<ShaderHandle::handle_t>(_id));

    const char *src = description.Source.c_str();
    ::glShaderSource(_id, 1, &src, nullptr);
    ::glCompileShader(_id);

    int success;
    ::glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      ::glGetShaderInfoLog(_id, 512, nullptr, infoLog);
      KRYS_ASSERT(false, "Shader compilation failed: {0}", infoLog);
    }
  }

  OpenGLShader::~OpenGLShader() noexcept
  {
    ::glDeleteShader(_handle.Id());
  }

  GLuint OpenGLShader::GetNativeHandle() const noexcept
  {
    return _id;
  }
}