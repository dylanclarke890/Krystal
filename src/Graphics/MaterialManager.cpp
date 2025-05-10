#include "Graphics/MaterialManager.hpp"
#include "Graphics/BufferWriter.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Materials/Material.hpp"
#include "Graphics/TextureManager.hpp"

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