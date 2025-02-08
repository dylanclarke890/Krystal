#include "Graphics/Renderer.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/MaterialManager.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/Scene/SceneGraph.hpp"
#include "Graphics/TextureManager.hpp"
#include "Graphics/Transform.hpp"

namespace Krys::Gfx
{
  Renderer::Renderer(RenderContext ctx) noexcept : _ctx(ctx)
  {
  }

  void Renderer::BeforeRender() noexcept
  {
  }

  void Renderer::Render(SceneGraph *scene, Camera &camera) noexcept
  {
    BeforeRender();
    auto *root = scene->GetRoot();
    Render(root, {}, camera);
  }
}