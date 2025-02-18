#pragma once

#include "Graphics/RenderPass.hpp"

namespace Krys::Gfx
{
  class RenderPipeline
  {
  public:
    ~RenderPipeline() = default;

    void AddPass(const RenderPass& pass) noexcept
    {
      _passes.push_back(pass);
    }

    NO_DISCARD const List<RenderPass>& GetPasses() const noexcept
    {
      return _passes;
    }

  protected:
    List<RenderPass> _passes;
  };
}