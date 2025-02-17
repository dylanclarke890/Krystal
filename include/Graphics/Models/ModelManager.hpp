#pragma once

#include "Base/Attributes.hpp"
#include "Base/Pointers.hpp"
#include "Base/Macros.hpp"
#include "Base/Types.hpp"
#include "Graphics/Materials/MaterialManager.hpp"
#include "Graphics/MeshManager.hpp"
#include "Graphics/Models/ModelLoaderFlags.hpp"
#include "Graphics/Models/Model.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Gfx {
  class ModelManager {
  public:
    NO_COPY_MOVE(ModelManager)

    ModelManager(Ptr<MaterialManager> materialManager, Ptr<MeshManager> meshManager,
                 Ptr<TextureManager> textureManager) noexcept;
    ~ModelManager() noexcept = default;


    /// @brief Load a model from a file.
    /// @param path The path to the model file.
    NO_DISCARD Expected<Model> LoadModel(const stringview &path,
                                         ModelLoaderFlags flags = ModelLoaderFlags::None) noexcept;

  protected:
      NO_DISCARD Vec3 GenerateNormal(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2) const noexcept;

    Ptr<MaterialManager> _materialManager;
    Ptr<MeshManager> _meshManager;
    Ptr<TextureManager> _textureManager;
  };
}