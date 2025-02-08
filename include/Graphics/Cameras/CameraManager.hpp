#pragma once

#include "Base/Attributes.hpp"
#include "Graphics/Cameras/Camera.hpp"

namespace Krys::Gfx
{
  class CameraManager
  {
    public:
      ~CameraManager() noexcept = default;

      void SetActiveCamera(Camera* camera) noexcept;
      NO_DISCARD Camera* GetActiveCamera() const noexcept;
      
    private:
      Camera* _activeCamera;
  };
}