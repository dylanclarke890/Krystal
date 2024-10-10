#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Krys
{
  typedef glm::vec2 Vec2;
  typedef glm::vec3 Vec3;
  typedef glm::vec4 Vec4;

  typedef glm::ivec2 Vec2i;
  typedef glm::ivec3 Vec3i;
  typedef glm::ivec4 Vec4i;

  typedef glm::mat2 Mat2;
  typedef glm::mat3 Mat3;

  /// @brief Mat3 Identity Matrix.
  constexpr Mat3 MAT3_I = Mat3(1.0f);
  typedef glm::mat4 Mat4;

  /// @brief Mat4 Identity Matrix.
  constexpr Mat4 MAT4_I = Mat4(1.0f);

  constexpr Vec3 ROTATE_AXIS_X = Vec3(1.0f, 0.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Y = Vec3(0.0f, 1.0f, 0.0f);
  constexpr Vec3 ROTATE_AXIS_Z = Vec3(0.0f, 0.0f, 1.0f);

  constexpr float PI32 = 3.1415927f;
  constexpr double PI64 = 3.141592653589793;

  inline constexpr float DegToRad(float degrees) noexcept
  {
    constexpr float ratio = PI32 * 2.0f / 360.0f;
    return degrees * ratio;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Max(const T &a, const T &b) noexcept
  {
    return a > b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Min(const T &a, const T &b) noexcept
  {
    return a < b ? a : b;
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  constexpr T Clamp(T value, T min, T max) noexcept
  {
    return Min<T>(Max<T>(value, min), max);
  }

  template <typename T>
  REQUIRES(std::is_integral_v<T> || std::is_floating_point_v<T>)
  struct BoundingBox
  {
    T Left, Right, Bottom, Top;

    BoundingBox() noexcept = default;
    constexpr BoundingBox(T left, T right, T bottom, T top) noexcept
        : Left(left), Right(right), Bottom(bottom), Top(top) {}

    constexpr T GetWidth() { return Right - Left; }
    constexpr T GetHeight() { return Top - Bottom; }
  };

  // inline constexpr void CalculateTangents(std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
  // {
  //   // Initialize tangents
  //   std::vector<Vec3> tan1(vertices.size(), Vec3(0.0f));
  //   std::vector<Vec3> tan2(vertices.size(), Vec3(0.0f));

  //   for (size_t i = 0; i < indices.size(); i += 3)
  //   {
  //     uint32_t i0 = indices[i + 0];
  //     uint32_t i1 = indices[i + 1];
  //     uint32_t i2 = indices[i + 2];

  //     const Vec3 &v0 = Vec3(vertices[i0].Position);
  //     const Vec3 &v1 = Vec3(vertices[i1].Position);
  //     const Vec3 &v2 = Vec3(vertices[i2].Position);

  //     const Vec2 &uv0 = vertices[i0].TextureCoords;
  //     const Vec2 &uv1 = vertices[i1].TextureCoords;
  //     const Vec2 &uv2 = vertices[i2].TextureCoords;

  //     Vec3 deltaPos1 = v1 - v0;
  //     Vec3 deltaPos2 = v2 - v0;

  //     Vec2 deltaUV1 = uv1 - uv0;
  //     Vec2 deltaUV2 = uv2 - uv0;

  //     float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
  //     Vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
  //     Vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

  //     tan1[i0] += tangent;
  //     tan1[i1] += tangent;
  //     tan1[i2] += tangent;

  //     tan2[i0] += bitangent;
  //     tan2[i1] += bitangent;
  //     tan2[i2] += bitangent;
  //   }

  //   for (size_t i = 0; i < vertices.size(); i++)
  //   {
  //     const Vec3 &n = vertices[i].Normal;
  //     const Vec3 &t = tan1[i];

  //     // Gram-Schmidt orthogonalize
  //     vertices[i].Tangent = glm::normalize(t - n * glm::dot(n, t));

  //     // Calculate handedness (not always needed)
  //     // float handedness = (glm::dot(glm::cross(n, t), tan2[i]) < 0.0f) ? -1.0f : 1.0f;
  //     // vertices[i].Tangent *= handedness;
  //   }
  // }
}