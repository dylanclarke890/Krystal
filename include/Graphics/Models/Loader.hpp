#pragma once

#include "Base/Attributes.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "Graphics/VertexLayout.hpp"

namespace Krys::Gfx
{
  enum class ModelLoaderFlags : uint8
  {
    None = 0,
    FlipUVs = 1 << 0,
    GenerateFaceNormals = 1 << 1,
    GenerateVertexNormals = 1 << 2,
    GenerateTangents = 1 << 3,
    GenerateBitangents = 1 << 4,
    Triangulate = 1 << 5,
  };

  ENUM_CLASS_BITWISE_OPERATORS(ModelLoaderFlags, uint8);

  struct Model
  {
    string Name;
    List<VertexData> Vertices;
    List<uint32> Indices;
  };

  /// @brief Load a model from a file.
  /// @param path The path to the model file.
  NO_DISCARD Expected<Model> LoadModel(const stringview &path,
                                       ModelLoaderFlags flags = ModelLoaderFlags::None) noexcept;
}