#pragma once

#include "Types.h"
#include "Maths/Vector.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  enum class ShaderType
  {
    None = 0,
    Fragment,
    Vertex,
    Geometry
  };

  class Shader
  {
  protected:
    uint32 _id;

  public:
    virtual ~Shader() = default;

    NO_DISCARD uint32 GetId() const noexcept { return _id; }

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void Load(const stringview &vertexFilepath, const stringview &fragmentFilepath) = 0;
    virtual void Load(ShaderType type, const stringview &filepath) = 0;
    virtual void Add(ShaderType type, const stringview &source) = 0;

    virtual void Link() = 0;

    virtual void SetUniform(const string &name, int value) = 0;
    virtual void TrySetUniform(const string &name, int value) = 0;
    virtual void SetUniform(const string &name, float value) = 0;
    virtual void TrySetUniform(const string &name, float value) = 0;
    virtual void SetUniform(const string &name, float *values, uint32_t count) = 0;
    virtual void TrySetUniform(const string &name, float *values, uint32_t count) = 0;
    virtual void SetUniform(const string &name, int *values, uint32_t count) = 0;
    virtual void TrySetUniform(const string &name, int *values, uint32_t count) = 0;
    virtual void SetUniform(const string &name, const Vec2 &value) = 0;
    virtual void TrySetUniform(const string &name, const Vec2 &value) = 0;
    virtual void SetUniform(const string &name, const Vec3 &value) = 0;
    virtual void TrySetUniform(const string &name, const Vec3 &value) = 0;
    virtual void SetUniform(const string &name, const Vec4 &value) = 0;
    virtual void TrySetUniform(const string &name, const Vec4 &value) = 0;
    virtual void SetUniform(const string &name, const Mat3 &matrix) = 0;
    virtual void TrySetUniform(const string &name, const Mat3 &matrix) = 0;
    virtual void SetUniform(const string &name, const Mat4 &matrix) = 0;
    virtual void TrySetUniform(const string &name, const Mat4 &matrix) = 0;
  };
}