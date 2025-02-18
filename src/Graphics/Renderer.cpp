#include "Graphics/Renderer.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Materials/MaterialManager.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/Scene/SceneGraph.hpp"
#include "Graphics/Textures/TextureManager.hpp"
#include "Graphics/Transform.hpp"

namespace Krys::Gfx
{
  Renderer::Renderer(const RenderContext &ctx) noexcept : _ctx(ctx)
  {
  }

  void Renderer::BeforeRender() noexcept
  {
  }

  void Renderer::AfterRender() noexcept
  {
  }

  void Renderer::OnRenderPipelineChange() noexcept
  {
  }

  void Renderer::SetRenderPipeline(RenderPipeline pipeline) noexcept
  {
    _pipeline = pipeline;
    OnRenderPipelineChange();
  }

  void Renderer::BeforeRenderPass(const RenderPass &) noexcept
  {
  }

  void Renderer::AfterRenderPass(const RenderPass &) noexcept
  {
  }
}