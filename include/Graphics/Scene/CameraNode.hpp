#pragma once

#include "Graphics/Cameras/Camera.hpp"
#include "Graphics/Scene/TransformNode.hpp"

namespace Krys::Gfx
{
  class CameraNode : public TransformNode
  {
  public:
    CameraNode(Camera &camera, const Transform &transform = {}) noexcept
        : TransformNode(transform), _camera(camera)
    {
    }

    Camera &GetCamera() const noexcept
    {
      return _camera;
    }

    void SetCamera(Camera &camera) noexcept
    {
      _camera = camera;
    }

  protected:
    Camera &_camera;
  };
}