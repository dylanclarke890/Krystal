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

    /// @brief Creates a material.
    /// @param program The program to use with the material.
    /// @return The handle of the created material.
    NO_DISCARD MaterialHandle CreateMaterial(ProgramHandle program) noexcept;

    /// @brief Gets a material by its handle.
    /// @param handle The handle of the material.
    /// @return A pointer to the material if it was found, nullptr otherwise.
    NO_DISCARD Material *GetMaterial(MaterialHandle handle) noexcept;

    /// @brief Destroys a material.
    /// @param handle The handle of the material.
    /// @return True if the material was found, false otherwise.
    NO_DISCARD  bool DestroyMaterial(MaterialHandle handle) noexcept;

  protected:
    MaterialManager() noexcept = default;

    /// @brief Implementation-specific material creation.
    /// @param handle The handle of the material.
    /// @param program The program to use with the material.
    /// @return The created material.
    NO_DISCARD virtual Unique<Material> CreateMaterialImpl(MaterialHandle handle,
                                                           ProgramHandle program) noexcept = 0;

  protected:
    MaterialHandleMap<Unique<Material>> _materials;
    MaterialHandleManager _materialHandles {};
  };
}