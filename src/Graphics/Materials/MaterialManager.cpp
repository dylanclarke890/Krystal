#include "Graphics/Materials/MaterialManager.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/Colours.hpp"
#include "Graphics/Materials/Material.hpp"

namespace Krys::Gfx
{
  MaterialManager::MaterialManager(Ptr<TextureManager> textureManager, Ptr<GraphicsContext> ctx) noexcept
      : _textureManager(textureManager), _ctx(ctx)
  {
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

  MaterialHandleMap<Unique<Material>> &MaterialManager::GetMaterials() noexcept
  {
    return _materials;
  }
}