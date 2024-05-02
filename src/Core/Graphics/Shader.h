#pragma once

#include "Maths/Maths.h"

namespace Krys
{
  enum class ShaderType
  {
    None = 0,
    Fragment,
    Vertex,
    Geometry
  };

  class Shader
  {
  public:
    virtual ~Shader() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Load(ShaderType type, const char *filepath) = 0;
    virtual void Add(ShaderType type, const char *source) = 0;

    virtual void Link() = 0;

    virtual void SetUniform(const char *name, int value) = 0;
    virtual void SetUniform(const char *name, float value) = 0;
    virtual void SetUniform(const char *name, float *values, uint32_t count) = 0;
    virtual void SetUniform(const char *name, int *values, uint32_t count) = 0;
    virtual void SetUniform(const char *name, const Vec2 &value) = 0;
    virtual void SetUniform(const char *name, const Vec3 &value) = 0;
    virtual void SetUniform(const char *name, const Vec4 &value) = 0;
    virtual void SetUniform(const char *name, const Mat3 &matrix) = 0;
    virtual void SetUniform(const char *name, const Mat4 &matrix) = 0;
  };
}