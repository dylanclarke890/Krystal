#pragma once

#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  struct Renderable
  {
    string Name;
    MeshHandle Mesh;
    MaterialHandle Material;
  };

  struct Model
  {
    string Name;
    List<Renderable> Renderables;
  };
}