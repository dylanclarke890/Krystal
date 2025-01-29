#pragma once

#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"

namespace Krys::Gfx
{
  struct RenderCommand
  {
    ProgramHandle Program;
    MeshHandle Mesh;
    MaterialHandle Material;
    PrimitiveType Type {PrimitiveType::Triangles};
  };
}