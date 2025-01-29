#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/Material.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"

namespace Krys::Gfx
{
  class MaterialManager
  {
  public:
    virtual ~MaterialManager() noexcept = default;

    /// @brief Creates a material.
    /// @tparam Args The types of the arguments to pass to the material's constructor.
    /// @param program The program to use with the material.
    /// @param args The arguments to pass to the material's constructor.
    /// @return The handle of the created material.
    template <typename... Args>
    NO_DISCARD MaterialHandle CreatePhongMaterial(ProgramHandle program, Args... args) noexcept
    {
      auto handle = _materialHandles.Next();
      _materials[handle] = CreateUnique<PhongMaterial>(handle, program, std::forward<Args>(args)...);
      return handle;
    }

    /// @brief Gets a material by its handle.
    /// @param handle The handle of the material.
    /// @return A pointer to the material if it was found, nullptr otherwise.
    NO_DISCARD Material *GetMaterial(MaterialHandle handle) noexcept;

    /// @brief Destroys a material.
    /// @param handle The handle of the material.
    /// @return True if the material was found, false otherwise.
    NO_DISCARD bool DestroyMaterial(MaterialHandle handle) noexcept;

  protected:
    MaterialManager() noexcept = default;

  protected:
    MaterialHandleMap<Unique<Material>> _materials;
    MaterialHandleManager _materialHandles {};
  };
}