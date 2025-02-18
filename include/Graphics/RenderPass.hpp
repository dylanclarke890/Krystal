#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/RenderTargetAttachment.hpp"

namespace Krys::Gfx
{
  class RenderPass
  {
  public:
    RenderPass(RenderPassHandle handle, const string &name) noexcept : _handle(handle), _name(name)
    {
    }

    NO_DISCARD const string &GetName() const noexcept
    {
      return _name;
    }

    NO_DISCARD RenderPassHandle GetHandle() const noexcept
    {
      return _handle;
    }

    NO_DISCARD const List<RenderTargetAttachment> &GetColorAttachments() const noexcept
    {
      return _colorAttachments;
    }

    NO_DISCARD const RenderTargetAttachment &GetDepthAttachment() const noexcept
    {
      return _depthAttachment;
    }

    NO_DISCARD const RenderTargetAttachment &GetStencilAttachment() const noexcept
    {
      return _stencilAttachment;
    }

    NO_DISCARD SceneGraphHandle GetSceneGraph() const noexcept
    {
      return _sceneGraph;
    }

    void SetSceneGraph(SceneGraphHandle sceneGraph) noexcept
    {
      _sceneGraph = sceneGraph;
    }

    void AddColorAttachment(const RenderTargetAttachment &attachment) noexcept
    {
      _colorAttachments.push_back(attachment);
    }

    void SetDepthAttachment(const RenderTargetAttachment &attachment) noexcept
    {
      _depthAttachment = attachment;
    }

    void SetStencilAttachment(const RenderTargetAttachment &attachment) noexcept
    {
      _stencilAttachment = attachment;
    }

  private:
    RenderPassHandle _handle;
    string _name;
    List<RenderTargetAttachment> _colorAttachments;
    RenderTargetAttachment _depthAttachment;
    RenderTargetAttachment _stencilAttachment;

    SceneGraphHandle _sceneGraph;
  };
}