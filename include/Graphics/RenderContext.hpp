#pragma once

#include "Base/Pointers.hpp"

namespace Krys::Gfx
{
  class MeshManager;
  class TextureManager;
  class MaterialManager;
  class GraphicsContext;
  class LightManager;

  struct RenderContext final
  {
    RenderContext(Ptr<GraphicsContext> graphicsContext, Ptr<MeshManager> meshManager,
                  Ptr<TextureManager> textureManager, Ptr<MaterialManager> materialManager,
                  Ptr<LightManager> lightManager) noexcept
        : GraphicsContext {graphicsContext}, MeshManager {meshManager}, TextureManager {textureManager},
          MaterialManager {materialManager}, LightManager {lightManager}
    {
    }

    Ptr<GraphicsContext> GraphicsContext {nullptr};
    Ptr<MeshManager> MeshManager {nullptr};
    Ptr<TextureManager> TextureManager {nullptr};
    Ptr<MaterialManager> MaterialManager {nullptr};
    Ptr<LightManager> LightManager {nullptr};
  };
}