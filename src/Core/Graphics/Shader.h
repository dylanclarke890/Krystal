#pragma once

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
  };
}