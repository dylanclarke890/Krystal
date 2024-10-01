#pragma once

#include <vector>

#include "Krystal.h"
#include "Graphics/Shaders/Shader.h"
#include "GL.h"

namespace Krys
{
  class GLShader : public Shader
  {
  private:
    uint Id;
    std::vector<uint> Shaders;

  public:
    GLShader();
    ~GLShader() override;

    void Bind() override;
    void Unbind() override;

    void Load(ShaderType type, const stringview &filepath) override;
    void Load(const stringview &vertexFilepath, const stringview &fragmentFilepath) override;
    void Add(ShaderType type, const stringview &source) override;

    void Link() override;

    void SetUniform(const string &name, int value) override;
    void TrySetUniform(const string &name, int value) override;
    void SetUniform(const string &name, float value) override;
    void TrySetUniform(const string &name, float value) override;
    void SetUniform(const string &name, int *values, uint32_t count) override;
    void TrySetUniform(const string &name, int *values, uint32_t count) override;
    void SetUniform(const string &name, float *values, uint32_t count) override;
    void TrySetUniform(const string &name, float *values, uint32_t count) override;
    void SetUniform(const string &name, const Vec2 &value) override;
    void TrySetUniform(const string &name, const Vec2 &value) override;
    void SetUniform(const string &name, const Vec3 &value) override;
    void TrySetUniform(const string &name, const Vec3 &value) override;
    void SetUniform(const string &name, const Vec4 &value) override;
    void TrySetUniform(const string &name, const Vec4 &value) override;
    void SetUniform(const string &name, const Mat3 &matrix) override;
    void TrySetUniform(const string &name, const Mat3 &matrix) override;
    void SetUniform(const string &name, const Mat4 &matrix) override;
    void TrySetUniform(const string &name, const Mat4 &matrix) override;

  private:
    static GLenum ToGLShaderType(ShaderType type);
  };
}