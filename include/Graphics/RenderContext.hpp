#pragma once

#include "Base/Pointers.hpp"
#include "Core/WindowManager.hpp"

namespace Krys::Gfx
{
  class MeshManager;
  class TextureManager;
  class MaterialManager;
  class GraphicsContext;
  class LightManager;
  class SceneGraphManager;
  class RenderTargetManager;

  struct RenderContext final
  {
    RenderContext(Ptr<GraphicsContext> graphicsContext, Ptr<MeshManager> meshManager,
                  Ptr<TextureManager> textureManager, Ptr<MaterialManager> materialManager,
                  Ptr<LightManager> lightManager, Ptr<SceneGraphManager> sceneGraphManager,
                  Ptr<RenderTargetManager> renderTargetManager, Ptr<WindowManager> windowManager) noexcept
        : GraphicsContext {graphicsContext}, MeshManager {meshManager}, TextureManager {textureManager},
          MaterialManager {materialManager}, LightManager {lightManager},
          SceneGraphManager {sceneGraphManager}, RenderTargetManager {renderTargetManager}, WindowManager {windowManager}
    {
    }

    Ptr<GraphicsContext> GraphicsContext {nullptr};
    Ptr<MeshManager> MeshManager {nullptr};
    Ptr<TextureManager> TextureManager {nullptr};
    Ptr<MaterialManager> MaterialManager {nullptr};
    Ptr<LightManager> LightManager {nullptr};
    Ptr<SceneGraphManager> SceneGraphManager {nullptr};
    Ptr<RenderTargetManager> RenderTargetManager {nullptr};
    Ptr<WindowManager> WindowManager {nullptr};
  };
}