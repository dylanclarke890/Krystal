#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Program.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLShader;

  class OpenGLProgram : public Program
  {
  public:
    OpenGLProgram(ProgramHandle handle, OpenGLShader& vertexShader, OpenGLShader& fragmentShader) noexcept;
    ~OpenGLProgram() noexcept override;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    void Link() noexcept;

    NO_DISCARD GLuint GetNativeHandle() const noexcept;

  private:
    GLuint _program;
    OpenGLShader& _vertexShader;
    OpenGLShader& _fragmentShader;
  };
}