#pragma once

#include "Types.h"
#include "Graphics/Enums.h"
#include "Graphics/Vertex.h"

namespace Krys::Graphics
{
  struct Mesh
  {
    PrimitiveType PrimitiveType = PrimitiveType::Triangles;
    List<Vertex> Vertices;
    List<uint32> Indices;
  };
}