#pragma once

#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"

namespace Krys::Gfx
{
  // TODO: right now we support both meshes and VBOs
  // consider splitting this into two separate commands
  struct RenderCommand
  {
    ProgramHandle Program;
    MeshHandle Mesh;
    PrimitiveType Type {PrimitiveType::Triangles};
  };
}