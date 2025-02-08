#include "Graphics/Cameras/CameraManager.hpp"

namespace Krys::Gfx
{
  void CameraManager::SetActiveCamera(Camera* camera) noexcept
  {
    _activeCamera = camera;
  }

  Camera* CameraManager::GetActiveCamera() const noexcept
  {
    return _activeCamera;
  }
}