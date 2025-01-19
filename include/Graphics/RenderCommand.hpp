#pragma once

#include "Base/Types.hpp"
#include "Base/Pointers.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Mesh.hpp"

namespace Krys::Gfx
{
  struct RenderCommand
  {
    PipelineHandle Pipeline {PipelineHandle::InvalidHandle};
    Mesh *Mesh {nullptr};
    VertexBufferHandle VBO {PipelineHandle::InvalidHandle};
    IndexBufferHandle EBO {PipelineHandle::InvalidHandle};
    PrimitiveType Type{PrimitiveType::Triangles};
    uint32 Count;
  };
}