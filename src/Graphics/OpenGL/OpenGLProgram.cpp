#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Core/Debug/Macros.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLProgram::OpenGLProgram() noexcept : Program(), _program(::glCreateProgram())
  {
    _handle = ProgramHandle(static_cast<ProgramHandle::handle_t>(_program));
  }

  OpenGLProgram::~OpenGLProgram() noexcept
  {
    ::glDeleteProgram(_program);
  }

  void OpenGLProgram::Bind() noexcept
  {
    KRYS_ASSERT(_linked && _isValid, "Pipeline must be valid and linked before binding");
    ::glUseProgram(_program);
  }

  void OpenGLProgram::Unbind() noexcept
  {
    KRYS_ASSERT(_linked && _isValid, "Pipeline must be valid and linked before unbinding");
    ::glUseProgram(0);
  }

  void OpenGLProgram::Link() noexcept
  {
    KRYS_ASSERT(!_linked, "Pipeline is already linked");

    for (auto shader : _shaders)
    {
      ::glAttachShader(_program, shader.Id());
    }

    ::glLinkProgram(_program);
    _linked = true;

    int success;
    ::glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      ::glGetProgramInfoLog(_program, 512, nullptr, infoLog);
      KRYS_ASSERT(false, "Program linking failed: {0}", infoLog);
    }
    _isValid = true;

    for (auto shader : _shaders)
    {
      ::glDeleteShader(shader.Id());
    }
  }

  void OpenGLProgram::AddShader(ShaderHandle handle) noexcept
  {
    _shaders.push_back(handle);
  }
}