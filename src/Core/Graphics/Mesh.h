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
    Vec4 Tint;
    float Shininess;

    Material(Ref<Texture2D> texture, Ref<Texture2D> specularMap = nullptr, Ref<Texture2D> emissionMap = nullptr)
        : Diffuse(texture), Specular(specularMap), Emission(emissionMap), Tint(1.0f), Shininess(32.0f) {}
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
    std::vector<Vertex> Vertices;
    std::vector<uint32> Indices;
    std::vector<Ref<Texture2D>> Textures;

  public:
    virtual ~Mesh() = default;

    const std::vector<Ref<Texture2D>> GetTextures() const noexcept
    {
      return Textures;
    }

    const std::vector<uint32> GetIndices() const noexcept
    {
      return Indices;
    }

    const std::vector<Vertex> GetVertices() const noexcept
    {
      return Vertices;
    }

    virtual void Setup() = 0;
    virtual void Draw(Ref<Shader> shader) const = 0;
  };
}