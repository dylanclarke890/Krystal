#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/Material.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"

namespace Krys::Gfx
{
  class GraphicsContext;
  class TextureManager;

  class MaterialManager
  {
  public:
    MaterialManager(Ptr<TextureManager> textureManager, Ptr<GraphicsContext> ctx) noexcept;

    // TODO: free buffers on destruction/shutdown
    virtual ~MaterialManager() noexcept = default;

    /// @brief Creates a material.
    /// @tparam Args The types of the arguments to pass to the material's constructor.
    /// @param program The program to use with the material.
    /// @param args The arguments to pass to the material's constructor.
    /// @return The handle of the created material.
    template <typename T, typename... Args>
    requires std::derived_from<T, Material>
    NO_DISCARD MaterialHandle CreateMaterial(ProgramHandle program, Args... args) noexcept
    {
      auto handle = _materialHandles.Next();
      _materials[handle] = CreateUnique<T>(handle, program, std::forward<Args>(args)...);
      return handle;
    }

    /// @brief Gets a material by its handle.
    /// @tparam T The type of the material to get. Can be omitted to get the base class, useful if the type is
    /// unknown.
    /// @param handle The handle of the material.
    /// @return A pointer to the material if it was found, nullptr otherwise.
    /// @note The type is static_cast to T, so it must be a valid cast. Use the default type if unsure then
    /// get the derived type via `material.GetType()` and cast it that way.
    template <typename T = Material>
    requires std::is_same_v<T, Material> || std::derived_from<T, Material>
    NO_DISCARD T *GetMaterial(MaterialHandle handle) noexcept
    {
      if (const auto it = _materials.find(handle); it != _materials.end())
        return static_cast<T *>(it->second.get());
      return nullptr;
    }

    /// @brief Destroys a material.
    /// @param handle The handle of the material.
    /// @return True if the material was found, false otherwise.
    NO_DISCARD bool DestroyMaterial(MaterialHandle handle) noexcept;

    /// @brief Gets the materials.
    NO_DISCARD MaterialHandleMap<Unique<Material>> &GetMaterials() noexcept;

  protected:
    MaterialHandleMap<Unique<Material>> _materials;
    MaterialHandleManager _materialHandles {};
    Ptr<TextureManager> _textureManager {nullptr};
    Ptr<GraphicsContext> _ctx {nullptr};
  };
}