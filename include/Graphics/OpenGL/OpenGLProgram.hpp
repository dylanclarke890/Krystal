#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/Program.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLProgram : public Program
  {
  public:
    OpenGLProgram() noexcept;
    ~OpenGLProgram() noexcept override;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    void Link() noexcept override;
    void AddShader(ShaderHandle handle) noexcept override;

  private:
    GLuint _program;
  };
}