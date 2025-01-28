#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"

namespace Krys::Gfx
{
  class Material;

  class MaterialManager
  {
  public:
    virtual ~MaterialManager() noexcept = default;

    NO_DISCARD virtual MaterialHandle CreateMaterial(ProgramHandle program) noexcept = 0;

    NO_DISCARD virtual Material &GetMaterial(MaterialHandle handle) noexcept = 0;

    NO_DISCARD virtual const Material &GetMaterial(MaterialHandle handle) const noexcept = 0;

    NO_DISCARD virtual bool DestroyMaterial(MaterialHandle handle) noexcept = 0;

  protected:
    MaterialManager() noexcept = default;

    NO_DISCARD virtual Unique<Material> CreateMaterialImpl(MaterialHandle handle,
                                                           ProgramHandle program) noexcept = 0;

  protected:
    HandleManager<MaterialHandle> _materialHandles {};
    Map<MaterialHandle, Unique<Material>> _materials;
  };
}