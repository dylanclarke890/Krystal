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

    void SetUniform(const char *name, int value) override;
    void SetUniform(const char *name, float value) override;
    void SetUniform(const char *name, int *values, uint32_t count) override;
    void SetUniform(const char *name, float *values, uint32_t count) override;
    void SetUniform(const char *name, const Vec2 &value) override;
    void SetUniform(const char *name, const Vec3 &value) override;
    void SetUniform(const char *name, const Vec4 &value) override;
    void SetUniform(const char *name, const Mat3 &matrix) override;
    void SetUniform(const char *name, const Mat4 &matrix) override;

  private:
    static GLenum ToGLShaderType(ShaderType type);
  };
}