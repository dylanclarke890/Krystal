#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/RenderTargets/RenderTargetAttachment.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Gfx
{
  struct ClearValues
  {
    Vec4 Color = Vec4(0.f, 0.f, 0.f, 1.f);
    float Depth = 1.0f;                      
    uint32 Stencil = 0;                  
  };

  struct RenderPass
  {
    string Name;
    List<RenderTargetAttachment> ColourAttachments;
    RenderTargetAttachment DepthAttachment;
    RenderTargetAttachment StencilAttachment;
    SceneGraphHandle SceneGraph;
    Camera *Camera;
    ClearValues ClearValues;

    NO_DISCARD bool HasNoAttachments() const noexcept
    {
      return ColourAttachments.empty() && !DepthAttachment.Target.IsValid()
             && !StencilAttachment.Target.IsValid();
    }
  };
}