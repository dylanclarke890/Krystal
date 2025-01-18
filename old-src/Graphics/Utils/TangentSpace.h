#pragma once

#include "Types.h"
#include "Maths/Vector.h"
#include "Graphics/Graphics.h"
#include "Graphics/Vertex.h"

namespace Krys::Gfx
{
  using namespace Krys::Maths;

  inline void CalculateTangents(List<Vertex> &vertices, const List<uint32> &indices)
  {
    List<Vec3> tangents(vertices.size());

    for (size_t i = 0; i < indices.size(); i += 3)
    {
      uint32_t i0 = indices[i + 0];
      uint32_t i1 = indices[i + 1];
      uint32_t i2 = indices[i + 2];

      const Vec3 &v0 = Vec3(vertices[i0].Position);
      const Vec3 &v1 = Vec3(vertices[i1].Position);
      const Vec3 &v2 = Vec3(vertices[i2].Position);

      const Vec2 &uv0 = vertices[i0].TextureCoords;
      const Vec2 &uv1 = vertices[i1].TextureCoords;
      const Vec2 &uv2 = vertices[i2].TextureCoords;

      Vec3 deltaPos1 = v1 - v0;
      Vec3 deltaPos2 = v2 - v0;

      Vec2 deltaUV1 = uv1 - uv0;
      Vec2 deltaUV2 = uv2 - uv0;

      float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
      Vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
      // We can calculate this on the gpu side to reduce the data load
      // Vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

      tangents[i0] = tangent;
      tangents[i1] = tangent;
      tangents[i2] = tangent;
    }

    for (size_t i = 0; i < vertices.size(); i++)
    {
      const Vec3 &n = vertices[i].Normal;
      const Vec3 &t = tangents[i];

      // Gram-Schmidt orthogonalize
      vertices[i].Tangent = glm::normalize(t - n * glm::dot(n, t));
    }
  }
}