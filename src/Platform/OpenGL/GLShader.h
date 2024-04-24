#pragma once

#include <vector>

#include "Graphics/Shader.h"
#include "GL.h"

namespace Krys
{
  class GLShader : public Shader
  {
  private:
    GLRendererId Id;
    std::vector<GLRendererId> Shaders;

  public:
    GLShader();
    ~GLShader() override;

    void Bind() override;
    void Unbind() override;

    void Load(ShaderType type, const char *filepath) override;
    void Add(ShaderType type, const char *source) override;

    void Link() override;

  private:
    static GLenum ToGLShaderType(ShaderType type);
  };
}