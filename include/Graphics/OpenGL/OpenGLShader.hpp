#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Shader.hpp"

#include <glad/gl.h>

namespace Krys::Gfx::OpenGL
{
  class OpenGLShader : public Shader
  {
  public:
    OpenGLShader(ShaderHandle handle, ShaderStage stage, const string &source) noexcept;
    ~OpenGLShader() noexcept override;

    NO_DISCARD GLuint GetNativeHandle() const noexcept;

  private:
    GLuint _id;
  };
}