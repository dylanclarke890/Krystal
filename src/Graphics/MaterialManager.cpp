#include "Graphics/MaterialManager.hpp"
#include "Graphics/Materials/Material.hpp"

namespace Krys::Gfx
{
  Material *MaterialManager::GetMaterial(MaterialHandle handle) noexcept
  {
    if (auto it = _materials.find(handle); it != _materials.end())
      return it->second.get();
    return nullptr;
  }

  bool MaterialManager::DestroyMaterial(MaterialHandle handle) noexcept
  {
    if (auto it = _materials.find(handle); it != _materials.end())
    {
      _materials.erase(it);
      _materialHandles.Recycle(handle);
      return true;
    }

    return false;
  }
}