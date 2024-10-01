#pragma once

#include "Graphics/Textures/Texture2D.h"
#include "Maths/Maths.h"

namespace Krys
{
  class Material
  {
  public:
    Ref<Texture2D> Diffuse;
    Ref<Texture2D> Specular;
    Ref<Texture2D> Emission;
    Ref<Texture2D> Normal;
    Ref<Texture2D> Displacement;
    Vec4 Tint;
    float Shininess;

    Material(Ref<Texture2D> texture)
        : Diffuse(texture), Specular(nullptr),
          Emission(nullptr), Normal(nullptr),
          Tint(1.0f), Shininess(32.0f) {}
  };

  struct Vertex
  {
    Vec3 Position;
    Vec3 Normal;
    Vec2 TextureCoords;
  };

  class Mesh
  {
  protected:
    List<Vertex> Vertices;
    List<uint32> Indices;
    List<Ref<Texture2D>> Textures;

  public:
    virtual ~Mesh() = default;

    const List<Ref<Texture2D>> GetTextures() const noexcept
    {
      return Textures;
    }

    const List<uint32> GetIndices() const noexcept
    {
      return Indices;
    }

    const List<Vertex> GetVertices() const noexcept
    {
      return Vertices;
    }

    virtual void Setup() = 0;
    virtual void Draw(Ref<Shader> shader) const = 0;
  };
}