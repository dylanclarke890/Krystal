#pragma once

#include "Graphics/Handles.hpp"
#include "Graphics/Pipeline.hpp"

#include <glad/gl.h>

namespace Krys::Graphics::OpenGL
{
  class OpenGLPipeline : public Pipeline
  {
  public:
    OpenGLPipeline() noexcept;
    ~OpenGLPipeline() noexcept override;

    void Bind() noexcept override;
    void Unbind() noexcept override;

    void Link() noexcept override;
    void AddShader(ShaderHandle handle) noexcept override;

  private:
    GLuint _program;
  };
}