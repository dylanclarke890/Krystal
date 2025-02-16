#pragma once

#include "Base/Types.hpp"
#include "Base/Macros.hpp"

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
    DeduplicateVertices = 1 << 6,
  };

  ENUM_CLASS_BITWISE_OPERATORS(ModelLoaderFlags, uint8);
}