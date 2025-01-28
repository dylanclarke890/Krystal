#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Core/Debug/Macros.hpp"
#include "Core/Logger.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  constexpr GLenum ToOpenGLEnum(ShaderStage stage) noexcept
  {
    switch (stage)
    {
      case ShaderStage::Vertex:   return GL_VERTEX_SHADER; break;
      case ShaderStage::Fragment: return GL_FRAGMENT_SHADER; break;
      default:                    return 0; break;
    }
  }

  OpenGLShader::OpenGLShader(ShaderHandle handle, ShaderStage stage, const string &source) noexcept
      : Shader(handle, stage), _id(::glCreateShader(ToOpenGLEnum(stage)))
  {
    KRYS_ASSERT(_id != 0, "Failed to create shader");

    const char *src = source.c_str();
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
    // We don't do this here because they are deleted after the program is linked
    // ::glDeleteShader(_id);
  }

  GLuint OpenGLShader::GetNativeHandle() const noexcept
  {
    return _id;
  }
}