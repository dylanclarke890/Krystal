#include "Graphics/Lights/LightManager.hpp"

namespace Krys::Gfx
{
  bool LightManager::DestroyLight(LightHandle handle) noexcept
  {
    auto it = _lights.find(handle);
    if (it == _lights.end())
      return false;

    _lights.erase(it);
    _lightHandles.Recycle(handle);
    return true;
  }
}