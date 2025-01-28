#include "Graphics/OpenGL/OpenGLProgram.hpp"
#include "Core/Debug/Macros.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"

namespace Krys::Gfx::OpenGL
{
  OpenGLProgram::OpenGLProgram(ProgramHandle handle, OpenGLShader &vertexShader,
                               OpenGLShader &fragmentShader) noexcept
      : Program(handle), _program(::glCreateProgram()), _vertexShader(vertexShader),
        _fragmentShader(fragmentShader)
  {
    Link();
  }

  OpenGLProgram::~OpenGLProgram() noexcept
  {
    ::glDeleteProgram(_program);
  }

  void OpenGLProgram::Bind() noexcept
  {
    KRYS_ASSERT(_handle.IsValid() && _linked && _isValid, "Program must be valid and linked before binding");
    ::glUseProgram(_program);
  }

  void OpenGLProgram::Unbind() noexcept
  {
    KRYS_ASSERT(_handle.IsValid() && _linked && _isValid,
                "Program must be valid and linked before unbinding");
    ::glUseProgram(0);
  }

  void OpenGLProgram::Link() noexcept
  {
    KRYS_ASSERT(_handle.IsValid(), "Program must be valid before linking");
    KRYS_ASSERT(!_linked, "Program is already linked");
    KRYS_ASSERT(_vertexShader.GetHandle().IsValid(), "Vertex shader must be valid");
    KRYS_ASSERT(_fragmentShader.GetHandle().IsValid(), "Fragment shader must be valid");

    ::glAttachShader(_program, _vertexShader.GetNativeHandle());
    ::glAttachShader(_program, _fragmentShader.GetNativeHandle());

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

    ::glDeleteShader(_vertexShader.GetNativeHandle());
    ::glDeleteShader(_fragmentShader.GetNativeHandle());
  }

  GLuint OpenGLProgram::GetNativeHandle() const noexcept
  {
    return _program;
  }
}