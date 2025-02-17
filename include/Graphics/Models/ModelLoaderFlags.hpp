#pragma once

#include "Base/Types.hpp"
#include "Base/Macros.hpp"

namespace Krys::Gfx
{
  enum class ModelLoaderFlags : uint8
  {
    None = 0,
    FlipUVs = 1 << 0,
    GenerateNormals = 1 << 1,
    GenerateTangents = 1 << 2,
    GenerateBitangents = 1 << 3,
    Triangulate = 1 << 4,
    RemoveDuplicateVertices = 1 << 5,
  };

  ENUM_CLASS_BITWISE_OPERATORS(ModelLoaderFlags, uint8);
}