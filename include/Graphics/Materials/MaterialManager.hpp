#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Types.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Colours.hpp"
#include "Graphics/GraphicsContext.hpp"
#include "Graphics/Handles.hpp"
#include "Graphics/Materials/Material.hpp"
#include "Graphics/Materials/PhongMaterial.hpp"
#include "Graphics/TextureManager.hpp"
#include "IO/IO.hpp"

namespace Krys::Gfx
{
  class MaterialManager
  {
  public:
    MaterialManager(Ptr<TextureManager> textureManager, Ptr<GraphicsContext> ctx) noexcept;

    // TODO: free buffers on destruction/shutdown
    virtual ~MaterialManager() noexcept = default;

    /// @brief Creates a phong material.
    /// @tparam Args The types of the arguments to pass to the material's constructor.
    /// @param args The arguments to pass to the material's constructor.
    /// @return The handle of the created material.
    template <typename... Args>
    NO_DISCARD MaterialHandle CreatePhongMaterial(Args &&...args) noexcept
    {
      auto handle = _materialHandles.Next();
      auto program = GetDefaultPhongProgram();

      _materials[handle] = CreateUnique<PhongMaterial>(handle, program, std::forward<Args>(args)...);
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

    NO_DISCARD MaterialHandle GetDefaultPhongMaterial() noexcept
    {
      static MaterialHandle handle {};

      if (!handle.IsValid())
      {
        auto pinkTexture = _textureManager->CreateFlatColourTexture(Colours::Lime);
        handle = CreatePhongMaterial(pinkTexture);
      }

      return handle;
    }

    NO_DISCARD ProgramHandle GetDefaultPhongProgram() noexcept
    {
      static ProgramHandle handle {};

      if (!handle.IsValid())
      {
        auto vertexShader =
          _ctx->CreateShader(ShaderStage::Vertex, IO::ReadFileText("shaders/phong.vert"));
        auto fragmentShader =
          _ctx->CreateShader(ShaderStage::Fragment, IO::ReadFileText("shaders/phong.frag"));

        handle = _ctx->CreateProgram(vertexShader, fragmentShader);
      }

      return handle;
    }

  protected:
    MaterialHandleMap<Unique<Material>> _materials;
    MaterialHandleManager _materialHandles {};
    Ptr<TextureManager> _textureManager {nullptr};
    Ptr<GraphicsContext> _ctx {nullptr};
  };
}